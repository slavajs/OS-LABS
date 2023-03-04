#include <stdlib.h>
#include <stdio.h>
#include "contracts.h"

int main() {
    int functionType;
    while (1){
        scanf("%d", &functionType);
        if (functionType == 1){
            int a, b, ans;
            scanf("%d %d",&a, &b);
            ans = GCD(a, b);
            printf("%d\n", ans);
        }
        else if (functionType == 2) {
            int x;
            double ans;
            scanf("%d", &x);
            ans = E(x);
            printf("%.5f\n", ans);

        } else {
            return 0;
        }
    }
}