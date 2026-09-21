#include <stdio.h>
long long algorithm1(int n) {
    long long count = 0;
    for (int i=0;i<n;i++) {
        count++;
    }
    return count;
}
long long algorithm2(int n) {
    long long count=0;
    for (int i=0;i<n;i++) {
        for (int j=0;j<i;j++) {
            count++;
        }
    }
    return count;
}
long long algorithm3(int n) {
    long long count=0;
    for (int i=1;i<n;i*=2) {
        count++;
    }
    return count;
}
long long algorithm4(int n) {
    long long count=0;
    for (int i=0;i<n;i++) {
        for (int j=1;j<n;j*=2) {
            count++;
        }
    }
    return count;
}
int main() {
    int test_size[]={2048,4096,8192,16384};
    int len = sizeof(test_size)/sizeof(test_size[0]);
    printf("%-6s %-12s %-10s %-12s\n","n","algorithm1","algorithm2","algorithm3","algorithm4");
    for (int idx=0;idx<len;idx++) {
        int n=test_size[idx];
        long long a1=algorithm1(n);
        long long a2=algorithm2(n);
        long long a3=algorithm3(n);
        long long a4=algorithm4(n);
        printf("%-6d %-12lld %-12lld %-10lld %-12lld\n",n,a1,a2,a3,a4);
    }
    return 0;
}
//
// Created by 联想电脑 on 2026/9/7.
//
