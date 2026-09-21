#include <stdio.h>
#include <windows.h> // 新增，用于设置控制台编码

static long long algorithm1 (int n) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        count++;
    }
    return count;
}

static long long algorithm2 (int n) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            count++;
        }
    }
    return count;
}

static long long algorithm3 (int n) {
    long long count = 0;
    for (int i = 1; i < n; i *= 2) {
        count++;
    }
    return count;
}

static long long algorithm4 (int n) {
    long long count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j *= 2) {
            count++;
        }
    }
    return count;
}

int main (void) {
    SetConsoleOutputCP (65001); // 设置控制台输出 UTF-8，解决中文乱码

    // 自动测试的数组：2048 4096 8192 16384
    int testArr[] = {2048, 4096, 8192, 16384};
    int len = sizeof(testArr) / sizeof(testArr[0]);

    for(int k = 0; k < len; k++)
    {
        int n = testArr[k];
        printf("======= n = %d =======\n", n);
        long long res1 = algorithm1 (n);
        long long res2 = algorithm2 (n);
        long long res3 = algorithm3 (n);
        long long res4 = algorithm4 (n);
        printf ("algorithm1 count = %lld\n", res1);
        printf ("algorithm2 count = %lld\n", res2);
        printf ("algorithm3 count = %lld\n", res3);
        printf ("algorithm4 count = %lld\n\n", res4);
    }

    return 0;
}