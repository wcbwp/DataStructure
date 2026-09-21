#include <stdio.h>

long long algorithm1(int n)
{
    long long count = 0;
    for (int i = 0; i < n; i++)
    {
        count++;
    }
    return count;
}

long long algorithm2(int n)
{
    long long count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            count++;
        }
    }
    return count;
}

long long algorithm3(int n)
{
    long long count = 0;
    for (int i = 1; i < n; i *= 2)
    {
        count++;
    }
    return count;
}

long long algorithm4(int n)
{
    long long count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n; j *= 2)
        {
            count++;
        }
    }
    return count;
}

int main(void)
{
    //测试用的n集合：2048,4096,8192,16384
    int test_n[] = {2048, 4096, 8192, 16384};
    int size = sizeof(test_n)/sizeof(test_n[0]);

    printf("n\talgorithm1\talgorithm2\talgorithm3\talgorithm4\n");
    for(int idx = 0; idx < size; idx++)
    {
        int n = test_n[idx];
        long long a1 = algorithm1(n);
        long long a2 = algorithm2(n);
        long long a3 = algorithm3(n);
        long long a4 = algorithm4(n);
        printf("%d\t%lld\t\t%lld\t\t%lld\t\t%lld\n", n, a1, a2, a3, a4);
    }
    return 0;
}