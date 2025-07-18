#include <bits/stdc++.h>
using namespace std;

void from_bottom(vector<vector<long long>> &dp, int &F, int &E)
{
    for (int f = 2; f <= F; ++f)
    {
        for (int e = 2; e <= E; ++e)
        {
            dp[f][e] = f; // ��ʼ��Ϊ���������Գ���

            for (int x = 1; x <= f; ++x)
            {
                long long broken = dp[x - 1][e - 1]; // ��������
                long long not_broken = dp[f - x][e]; // ����û��
                long long worst = max(broken, not_broken) + 1;
                dp[f][e] = min(dp[f][e], worst);
            }
        }
    }
}
int main()
{
    // �����
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    uniform_int_distribution<int> dist(1, 1000);

    int F = dist(gen); // ¥��
    int E = dist(gen); // ������

    // F = 8; E = 4;

    vector<vector<long long>> dp(F + 1, vector<long long>(E + 1, 0));

    // ��ʼ����¥��Ϊ0�����Դ���Ϊ0��¥��Ϊ1ʱ���Դ���Ϊ1
    for (int e = 1; e <= E; ++e)
    {
        dp[0][e] = 0;
        dp[1][e] = 1;
    }

    for (int f = 1; f <= F; ++f)
    {
        dp[f][1] = f; // ֻ��һ������ʱ��������㳢��
    }

    clock_t start_T = clock();
    // ״̬ת��
    from_bottom(dp, F, E);

    clock_t end_T = clock();
    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << F << " floor and " << E << " eggs -> total " << dp[F][E] << " tries" << endl;
    return 0;
}
