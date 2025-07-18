#include <bits/stdc++.h>
using namespace std;

long long DPfrom_bottom(vector<vector<long long>> &sos, int f, int e) // 返回的是f层楼，e个鸡蛋时的最小尝试次数
{
    int m = 0;
    while (sos[m][e] < f) // 直到可以覆盖f层
    {
        m++;

        for (int i = 1; i <= e; i++)
        {
            sos[m][i] = sos[m - 1][i - 1] + sos[m - 1][i] + 1;
        }
    }
    return m;
}
int main()
{
    // 随机数
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_int_distribution<int> dist(1, 10000);

    int F = dist(gen);
    int E = dist(gen);

    // F = 8;
    // E = 4;

    vector<vector<long long>> sos(F + 2, vector<long long>(E + 2, 0)); // dp数组

    clock_t start_T = clock();
    long long ans = DPfrom_bottom(sos, F, E);
    clock_t end_T = clock();
    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << F << " floor and " << E << " eggs -> total " << ans << " ans" << endl;
    return 0;
}