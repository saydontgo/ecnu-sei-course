
/* Matrix multiplication: C = A * B.
 * Device code.
 */

#ifndef _MATRIXMUL_KERNEL_H_
#define _MATRIXMUL_KERNEL_H_

#include <stdio.h>
#include "matrixMul.h"

#define CHECK_BANK_CONFLICTS 0
#if CHECK_BANK_CONFLICTS
#define AS(i, j) cutilBankChecker(((float*)&As[0][0]), (BLOCK_SIZE * i + j))
#define BS(i, j) cutilBankChecker(((float*)&Bs[0][0]), (BLOCK_SIZE * i + j))
#else
#define AS(i, j) As[i][j]
#define BS(i, j) Bs[i][j]
#endif

////////////////////////////////////////////////////////////////////////////////
//! Matrix multiplication on the device: C = A * B
//! wA is A's width and wB is B's width
////////////////////////////////////////////////////////////////////////////////



__global__ void
matrixMul1( float* C, float* A, float* B, int wA, int wB)
{
    int tx = threadIdx.x;
    int ty = threadIdx.y;

   //请结合ppt在此补充相关的代码
}








__global__ void
matrixMul2( float* C, float* A, float* B, int wA, int wB, int bx, int by)
{
    int realX = bx * blockDim.x + threadIdx.x;
    int realY = by * blockDim.y + threadIdx.y; 

    float Csub = 0;
    
    int aBegin = realY * wA;
    int bBegin = realX;
  
    for (int k = 0; k < wA; ++k)
       Csub += A[aBegin + k] * B[bBegin + k*wB];

    C[realX + realY* wB ] = Csub;
}



__global__ void
matrixMul3( float* C, float* A, float* B, int wA, int wB)
{
    // Block index
    int bx = blockIdx.x;
    int by = blockIdx.y;

    // Thread index
    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int realX = bx * blockDim.x + tx;
    int realY = by * blockDim.y + ty; 

    float Csub = 0;
    
    int aBegin = realY * wA;
    int bBegin = realX;
  
    for (int k = 0; k < wA; ++k)
       Csub += A[aBegin + k] * B[bBegin + k*wB];

    C[realX + realY* wB ] = Csub;
}

#endif // #ifndef _MATRIXMUL_KERNEL_H_
