#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int main()
{
    ofstream of;
    of.open("in1.txt", ios::out); // 打开文件

    // 设置随机数
    unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_int_distribution<int> dist(1, 50000000);

    // 随机数写入文件
    for (int i = 0; i < 100000; i++)
    {
        of << dist(gen) << " ";
    }
    of.close();

    // 读取文件
    ifstream ifm;
    ifm.open("in1.txt", ios::in);
    vector<int> sos;
    int num;
    while (ifm >> num)
    {
        sos.push_back(num);
    }
    ifm.close();

    // 开始计算时间
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    // 排序函数
    for (int i = 0; i < sos.size() - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < sos.size(); j++)
        {
            if (sos[j] < sos[k])
            {
                k = j;
            }
        }
        if (i != k)
        {
            int temp = sos[i];
            sos[i] = sos[k];
            sos[k] = temp;
        }
    }
    // 计算运行时间
    QueryPerformanceCounter(&end);
    double duration = (end.QuadPart - start.QuadPart) * 1e6 / freq.QuadPart;
    cout << "运行时间为：" << duration / 1000000 << endl;
    return 0;

    // 保存数据到文件
    ofstream of;
    of.open("result1.txt", ios::out);
    for (int i = 0; i < N; i++)
    {
        of << sos[i] << " ";
    }
    of.close();
}
