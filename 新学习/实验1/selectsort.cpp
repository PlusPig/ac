#include <bits/stdc++.h>
using namespace std;

void selectsort(vector<int> &sos)
{
    for (int i = 0; i < sos.size() - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < sos.size(); j++)
        {
            if (sos[j] < sos[k]) // 每次选择最小的与之交换
            {
                k = j;
            }
        }
        if (k != i)
        {
            int temp = sos[k];
            sos[k] = sos[i];
            sos[i] = temp;
        }
    }
}