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
// ��������ߵ����
double closeststrip(vector<Point> &strip, double d)
{
    double mindis = d;
    int n = strip.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < i + 7 && j < n; j++) // ÿ����������7����������
        {
            if (strip[j].y - strip[i].y > mindis)
                break; // ���������������minlen�Ͳ���Ҫ������
            mindis = min(mindis, getdis(strip[i], strip[j]));
        }
    }
    return mindis;
}
// �ݹ���������
double closestmerge(vector<Point> &xPoints, vector<Point> &yPoints, int left, int right)
{
    if (right - left <= 3)
    {
        return bruteForce(xPoints, left, right);
    }
    int mid = (left + right) / 2;
    double midx = xPoints[mid].x; // ���߻��֣�����2���ֵĵ��������

    // �ֱ������������ֵ���̾���
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

    // �߽����
    vector<Point> strip;
    for (auto &p : yPoints)
    {
        if ((p.x - midx) * (p.x - midx) < d) // �����ߵľ���С��d
        {
            strip.push_back(p);
        }
    }

    sort(strip.begin(), strip.end(), cmpy); // ����y�Ӵ�С����

    return min(d, closeststrip(strip, d)); // ����߽�
}

double closestpair(vector<Point> &sos)
{
    vector<Point> xPoints = sos;
    vector<Point> yPoints = sos;                // �ֱ���x��y��������
    sort(xPoints.begin(), xPoints.end(), cmpx); // ����Ȼ�����е�
    sort(yPoints.begin(), yPoints.end(), cmpy);

    return sqrt(closestmerge(xPoints, yPoints, 0, sos.size()));
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
        // cout << "��̾��룺" << mindis << endl;
        sumtime += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    cout << "ƽ��ʱ��Ϊ��" << sumtime / runTime << endl;
    return 0;
}