#include <bits/stdc++.h>
using namespace std;

// �������Ż��Ŀռ�ѹ���漦������ DP
long long solve(int F, int E)
{
    vector<long long> prev(F + 1, 0); // e-1 ��������״̬
    vector<long long> curr(F + 1, 0); // e ��������״̬

    // ��ʼ����1������ʱֻ��������
    for (int f = 1; f <= F; ++f)
        prev[f] = f;

    for (int e = 2; e <= E; ++e)
    {
        curr[0] = 0; // 0��Ϊ0
        curr[1] = 1; // 1��Ϊ1

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
            // �� low �� high ��ȡ����
            long long ans = min(max(prev[low - 1], curr[f - low]), max(prev[high - 1], curr[f - high])) + 1;
            curr[f] = ans;
        }

        // ��������
        prev = curr;
    }

    return prev[F];
}

int main()
{
    // �������¥��ͼ�����
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    uniform_int_distribution<int> dist(1, 1000);

    int F = dist(gen); // ¥��
    int E = dist(gen); // ����

    F = 1000;
    E = 100;

    clock_t start_T = clock();
    long long result = solve(F, E);
    clock_t end_T = clock();

    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << F << " floor and " << E << " eggs -> total " << result << " tries" << endl;

    return 0;
}
