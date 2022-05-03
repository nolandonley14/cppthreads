#ifdef __cplusplus
extern "C" {
#endif
    void mmm_( int *threads, int *len,  double *a, double *b, double*c );
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>

using namespace std;
/* Function prototypes */

void mmm_thread_worker( int N, int rowStart, int rowStop, double *A, double *B, double *C);

void mmm_( int *threads, int *len, double *A, double *B, double *C ){

    // This function has to break up the data, spawn the processes, gather the results, and
    // clean up after itself.

    cout << "C++ Threads MMM" << endl;

    int numThreads = *threads;
    int matrixDimension = *len;
    int *numberOfRows;
    int startRow, stopRow;

    if ( matrixDimension < numThreads) {
      numThreads = 1;
      mmm_(&numThreads, len, A, B, C);
    } else {

        /*
         *  The parallel work begins.  The process is to first determine how to break
         *  up the matrix work equitably across the threads.  Once this is done the struct is filled with
         *  the information and a thread is started using the information.  Other than the size of the
         *  matrices and the rows to be processed, only the pointers to the memory locations of the matrices
         *  are passed.
         */

        // Create an array to keep up with thread id's for each thread
        std::thread threadList[numThreads];

        // Malloc an array to keep up with how many rows to work on in each thread
        numberOfRows = ( int * ) malloc( numThreads * sizeof(int) );

        // Here we detemine the number of rows over which each thread will work
        for (int i=0; i<numThreads; i++ ){
            *(numberOfRows+i) = matrixDimension / numThreads;
        }
        for (int i=0; i< matrixDimension % numThreads; i++ ){
            *(numberOfRows+i) = *(numberOfRows+i) + 1;
        }

        // Now that we know how many rows each thread will be responsible for computing,
        // malloc memory for the struct data, pack the struct with the thread-specific info
        // on where it is to start and stop processing, and create the thread using this data.
        stopRow=0;
        for(int i=0; i < numThreads ; i++) {
            {
                startRow=stopRow;
                stopRow=startRow+*(numberOfRows+i);
                threadList[i] = std::thread(mmm_thread_worker, matrixDimension, startRow, stopRow, A, B, C);
            }
        }
        for(int i=0; i < numThreads ; i++) {
          threadList[i].join();
        }
        free(numberOfRows);
      }
    // END OF MMM -- the memory pointed to by *C should now contain the product A.B
}


void mmm_thread_worker( int N, int rowStart, int rowStop, double *A, double *B, double *C) {

    // This is where the actual work of multiplying each matrix takes place --
    // with each mmm_thread_worker only responsible for a piece of the matrix A.

    // It is worth noting here that while the thread workers are reading simultaneously
    // from *A and *B, they never write to same memory locations in *C.

    int i, j, k;

    // Process the rows for which this thread is responsible
    for (i=rowStart;i<rowStop;i++) {
        for (j=0;j<N;j++) {
            *(C+(i*N+j))=0.0;
            for (k=0;k<N;k++) {
                *(C+(i*N+j)) += *(A+(i*N+k)) * *(B+(k*N+j));
            }
        }
    }
}
