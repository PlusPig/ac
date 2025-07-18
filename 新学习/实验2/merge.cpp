#include <bits/stdc++.h>
using namespace std;
#define n 20
int f(vector<int> &sos, int l, int r) // 事实上就是动态规划？
{
    int m = (l + r) / 2;
    int sumL = 0, ansL = sos[m];
    int sumR = 0, ansR = sos[m + 1]; // 初始化
    // 然后求最大值
    for (int i = m; i >= l; i--)
    {
        sumL += sos[i];
        ansL = max(ansL, sumL);
    }
    for (int i = m + 1; i <= r; i++)
    {
        sumR += sos[i];
        ansR = max(ansR, sumR);
    }
    return ansL + ansR;
}
int maxsum(vector<int> &sos, int l, int r)
{
    if (l == r)
    {
        return sos[l];
    }
    int m = (l + r) / 2;
    int suml = maxsum(sos, l, m);
    int sumr = maxsum(sos, m + 1, r);
    int sumrl = f(sos, l, r);
    return max(max(suml, sumr), sumrl);
}
int main()
{
    int t = n;
    vector<int> sos(t);
    unsigned long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_int_distribution<int> dist(-100, 100);

    for (int i = 0; i < t; i++)
    {
        sos[i] = dist(gen);
        cout << sos[i] << " ";
    }
    cout << endl;

    cout << maxsum(sos, 0, sos.size() - 1);
    return 0;
}