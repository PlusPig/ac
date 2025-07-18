#include <bits/stdc++.h>
#include <windows.h>
#include "selectsort.cpp"
#include "quicksort.cpp"
#include "bubblesort.cpp"
#include "insertsort.cpp"
#include "mergesort.cpp"
#define N 500000
#define n 20
using namespace std;
int main()
{
    int T = n; // 20次取平均值
    double sumTime = 0;

    // 设置随机数
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_int_distribution<int> dist(1, 50000000);

    while (T--)
    {
        // 生成随机数
        vector<int> sos;
        for (int i = 0; i < N; i++)
        {
            sos.push_back(dist(gen));
        }

        // 开始计算时间
        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
        // clock_t start_time = clock();

        // 排序函数
        selectsort(sos); // 选择排序
        // quicksort(sos); // 快速排序
        // bubblesort(sos); // 冒泡排序
        // insertsort(sos); // 插入排序
        //  mergesort(sos); // 归并排序

        // 计算运行时间
        QueryPerformanceCounter(&end);
        double duration = (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;
        cout << "第" << 20 - T << "次运行时间为：" << duration / 1000000 << endl;

        sumTime += duration / 1000000;
        // clock_t end_time = clock();
        // cout << "第" << 20 - T << "次运行时间为：" << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;

        // sumTime += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }

    cout << "平均运行时间为" << sumTime / n << endl;
    return 0;
}
