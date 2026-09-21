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

int main() {

    int inputs[] = {2048, 4096, 8192, 16384};

    int num_tests = sizeof(inputs) / sizeof(inputs[0]);

    printf("%-8s %-12s %-12s %-12s %-12s\n", "n", "algorithm1", "algorithm2", "algorithm3", "algorithm4");

    for (int k = 0; k < num_tests; k++) {
        int n = inputs[k];
        long long res1 = algorithm1(n);
        long long res2 = algorithm2(n);
        long long res3 = algorithm3(n);
        long long res4 = algorithm4(n);

        printf("%-8d %-12lld %-12lld %-12lld %-12lld\n", n, res1, res2, res3, res4);
    }

    return 0;
}