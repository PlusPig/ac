#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <ctime>

using namespace std;

// ���鼯
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

// ȫ�ֱ���
int V, E;
vector<pair<int, int>> edges;
vector<vector<pair<int, int>>> adj; // �ڽӱ���ߺͱ߱��
vector<int> parent, depth, edgeToParent;
int LOG;
vector<vector<int>> fa;

// ��ȡ�ļ�����
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

// ���ͼ���ɺ���
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

// DFS��ʼ��������Ⱥ͸��߱��
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

// LCA��ʼ��
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

// ����LCA
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

// ���u��anc·���ϵ����߷���
void markPath(int u, int anc, vector<bool> &visited)
{
    while (u != anc)
    {
        int eid = edgeToParent[u];
        visited[eid] = true;
        u = parent[u];
    }
}

// �������������������߱���б������ڽӱ�
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

// LCA + ·������ж��ŵ�����
int findBridgesLCA(const vector<int> &treeEdges)
{
    initLCA();

    vector<bool> visited(E, false);
    // �Է����ߣ����·���ϵ����߷���
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
    // ѡ�����ļ���ȡ����������ɣ�
    readFile("largeG.txt");
    // generateRandomGraph(1000, 2000);

    vector<int> treeEdges = buildSpanningTree();
    sort(treeEdges.begin(), treeEdges.end()); // binary_search��Ҫ

    clock_t start = clock();
    int bridgeCount = findBridgesLCA(treeEdges);
    clock_t end = clock();

    cout << "Bridge count: " << bridgeCount << endl;
    cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;

    return 0;
}
