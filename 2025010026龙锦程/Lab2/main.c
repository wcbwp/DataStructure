#include <stdio.h>

long long algorithm1(int n) {
    long long count = 0;

    for (int i = 0; i < n; i++) {
        count++;
    }

    return count;
}

long long algorithm2(int n) {
    long long count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            count++;
        }
    }

    return count;
}

long long algorithm3(int n) {
    long long count = 0;

    for (int i = 1; i < n; i *= 2) {
        count++;
    }

    return count;
}

long long algorithm4(int n) {
    long long count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j *= 2) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int sizes[] = {2048, 4096, 8192, 16384};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("%-8s%-14s%-14s%-14s%-14s\n",
           "n", "algorithm1", "algorithm2", "algorithm3", "algorithm4");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        long long r1 = algorithm1(n);
        long long r2 = algorithm2(n);
        long long r3 = algorithm3(n);
        long long r4 = algorithm4(n);

        printf("%-8d%-14lld%-14lld%-14lld%-14lld\n",
               n, r1, r2, r3, r4);
    }

    return 0;
}
//
// Created by LJC on 2026/9/7.
//
