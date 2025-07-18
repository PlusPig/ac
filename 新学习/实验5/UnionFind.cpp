#include <bits/stdc++.h>
using namespace std;

// ��װ���鼯��
class UnionFind
{
private:
    vector<int> parent, rank; // parent�����ڵ㣬rank������ʾ�ڵ�ĸ߶�
    int components;

public:
    UnionFind(int n) : parent(n), rank(n, 0), components(n) // init
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) // ������ǰ��Ⱥϲ������ӽڵ�ֱ�Ӽ��뵽���ڵ���
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) // ������ǰ��Ⱥϲ����Ż����ĸ߶�
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

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }

    int count() const
    {
        return components;
    }
};

int V, E;
vector<pair<int, int>> edges;

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

    set<pair<int, int>> edgeSet; // ������¼�ظ���

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

// �ж�ɾ���� i ���ߺ��Ƿ�����
bool isBridge(int skipIdx) // ����Ǽӵģ�dfs�Ǽ���
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

int main()
{
    read(1000, 6000); // ��ȡ

    int bridgeCount = 0;
    clock_t start_T = clock();

    for (int i = 0; i < E; ++i) // ѭ����ȡÿһ����
    {
        if (isBridge(i))
            bridgeCount++;
    }
    clock_t end_T = clock();

    cout << fixed << setprecision(3) << (double)(end_T - start_T) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << "bridge nums: " << bridgeCount << endl;
    return 0;
}
