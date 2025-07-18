#include <bits/stdc++.h>
using namespace std;

const int VERTEX = 450;
const int COLOUR = 5;

struct Node
{
    int color = 0;
    int degree = 0;
    int leftColours = COLOUR;
    bitset<COLOUR + 1> used;
};

vector<Node> nodes(VERTEX);
vector<int> connected[VERTEX];

int sum = 0;
clock_t start_time;

void read()
{
    ifstream ifs("le450_5a.txt");
    char c;
    int u, v;
    while (ifs >> c >> u >> v)
    {
        --u, --v;
        connected[u].push_back(v);
        connected[v].push_back(u);
        nodes[u].degree++;
        nodes[v].degree++;
    }
    ifs.close();
}

int select_node()
{
    int min_left = COLOUR + 1, max_deg = -1, idx = -1;
    for (int i = 0; i < VERTEX; ++i)
    {
        if (nodes[i].color != 0)
            continue;
        if (nodes[i].leftColours < min_left ||
            (nodes[i].leftColours == min_left && nodes[i].degree > max_deg))
        {
            min_left = nodes[i].leftColours;
            max_deg = nodes[i].degree;
            idx = i;
        }
    }
    return idx;
}

bool propagate(vector<pair<int, int>> &changed, vector<int> &assigned)
{
    queue<int> q;
    vector<bool> in_queue(VERTEX, false);

    for (int i = 0; i < VERTEX; ++i)
    {
        if (nodes[i].color == 0 && nodes[i].leftColours == 1)
        {
            q.push(i);
            in_queue[i] = true;
        }
    }

    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        if (nodes[v].color != 0)
            continue;

        int only_color = -1;
        for (int c = 1; c <= COLOUR; ++c)
        {
            if (!nodes[v].used[c])
            {
                only_color = c;
                break;
            }
        }
        if (only_color == -1)
            return false;

        nodes[v].color = only_color;
        assigned.push_back(v);

        for (int u : connected[v])
        {
            if (nodes[u].color == 0 && !nodes[u].used[only_color])
            {
                nodes[u].used[only_color] = true;
                nodes[u].leftColours--;
                changed.emplace_back(u, only_color);
                if (nodes[u].leftColours == 0)
                    return false;
                if (nodes[u].leftColours == 1 && !in_queue[u])
                {
                    q.push(u);
                    in_queue[u] = true;
                }
            }
        }
    }

    return true;
}

void dfs(int num)
{
    if (num == VERTEX)
    {
        sum++;
        if (sum == 1 || sum % 100 == 0)
            cout << "找到方案: " << sum << "，耗时: "
                 << (clock() - start_time) * 1000.0 / CLOCKS_PER_SEC << " ms" << endl;
        return;
    }

    int u = select_node();
    if (u == -1)
        return;

    for (int c = 1; c <= COLOUR; ++c)
    {
        if (nodes[u].used[c])
            continue;

        vector<Change> changes;

        // 设置当前节点u的颜色
        changes.push_back({u, Change::COLOR, c, nodes[u].color});
        nodes[u].color = c;

        bool valid = true;

        queue<int> propagation_queue;

        // 处理u的邻居
        for (int v : connected[u])
        {
            if (nodes[v].color != 0)
                continue;

            if (!nodes[v].used[c])
            {
                // 记录used和leftColours的修改
                changes.push_back({v, Change::USED, c, nodes[v].used[c]});
                nodes[v].used[c] = true;
                changes.push_back({v, Change::LEFT_COLOURS, nodes[v].leftColours - 1, nodes[v].leftColours});
                nodes[v].leftColours--;

                if (nodes[v].leftColours == 0)
                {
                    valid = false;
                    break;
                }

                if (nodes[v].leftColours == 1)
                {
                    // 找到唯一可用的颜色
                    int only_color = 0;
                    for (int clr = 1; clr <= COLOUR; ++clr)
                    {
                        if (!nodes[v].used[clr])
                        {
                            only_color = clr;
                            break;
                        }
                    }
                    if (only_color == 0)
                    {
                        valid = false;
                        break;
                    }
                    // 自动着色v
                    propagation_queue.push(v);
                    changes.push_back({v, Change::COLOR, only_color, nodes[v].color});
                    nodes[v].color = only_color;
                }
            }
        }

        if (!valid)
        {
            // 回滚changes
            rollback(changes);
            continue;
        }

        // 处理传播队列中的节点
        while (!propagation_queue.empty() && valid)
        {
            int v = propagation_queue.front();
            propagation_queue.pop();

            for (int w : connected[v])
            {
                if (nodes[w].color != 0)
                    continue;

                int clr_v = nodes[v].color;
                if (!nodes[w].used[clr_v])
                {
                    changes.push_back({w, Change::USED, clr_v, nodes[w].used[clr_v]});
                    nodes[w].used[clr_v] = true;
                    changes.push_back({w, Change::LEFT_COLOURS, nodes[w].leftColours - 1, nodes[w].leftColours});
                    nodes[w].leftColours--;

                    if (nodes[w].leftColours == 0)
                    {
                        valid = false;
                        break;
                    }

                    if (nodes[w].leftColours == 1)
                    {
                        int only_clr = 0;
                        for (int clr = 1; clr <= COLOUR; ++clr)
                        {
                            if (!nodes[w].used[clr])
                            {
                                only_clr = clr;
                                break;
                            }
                        }
                        if (only_clr == 0)
                        {
                            valid = false;
                            break;
                        }
                        // 自动着色w
                        propagation_queue.push(w);
                        changes.push_back({w, Change::COLOR, only_clr, nodes[w].color});
                        nodes[w].color = only_clr;
                    }
                }
            }
        }

        if (!valid)
        {
            rollback(changes);
            continue;
        }

        // 计算自动着色的节点数目
        int auto_colored = 0;
        for (const auto &ch : changes)
        {
            if (ch.type == Change::COLOR && ch.node != u)
            {
                auto_colored++;
            }
        }

        // 递归处理，num增加1（当前节点u）加上自动着色的数目
        dfs(num + 1 + auto_colored);

        // 回溯，恢复
    }
}

int main()
{
    read();
    start_time = clock();
    dfs(0);
    cout << "总共找到 " << sum << " 个解。" << endl;
    cout << "总耗时: " << (clock() - start_time) * 1000.0 / CLOCKS_PER_SEC << " ms" << endl;
    return 0;
}
