#include <bits/stdc++.h>
#define N 500000
#define runTime 10
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

double getdis(Point a, Point b) // ����ƽ���ͣ�����sqrt�����Ķ�ε���
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double bruteForce(vector<Point> &points, int left, int right) // ������
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

double closestpair(vector<Point> &sos)
{
    return sqrt(bruteForce(sos, 0, sos.size()));
}

int main()
{
    int T = N, t = runTime; // ���ɶ��ٸ���
    double sumtime = 0;

    unsigned long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // ʱ�����Ϊ����
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

        // ���ڿ�ʼ������̵ľ���

        clock_t start_time = clock(); // ����ʱ��

        double mindis = closestpair(sos); // ִ�к���

        clock_t end_time = clock(); // �������

        cout << "����ʱ��Ϊ��" << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
        cout << "��̾��룺" << sqrt(mindis) << endl;
        sumtime += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    cout << "ƽ��ʱ��Ϊ��" << sumtime / runTime << endl;
    return 0;
}