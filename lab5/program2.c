#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

const char firstRealization[] = "./libd1_dynamic.so";
const char secondRealization[] = "./libd2_dynamic.so";

int main() {
    int flag = 1;
    int mode;
    int (* GCD)(int a, int b);
    double (* E)(int x);
    void *library = dlopen(firstRealization, RTLD_LAZY);
    if (library == NULL) {
        printf("Error opening library \n");
        return 1;
    }
    *(void**)(&GCD) = dlsym(library, "GCD");
    *(void**)(&E) = dlsym(library, "E");
    while(1) {
        scanf("%d", &mode);
        if (mode == 0) {
            dlclose(library);
            if (flag) {
                library = dlopen(secondRealization, RTLD_LAZY);
                flag = 0;
            } else {
                library = dlopen(firstRealization, RTLD_LAZY);
                flag = 1;
            }
            *(void **)(&GCD) = dlsym(library, "GCD");
            *(void **)(&E) = dlsym(library, "E");
        } else if(mode == 1) {
            int a, b, ans;
            scanf("%d %d",&a, &b);
            ans = GCD(a, b);
            printf("%d\n", ans);
        }
        else if (mode == 2) {
            int x;
            float ans;
            scanf("%d", &x);
            ans = E(x);
            printf("%.5f\n", ans);
        } else {
            dlclose(library);
            break;
        }
    }
    return 0;
}