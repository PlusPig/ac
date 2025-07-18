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
    int T = n; // 20��ȡƽ��ֵ
    double sumTime = 0;

    // ���������
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // ʱ�����Ϊ����
    uniform_int_distribution<int> dist(1, 50000000);

    while (T--)
    {
        // ���������
        vector<int> sos;
        for (int i = 0; i < N; i++)
        {
            sos.push_back(dist(gen));
        }

        // ��ʼ����ʱ��
        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
        // clock_t start_time = clock();

        // ������
        selectsort(sos); // ѡ������
        // quicksort(sos); // ��������
        // bubblesort(sos); // ð������
        // insertsort(sos); // ��������
        //  mergesort(sos); // �鲢����

        // ��������ʱ��
        QueryPerformanceCounter(&end);
        double duration = (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;
        cout << "��" << 20 - T << "������ʱ��Ϊ��" << duration / 1000000 << endl;

        sumTime += duration / 1000000;
        // clock_t end_time = clock();
        // cout << "��" << 20 - T << "������ʱ��Ϊ��" << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;

        // sumTime += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }

    cout << "ƽ������ʱ��Ϊ" << sumTime / n << endl;
    return 0;
}
