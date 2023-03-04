#include "../include/contracts.h"

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}
long long int factorial(int a) {
    long long int ans = 1;
    for (int i = 1; i <= a; i++) {
        ans *= i;
    }
    return ans;
}

int GCD(int a, int b) {
    if (a == 0) {
        return b;
    }
    return GCD(b % a, a);
}

double E(int x) {
    double sum = 1.0;
    double prev = 1.0;
    double newEl = 1.0;
    if (x == 0) {
        return 1;
    }
    // if (x == 1) {
    //     return 2;
    // }
    for (int i = 1; i <= x; i++) {
        newEl = prev/(double)i;
        prev = newEl;
        sum += newEl;
    }
    return sum;
}