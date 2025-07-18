#include <bits/stdc++.h>
using namespace std;

long long DPfrom_top(vector<vector<long long>> &sos, int f, int e) // 返回的是f层楼，e个鸡蛋时的最小尝试次数
{

    if (e == 1) // 只有一个鸡蛋，保守逐层放置
        return f;
    if (f == 0) // 没有楼层了返回0
        return 0;
    if (sos[f][e] != -1)
        return sos[f][e];

    long long res = f; // 最坏的选择
    for (int i = 1; i <= f; i++)
    {
        res = min(res, max(DPfrom_top(sos, f - i, e), DPfrom_top(sos, i - 1, e - 1)) + 1);
        // max表示考虑最坏的情况，min则表示选择最优的方法
    }
    sos[f][e] = res; // 最后把结果存起来
    return res;
}
int main()
{
    // 随机数
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_int_distribution<int> dist(1, 1000);

    int F = dist(gen);
    int E = dist(gen);

    // F = 8;
    // E = 4;

    vector<vector<long long>> sos(F + 1, vector<long long>(E + 1, -1)); // dp数组

    clock_t start_T = clock();
    long long ans = DPfrom_top(sos, F, E);
    clock_t end_T = clock();
    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << F << " floor and " << E << " eggs -> total " << ans << " ans" << endl;
    return 0;
}