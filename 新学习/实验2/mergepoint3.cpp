#include <bits/stdc++.h>
#define N 100000
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

void merge(vector<Point> &points, int left, int mid, int right) // ��д�鲢����
{
    // vector<Point> temp;
    // int i = left, j = mid + 1;
    // while (i <= mid && j <= right)
    // {
    //     if (points[i].y <= points[j].y)
    //         temp.push_back(points[i++]);
    //     else
    //         temp.push_back(points[j++]);
    // }
    // while (i <= mid)
    //     temp.push_back(points[i++]);
    // while (j <= right)
    //     temp.push_back(points[j++]);
    // for (int k = 0; k < temp.size(); k++)
    //     points[left + k] = temp[k];
    inplace_merge(points.begin() + left, points.begin() + mid + 1, points.begin() + right + 1, cmpy);
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
double closestmerge(vector<Point> &xPoints, int left, int right)
{
    if (right - left <= 3) // С��3����ʱֻ��Ҫ������
    {
        return bruteForce(xPoints, left, right);
    }
    int mid = (left + right) / 2;
    double midx = xPoints[mid].x; // ���߻��֣�����2���ֵĵ��������

    double ansL = closestmerge(xPoints, left, mid);
    double ansR = closestmerge(xPoints, mid, right);
    double d = min(ansL, ansR);

    merge(xPoints, left, mid, right); // ��������y�������кϲ���һ����y�������У�����ʱ�临�Ӷ�O(n)

    // ��߽����
    vector<Point> strip;
    for (int i = left; i < right; i++)
    {
        if ((xPoints[i].x - midx) * (xPoints[i].x - midx) < d)
        {
            strip.push_back(xPoints[i]);
        }
    }

    // sort(strip.begin(), strip.end(), cmpy); // �� y ������

    return min(d, closeststrip(strip, d)); // ����߽�
}

double closestpair(vector<Point> &sos)
{
    vector<Point> xPoints = sos;
    sort(xPoints.begin(), xPoints.end(), cmpx); // ����Ȼ�����е�

    return sqrt(closestmerge(xPoints, 0, sos.size()));
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
        cout << "��̾��룺" << mindis << endl;
        sumtime += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    cout << "ƽ��ʱ��Ϊ��" << sumtime / runTime << endl;
    return 0;
}