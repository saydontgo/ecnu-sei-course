/* Matrix multiplication: C = A * B.
 * Host code.
 *
 * This sample implements matrix multiplication and is exactly the same as
 * Chapter 7 of the programming guide.
 * It has been written for clarity of exposition to illustrate various CUDA
 * programming principles, not with the goal of providing the most
 * performant generic kernel for matrix multiplication.
 *
 * CUBLAS provides high-performance matrix multiplication.
 */

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "matrixMul.h"
// includes, project
// #include <cutil_inline.h>
#include "matrixMul_gold.cpp"
// includes, kernels
#include "legacy_cutil.h"
#include "matrixMul_kernel.cu"
////////////////////////////////////////////////////////////////////////////////
// declaration, forward
void runTest(int argc, char** argv);
void randomInit(float*, int);
void printDiff(float*, float*, int, int);

extern "C"
void computeGold(float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int
main(int argc, char** argv)
{
    runTest(argc, argv);

    cutilExit(argc, argv);
}


////////////////////////////////////////////////////////////////////////////////
//! Run three simple tests for CUDA seperately
////////////////////////////////////////////////////////////////////////////////

// 16 * 16  matrix multiplication


void
test1( )
{

 // allocate host memory for matrices A and B
    unsigned int size_A = SZ1 * SZ1;
    unsigned int mem_size_A = sizeof(float) * size_A;
    float* h_A = (float*) malloc(mem_size_A);
    unsigned int size_B = SZ1 * SZ1;
    unsigned int mem_size_B = sizeof(float) * size_B;
    float* h_B = (float*) malloc(mem_size_B);

    // initialize host memory
    randomInit(h_A, size_A);
    randomInit(h_B, size_B);

    // allocate device memory
    float* d_A;
    cutilSafeCall(cudaMalloc((void**) &d_A, mem_size_A));
    float* d_B;
    cutilSafeCall(cudaMalloc((void**) &d_B, mem_size_B));

    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );

    // allocate device memory for result
    unsigned int size_C = SZ1 * SZ1;
    unsigned int mem_size_C = sizeof(float) * size_C;
    float* d_C;
    cutilSafeCall(cudaMalloc((void**) &d_C, mem_size_C));

    // allocate host memory for the result
    float* h_C = (float*) malloc(mem_size_C);
    
    // create and start timer
    unsigned int timer = 0;
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));

    // setup execution parameters
    dim3 threads(BLOCK_SIZE, BLOCK_SIZE);

    // execute the kernel
    matrixMul1<<< 1, threads >>>(d_C, d_A, d_B, SZ1, SZ1);

    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");


    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );

 

   // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("Processing time: %f (ms) \n", cutGetTimerValue(timer));
    cutilCheckError(cutDeleteTimer(timer));



    // compute reference solution
    float* reference = (float*) malloc(mem_size_C);
    computeGold(reference, h_A, h_B, SZ1, SZ1, SZ1);

    // check result
    CUTBoolean res = cutCompareL2fe(reference, h_C, size_C, 0.01);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, SZ1, SZ1);

    // clean up memory
    free(h_A);
    free(h_B);
    free(h_C);
    free(reference);
    cutilSafeCall(cudaFree(d_A));
    cutilSafeCall(cudaFree(d_B));
    cutilSafeCall(cudaFree(d_C));

    cudaThreadExit();

}








void 
test2(float * h_C, float * d_C, float * d_A, float * d_B)
{
   // create and start timer
    unsigned int timer1 = 0;
    cutilCheckError(cutCreateTimer(&timer1));
    cutilCheckError(cutStartTimer(timer1));

    dim3 threads(BLOCK_SIZE*2, BLOCK_SIZE);
    
    for(int i=0; i< WA /(BLOCK_SIZE *2) ; i++)
	for(int j=0; j<  WB / BLOCK_SIZE ; j++)
	{
	        // execute the kernel
    		matrixMul2<<< 1, threads >>>(d_C, d_A, d_B, WA, WB, i, j);	
	}

    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");

    unsigned int size_C = WC * HC;
    unsigned int mem_size_C = sizeof(float) * size_C;

    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );


    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer1));
    printf("Processing time: %f (ms) \n", cutGetTimerValue(timer1));
    cutilCheckError(cutDeleteTimer(timer1));


   // free(reference);
    cutilSafeCall(cudaFree(d_A));
    cutilSafeCall(cudaFree(d_B));
    cutilSafeCall(cudaFree(d_C));

    cudaThreadExit();

}



