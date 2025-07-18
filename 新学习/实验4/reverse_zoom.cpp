#include <bits/stdc++.h>
using namespace std;

long long DPfrom_bottom(int f, int e)
{
    vector<long long> sos(e + 2, 0);
    int m = 0;
    while (sos[e] < f)
    {
        m++;
        for (int i = e; i >= 1; i--)
        {
            sos[i] = sos[i] + sos[i - 1] + 1;
        }
    }
    return m;
}

int main()
{
    // Ëæ»úÊý
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    uniform_int_distribution<int> dist(1, 10000);

    int F = dist(gen);
    int E = dist(gen);

    F = 1000;
    E = 100;

    clock_t start_T = clock();
    long long ans = DPfrom_bottom(F, E);
    clock_t end_T = clock();

    cout << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << F << " floor and " << E << " eggs -> total " << ans << " tries" << endl;

    return 0;
}
