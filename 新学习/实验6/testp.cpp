#include <iostream>
#include <cmath>
#include <queue>
#include <fstream>
#include <vector>
#include <utility>
#include <chrono>
using namespace std;
int V;

int **residual;               // 残余流量
int *pre;                     // 记录父节点
int *vis;                     // 未知
int **myarr;                  //
int *victory, **arr, *noplay; // arr记录capacity
string *name;
int *EK_queue; // 不知道

int BFS()
{
    int front = 0, tail = -1;
    EK_queue[++tail] = 0;
    vis[0] = 1;
    while (front <= tail)
    {
        int temp = EK_queue[front++];
        for (int node = 1; node <= myarr[temp][0]; node++)
        {
            int i = myarr[temp][node];
            if (vis[i] == 0 && residual[temp][i] > 0)
            {
                EK_queue[++tail] = i;
                pre[i] = temp;
                vis[i] = 1;
                if (vis[V - 1] == 1)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int maxflow()
{
    int EK_flow = 0;
    while (1)
    {
        for (int i = 0; i < V; i++)
        {
            vis[i] = 0, pre[i] = -1;
        }
        int flag = BFS();
        //	cout<<flag<<endl;
        if (flag == 0)
            break;
        int temp_flow = INT_MAX;
        for (int i = V - 1; i != 0; i = pre[i])
        {
            temp_flow = min(temp_flow, residual[pre[i]][i]);
        }
        int i = V - 1;
        while (i != 0)
        {
            residual[i][pre[i]] += temp_flow;
            residual[pre[i]][i] -= temp_flow;
            i = pre[i];
        }
        EK_flow += temp_flow;
    }
    return EK_flow;
}

int main()
{
    ifstream file("D:\\edge downlode anything\\baseball\\teams32.txt");
    int n;
    file >> n;
    V = n * n + n + 2;
    residual = new int *[V];
    pre = new int[V];
    EK_queue = new int[V];
    vis = new int[V];
    myarr = new int *[V];
    for (int i = 0; i < V; i++)
        myarr[i] = new int[V];
    for (int i = 0; i < V; i++)
    {
        myarr[i][0] = 0;
    }
    victory = new int[n], noplay = new int[n], name = new string[n], arr = new int *[n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[n];
    for (int i = 0; i < V; i++)
    {
        residual[i] = new int[V];
    }

    int str2;
    for (int i = 0; i < n; i++)
    {
        file >> name[i] >> victory[i] >> str2 >> noplay[i];
        for (int j = 0; j < n; j++)
        {
            file >> arr[i][j];
        }
    }

    double sumtime = 0;
    for (int winteam = 0; winteam < n; winteam++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                residual[i][j] = 0;
            }
        }
        vector<pair<int, int>> node;
        node.push_back({-1, -1});
        int cnt = 1, sum = 0;
        int line = victory[winteam] + noplay[winteam];
        for (int i = 0; i < n; i++)
        {
            if (i == winteam)
                continue;
            for (int j = i + 1; j < n; j++)
            {
                if (j == winteam)
                    continue;
                if (arr[i][j] > 0)
                {
                    myarr[0][++myarr[0][0]] = cnt;
                    residual[0][cnt++] = arr[i][j];
                    sum += arr[i][j];
                    node.push_back({i, j});
                }
            }
        }
        int tmp = cnt;
        cnt = cnt + n;
        for (int i = 0; i < n; i++)
        {

            if (i > winteam)
                residual[tmp + i - 1][cnt - 1] = min(line - victory[i], noplay[i]), myarr[tmp + i - 1][++myarr[tmp + i - 1][0]] = cnt - 1;
            else
                residual[tmp + i][cnt - 1] = min(line - victory[i], noplay[i]), myarr[tmp + i][++myarr[tmp + i][0]] = cnt - 1;
        }

        for (int i = 1; i < node.size(); i++)
        {
            int t1 = node[i].first, t2 = node[i].second;
            if (t1 > winteam)
                residual[i][tmp + t1 - 1] = sum, myarr[i][++myarr[i][0]] = tmp + t1 - 1;
            else
                residual[i][tmp + t1] = sum, myarr[i][++myarr[i][0]] = tmp + t1;

            if (t2 > winteam)
                residual[i][tmp + t2 - 1] = sum, myarr[i][++myarr[i][0]] = tmp + t2 - 1;
            else
                residual[i][tmp + t2] = sum, myarr[i][++myarr[i][0]] = tmp + t2;
        }
        V = cnt;

        std::chrono::duration<int, std::milli> duration1(20);
        auto startTime = chrono::steady_clock::now();
        int result = maxflow();
        auto endTime = std::chrono::steady_clock::now();
        auto time = endTime - startTime;
        if (result == sum)
        {
            cout << name[winteam] << "可以获胜，"
                 << "且最大流为：" << result << endl;
        }
        sumtime += (double)(time.count()) / (1000000.0);
    }
    cout << "total time: " << sumtime / 10 << "ms" << endl;

    return 0;
}
