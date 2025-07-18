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
    int T = N; // ���ɶ��ٸ���

    unsigned long long seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // ʱ�����Ϊ����
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

    // ���ڿ�ʼ������̵ľ���
    double mindis = DBL_MAX;
    clock_t start_time = clock(); // ����ʱ��

    for (int i = 0; i < sos.size() - 1; i++)
    {
        for (int j = i + 1; j < sos.size(); j++)
        {
            double dis = sqrt(pow(sos[i].getx() - sos[j].getx(), 2) + pow(sos[i].gety() - sos[j].gety(), 2)); // ����2������
            mindis = min(mindis, dis);
        }
    }

    clock_t end_time = clock();

    cout << "����ʱ��Ϊ��" << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
    cout << "��̾��룺" << mindis << endl;
    return 0;
}