#include <stdio.h>

int  main() {
    inline x = 0.000000000000000000000001;
    short y = 0.000000000000000000000001;

    double z = x -y;

    if (z == 0.0) {
        printf("РАВЕН");
        return 0;
    }

    printf("НЕ РАВЕН");
    return 0;
}