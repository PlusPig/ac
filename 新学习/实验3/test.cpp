#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ����������Ҫ�ĵ�λ��������
int min_interval_count(vector<double> &points)
{
    sort(points.begin(), points.end()); // ����㼯

    int count = 0;
    int i = 0, n = points.size();

    while (i < n)
    {
        double start = points[i];
        double end = start + 1; // ��ǰ��λ����Ϊ [start, start+1]

        // ���ܱ�������串�ǵĵ�ȫ������
        while (i < n && points[i] <= end)
        {
            i++;
        }

        count++; // ѡ��һ���µĵ�λ����
    }
    return count;
}

int main()
{
    vector<double> points = {0.2, 2.3, 1.5, 0.5, 3.0, 3.7, 4.9};

    int result = min_interval_count(points);

    cout << "������Ҫ�ĵ�λ��������: " << result << endl;

    return 0;
}
