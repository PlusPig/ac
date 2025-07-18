#include <iostream>
#include <vector>
using namespace std;
void bubblesort(vector<int> &sos)
{
    for (int i = 0; i < sos.size() - 1; i++)
    {
        bool run = false;
        for (int j = 0; j < sos.size() - 1 - i; j++)
        {
            if (sos[j] > sos[j + 1]) // 每次都把最大的浮到前端
            {
                int temp = sos[j];
                sos[j] = sos[j + 1];
                sos[j + 1] = temp;
                run = 1;
            }
        }
        if (!run) // 如果顺序全对，说明排好了
            break;
    }
}