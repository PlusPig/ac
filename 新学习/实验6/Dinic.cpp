#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <queue>
using namespace std;

const int INF = 1e9;

struct Dinic
{
    int V, s, t;
    vector<vector<int>> res, connected;
    vector<int> level, ptr;

    Dinic(int V_) : V(V_), res(V_, vector<int>(V_, 0)), connected(V_) {}

    void add_edge(int u, int v, int cap)
    {
        res[u][v] = cap;
        connected[u].push_back(v);
        connected[v].push_back(u); // 反向边用于残量网络
    }

    bool bfs()
    {
        level.assign(V, -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : connected[u])
            {
                if (level[v] == -1 && res[u][v] > 0)
                {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int pushed)
    {
        if (u == t || pushed == 0)
            return pushed;
        for (int &cid = ptr[u]; cid < (int)connected[u].size(); ++cid)
        {
            int v = connected[u][cid];
            if (level[v] == level[u] + 1 && res[u][v] > 0)
            {
                int tr = dfs(v, min(pushed, res[u][v]));
                if (tr > 0)
                {
                    res[u][v] -= tr;
                    res[v][u] += tr;
                    return tr;
                }
            }
        }
        return 0;
    }

    int maxflow(int s_, int t_)
    {
        s = s_;
        t = t_;
        int flow = 0;
        while (bfs())
        {
            ptr.assign(V, 0);
            int pushed;
            while ((pushed = dfs(s, INF)) > 0)
                flow += pushed;
        }
        return flow;
    }
};

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
    int MAXV = n * n + n + 2;

    for (int winteam = 0; winteam < n; winteam++)
    {
        vector<pair<int, int>> games; // 记录比赛是谁
        games.push_back({-1, -1});    // 占位，比赛编号从1开始
        int gameidx = 1;
        int sum = 0;

        // 1. 构建图
        // Dinic实例
        Dinic dinic(MAXV);

        // 源点编号0，比赛节点gameidx
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (i != winteam && j != winteam && capacity[i][j] > 0)
                {
                    dinic.add_edge(0, gameidx, capacity[i][j]);
                    games.push_back({i, j});
                    sum += capacity[i][j];
                    gameidx++;
                }
            }
        }
        int num_games = gameidx - 1;
        int team_base = num_games + 1;
        int team_count = n - 1;
        int sink = team_base + team_count;
        int V = sink + 1;

        // 比赛节点到队伍节点
        for (int k = 1; k <= num_games; k++)
        {
            int t1 = games[k].first, t2 = games[k].second;
            int idx1 = (t1 < winteam) ? team_base + t1 : team_base + t1 - 1;
            int idx2 = (t2 < winteam) ? team_base + t2 : team_base + t2 - 1;
            dinic.add_edge(k, idx1, INF);
            dinic.add_edge(k, idx2, INF);
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
            dinic.add_edge(idx, sink, cap);
        }

        // 计时
        auto startTime = chrono::steady_clock::now();
        int result = dinic.maxflow(0, sink);
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