#include <bits/stdc++.h>
using namespace std;

int EDGE, VERTEX;
vector<int> *connected; // 邻接表
vector<pair<int, int>> edge;
vector<bool> visited;

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

void read(int V, int E) // 随机生成边
{
    VERTEX = V;
    EDGE = E;
    connected = new vector<int>[VERTEX];
    visited.resize(VERTEX, false);

    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    uniform_int_distribution<int> dist(0, V - 1);

    set<pair<int, int>> edgeSet; // 用来记录重复边
    while (edge.size() < EDGE)
    {
        int u = dist(gen);
        int v = dist(gen);
        if (u == v)
            continue;

        if (edgeSet.count({u, v}) || edgeSet.count({v, u}))
            continue;

        edgeSet.insert({u, v});
        connected[u].push_back(v);
        connected[v].push_back(u);
        edge.push_back({u, v});
    }
}

void dfs(int cur) // 标记同一个连通分量中的点
{
    for (int i = 0; i < connected[cur].size(); i++)
    {
        int v = connected[cur][i];
        if (connected[cur][i] != -1 && !visited[v])
        {
            visited[v] = true;
            dfs(v);
        }
    }
}

int count() // 计算连通块的数量
{
    for (int i = 0; i < VERTEX; i++)
        visited[i] = false; // init

    int num = 0;
    for (int i = 0; i < VERTEX; i++)
    {
        if (!visited[i])
        {
            num++;
            visited[i] = true;
            dfs(i);
        }
    }

    return num;
}

int countbridge()
{
    int bridge = 0;
    int num1 = count(), num2 = 0;
    for (int i = 0; i < EDGE; i++)
    {
        int v1 = edge[i].first, v2 = edge[i].second;
        int j, k;
        for (j = 0; j < connected[v1].size(); j++)
        {
            if (connected[v1][j] == v2)
            {
                connected[v1][j] = -1;
                break;
            }
        }
        for (k = 0; k < connected[v2].size(); k++)
        {
            if (connected[v2][k] == v1)
            {
                connected[v2][k] = -1;
                break;
            }
        }

        num2 = count();
        if (num2 > num1)
            bridge++;

        connected[v1][j] = v2;
        connected[v2][k] = v1; // 加边
    }
    return bridge;
}

int main()
{
    read(2000, 10000); // V,E
    // read();
    clock_t start_T = clock();
    int bridge = countbridge();
    clock_t end_T = clock();

    cout << "bridge's num: " << bridge << endl;
    cout << fixed << setprecision(3) << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}