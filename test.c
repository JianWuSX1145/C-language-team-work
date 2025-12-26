#include <stdio.h>
#include <stdlib.h>

int main () {
    int a;
    while (scanf("%d", &a) != EOF) {
        system("cls");
        printf("%d\n", a);
    }
    return 0;
}