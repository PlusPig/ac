#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <queue>
using namespace std;

const int INF = 1e9;

// Edmonds-Karp: BFS找增广路
int bfs(int s, int t, int V, vector<vector<int>> &res, vector<vector<int>> &connected, vector<int> &parent)
{
    fill(parent.begin(), parent.end(), -1);
    queue<pair<int, int>> q;
    q.push({s, INF});
    parent[s] = -2;
    while (!q.empty())
    {
        int u = q.front().first, flow = q.front().second;
        q.pop();
        for (int v : connected[u])
        {
            if (parent[v] == -1 && res[u][v] > 0)
            {
                parent[v] = u;
                int new_flow = min(flow, res[u][v]);
                if (v == t)
                    return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t, int V, vector<vector<int>> &res, vector<vector<int>> &connected)
{
    int flow = 0, new_flow;
    vector<int> parent(V, -1);
    while ((new_flow = bfs(s, t, V, res, connected, parent)) > 0)
    {
        flow += new_flow;
        int v = t;
        while (v != s)
        {
            int u = parent[v];
            res[u][v] -= new_flow;
            res[v][u] += new_flow;
            v = u;
        }
    }
    return flow;
}

void solve(string filename)
{
    int n, teamnum = 0;
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        cerr << "Failed to open file." << endl;
    }
    ifs >> n;

    vector<string> teamname(n);
    vector<int> win(n), unplay(n);
    vector<vector<int>> capacity(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        int dummy;
        ifs >> teamname[i] >> win[i] >> dummy >> unplay[i];
        for (int j = 0; j < n; j++)
        {
            ifs >> capacity[i][j];
        }
    }

    double sumtime = 0.0;
    // 最大需要的节点数
    int MAXV = n * n + n + 2;

    for (int winteam = 0; winteam < n; winteam++)
    {
        // 重新建图
        vector<vector<int>> res(MAXV, vector<int>(MAXV, 0));
        vector<vector<int>> connected(MAXV);

        vector<pair<int, int>> games; // 记录比赛是谁
        games.push_back({-1, -1});    // 占位，比赛编号从1开始
        int gameidx = 1;
        int sum = 0;
        // 比赛节点编号从1开始
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (i != winteam && j != winteam && capacity[i][j] > 0)
                {
                    // 源点编号0，比赛节点gameidx
                    res[0][gameidx] = capacity[i][j];
                    connected[0].push_back(gameidx);
                    connected[gameidx].push_back(0);
                    games.push_back({i, j});
                    sum += capacity[i][j];
                    gameidx++;
                }
            }
        }
        int num_games = gameidx - 1;
        // 队伍节点编号: num_games+1 ~ num_games+n (不含winteam)
        int team_base = num_games + 1;
        int team_count = n - 1;            // 不含winteam
        int sink = team_base + team_count; // 汇点
        int V = sink + 1;                  // 本次网络节点数

        // 比赛节点到队伍节点
        for (int k = 1; k <= num_games; k++)
        {
            int t1 = games[k].first, t2 = games[k].second;
            int idx1 = (t1 < winteam) ? team_base + t1 : team_base + t1 - 1;
            int idx2 = (t2 < winteam) ? team_base + t2 : team_base + t2 - 1;
            res[k][idx1] = INF;
            connected[k].push_back(idx1);
            connected[idx1].push_back(k);
            res[k][idx2] = INF;
            connected[k].push_back(idx2);
            connected[idx2].push_back(k);
        }
        // 队伍节点到汇点
        int line = win[winteam] + unplay[winteam];
        for (int i = 0; i < n; i++)
        {
            if (i == winteam)
                continue;
            int idx = (i < winteam) ? team_base + i : team_base + i - 1;
            int cap = line - win[i];
            if (cap < 0)
                cap = 0;
            res[idx][sink] = cap;
            connected[idx].push_back(sink);
            connected[sink].push_back(idx);
        }

        // 计时部分
        auto startTime = chrono::steady_clock::now();
        int result = maxflow(0, sink, V, res, connected);
        auto endTime = chrono::steady_clock::now();
        auto time = chrono::duration<double, milli>(endTime - startTime).count();
        sumtime += time;
        teamnum++;
    }
    cout << filename << "'s teamnum: " << teamnum;
    cout << " with total time: " << sumtime << "ms" << endl;
}
int main()
{
    string filenames[] = {
        "baseball/teams1.txt",
        "baseball/teams4.txt",
        "baseball/teams4a.txt",
        "baseball/teams4b.txt",
        "baseball/teams5.txt",
        "baseball/teams5a.txt",
        "baseball/teams5b.txt",
        "baseball/teams5c.txt",
        "baseball/teams7.txt",
        "baseball/teams8.txt",
        "baseball/teams10.txt",
        "baseball/teams12-allgames.txt",
        "baseball/teams12.txt",
        "baseball/teams24.txt",
        "baseball/teams29.txt",
        "baseball/teams30.txt",
        "baseball/teams32.txt",
        "baseball/teams36.txt",
        "baseball/teams42.txt",
        "baseball/teams48.txt",
        "baseball/teams50.txt",
        "baseball/teams54.txt",
        "baseball/teams60.txt",
    };

    for (const auto &filename : filenames)
    {
        cout << "filename: " << filename << endl; // 输出文件名
        solve(filename);
    }

    return 0;
}