#include <iostream>
#include <vector>
using namespace std;
void sort(vector<int> &arr, int left, int right);
void mergesort(vector<int> &sos)
{
    sort(sos, 0, sos.size() - 1);
}
void merge(vector<int> &sos, int left, int mid, int right)
{
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    // 合并两个有序子数组
    while (i <= mid && j <= right)
    {
        if (sos[i] <= sos[j])
            temp[k++] = sos[i++];
        else
            temp[k++] = sos[j++];
    }

    // 处理剩余元素
    while (i <= mid)
        temp[k++] = sos[i++];
    while (j <= right)
        temp[k++] = sos[j++];

    // 将临时数组复制回原数组
    for (int p = 0; p < k; p++)
    {
        sos[left + p] = temp[p];
    }
}

void sort(vector<int> &sos, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        sort(sos, left, mid);         // 递归左半部分
        sort(sos, mid + 1, right);    // 递归右半部分
        merge(sos, left, mid, right); // 合并
    }
}
