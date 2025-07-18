#include <bits/stdc++.h>
using namespace std;
#define F 8
#define E 4

int DP(int f, int e) // 返回的是f层楼，e个鸡蛋时的最小尝试次数
{
    if (e == 1) // 只有一个鸡蛋，保守逐层放置
    {
        return f;
    }
    else if (f == 0)
    {
        return 0;
    }
    else
    {
        int res = INT_MAX;
        for (int i = 1; i <= f; i++)
        {
            res = min(res, max(DP(f - i, e), DP(i - 1, e - 1)) + 1);
            // max表示考虑最坏的情况，min则表示选择最优的方法
        }
        return res;
    }
}
int main()
{
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_int_distribution<int> dist(1, 1000);

    // int F = dist(gen);
    // int E = dist(gen);

    // cout << F << " " << E << endl;
    clock_t start_T = clock();
    int ans = DP(F, E);
    clock_t end_T = clock();
    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC << endl;
    cout << ans;
    return 0;
}