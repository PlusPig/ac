#include <bits/stdc++.h>
using namespace std;
#define VERTEX 9
#define EDGE 0
#define COLOUR 4

class node
{
public:
    int degree;     // ����
    int id;         // ԭʼ�±�
    int leftcolour; // ʣ����ɫ
    node()
    {
        leftcolour = 4;
        degree = 0;
    }
    bool operator<(const node v) const
    {
        return this->degree >= v.degree;
    }
};

// ȫ�ֱ���
vector<vector<int>> connect;
vector<int> colour;
vector<node> vertex;
clock_t start_time, end_time;
ofstream ofs("smallresult.txt");
int sum = 0; // ��ʾ������

bool check(int id)
{
    for (int i = 0; i < VERTEX; i++)
    {
        if (connect[id][i] == 1 && colour[i] == colour[id])
        {
            return false;
        }
    }
    return true;
}

void read()
{
    ifstream ifs("smalltext.txt"); // ������ļ�
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

void sorted()
{
    sort(vertex.begin(), vertex.end());
}

void writeinfile() // д���ļ�
{
    for (int i = 0; i < VERTEX; i++)
    {
        ofs << colour[i] << " ";
    }
    ofs << endl;
}

void dfs(int idx)
{
    if (idx == VERTEX)
    {
        sum++;
        // writeinfile();
        if (sum == 1000000)
        {
            end_time = clock();
            cout << "Ŀǰ�ҵ�" << sum << "����ɫ����" << endl;
            cout << "����ʱ��Ϊ��" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
        }
        return;
    }
    for (int i = 1; i <= COLOUR; i++)
    {
        // idxֻ��ʵ���˼�������
        // ʵ�ʸõ���±겻��idx
        // ������ԭ����id
        int realid = vertex[idx].id;
        colour[realid] = i;
        if (check(realid))
        {
            dfs(idx + 1);
        }
        colour[realid] = 0;
    }
}

int main()
{
    connect.resize(VERTEX, vector<int>(VERTEX, 0));
    colour.resize(VERTEX, 0);
    vertex.resize(VERTEX);

    read(); // ��ȡ�ļ�

    // ����sort�������ط�
    //  sorted(); // ���նȵĴ�С����

    start_time = clock();
    dfs(0); // ��ʼ����
    end_time = clock();

    cout << "�ܹ��ҵ�" << sum << "����ɫ����" << endl;
    cout << "����ʱ��Ϊ��" << (double)(end_time - start_time) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}
