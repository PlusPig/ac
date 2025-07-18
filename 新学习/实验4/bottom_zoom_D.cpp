#include <bits/stdc++.h>
using namespace std;

void from_bottom_monotonic(vector<vector<long long>> &dp, int F, int E)
{
    for (int e = 2; e <= E; ++e)
    {
        vector<long long> prev(F + 1, 0);
        vector<long long> curr(F + 1, 0);
        vector<int> opt(F + 1, 0); // ��¼ÿһ������ž��ߵ�

        for (int f = 1; f <= F; ++f)
        {
            prev[f] = dp[f][e - 1];
            curr[f] = f; // ��ʼ��Ϊ����
            opt[f] = 1;  // ��ʼ�����ž��ߵ�
        }

        for (int f = 2; f <= F; ++f)
        {
            int left = opt[f - 1];
            int right = f;
            int best_x = left;

            for (int x = left; x <= right; ++x)
            {
                long long broken = prev[x - 1];
                long long not_broken = curr[f - x];
                long long worst = max(broken, not_broken) + 1;

                if (worst < curr[f])
                {
                    curr[f] = worst;
                    best_x = x;
                }
            }

            opt[f] = best_x; // ��¼���ž��ߵ㣬��һ�δ����￪ʼ
        }

        for (int f = 1; f <= F; ++f)
            dp[f][e] = curr[f];
    }
}

int main()
{
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    uniform_int_distribution<int> dist(1, 1000);

    int F = dist(gen);
    int E = dist(gen);

    F = 1000;
    E = 10;

    vector<vector<long long>> dp(F + 1, vector<long long>(E + 1, 0));

    for (int e = 1; e <= E; ++e)
    {
        dp[0][e] = 0;
        dp[1][e] = 1;
    }

    for (int f = 1; f <= F; ++f)
        dp[f][1] = f;

    clock_t start_T = clock();
    from_bottom_monotonic(dp, F, E);
    clock_t end_T = clock();

    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << F << " floors and " << E << " eggs -> total " << dp[F][E] << " tries" << endl;

    return 0;
}
