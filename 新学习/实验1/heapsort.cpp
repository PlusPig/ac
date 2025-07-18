#include <bits/stdc++.h>
using namespace std;
#define N 700000
#define T 2
void heapdown(vector<int> &sos, int n, int i)
{
    int left = 2 * i + 1, right = 2 * i + 2;
    int biggest = i;

    if (left < n && sos[left] > sos[biggest]) // 找到左右节点中的最大值
        biggest = left;
    if (right < n && sos[right] > sos[biggest])
        biggest = right;

    if (biggest != i)
    {
        int temp = sos[i];
        sos[i] = sos[biggest];
        sos[biggest] = temp;
        heapdown(sos, n, biggest);
    }
}
void buildheap(vector<int> &sos, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapdown(sos, n, i);
    }
}
int main()
{
    unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_int_distribution<int> dist(1, 50000000);

    int t = T;
    while (t--)
    {
        vector<int> sos;

        for (int i = 0; i < N; i++)
        {
            sos.push_back(dist(gen));
        }

        cout << "排序前：" << endl;
        for (int i = N - 1; i > N - 11; i--)
        {
            cout << sos[i] << " ";
        }
        cout << endl;

        clock_t start_time = clock(); // 开始计时

        buildheap(sos, sos.size()); // 建立最大堆

        for (int i = N - 1; i > N - 11; i--) // 只需交换10次
        {
            int temp = sos[0];
            sos[0] = sos[i];
            sos[i] = temp;
            heapdown(sos, i, 0); // 与堆顶元素交换并且重新调整最大堆
        }

        clock_t end_time = clock();

        // 最后验证前10个
        cout << "排序后：" << endl;
        for (int i = N - 1; i > N - 11; i--)
        {
            cout << sos[i] << " ";
        }
        cout << endl;

        cout << "第" << 10 - t << "次排序的时间：" << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
    }
    // system("pause");
    return 0;
}