void 
test3( float * h_C, float * d_C, float * d_A, float * d_B)
{

    // create and start timer
    unsigned int timer2 = 0;
    cutilCheckError(cutCreateTimer(&timer2));
    cutilCheckError(cutStartTimer(timer2));


    dim3 threads(BLOCK_SIZE*2, BLOCK_SIZE);
    dim3 grid(WA / threads.x,  WB/ threads.y);


    // execute the kernel
    matrixMul3<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);

    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");

    // copy result from device to host
    unsigned int size_C = WC * HC;
    unsigned int mem_size_C = sizeof(float) * size_C;


   cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );

 // stop and destroy timer
    cutilCheckError(cutStopTimer(timer2));
    printf("Processing time: %f (ms) \n", cutGetTimerValue(timer2));
    cutilCheckError(cutDeleteTimer(timer2));



    cutilSafeCall(cudaFree(d_A));
    cutilSafeCall(cudaFree(d_B));
    cutilSafeCall(cudaFree(d_C));

    cudaThreadExit();

}



void
test23()
{

 // allocate host memory for matrices A and B
    unsigned int size_A = WA * HA;
    unsigned int mem_size_A = sizeof(float) * size_A;
    float* h_A = (float*) malloc(mem_size_A);
    unsigned int size_B = WB * HB;
    unsigned int mem_size_B = sizeof(float) * size_B;
    float* h_B = (float*) malloc(mem_size_B);

    // initialize host memory
    randomInit(h_A, size_A);
    randomInit(h_B, size_B);

    // allocate device memory
    float* d_A;
    float* d_B;
    cutilSafeCall(cudaMalloc((void**) &d_A, mem_size_A));
    cutilSafeCall(cudaMalloc((void**) &d_B, mem_size_B));

    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );

    // allocate device memory for result
    unsigned int size_C = WC * HC;
    unsigned int mem_size_C = sizeof(float) * size_C;
    float* d_C;
    cutilSafeCall(cudaMalloc((void**) &d_C, mem_size_C));

    // allocate host memory for the result
    float* h_C1 = (float*) malloc(mem_size_C);
    
    //process the second question
    test2(h_C1, d_C, d_A, d_B);

 // compute reference solution
    float* reference = (float*) malloc(mem_size_C);
    computeGold(reference, h_A, h_B, HA, WA, WB);

    // check result 2
    CUTBoolean res = cutCompareL2fe(reference, h_C1, size_C, 0.01);
    printf("Test 2 %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C1, WC, HC);

    free(h_C1);

//
// Process the third question.
//
    // allocate device memory
    cutilSafeCall(cudaMalloc((void**) &d_A, mem_size_A));
    cutilSafeCall(cudaMalloc((void**) &d_B, mem_size_B));

    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );

    // allocate device memory for result
    cutilSafeCall(cudaMalloc((void**) &d_C, mem_size_C));

    // allocate host memory for the result
    float* h_C2 = (float*) malloc(mem_size_C);
    
    //process the trhird question
    test3(h_C2, d_C, d_A, d_B);

    // check result 3
    res = cutCompareL2fe(reference, h_C2, size_C, 0.01);
    printf("Test 3 %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C2, WC, HC);

    // clean up memory
    free(h_A);
    free(h_B);
    free(h_C2);
    free(reference);

}





////////////////////////////////////////////////////////////////////////////////
//! Run three simple tests for CUDA
////////////////////////////////////////////////////////////////////////////////
void
runTest(int argc, char** argv)
{
    if( cutCheckCmdLineFlag(argc, (const char**)argv, "device") )
        cutilDeviceInit(argc, argv);
    else
        cudaSetDevice( cutGetMaxGflopsDeviceId() );

    // set seed for rand()
    srand(2006);

    printf("start to process a 16*16 matrix using 1 block \n");
    test1();
	
    printf("\n\nstart to process a 256*256 matrix using 1 block vs multi blocks\n");
    test23();
  
}

// Allocates a matrix with random float entries.
void randomInit(float* data, int size)
{
    for (int i = 0; i < size; ++i)
        data[i] = rand() / (float)RAND_MAX;
}



void printDiff(float *data1, float *data2, int width, int height)
{
  int i,j,k;
  int error_count=0;
  for (j=0; j<height; j++) {
    for (i=0; i<width; i++) {
      k = j*width+i;
      if (data1[k] != data2[k]) {
         printf("diff(%d,%d) CPU=%4.4f, GPU=%4.4f n", i,j, data1[k], data2[k]);
         error_count++;
      }
    }
  }
  printf(" nTotal Errors = %d n", error_count);
}

