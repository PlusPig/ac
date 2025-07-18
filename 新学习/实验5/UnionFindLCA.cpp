#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <ctime>

using namespace std;

// 并查集
class UnionFind
{
    vector<int> parent, rank;

public:
    int components;
    UnionFind(int n) : parent(n), rank(n, 0), components(n)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx == fy)
            return false;
        if (rank[fx] < rank[fy])
            parent[fx] = fy;
        else
        {
            parent[fy] = fx;
            if (rank[fx] == rank[fy])
                rank[fx]++;
        }
        components--;
        return true;
    }
};

// 全局变量
int V, E;
vector<pair<int, int>> edges;
vector<vector<pair<int, int>>> adj; // 邻接表，存边和边编号
vector<int> parent, depth, edgeToParent;
int LOG;
vector<vector<int>> fa;

// 读取文件函数
void readFile(const string &filename)
{
    ifstream infile(filename.c_str());
    infile >> V >> E;
    edges.clear();
    for (int i = 0; i < E; ++i)
    {
        int u, v;
        infile >> u >> v;
        edges.push_back(make_pair(u, v));
    }
    infile.close();
}

// 随机图生成函数
void generateRandomGraph(int a, int b)
{
    V = a;
    E = b;
    edges.clear();
    srand((unsigned)time(NULL));
    set<pair<int, int>> edgeSet;
    while ((int)edges.size() < E)
    {
        int u = rand() % V;
        int v = rand() % V;
        if (u == v)
            continue;
        if (edgeSet.count(make_pair(u, v)) || edgeSet.count(make_pair(v, u)))
            continue;
        edgeSet.insert(make_pair(u, v));
        edges.push_back(make_pair(u, v));
    }
}

// DFS初始化父亲深度和父边编号
void dfs(int u, int p, int d)
{
    parent[u] = p;
    depth[u] = d;
    for (size_t i = 0; i < adj[u].size(); ++i)
    {
        int v = adj[u][i].first, eid = adj[u][i].second;
        if (v == p)
            continue;
        edgeToParent[v] = eid;
        dfs(v, u, d + 1);
    }
}

// LCA初始化
void initLCA()
{
    parent.resize(V);
    depth.resize(V);
    edgeToParent.resize(V, -1);
    dfs(0, -1, 0);

    LOG = 1;
    while ((1 << LOG) <= V)
        LOG++;
    fa.assign(V, vector<int>(LOG, -1));
    for (int i = 0; i < V; ++i)
        fa[i][0] = parent[i];
    for (int k = 1; k < LOG; ++k)
    {
        for (int i = 0; i < V; ++i)
        {
            if (fa[i][k - 1] != -1)
                fa[i][k] = fa[fa[i][k - 1]][k - 1];
        }
    }
}

// 计算LCA
int LCA(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    for (int k = LOG - 1; k >= 0; --k)
    {
        if (fa[u][k] != -1 && depth[fa[u][k]] >= depth[v])
        {
            u = fa[u][k];
        }
    }
    if (u == v)
        return u;
    for (int k = LOG - 1; k >= 0; --k)
    {
        if (fa[u][k] != -1 && fa[u][k] != fa[v][k])
        {
            u = fa[u][k];
            v = fa[v][k];
        }
    }
    return parent[u];
}

// 标记u到anc路径上的树边非桥
void markPath(int u, int anc, vector<bool> &visited)
{
    while (u != anc)
    {
        int eid = edgeToParent[u];
        visited[eid] = true;
        u = parent[u];
    }
}

// 构建生成树，返回树边编号列表，构建邻接表
vector<int> buildSpanningTree()
{
    UnionFind uf(V);
    adj.assign(V, vector<pair<int, int>>());
    vector<int> treeEdges;
    for (int i = 0; i < E; ++i)
    {
        int u = edges[i].first;
        int v = edges[i].second;
        if (uf.unite(u, v))
        {
            treeEdges.push_back(i);
            adj[u].push_back(make_pair(v, i));
            adj[v].push_back(make_pair(u, i));
        }
    }
    return treeEdges;
}

// LCA + 路径标记判断桥的数量
int findBridgesLCA(const vector<int> &treeEdges)
{
    initLCA();

    vector<bool> visited(E, false);
    // 对非树边，标记路径上的树边非桥
    for (int i = 0; i < E; ++i)
    {
        if (binary_search(treeEdges.begin(), treeEdges.end(), i))
            continue;
        int u = edges[i].first;
        int v = edges[i].second;
        int w = LCA(u, v);
        markPath(u, w, visited);
        markPath(v, w, visited);
    }

    int bridgeCount = 0;
    for (size_t i = 0; i < treeEdges.size(); ++i)
    {
        if (!visited[treeEdges[i]])
            bridgeCount++;
    }
    return bridgeCount;
}

int main()
{
    // 选择用文件读取还是随机生成：
    readFile("largeG.txt");
    // generateRandomGraph(1000, 2000);

    vector<int> treeEdges = buildSpanningTree();
    sort(treeEdges.begin(), treeEdges.end()); // binary_search需要

    clock_t start = clock();
    int bridgeCount = findBridgesLCA(treeEdges);
    clock_t end = clock();

    cout << "Bridge count: " << bridgeCount << endl;
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    return 0;
}
