#ifndef LEGACY_CUTIL_H
#define LEGACY_CUTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <time.h>

// --- 错误处理宏 (Error Handling Macros) ---
// 这些宏期望函数返回 cudaError_t 类型
#define cutilSafeCall(err) __cudaSafeCall(err, __FILE__, __LINE__)
#define cutilCheckError(err) __cudaSafeCall(err, __FILE__, __LINE__)
#define cutilCheckMsg(msg) __cutilCheckMsg(msg, __FILE__, __LINE__)

inline void __cudaSafeCall(cudaError_t err, const char *file, const int line) {
    if (cudaSuccess != err) {
        fprintf(stderr, "CUDA Error in file <%s>, line %i : %s.\n",
                file, line, cudaGetErrorString(err));
        exit(-1);
    }
}

inline void __cutilCheckMsg(const char *errorMessage, const char *file, const int line) {
    cudaError_t err = cudaGetLastError();
    if (cudaSuccess != err) {
        fprintf(stderr, "CUDA Error in file <%s>, line %i : %s %s.\n",
                file, line, errorMessage, cudaGetErrorString(err));
        exit(-1);
    }
}

// --- 计时器实现 (Timer Implementation) ---
static clock_t _timers[10]; 

// 修改点：将返回类型从 int 改为 cudaError_t，并返回 cudaSuccess
// 这样 cutilCheckError 宏就不会报错了

inline cudaError_t cutCreateTimer(unsigned int* timer) { 
    static int timerCount = 0;
    *timer = timerCount++; 
    return cudaSuccess; 
}
inline cudaError_t cutStartTimer(unsigned int timer) { 
    if (timer < 10) _timers[timer] = clock(); 
    return cudaSuccess;
}
inline cudaError_t cutStopTimer(unsigned int timer) { 
    if (timer < 10) {
        clock_t end = clock(); 
        _timers[timer] = end - _timers[timer]; 
    }
    return cudaSuccess;
}
inline float cutGetTimerValue(unsigned int timer) { 
    if (timer < 10) return (float)_timers[timer] / CLOCKS_PER_SEC * 1000.0f; 
    return 0.0f;
}
inline cudaError_t cutDeleteTimer(unsigned int timer) { return cudaSuccess; }

// --- 其他工具函数 (Other Utilities) ---
typedef int CUTBoolean;
#define cutilExit(argc, argv) exit(0)

inline int cutCompareL2fe(float* reference, float* data, unsigned int len, float epsilon) {
    for(unsigned int i = 0; i < len; ++i) {
        float diff = reference[i] - data[i];
        if (diff < 0) diff = -diff;
        if (diff > epsilon) return 0; // 测试失败
    }
    return 1; // 测试通过
}

inline int cutCheckCmdLineFlag(int argc, const char** argv, const char* flag) { return 0; }
inline void cutilDeviceInit(int argc, char** argv) { cudaSetDevice(0); }
inline int cutGetMaxGflopsDeviceId() { return 0; }

#endif