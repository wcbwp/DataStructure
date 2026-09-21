#include <stdio.h>

long long algorithm1(int n) {
    long long num = 0;
    for (int i = 0; i < n; i++) {
        num++;
    }
    return num;
}
long long algorithm2(int n) {
    long long num = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            num++;
        }
    }
    return num;
}
long long algorithm3(int n) {
    long long num = 0;
    for (int i = 1; i < n; i *= 2) {
        num++;
    }
    return num;
}
long long algorithm4(int n) {
    long long num = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j *= 2) {
            num++;
        }
    }
    return num;
}

int main() {
    int a[] = {2048, 4096, 8192, 16384};
    for (int i = 0; i < 4; i++) {
        printf("%d %lld %lld %lld %lld\n", a[i], algorithm1(a[i]), algorithm2(a[i]), algorithm3(a[i]), algorithm4(a[i]));
    }
    return 0;
}