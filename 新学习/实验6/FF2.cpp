#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define maxs 10000
int V;
vector<bool> visited;
vector<int> parent, unplay, win;
vector<vector<int>> res, capacity;
vector<string> teamname;
vector<vector<int>> connected;

int dfs(int u, int maxflow)
{
    visited[u] = true;
    if (u == V - 1)
    {
        return maxflow;
    }

    for (int v : connected[u])
    {
        if (!visited[v] && res[u][v] > 0)
        {
            maxflow = dfs(v, min(maxflow, res[u][v])); // 更新最小值同时递归
            if (visited[V - 1])                        // 只有到了汇点才可以更新残量网络
            {
                res[u][v] -= maxflow;
                res[v][u] += maxflow;
                return maxflow;
            }
        }
    }
    return 0;
}

int ff()
{
    int maxflow_ff = 0; // 从源点能到汇点的所有最大流
    while (true)
    {
        // memset(visited, false, sizeof(visited)); // 每次都要初始化
        visited.assign(V, false);
        int maxflow = dfs(0, INT_MAX);
        if (maxflow > 0)
        {
            maxflow_ff += maxflow;
        }
        else
            break;
    }
    return maxflow_ff;
}

int main()
{
    int n;
    string str;
    ifstream ifs("D:\\edge downlode anything\\baseball\\teams32.txt");
    ifs >> n;
    V = n * n + n + 2;

    // memset(res, 0, sizeof(res));
    // memset(win, 0, sizeof(win));
    // memset(unplay, 0, sizeof(unplay));
    res.resize(V);
    win.resize(V);
    unplay.resize(V);
    visited.resize(V);
    teamname.resize(V);
    connected.resize(V);
    res.resize(V, vector<int>(V, 0));
    capacity.resize(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        int dummy;
        ifs >> teamname[i] >> win[i] >> dummy >> unplay[i];
        for (int j = 0; j < n; j++)
        {
            ifs >> capacity[i][j];
        }
    }
    // 初始化结束了
    double sumtime = 0;
    for (int winteam = 0; winteam < n; winteam++)
    {
        connected.clear();
        connected.resize(V);
        res.assign(V, vector<int>(V, 0)); // 清空残余网络
        // memset(res, 0, sizeof(res));  // 清空残量网络
        vector<pair<int, int>> games; // 记录比赛是谁
        games.push_back({-1, -1});    // 手动对齐比赛下标
        int gameindex = 1;            // 表示比赛的下标，因为0是源点，比赛只能从1开始
        int sum = 0;                  // 记录所需要的总流量

        // 然后是更新残量网络
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (i != winteam && j != winteam && capacity[i][j] > 0)
                {
                    connected[0].push_back(gameindex); // 源节点连接比赛
                    connected[gameindex].push_back(0); // 111111111111
                    res[0][gameindex++] = capacity[i][j];
                    sum += capacity[i][j];
                    games.push_back({i, j});
                }
            }
        }

        // 现在是更新队伍和汇点的链接
        int resindex = gameindex + n;              // 获取汇点的节点下标
        int line = win[winteam] + unplay[winteam]; // 总比赛数
        for (int i = 0; i < n; i++)
        {
            if (i == winteam)
                continue;
            int cap = min(unplay[i], line - win[i]); // 最多能赢的场数
            // 即不超过剩下比赛，也不超过冠军点
            // 同时更新邻接表以及残量矩阵
            if (i < winteam)
            {
                res[gameindex + i][resindex - 1] = cap;
                connected[gameindex + i].push_back(resindex - 1);
                connected[resindex - 1].push_back(gameindex + i);
            }
            else
            {
                res[gameindex + i - 1][resindex - 1] = cap;
                connected[gameindex + i - 1].push_back(resindex - 1);
                connected[resindex - 1].push_back(gameindex + i - 1);
            }
        }

        // 现在是更新比赛和队伍的链接
        for (int i = 1; i < games.size(); i++) // 前面已经手动对齐比赛下标
        {
            int t1 = games[i].first, t2 = games[i].second;
            // t1,t2还是原始的team下标
            if (t1 < winteam)
            {
                res[i][t1 + gameindex] = sum; // 不需要控制流量
                connected[i].push_back(t1 + gameindex);
                connected[t1 + gameindex].push_back(i);
            }
            else
            {
                res[i][t1 + gameindex - 1] = sum;
                connected[i].push_back(t1 + gameindex - 1);
                connected[t1 + gameindex - 1].push_back(i);
            }
            if (t2 < winteam)
            {
                res[i][t2 + gameindex] = sum; // gameindex表示first team
                connected[i].push_back(t2 + gameindex);
                connected[t2 + gameindex].push_back(i);
            }
            else
            {
                res[i][t2 + gameindex - 1] = sum;
                connected[i].push_back(t2 + gameindex - 1);
                connected[t2 + gameindex - 1].push_back(i);
            }
        }
        V = resindex;

        // 计时部分
        std::chrono::duration<int, std::milli> duration1(20);
        auto startTime = chrono::steady_clock::now();
        int result = ff();
        auto endTime = std::chrono::steady_clock::now();
        auto time = endTime - startTime;
        if (result == sum)
        {
            cout << teamname[winteam] << " can win with maxflow: " << result << endl;
        }
        sumtime += (double)(time.count()) / (1000000.0);
    }
    cout << "total time: " << sumtime << "ms" << endl;
}