#include <bits/stdc++.h>
using namespace std;
#define vertexnum 450
#define colournum 25
#define edgenum 17

int sum = 0;
vector<int> order(vertexnum); // 着色顺序
clock_t start_time, end_time;

bool judgeone(vector<vector<int>> &tu, vector<int> &colour, int &row)
{
    for (int j = 0; j < vertexnum; j++)
    {
        if (tu[row][j] == 1 && colour[row] == colour[j])
        {
            return false;
        }
    }
    return true;
}

void dfs(vector<vector<int>> &tu, vector<int> &colour, int idx, ofstream &ofs)
{
    if (idx == tu.size())
    {
        sum++;
        if (sum == 10000000)
        {
            end_time = clock(); // 计算完成
            cout << "总共找到" << sum << "种填色方案" << endl;
            cout << "运行时间为：" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
        }
        if (sum == 1000000000)
        {
            end_time = clock(); // 计算完成
            cout << "总共找到" << sum << "种填色方案" << endl;
            cout << "运行时间为：" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
        }

        return;
    }
    for (int i = 1; i <= colournum; i++)
    {
        colour[order[idx]] = i;

        // 检查部分
        if (judgeone(tu, colour, order[idx]))
        {
            dfs(tu, colour, idx + 1, ofs);
        }
        colour[order[idx]] = 0;
    }
}

int main()
{
    vector<vector<int>> tu(vertexnum, vector<int>(vertexnum, 0)); // 记录邻接关系
    vector<int> colour(vertexnum, 0);                             // 用来记录是什么颜色的
    vector<int> du(vertexnum);                                    // 用来记录度数,前面的编号，后面是度数

    ifstream ifs;
    // ifs.open("smalltext.txt", ios::in);
    ifs.open("le450_25a.txt", ios::in);

    ofstream ofs;
    ofs.open("smallresult.txt", ios::out);

    char a;
    int b, c;
    while (ifs >> a >> b >> c)
    {
        tu[b - 1][c - 1] = 1;
        tu[c - 1][b - 1] = 1;
        du[b - 1]++;
        du[c - 1]++;
    }

    ifs.close();

    for (int i = 0; i < vertexnum; i++)
    {
        order[i] = i;
    }

    sort(order.begin(), order.end(), [&](int a, int b)
         { return du[a] > du[b]; });

    start_time = clock(); // 计算时间

    dfs(tu, colour, 0, ofs);

    end_time = clock(); // 计算完成
    cout << "总共找到" << sum << "种填色方案" << endl;
    cout << "运行时间为：" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
}