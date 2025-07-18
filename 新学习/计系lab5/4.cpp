#include <iostream>
#include <chrono>

const int NUM_ITERATIONS = 100000000; // 1亿次访问
const int BUFFER_SIZE = 4096;         // 缓冲区大小，可以根据需要调整

void measureTLBSize(int blockSize)
{
    char *buffer = new char[BUFFER_SIZE];
    auto start = std::chrono::high_resolution_clock::now();

    // 访问缓冲区中的数据，模拟对TLB的频繁访问
    volatile char dummy; // 防止编译器优化
    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        int index = (i * blockSize) % BUFFER_SIZE;
        dummy = buffer[index]; // 访问缓冲区
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double totalTime = duration.count();

    std::cout << "Block size: " << blockSize << " bytes\n";
    std::cout << "Total time for " << NUM_ITERATIONS << " accesses: " << totalTime << " seconds\n";

    delete[] buffer;
}

int main()
{
    // 测试不同大小的数据块，以尝试测量TLB的大小
    measureTLBSize(1);    // 测试块大小为1字节
    measureTLBSize(4);    // 测试块大小为4字节
    measureTLBSize(16);   // 测试块大小为16字节
    measureTLBSize(64);   // 测试块大小为64字节
    measureTLBSize(256);  // 测试块大小为256字节
    measureTLBSize(1024); // 测试块大小为1024字节

    return 0;
}
