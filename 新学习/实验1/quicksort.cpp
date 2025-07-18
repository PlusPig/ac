#include <bits/stdc++.h>
using namespace std;
void sort(vector<int> &sos, int left, int right, int n);
void quicksort(vector<int> &sos)
{
    sort(sos, 0, sos.size() - 1, sos.size());
}
void sort(vector<int> &sos, int left, int right, int n)
{
    int mid = sos[left];
    int temp1 = left, temp2 = right;
    if (left >= right)
    {
        return;
    }
    bool translate = 0;

    while (left < right)
    {
        if (translate == 1)
        {
            if (sos[left] <= mid)
            {
                left++;
            }
            else
            {
                sos[right] = sos[left];
                right--;
                translate = 0; //
            }
        }
        else
        {
            if (sos[right] >= mid)
            {
                right--;
            }
            else
            {
                sos[left] = sos[right]; //
                left++;
                translate = 1;
            }
        }
    }
    sos[(left + right) / 2] = mid;
    sort(sos, temp1, left - 1, n);
    sort(sos, right + 1, temp2, n);
}