#include "../include/contracts.h"
#include "math.h"

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
    int maxim = max(a, b);
    int maxDiv = 1;
    for (int i = 2; i < maxim; i++) {
        if (a % i == 0 && b % i == 0) {
            maxDiv = i;
        }
    }
    return maxDiv;
}

double E(int x) {
    return pow(1 + (float)1 / x, x);
}