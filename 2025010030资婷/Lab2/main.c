#include <stdio.h>
long long algorithm1(int n) {
    long long count = 0;
    int i;
    for (i = 0; i < n; i++) {
        count++;
    }

    return count;
}
long long algorithm2(int n) {
    long long count = 0;
    int i;
    for (i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            count++;
        }
    }

    return count;
}
long long algorithm3(int n) {
    long long count = 0;
    int i;
    for (i = 1; i < n; i *= 2) {
        count++;
    }

    return count;
}
long long algorithm4(int n) {
    long long count = 0;
    int i;
    for (i=0; i < n; i++) {
        for (int j = 1; j < n; j *= 2) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int a[]={2048,4096,8192,16384};
    int i;
    printf("%-8s %-11s %-11s %-11s %-11s\n","n","algorithm1","algorithm2","algorithm3","algorithm4");
    for (i = 0; i < 4; i++) {
        long long c1=algorithm1(a[i]);
        long long c2=algorithm2(a[i]);
        long long c3=algorithm3(a[i]);
        long long c4=algorithm4(a[i]);
        printf("%-8d %-11lld %-11lld %-11lld %-11lld\n",a[i],c1,c2,c3,c4);
    }
    return 0;
}
