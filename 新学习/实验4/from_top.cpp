#include <bits/stdc++.h>
using namespace std;

long long DPfrom_top(vector<vector<long long>> &sos, int f, int e) // ���ص���f��¥��e������ʱ����С���Դ���
{

    if (e == 1) // ֻ��һ������������������
        return f;
    if (f == 0) // û��¥���˷���0
        return 0;
    if (sos[f][e] != -1)
        return sos[f][e];

    long long res = f; // ���ѡ��
    for (int i = 1; i <= f; i++)
    {
        res = min(res, max(DPfrom_top(sos, f - i, e), DPfrom_top(sos, i - 1, e - 1)) + 1);
        // max��ʾ������������min���ʾѡ�����ŵķ���
    }
    sos[f][e] = res; // ���ѽ��������
    return res;
}
int main()
{
    // �����
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // ʱ�����Ϊ����
    uniform_int_distribution<int> dist(1, 1000);

    int F = dist(gen);
    int E = dist(gen);

    // F = 8;
    // E = 4;

    vector<vector<long long>> sos(F + 1, vector<long long>(E + 1, -1)); // dp����

    clock_t start_T = clock();
    long long ans = DPfrom_top(sos, F, E);
    clock_t end_T = clock();
    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << F << " floor and " << E << " eggs -> total " << ans << " ans" << endl;
    return 0;
}