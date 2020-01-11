/**
 * @file  lab2 (2018)
 * @author  Gabriel Bordovsky
 * @brief - lab2 for optimisation of Matrix times Matrix problem
 *          Architecture processors
 */

#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <malloc.h>
#include <stdio.h>

#ifdef PAPI
#include "PapiCounter.h"
#endif


/**
 *  main funciton
 */
int main(int argc, char** argv) {

  FILE      *fp_a, *fp_b, *fp_c;
  size_t    nsize;
  float     **c, **b, **a, *d1, *d2, *d3;
  char      name[30];

  if (argc != 5) {
    printf(" Got %d arguments. Expected: \n", argc-1);
    printf(" %s Size Matrix-File-1 Matrix-File-2 Matrix-out-file\n",argv[0]);
    return -1;
   } else {
      nsize = atoi(argv[1]);
   }
   time_t t;

     /* Intializes random number generator */
   srand((unsigned) time(&t));

  //.......................//

   a=(float**)malloc(nsize*sizeof(float*));
   b=(float**)malloc(nsize*sizeof(float*));
   c=(float**)malloc(nsize*sizeof(float*));

   d1 = (float*)malloc(nsize*nsize*sizeof(float));
   d2 = (float*)malloc(nsize*nsize*sizeof(float));
   d3 = (float*)malloc(nsize*nsize*sizeof(float));


   for (size_t i = 0; i < nsize; i++) {
     a[i] = &d1[nsize*i];
     b[i] = &d2[nsize*i];
     c[i] = &d3[nsize*i];
   }

   if (!(a && b && c)){
      printf(" Allocation failure reduce n %lu \n",nsize);
      exit(-1);
   }

   gethostname(name, 30);
   printf("--------------------------------------------\n");
   printf("Program for matrix times matrix\n");
   printf("Running on:  %30s\n",name);
  //  printf("Number of Repeats:     %10ld\n",nrpt);
   printf("Total Bytes for matrices %10lu x3\n\n",nsize*nsize*sizeof(float));

   printf("--------------------------------------------\n");


    //-------------------------------------------------------------------//
    //------------ Definitions of routines measure by PAPI --------------//
    //-------------------------------------------------------------------//
#ifdef PAPI
   PapiCounterList papi_exampined_routines;
   papi_exampined_routines.AddRoutine("matrix times matrix");
#endif

    //null c
   for (size_t i = 0; i < nsize; i++){
      for (size_t j = 0; j < nsize; j++) {
         c[i][j] = 0.0f;
      }
   }

    printf( "Load input file 1 ...\n");

    fp_a = fopen(argv[2], "r");
    if (fp_a == nullptr)
    {
        printf("Can't open file %s!\n", argv[2]);
        exit(1);
    }

    for (size_t i = 0; i < nsize*nsize; i++) {
        fscanf(fp_a, "%f", &d1[i]);
    }

    fclose(fp_a);
    fp_b = fopen(argv[3], "r");
    if (fp_b == nullptr)
    {
        printf("Can't open file %s!\n", argv[3]);
        exit(1);
    }

    for (size_t i = 0; i < nsize*nsize; i++) {
        fscanf(fp_b, "%f", &d2[i]);
    }
    fclose(fp_b);


    //-------------------------------------------------------------------//
    //------------------- Measured loops ---------------------------------//
    //-------------------------------------------------------------------//


    printf( "Begin computation...\n");
#ifdef PAPI
    papi_exampined_routines["matrix times matrix"].Start();
#endif
    //store result by columns ()
    for (size_t i = 0; i < nsize; i++){
      for (size_t j = 0; j < nsize; j++){
        for (size_t k = 0; k < nsize; k++)
        {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }
#ifdef PAPI
    papi_exampined_routines["matrix times matrix"].Stop();
#endif

    printf( "Stop computation...\n");

#ifdef PAPI
    papi_exampined_routines.PrintScreen();

#endif

    printf( "Writing result ...\n");
    fp_c = fopen(argv[4], "w");
    if (fp_c == nullptr)
    {
        printf("Can't open file %s!\n", argv[4]);
        exit(1);
    }

    for (size_t i = 0; i < nsize; i++){
       for (size_t j = 0; j < nsize; j++) {
          fprintf(fp_c, "%10.10f ", c[i][j]);
       }
       fprintf(fp_c,"\n");
    }
    printf( "Done...\n");

    free(a);
    free(b);
    free(c);

    free(d1);
    free(d2);
    free(d3);

    fclose(fp_c);

    return 0;
}
