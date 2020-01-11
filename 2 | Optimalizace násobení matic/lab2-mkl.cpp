/**
 * @file  lab2 (2018)
 * @author  Gabriel Bordovsky
 * @brief - lab2 demo for reference of matrix multiplication
 *          Architecture processors
 */
#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"

#ifdef PAPI
#include "PapiCounter.h"
#endif

int main(int argc, char* argv[])
{
    FILE *fp_a, *fp_b, *fp_c;
    double *A, *B, *C;
    int m, n, k, i, nsize;
    double alpha, beta;

    if (argc != 5) {
      printf(" Got %d arguments. Expected: \n", argc-1);
      printf(" %s Size Matrix-File-1 Matrix-File-2 Matrix-out-file\n",argv[0]);
      return -1;
    } else {
      nsize = atoi(argv[1]);
    }


    printf ("\n This is modified example that computes real matrix C=alpha*A*B+beta*C using \n"
            " Intel(R) MKL function dgemm, where A, B, and  C are matrices and \n"
            " alpha and beta are double precision scalars\n\n");

    m = nsize, k = nsize, n = nsize;
    printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
            " A(%ix%i) and matrix B(%ix%i)\n\n", m, k, k, n);
    alpha = 1.0; beta = 0.0;

    printf (" Allocating memory for matrices aligned on 64-byte boundary for better \n"
            " performance \n\n");
    A = (double *)mkl_malloc( m*k*sizeof( double ), 64 );
    B = (double *)mkl_malloc( k*n*sizeof( double ), 64 );
    C = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
    if (A == NULL || B == NULL || C == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
      mkl_free(A);
      mkl_free(B);
      mkl_free(C);
      return 1;
    }
    printf( "Load input file 1 ...\n");

    fp_a = fopen(argv[2], "r");
    if (fp_a == nullptr)
    {
        printf("Can't open file %s!\n", argv[2]);
        exit(1);
    }

    for (size_t i = 0; i < nsize*nsize; i++) {
        fscanf(fp_a, "%lf", &A[i]);
    }

    printf( "Load input file 2 ...\n");

    fp_b = fopen(argv[3], "r");
    if (fp_b == nullptr)
    {
        printf("Can't open file %s!\n", argv[3]);
        exit(1);
    }

    for (size_t i = 0; i < nsize*nsize; i++) {
        fscanf(fp_b, "%lf", &B[i]);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }

    fclose(fp_a);
    fclose(fp_b);
    printf (" Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n\n");

    #ifdef PAPI
       PapiCounterList papi_exampined_routines;
       papi_exampined_routines.AddRoutine("matrix times matrix");
       papi_exampined_routines["matrix times matrix"].Start();
    #endif


    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, A, k, B, n, beta, C, n);

    #ifdef PAPI
       papi_exampined_routines["matrix times matrix"].Stop();
    #endif

    printf ("\n Computations completed.\n\n");

    printf( "Writing result ...\n");
    fp_c = fopen(argv[4], "w");
    if (fp_c == nullptr)
    {
        printf("Can't open file %s!\n", argv[4]);
        exit(1);
    }

    for (size_t i = 0; i < nsize*nsize; i++){
          fprintf(fp_c, "%10.10f ", C[i]);
    }
    fclose(fp_c);

    #ifdef PAPI
        papi_exampined_routines.PrintScreen();
    #endif

    printf ("\n Deallocating memory \n\n");
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);

    printf (" Example completed. \n\n");
    return 0;
}
