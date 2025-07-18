#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    float *a, *b, *c, temp;
    long int i, j, k, size, m;
    clock_t start_time, end_time;
    if (argc < 2)
    {
        printf("\n\tUsage:%s <Row of square matrix>\n", argv[0]);
        exit(-1);
    } // if
    size = atoi(argv[1]);
    m = size * size;
    a = (float *)malloc(sizeof(float) * m);
    b = (float *)malloc(sizeof(float) * m);
    c = (float *)malloc(sizeof(float) * m);
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            a[i * size + j] = (float)(rand() % 1000 / 100.0);
            b[j * size + i] = (float)(rand() % 1000 / 100.0);
        }
    }
    start_time = clock(); // 开始计时
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            c[i * size + j] = 0;
            for (k = 0; k < size; k++)
                c[i * size + j] += a[i * size + k] * b[j * size + k];
        }
    }
    end_time = clock();
    printf("Executiontime=%lf seconds", (double)(end_time - start_time));
    free(a);
    free(b);
    free(c);
    return (0);
} // main