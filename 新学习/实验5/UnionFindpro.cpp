#include <bits/stdc++.h>
using namespace std;

// ------------------ 并查集封装 ------------------
class UnionFind
{
private:
    vector<int> parent, rank;
    int components;

public:
    UnionFind(int n) : parent(n), rank(n, 0), components(n)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // 路径压缩
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int fx = find(x), fy = find(y);
        if (fx == fy)
            return false;
        if (rank[fx] < rank[fy])
        {
            parent[fx] = fy;
        }
        else
        {
            parent[fy] = fx;
            if (rank[fx] == rank[fy])
                rank[fx]++;
        }
        components--;
        return true;
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }

    int count() const
    {
        return components;
    }
};

// ------------------ 全局变量 ------------------
int V, E;
vector<pair<int, int>> edges;
vector<int> treeEdgeIdx; // 生成树边的编号

// ------------------ 读入函数 ------------------
void read(const string &filename = "mediumDG.txt")
{
    ifstream infile(filename);
    infile >> V >> E;
    edges.clear();
    for (int i = 0; i < E; ++i)
    {
        int u, v;
        infile >> u >> v;
        edges.emplace_back(u, v);
    }
    infile.close();
}

void read(int a, int b)
{
    V = a, E = b;
    random_device rd;
    unsigned long long seed = rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed);
    uniform_int_distribution<int> dist(0, V - 1);

    set<pair<int, int>> edgeSet; // 用来记录重复边

    while (edges.size() < E)
    {
        int u = dist(gen);
        int v = dist(gen);

        if (u == v)
            continue;

        if (edgeSet.count({u, v}) || edgeSet.count({v, u}))
            continue;

        edgeSet.insert({u, v});
        edges.emplace_back(u, v);
    }
}
// ------------------ 判断删掉某条边是否是桥 ------------------
bool isBridge(int skipIdx)
{
    UnionFind uf(V);
    for (int i = 0; i < edges.size(); ++i)
    {
        if (i == skipIdx)
            continue;
        uf.unite(edges[i].first, edges[i].second);
    }
    return !uf.connected(edges[skipIdx].first, edges[skipIdx].second);
}

// ------------------ 主程序 ------------------
int main()
{
    read(); // 读图
    clock_t start_T = clock();

    // Step 1: 构建生成树
    UnionFind uf(V);
    treeEdgeIdx.clear();

    for (int i = 0; i < E; ++i)
    {
        if (uf.unite(edges[i].first, edges[i].second))
        {
            treeEdgeIdx.push_back(i); // 只记录生成树边
        }
    }

    // Step 2: 只判断生成树中的边是否是桥
    int bridgeCount = 0;
    for (int idx : treeEdgeIdx)
    {
        if (isBridge(idx))
            bridgeCount++;
    }

    clock_t end_T = clock();

    cout << fixed << setprecision(3)
         << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << "bridge nums: " << bridgeCount << endl;

    return 0;
}
