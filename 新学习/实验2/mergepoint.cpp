#include <bits/stdc++.h>
#define N 1000000
#define runTime 20
using namespace std;
class Point
{
public:
    double x, y;

public:
    Point() = default;
    Point(double a, double b) : x(a), y(b)
    {
    }
};

bool cmpy(Point a, Point b)
{
    return a.y < b.y;
}

bool cmpx(Point a, Point b)
{
    return a.x < b.x;
}

double getdis(Point a, Point b) // 先求平方和，避免sqrt函数的多次调用
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double bruteForce(vector<Point> &points, int left, int right) // 暴力法
{
    double mindis = DBL_MAX;
    for (int i = left; i < right - 1; i++)
    {
        for (int j = i + 1; j < right; j++)
        {
            mindis = min(mindis, getdis(points[i], points[j]));
        }
    }
    return mindis;
}
// 处理跨中线的情况
double closeststrip(vector<Point> &strip, double d)
{
    double mindis = d;
    int n = strip.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < i + 7 && j < n; j++) // 每个点与往上7个点计算距离
        {
            if (strip[j].y - strip[i].y > mindis)
                break; // 如果纵坐标距离大于minlen就不需要计算了
            mindis = min(mindis, getdis(strip[i], strip[j]));
        }
    }
    return mindis;
}
// 递归求最近点对
double closestmerge(vector<Point> &xPoints, vector<Point> &yPoints, int left, int right)
{
    if (right - left <= 3)
    {
        return bruteForce(xPoints, left, right);
    }
    int mid = (left + right) / 2;
    double midx = xPoints[mid].x; // 中线划分，左右2部分的点数量相等

    // 分别求左右两部分的最短距离
    vector<Point> leftY, rightY;

    for (int i = 0; i < yPoints.size(); i++)
    {
        if (yPoints[i].x < midx)
        {
            leftY.push_back(yPoints[i]);
        }
        else
        {
            rightY.push_back(yPoints[i]);
        }
    }

    double ansL = closestmerge(xPoints, leftY, left, mid);
    double ansR = closestmerge(xPoints, rightY, mid, right);
    double d = min(ansL, ansR);

    // 边界情况
    vector<Point> strip;
    for (auto &p : yPoints)
    {
        if ((p.x - midx) * (p.x - midx) < d) // 和中线的距离小于d
        {
            strip.push_back(p);
        }
    }

    sort(strip.begin(), strip.end(), cmpy); // 按照y从大到小排序

    return min(d, closeststrip(strip, d)); // 处理边界
}

double closestpair(vector<Point> &sos)
{
    vector<Point> xPoints = sos;
    vector<Point> yPoints = sos;                // 分别用x和y进行排序
    sort(xPoints.begin(), xPoints.end(), cmpx); // 排序，然后找中点
    sort(yPoints.begin(), yPoints.end(), cmpy);

    return sqrt(closestmerge(xPoints, yPoints, 0, sos.size()));
}

int main()
{
    int T = N, t = runTime; // 生成多少个点
    double sumtime = 0;

    unsigned long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // 时间戳作为种子
    uniform_real_distribution<double> dist(-1000000, 1000000);

    while (t--)
    {
        vector<Point> sos;
        for (int i = 0; i < T; i++)
        {
            double x = dist(gen);
            double y = dist(gen);
            Point a(x, y);
            sos.push_back(a);
        }

        // 现在开始计算最短的距离

        clock_t start_time = clock(); // 计算时间

        double mindis = closestpair(sos); // 执行函数

        clock_t end_time = clock(); // 计算完成

        cout << "运行时间为：" << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
        // cout << "最短距离：" << mindis << endl;
        sumtime += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    cout << "平均时间为：" << sumtime / runTime << endl;
    return 0;
}