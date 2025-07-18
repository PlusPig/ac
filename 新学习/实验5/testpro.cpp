#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <iomanip>

using namespace std;

int VERTEX, EDGE;
vector<vector<int>> connected; // 邻接表
vector<pair<int, int>> edges;  // 所有边

// 随机图生成（避免重复边）
void read(int V, int E)
{
    VERTEX = V;
    EDGE = E;
    connected.assign(VERTEX, vector<int>());
    set<pair<int, int>> edgeSet;

    srand((unsigned int)time(0));
    while ((int)edges.size() < EDGE)
    {
        int u = rand() % VERTEX;
        int v = rand() % VERTEX;
        if (u == v)
            continue;
        if (edgeSet.count(make_pair(u, v)) || edgeSet.count(make_pair(v, u)))
            continue;

        edgeSet.insert(make_pair(u, v));
        connected[u].push_back(v);
        connected[v].push_back(u);
        edges.push_back(make_pair(u, v));
    }
}

void read() // 读文件
{
    ifstream ifs("mediumDG.txt");
    int u, v;

    ifs >> VERTEX >> EDGE;
    // cout << VERTEX << EDGE;
    connected = new vector<int>[VERTEX];
    visited.resize(VERTEX, false);

    while (ifs >> u >> v)
    {
        connected[u].push_back(v);
        connected[v].push_back(u);
        edge.push_back({u, v});
    }
    ifs.close();
}

// 跳过 (skip_u, skip_v) 这条边进行 DFS 判断是否联通
bool dfs(int cur, int target, vector<bool> &visited, int skip_u, int skip_v)
{
    if (cur == target)
        return true;
    visited[cur] = true;

    for (int i = 0; i < (int)connected[cur].size(); ++i)
    {
        int neighbor = connected[cur][i];
        if ((cur == skip_u && neighbor == skip_v) || (cur == skip_v && neighbor == skip_u))
            continue;
        if (!visited[neighbor])
        {
            if (dfs(neighbor, target, visited, skip_u, skip_v))
                return true;
        }
    }
    return false;
}

// 逐边判断是否是桥
int count_bridges()
{
    int count = 0;
    for (int i = 0; i < (int)edges.size(); ++i)
    {
        int u = edges[i].first;
        int v = edges[i].second;
        vector<bool> visited(VERTEX, false);
        if (!dfs(u, v, visited, u, v))
        {
            count++;
        }
    }
    return count;
}

int main()
{
    // read(4000, 10000); // 你可以改成 read() 从文件读取
    read();
    clock_t start = clock();
    int bridge_num = count_bridges();
    clock_t end = clock();

    cout << "Bridge's num: " << bridge_num << endl;
    cout << fixed << setprecision(3)
         << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    return 0;
}
