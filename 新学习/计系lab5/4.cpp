#include <iostream>
#include <chrono>

const int NUM_ITERATIONS = 100000000; // 1�ڴη���
const int BUFFER_SIZE = 4096;         // ��������С�����Ը�����Ҫ����

void measureTLBSize(int blockSize)
{
    char *buffer = new char[BUFFER_SIZE];
    auto start = std::chrono::high_resolution_clock::now();

    // ���ʻ������е����ݣ�ģ���TLB��Ƶ������
    volatile char dummy; // ��ֹ�������Ż�
    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        int index = (i * blockSize) % BUFFER_SIZE;
        dummy = buffer[index]; // ���ʻ�����
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
    // ���Բ�ͬ��С�����ݿ飬�Գ��Բ���TLB�Ĵ�С
    measureTLBSize(1);    // ���Կ��СΪ1�ֽ�
    measureTLBSize(4);    // ���Կ��СΪ4�ֽ�
    measureTLBSize(16);   // ���Կ��СΪ16�ֽ�
    measureTLBSize(64);   // ���Կ��СΪ64�ֽ�
    measureTLBSize(256);  // ���Կ��СΪ256�ֽ�
    measureTLBSize(1024); // ���Կ��СΪ1024�ֽ�

    return 0;
}
