#include <bits/stdc++.h>
using namespace std;
#define vertexnum 9
#define colournum 4

int sum = 0;
vector<int> colour(vertexnum, 0);
vector<vector<int>> tu(vertexnum, vector<int>(vertexnum, 0));

// �жϵ�ǰ����ɫ�Ƿ�Ϸ�
bool judgeone(int row)
{
    for (int j = 0; j < vertexnum; j++)
    {
        if (tu[row][j] == 1 && colour[row] == colour[j])
        {
            return false;
        }
    }
    return true;
}

// ͳ��ĳ���������ʹ�õ���ɫ����
int count_remaining_colours(int v)
{
    set<int> used;
    for (int i = 0; i < vertexnum; i++)
    {
        if (tu[v][i] == 1 && colour[i] != 0)
        {
            used.insert(colour[i]);
        }
    }
    return colournum - used.size();
}

// ������һ����ʣ����ɫ���١��Ķ���
int select_next_vertex()
{
    int min_remaining = INT_MAX;
    int selected = -1;
    for (int i = 0; i < vertexnum; i++)
    {
        if (colour[i] == 0)
        {
            int remain = count_remaining_colours(i);
            if (remain < min_remaining)
            {
                min_remaining = remain;
                selected = i;
            }
        }
    }
    return selected;
}

void dfs(int depth, ofstream &ofs)
{
    if (depth == vertexnum)
    {
        sum++;
        for (int i = 0; i < vertexnum; i++)
        {
            ofs << colour[i] << " ";
        }
        ofs << endl;
        return;
    }

    int v = select_next_vertex();
    if (v == -1)
        return; // ��ֹ�쳣

    for (int c = 1; c <= colournum; c++)
    {
        colour[v] = c;
        if (judgeone(v))
        {
            dfs(depth + 1, ofs);
        }
        colour[v] = 0;
    }
}

int main()
{
    ifstream ifs("smalltext.txt");
    ofstream ofs("smallresult.txt");

    char a;
    int b, c;
    while (ifs >> a >> b >> c)
    {
        tu[b - 1][c - 1] = 1;
        tu[c - 1][b - 1] = 1;
    }
    ifs.close();

    clock_t start_time = clock();

    dfs(0, ofs);

    clock_t end_time = clock();
    cout << "�ܹ��ҵ�" << sum << "����ɫ����" << endl;
    cout << "����ʱ��Ϊ��" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
}
