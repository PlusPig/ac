#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
#define maxs 1000
#define games 162

int res[maxs][maxs], capacity[maxs][maxs]; // ��������
int parent[maxs], visited[maxs];           // bfs
vector<int> connected[maxs];               // �ڽӱ�
int win[maxs], leftnum[maxs];              // Ӯ�õģ���ʣ�µı���
int V;                                     // �ܵ���

bool bfs(int source, int sink) // �����㣬��������·�ϵ���С��������
{
    memset(parent, -1, sizeof(parent));
    memset(visited, 0, sizeof(visited));
    queue<int> que;
    que.push(source);
    visited[source] = 1;

    while (!que.empty())
    {
        int u = que.front();
        que.pop();

        for (int v : connected[u])
        {
            // ��ǰû�б������������ҵ�ǰ�������ڵ�ǰ����
            if (!visited[v] && res[u][v] > 0)
            {
                visited[v] = 1;
                parent[v] = u;
                if (v == sink)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int Edmonds_Karp(int source, int sink) // ����Ѱ��·��
{
    int total_flow = 0;

    while (bfs(source, sink))
    {
        int path_flow = INF;
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            path_flow = min(path_flow, res[u][v]);
        }
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            res[u][v] -= path_flow;
            res[v][u] += path_flow;
        } // ���²�������
        total_flow += path_flow;
    }
    return total_flow;
}

int main() // ��װ�ɽṹ������
{
    // �����ʼ��
    int n;
    string str;
    ifstream ifs("D:\\edge downlode anything\\baseball\\teams4.txt"); // ������ļ�
    ifs >> n;
    vector<string> teamname(n);
    memset(res, 0, sizeof(res));
    memset(win, 0, sizeof(win));
    memset(leftnum, 0, sizeof(leftnum));

    for (int i = 0; i < n; i++)
    {
        int dummy;
        ifs >> teamname[i] >> win[i] >> dummy >> leftnum[i];
        for (int j = 0; j < n; j++)
        {
            ifs >> capacity[i][j];
        }
    }

    double totaltime = 0;
    for (int winteam = 0; winteam < n; winteam++)
    {
        for (int i = 0; i < maxs; i++)
            connected[i].clear();

        int gamenum = 0;
        vector<pair<int, int>> gamepair;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (i != winteam && j != winteam && capacity[i][j] > 0)
                {
                    gamepair.push_back({i, j});
                }
            }
        }

        int gameNodeStart = 1;
        int teamNodeStart = gameNodeStart + gamepair.size();
        int sink = teamNodeStart + n - 1;
        V = sink + 1;

        memset(res, 0, sizeof(res));

        int line = win[winteam] + leftnum[winteam];
        int totalGames = 0;

        // ��Դ�㵽ÿ�������ڵ�
        for (int i = 0; i < gamepair.size(); i++)
        {
            int gameNode = gameNodeStart + i;
            int team1 = gamepair[i].first;
            int team2 = gamepair[i].second;
            int cap = capacity[team1][team2];

            res[0][gameNode] = cap;

            connected[0].push_back(gameNode);
            connected[gameNode].push_back(0);

            // �����ڵ������Ӧ��������
            int t1Node = teamNodeStart + (team1 > winteam ? team1 - 1 : team1);
            int t2Node = teamNodeStart + (team2 > winteam ? team2 - 1 : team2);
            res[gameNode][t1Node] = INT_MAX;
            res[gameNode][t2Node] = INT_MAX;

            connected[gameNode].push_back(t1Node);
            connected[gameNode].push_back(t2Node);
            connected[t1Node].push_back(gameNode);
            connected[t2Node].push_back(gameNode);

            totalGames += cap;
        }

        // ��������ڵ�������
        for (int i = 0; i < n; i++)
        {
            if (i == winteam)
                continue;
            int teamNode = teamNodeStart + (i > winteam ? i - 1 : i);
            int maxWin = line - win[i];
            maxWin = min(maxWin, leftnum[i]);
            res[teamNode][sink] = maxWin;

            connected[teamNode].push_back(sink);
            connected[sink].push_back(teamNode);
        }

        auto start = chrono::steady_clock::now();
        int result = Edmonds_Karp(0, sink);
        auto end = chrono::steady_clock::now();

        if (result == totalGames)
            cout << teamname[winteam] << " ���Ի�ʤ������� = " << result << endl;

        totaltime += chrono::duration<double, milli>(end - start).count();
    }
    cout << "�ܺ�ʱ: " << totaltime << " ms" << endl;
    return 0;
}