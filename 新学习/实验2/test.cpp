#include <bits/stdc++.h>
#define N 100
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
    uniform_real_distribution<double> dist(-100, 100);

    vector<Point> sos;
    for (int i = 0; i < T; i++)
    {
        double x = dist(gen);
        double y = dist(gen);
        cout << x << " " << y << endl;
        Point a(x, y);
        sos.push_back(a);
    }

    return 0;
}