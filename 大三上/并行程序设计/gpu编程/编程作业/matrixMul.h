#ifndef _MATRIXMUL_H_
#define _MATRIXMUL_H_

// Thread block size
#define BLOCK_SIZE 16

// Matrix dimensions
// (chosen as multiples of the thread block size for simplicity)
#define SZ1 BLOCK_SIZE

#define WA (16 * BLOCK_SIZE) // Matrix A width
#define HA (16 * BLOCK_SIZE) // Matrix A height
#define WB (16 * BLOCK_SIZE) // Matrix B width
#define HB WA  // Matrix B height
#define WC WB  // Matrix C width 
#define HC HA  // Matrix C height

#endif // _MATRIXMUL_H_

