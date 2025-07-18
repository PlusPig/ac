#include <iostream>
#include <vector>
using namespace std;
void insertsort(vector<int> &sos)
{
    for (int i = 0; i < sos.size() - 1; i++)
    {
        int end = i;            // 有序序列的最后一个数的下标
        int num = sos[end + 1]; // 待插入的数
        while (end >= 0)
        {
            if (num < sos[end]) // 前面的比后面的大，就把前面的往后推
            {
                sos[end + 1] = sos[end];
                end--;
            }
            else
            {
                break;
            }
        }
        sos[end + 1] = num; // 插入到比它小的那个数的下标后面
    }
}