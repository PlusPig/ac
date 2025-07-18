#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stack>
#include <queue>
#include <cmath>
#include <cctype>
#include <chrono>

using namespace std;
using namespace std::chrono;

inline int readInt(ifstream &in)
{
    int x = 0;
    char c;
    while (in.get(c) && !isdigit(c))
        ;
    for (; isdigit(c); in.get(c))
    {
        x = x * 10 + c - '0';
    }
    return x;
}

class UnionFind
{
    vector<int> parent;

public:
    UnionFind(int n) : parent(n)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        while (parent[x] != x)
        {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool unite(int x, int y)
    {
        int rx = find(x), ry = find(y);
        if (rx == ry)
            return false;
        parent[ry] = rx;
        return true;
    }
};

int V, E, LOG;
vector<pair<int, int>> edges;
vector<vector<pair<int, int>>> adj;
vector<int> depth, parent, edgeToParent;
vector<int> compRoot;
vector<vector<int>> buckets;
vector<int> cover;
vector<vector<int>> fa;
vector<int> logTable;
vector<bool> isTreeEdge;

void readTextFile(const string &filename)
{
    ifstream in(filename);
    in >> V >> E;
    edges.resize(E);
    for (int i = 0; i < E; ++i)
    {
        in >> edges[i].first >> edges[i].second;
        // edges[i].first--;
        // edges[i].second--;
    }
    in.close();
}

void dfsIterative(int root)
{
    depth.assign(V, -1);
    parent.assign(V, -1);
    edgeToParent.assign(V, -1);
    stack<int> st;
    st.push(root);
    depth[root] = 0;
    parent[root] = -1;

    while (!st.empty())
    {
        int u = st.top();
        st.pop();
        for (const auto &edge : adj[u])
        {
            int v = edge.first;
            if (v == parent[u])
                continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            edgeToParent[v] = edge.second;
            st.push(v);
        }
    }
}

void initLogTable(int maxDepth)
{
    logTable.resize(maxDepth + 2);
    logTable[0] = -1;
    for (int i = 1; i <= maxDepth + 1; i++)
    {
        logTable[i] = logTable[i >> 1] + 1;
    }
}

void initLCA(const vector<int> &nodes)
{
    int max_depth = 0;
    for (int u : nodes)
    {
        if (depth[u] > max_depth)
            max_depth = depth[u];
    }

    initLogTable(max_depth);
    LOG = max_depth > 0 ? logTable[max_depth] + 1 : 1;
    fa.assign(V, vector<int>(LOG + 1, -1));

    for (int u : nodes)
        fa[u][0] = parent[u];

    for (int j = 1; j <= LOG; ++j)
    {
        for (int u : nodes)
        {
            if (fa[u][j - 1] != -1)
                fa[u][j] = fa[fa[u][j - 1]][j - 1];
        }
    }
}

inline int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);

    int diff = depth[u] - depth[v];
    while (diff)
    {
        int step = logTable[diff & -diff];
        u = fa[u][step];
        diff ^= diff & -diff;
    }

    if (u == v)
        return u;

    for (int i = LOG; i >= 0; --i)
    {
        if (fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int findBridges()
{
    UnionFind uf(V);
    adj.resize(V);
    isTreeEdge.assign(E, false);

    for (int i = 0; i < E; ++i)
    {
        int u = edges[i].first, v = edges[i].second;
        if (uf.unite(u, v))
        {
            isTreeEdge[i] = true;
            adj[u].emplace_back(v, i);
            adj[v].emplace_back(u, i);
        }
    }

    compRoot.resize(V);
    for (int i = 0; i < V; ++i)
        compRoot[i] = uf.find(i);

    buckets.assign(V, {});
    for (int i = 0; i < V; ++i)
        buckets[compRoot[i]].push_back(i);

    cover.assign(V, 0);
    int bridgeCount = 0;

    for (int root = 0; root < V; ++root)
    {
        if (buckets[root].empty())
            continue;

        dfsIterative(root);

        if (buckets[root].size() > 1)
        {
            int maxDepth = 0;
            for (int u : buckets[root])
            {
                if (depth[u] > maxDepth)
                    maxDepth = depth[u];
            }
            initLCA(buckets[root]);

            vector<vector<int>> depthBuckets(maxDepth + 1);
            for (int u : buckets[root])
            {
                depthBuckets[depth[u]].push_back(u);
            }

            for (int i = 0; i < E; ++i)
            {
                if (isTreeEdge[i])
                    continue;
                int u = edges[i].first, v = edges[i].second;
                if (compRoot[u] != root || compRoot[v] != root)
                    continue;

                int w = lca(u, v);
                cover[u]++;
                cover[v]++;
                if (w != -1)
                    cover[w] -= 2;
            }

            for (int d = maxDepth; d > 0; --d)
            {
                for (int u : depthBuckets[d])
                {
                    if (parent[u] != -1)
                    {
                        cover[parent[u]] += cover[u];
                    }
                }
            }

            // 统计桥
            for (int u : buckets[root])
            {
                if (u != root && cover[u] == 0)
                {
                    bridgeCount++;
                }
            }
        }
    }

    return bridgeCount;
}

int main()
{
    // 读取图数据
    readTextFile("largeG.txt");

    auto start = high_resolution_clock::now();
    int bridgeCount = findBridges();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Total bridges: " << bridgeCount << endl;
    cout << "Time: " << duration.count() << " ms" << endl;

    return 0;
}