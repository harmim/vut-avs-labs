/**
 * @file  lab2 (2018)
 * @author  Gabriel Bordovsky
 * @brief - lab2 for generation of datafiles
 *          Architecture processors
 */

#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#include <ctime>
#include <malloc.h>
#include <stdio.h>



/**
 *  main funciton
 */
int main(int argc, char** argv) {

  FILE      *fp;
  size_t    nsize;
  char      name[30];

  if (argc != 3) {
    printf(" Got %d arguments. Expected: \n", argc-1);
    printf(" %s Size Matrix-out-file\n",argv[0]);
    return -1;
   } else {
      nsize = atoi(argv[1]);
   }


  //.......................//


   gethostname(name, 30);
   printf("--------------------------------------------\n");
   printf("Program for matrix data generation\n");
   printf("Running on:  %30s\n",name);
  //  printf("Number of Repeats:     %10ld\n",nrpt);

   printf("--------------------------------------------\n");


    //-------------------------------------------------------------------//
    //------------------- Measured loops ---------------------------------//
    //-------------------------------------------------------------------//


    printf( "Generate data...\n");

    srand (time(NULL));

    fp = fopen(argv[2], "w");
    if (fp == nullptr)
    {
        printf("Can't open file %s!\n", argv[2]);
        exit(1);
    }

    for (size_t i = 0; i < nsize; i++){
       for (size_t j = 0; j < nsize; j++) {
          fprintf(fp, "%10.10f ", 100 * (float) rand()/ (float) RAND_MAX);
       }
       fprintf(fp,"\n");
    }
    printf( "Done...\n");

    fclose(fp);

    return 0;
}
