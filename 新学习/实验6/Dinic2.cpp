#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>
#include <queue>
using namespace std;

const int INF = 1e9;

// Dinic变量
vector<vector<int>> res, connected;
vector<int> level, ptr;
int V, S, T;

bool bfs()
{
    level.assign(V, -1);
    queue<int> q;
    q.push(S);
    level[S] = 0;
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
    return level[T] != -1;
}

int dfs(int u, int pushed)
{
    if (u == T || pushed == 0)
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

int maxflow(int s, int t)
{
    S = s;
    T = t;
    int flow = 0;
    while (bfs())
    {
        ptr.assign(V, 0);
        int pushed;
        while ((pushed = dfs(S, INF)) > 0)
            flow += pushed;
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
    int MAXV = n * n + n + 2;

    for (int winteam = 0; winteam < n; winteam++)
    {
        vector<pair<int, int>> games; // 记录比赛是谁
        games.push_back({-1, -1});    // 占位，比赛编号从1开始
        int gameidx = 1;
        int sum = 0;

        // 初始化Dinic变量
        V = MAXV;
        res.assign(V, vector<int>(V, 0));
        connected.assign(V, vector<int>());
        level.assign(V, 0);
        ptr.assign(V, 0);

        // 源点编号0，比赛节点gameidx
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (i != winteam && j != winteam && capacity[i][j] > 0)
                {
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
        int team_base = num_games + 1;
        int team_count = n - 1;
        int sink = team_base + team_count;
        V = sink + 1; // 实际用节点数

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

        // 计时
        auto startTime = chrono::steady_clock::now();
        int result = maxflow(0, sink);
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