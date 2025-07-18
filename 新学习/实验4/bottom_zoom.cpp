#include <bits/stdc++.h>
using namespace std;

// 带二分优化的空间压缩版鸡蛋掉落 DP
long long solve(int F, int E)
{
    vector<long long> prev(F + 1, 0); // e-1 个鸡蛋的状态
    vector<long long> curr(F + 1, 0); // e 个鸡蛋的状态

    // 初始化：1个鸡蛋时只能线性试
    for (int f = 1; f <= F; ++f)
        prev[f] = f;

    for (int e = 2; e <= E; ++e)
    {
        curr[0] = 0; // 0层为0
        curr[1] = 1; // 1层为1

        for (int f = 2; f <= F; ++f)
        {
            int low = 1, high = f;
            while (low + 1 < high)
            {
                int mid = (low + high) / 2;
                long long broken = prev[mid - 1];
                long long not_broken = curr[f - mid];
                if (broken < not_broken)
                    low = mid;
                else
                    high = mid;
            }
            // 在 low 和 high 中取最优
            long long ans = min(max(prev[low - 1], curr[f - low]), max(prev[high - 1], curr[f - high])) + 1;
            curr[f] = ans;
        }

        // 滚动更新
        prev = curr;
    }

    return prev[F];
}

int main()
{
    // 随机生成楼层和鸡蛋数
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    uniform_int_distribution<int> dist(1, 1000);

    int F = dist(gen); // 楼层
    int E = dist(gen); // 鸡蛋

    F = 1000;
    E = 100;

    clock_t start_T = clock();
    long long result = solve(F, E);
    clock_t end_T = clock();

    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << F << " floor and " << E << " eggs -> total " << result << " tries" << endl;

    return 0;
}
