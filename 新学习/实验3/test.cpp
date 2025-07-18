#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 返回最少需要的单位区间数量
int min_interval_count(vector<double> &points)
{
    sort(points.begin(), points.end()); // 排序点集

    int count = 0;
    int i = 0, n = points.size();

    while (i < n)
    {
        double start = points[i];
        double end = start + 1; // 当前单位区间为 [start, start+1]

        // 把能被这个区间覆盖的点全部跳过
        while (i < n && points[i] <= end)
        {
            i++;
        }

        count++; // 选了一个新的单位区间
    }
    return count;
}

int main()
{
    vector<double> points = {0.2, 2.3, 1.5, 0.5, 3.0, 3.7, 4.9};

    int result = min_interval_count(points);

    cout << "最少需要的单位区间数量: " << result << endl;

    return 0;
}
