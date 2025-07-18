#include <bits/stdc++.h>
using namespace std;
#define N 700000
#define T 2
void heapdown(vector<int> &sos, int n, int i)
{
    int left = 2 * i + 1, right = 2 * i + 2;
    int biggest = i;

    if (left < n && sos[left] > sos[biggest]) // �ҵ����ҽڵ��е����ֵ
        biggest = left;
    if (right < n && sos[right] > sos[biggest])
        biggest = right;

    if (biggest != i)
    {
        int temp = sos[i];
        sos[i] = sos[biggest];
        sos[biggest] = temp;
        heapdown(sos, n, biggest);
    }
}
void buildheap(vector<int> &sos, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapdown(sos, n, i);
    }
}
int main()
{
    unsigned long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937_64 gen(seed); // ʱ�����Ϊ����
    uniform_int_distribution<int> dist(1, 50000000);

    int t = T;
    while (t--)
    {
        vector<int> sos;

        for (int i = 0; i < N; i++)
        {
            sos.push_back(dist(gen));
        }

        cout << "����ǰ��" << endl;
        for (int i = N - 1; i > N - 11; i--)
        {
            cout << sos[i] << " ";
        }
        cout << endl;

        clock_t start_time = clock(); // ��ʼ��ʱ

        buildheap(sos, sos.size()); // ��������

        for (int i = N - 1; i > N - 11; i--) // ֻ�轻��10��
        {
            int temp = sos[0];
            sos[0] = sos[i];
            sos[i] = temp;
            heapdown(sos, i, 0); // ��Ѷ�Ԫ�ؽ����������µ�������
        }

        clock_t end_time = clock();

        // �����֤ǰ10��
        cout << "�����" << endl;
        for (int i = N - 1; i > N - 11; i--)
        {
            cout << sos[i] << " ";
        }
        cout << endl;

        cout << "��" << 10 - t << "�������ʱ�䣺" << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
    }
    // system("pause");
    return 0;
}