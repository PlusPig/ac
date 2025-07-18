#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
#include <climits>
using namespace std;

// ȫ�ֱ���
int V;                          // �ܵ���
vector<vector<int>> residual;   // ��������
vector<vector<int>> adj;        // �ڽӱ����� BFS��
vector<int> pre, vis, EK_queue; // BFS ��������
vector<int> victory, noplay;    // ÿ֧���鵱ǰʤ����ʣ�������
vector<string> name;            // ������
vector<vector<int>> matchLeft;  // ÿ�Զ���ʣ�������

// �������������Ѱ������·��
bool BFS(int source, int sink)
{
    fill(vis.begin(), vis.end(), 0);
    fill(pre.begin(), pre.end(), -1);

    int front = 0, tail = 0;
    EK_queue[tail++] = source;
    vis[source] = 1;

    while (front < tail)
    {
        int u = EK_queue[front++];
        for (int v : adj[u])
        {
            if (!vis[v] && residual[u][v] > 0)
            {
                vis[v] = 1;
                pre[v] = u;
                if (v == sink)
                    return true;
                EK_queue[tail++] = v;
            }
        }
    }
    return false;
}

// Edmonds-Karp �㷨�������
int maxflow(int source, int sink)
{
    int total_flow = 0;
    while (BFS(source, sink))
    {
        int path_flow = INT_MAX;
        for (int v = sink; v != source; v = pre[v])
        {
            int u = pre[v];
            path_flow = min(path_flow, residual[u][v]);
        }
        for (int v = sink; v != source; v = pre[v])
        {
            int u = pre[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
        total_flow += path_flow;
    }
    return total_flow;
}

int main()
{
    ifstream file("D:\\edge downlode anything\\baseball\\teams4.txt");
    int n;
    file >> n;

    victory.resize(n);
    noplay.resize(n);
    name.resize(n);
    matchLeft.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        int dummy;
        file >> name[i] >> victory[i] >> dummy >> noplay[i];
        for (int j = 0; j < n; j++)
        {
            file >> matchLeft[i][j];
        }
    }

    double totalTime = 0;
    for (int target = 0; target < n; ++target)
    {
        // ͼ���ܵ������㣺source + game nodes + team nodes + sink
        int gameCount = 0;
        vector<pair<int, int>> gamePairs;

        // ÿһ�ζ�Ҫ������ӱ�
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (i != target && j != target && matchLeft[i][j] > 0)
                    gamePairs.push_back({i, j});

        int gameNodeStart = 1;
        int teamNodeStart = gameNodeStart + gamePairs.size();
        int sink = teamNodeStart + n - 1;
        V = sink + 1;

        residual.assign(V, vector<int>(V, 0));
        adj.assign(V, vector<int>());
        pre.assign(V, -1);
        vis.assign(V, 0);
        EK_queue.assign(V, 0);

        int line = victory[target] + noplay[target];
        int totalGames = 0;

        // ��Դ�㵽ÿ�������ڵ�
        for (int i = 0; i < gamePairs.size(); i++)
        {
            int gameNode = gameNodeStart + i;
            int team1 = gamePairs[i].first;
            int team2 = gamePairs[i].second;
            int cap = matchLeft[team1][team2];

            residual[0][gameNode] = cap;
            adj[0].push_back(gameNode);
            adj[gameNode].push_back(0);

            // �����ڵ������Ӧ��������
            int t1Node = teamNodeStart + (team1 > target ? team1 - 1 : team1);
            int t2Node = teamNodeStart + (team2 > target ? team2 - 1 : team2);
            residual[gameNode][t1Node] = INT_MAX;
            residual[gameNode][t2Node] = INT_MAX;

            adj[gameNode].push_back(t1Node);
            adj[gameNode].push_back(t2Node);
            adj[t1Node].push_back(gameNode);
            adj[t2Node].push_back(gameNode);

            totalGames += cap;
        }

        // ��������ڵ�������
        for (int i = 0; i < n; i++)
        {
            if (i == target)
                continue;
            int teamNode = teamNodeStart + (i > target ? i - 1 : i);
            int maxWin = line - victory[i];
            maxWin = min(maxWin, noplay[i]);
            residual[teamNode][sink] = maxWin;

            adj[teamNode].push_back(sink);
            adj[sink].push_back(teamNode);
        }

        auto start = chrono::steady_clock::now();
        int result = maxflow(0, sink);
        auto end = chrono::steady_clock::now();

        if (result == totalGames)
            cout << name[target] << " ���Ի�ʤ������� = " << result << endl;

        totalTime += chrono::duration<double, milli>(end - start).count();
    }

    cout << "�ܺ�ʱ: " << totalTime << " ms" << endl;
    return 0;
}
