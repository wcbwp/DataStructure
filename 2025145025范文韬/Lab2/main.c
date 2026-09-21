#include <stdio.h>

// 第1题：单层循环 O(n)
long long algorithm1(int n)
{
    long long count = 0;
    for (int i = 0; i < n; i++)
    {
        count++;
    }
    return count;
}

// 第2题：嵌套i<=i，求和 n(n+1)/2  O(n²)
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

// 第3题：i *=2 倍增循环 O(logn)
long long algorithm3(int n)
{
    long long count = 0;
    for (int i = 1; i < n; i *= 2)
    {
        count++;
    }
    return count;
}

//第4题：外层n次，内层倍增，O(n log n)
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
    // 4组测试规模
    int size_arr[] = {2048, 4096, 8192, 16384};
    int len = sizeof(size_arr) / sizeof(size_arr[0]);

    //打印表头
    printf("%-8s %-15s %-15s %-15s %-15s\n",
           "n", "algorithm1", "algorithm2", "algorithm3", "algorithm4");

    //循环遍历，不复制重复代码
    for(int i = 0; i < len; i++)
    {
        int n = size_arr[i];
        long long a1 = algorithm1(n);
        long long a2 = algorithm2(n);
        long long a3 = algorithm3(n);
        long long a4 = algorithm4(n);

        printf("%-8d %-15lld %-15lld %-15lld %-15lld\n",
               n, a1, a2, a3, a4);
    }

    return 0;
}