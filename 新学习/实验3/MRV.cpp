#include <bits/stdc++.h>
using namespace std;
#define FILENAME "smalltext.txt"
#define VERTEX 450
#define EDGE 0
#define COLOUR 25

class node
{
public:
    int degree; // 度数
    int id;     // 原始下标
    vector<int> leftcolour;
    int leftnum;
    node()
    {
        degree = 0;
        leftnum = COLOUR;
        leftcolour.resize(COLOUR, 0); // 0表示还可以用这种颜色
    }
    bool operator<(const node v) const
    {
        return this->degree >= v.degree;
    }
};

// 全局变量
vector<vector<int>> connect; // 使用邻接矩阵
vector<int> colour;
vector<node> vertex;
clock_t start_time, end_time;
ofstream ofs("smallresult.txt");
int sum = 0; // 表示方案数

bool check(int id, set<int> &used)
{
    for (int i = 0; i < VERTEX; i++)
    {
        if (connect[id][i])
        {
            used.insert(i);
        }
        if (connect[id][i] == 1 && colour[i] == colour[id])
        {
            return false;
        }
    }
    return true;
}

void read()
{
    ifstream ifs("le450_25a.txt"); // 这里改文件
    int v1, v2;
    char e;
    while (ifs >> e >> v1 >> v2)
    {
        connect[v1 - 1][v2 - 1] = 1;
        connect[v2 - 1][v1 - 1] = 1;
        vertex[v1 - 1].degree++;
        vertex[v2 - 1].degree++;
    }

    for (int i = 0; i < VERTEX; ++i)
    {
        vertex[i].id = i;
    }

    ifs.close();
}

void writeinfile() // 写入文件
{
    for (int i = 0; i < VERTEX; i++)
    {
        ofs << colour[i] << " ";
    }
    ofs << endl;
}

int MRV_find() // 找到最少可用颜色而且还未上色的节点
{
    int min = INT_MAX;
    int index = -1;

    for (int i = 0; i < VERTEX; i++) // 就是寻找约束最大的点
    {
        // 没有排序过，直接用i即可
        if (colour[i])
            continue;

        if (vertex[i].leftnum < min)
        {
            min = vertex[i].leftnum; // 寻找约束最大的点
            index = i;
        }
    }
    return index;
}

void decrease(set<int> &used, int Colour)
{
    for (int realidx : used)
    {
        if (vertex[realidx].leftcolour[Colour] == 0)
        {
            vertex[realidx].leftcolour[Colour] = 1;
            vertex[realidx].leftnum--;
        }
        else
        {
            vertex[realidx].leftcolour[Colour]++;
        }
    }
}

void increase(set<int> &used, int Colour)
{
    for (int realidx : used)
    {
        if (vertex[realidx].leftcolour[Colour] == 1)
        {
            vertex[realidx].leftcolour[Colour] = 0;
            vertex[realidx].leftnum++;
        }
        else
        {
            vertex[realidx].leftcolour[Colour]--;
        }
    }
}

void MRV_dfs(int num)
{
    if (num == VERTEX)
    {
        sum++;
        if (sum == 10000000)
        {
            end_time = clock();
            cout << "目前找到" << sum << "种填色方案" << endl;
            cout << "运行时间为：" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
        }
        return;
    }

    int minidx = MRV_find(); // 最少可填颜色的下标
    if (minidx == -1)
    {
        return;
    }

    for (int i = 1; i <= COLOUR; i++)
    {
        // 没有排序，所以获得得最小下标就是真实下标
        colour[minidx] = i;
        set<int> used; // 用来记录有链接的节点，方便后续复原
        if (check(minidx, used))
        {
            decrease(used, i - 1);
            MRV_dfs(num + 1);
            increase(used, i - 1);
        }
        colour[minidx] = 0;
    }
}

int main()
{
    connect.resize(VERTEX, vector<int>(VERTEX, 0));
    colour.resize(VERTEX, 0);
    vertex.resize(VERTEX);

    read(); // 读取文件

    start_time = clock();
    MRV_dfs(0); // 开始回溯
    end_time = clock();

    cout << "总共找到" << sum << "种填色方案" << endl;
    cout << "运行时间为：" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}
