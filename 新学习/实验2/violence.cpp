#include <bits/stdc++.h>
#define N 100000
using namespace std;
class Point
{
private:
    double x, y;

public:
    Point() = default;
    Point(double a, double b) : x(a), y(b)
    {
    }
    double getx()
    {
        return x;
    }
    double gety()
    {
        return y;
    }
};
int main()
{
    int T = N; // 生成多少个点

    unsigned long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_real_distribution<double> dist(-1000000, 1000000);

    vector<Point> sos;
    for (int i = 0; i < T; i++)
    {
        double x = dist(gen);
        double y = dist(gen);
        // cout << x << " " << y << endl;
        Point a(x, y);
        sos.push_back(a);
    }

    // 现在开始计算最短的距离
    double mindis = DBL_MAX;
    clock_t start_time = clock(); // 计算时间

    for (int i = 0; i < sos.size() - 1; i++)
    {
        for (int j = i + 1; j < sos.size(); j++)
        {
            double dis = sqrt(pow(sos[i].getx() - sos[j].getx(), 2) + pow(sos[i].gety() - sos[j].gety(), 2)); // 计算2点间距离
            mindis = min(mindis, dis);
        }
    }

    clock_t end_time = clock();

    cout << "运行时间为：" << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
    cout << "最短距离：" << mindis << endl;
    return 0;
}