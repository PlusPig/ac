#include <bits/stdc++.h>
using namespace std;
#define FILENAME "smalltext.txt"
#define VERTEX 450
#define EDGE 0
#define COLOUR 25

class node
{
public:
    int degree; // ����
    int id;     // ԭʼ�±�
    vector<int> leftcolour;
    int leftnum;
    node()
    {
        degree = 0;
        leftnum = COLOUR;
        leftcolour.resize(COLOUR, 0); // 0��ʾ��������������ɫ
    }
    bool operator<(const node v) const
    {
        return this->degree >= v.degree;
    }
};

// ȫ�ֱ���
vector<vector<int>> connect; // ʹ���ڽӾ���
vector<int> colour;
vector<node> vertex;
clock_t start_time, end_time;
ofstream ofs("smallresult.txt");
int sum = 0; // ��ʾ������

bool check(int id, set<int> &used)
{
    for (int i = 0; i < VERTEX; i++)
    {
        if (connect[id][i])
        {
            used.insert(i);
        }
        if (connect[id][i] == 1 && colour[i] == colour[id])
        {
            return false;
        }
    }
    return true;
}

void read()
{
    ifstream ifs("le450_25a.txt"); // ������ļ�
    int v1, v2;
    char e;
    while (ifs >> e >> v1 >> v2)
    {
        connect[v1 - 1][v2 - 1] = 1;
        connect[v2 - 1][v1 - 1] = 1;
        vertex[v1 - 1].degree++;
        vertex[v2 - 1].degree++;
    }

    for (int i = 0; i < VERTEX; ++i)
    {
        vertex[i].id = i;
    }

    ifs.close();
}

void writeinfile() // д���ļ�
{
    for (int i = 0; i < VERTEX; i++)
    {
        ofs << colour[i] << " ";
    }
    ofs << endl;
}

int MRV_find() // �ҵ����ٿ�����ɫ���һ�δ��ɫ�Ľڵ�
{
    int min = INT_MAX;
    int index = -1;

    for (int i = 0; i < VERTEX; i++) // ����Ѱ��Լ�����ĵ�
    {
        // û���������ֱ����i����
        if (colour[i])
            continue;

        if (vertex[i].leftnum < min)
        {
            min = vertex[i].leftnum; // Ѱ��Լ�����ĵ�
            index = i;
        }
    }
    return index;
}

void decrease(set<int> &used, int Colour)
{
    for (int realidx : used)
    {
        if (vertex[realidx].leftcolour[Colour] == 0)
        {
            vertex[realidx].leftcolour[Colour] = 1;
            vertex[realidx].leftnum--;
        }
        else
        {
            vertex[realidx].leftcolour[Colour]++;
        }
    }
}

void increase(set<int> &used, int Colour)
{
    for (int realidx : used)
    {
        if (vertex[realidx].leftcolour[Colour] == 1)
        {
            vertex[realidx].leftcolour[Colour] = 0;
            vertex[realidx].leftnum++;
        }
        else
        {
            vertex[realidx].leftcolour[Colour]--;
        }
    }
}

void MRV_dfs(int num)
{
    if (num == VERTEX)
    {
        sum++;
        if (sum == 10000000)
        {
            end_time = clock();
            cout << "Ŀǰ�ҵ�" << sum << "����ɫ����" << endl;
            cout << "����ʱ��Ϊ��" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
        }
        return;
    }

    int minidx = MRV_find(); // ���ٿ�����ɫ���±�
    if (minidx == -1)
    {
        return;
    }

    for (int i = 1; i <= COLOUR; i++)
    {
        // û���������Ի�õ���С�±������ʵ�±�
        colour[minidx] = i;
        set<int> used; // ������¼�����ӵĽڵ㣬���������ԭ
        if (check(minidx, used))
        {
            decrease(used, i - 1);
            MRV_dfs(num + 1);
            increase(used, i - 1);
        }
        colour[minidx] = 0;
    }
}

int main()
{
    connect.resize(VERTEX, vector<int>(VERTEX, 0));
    colour.resize(VERTEX, 0);
    vertex.resize(VERTEX);

    read(); // ��ȡ�ļ�

    start_time = clock();
    MRV_dfs(0); // ��ʼ����
    end_time = clock();

    cout << "�ܹ��ҵ�" << sum << "����ɫ����" << endl;
    cout << "����ʱ��Ϊ��" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}
