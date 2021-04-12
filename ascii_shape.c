#include <stdlib.h>
#include <stdio.h>

int
main(int argc, const char * argv[]){
    int num;
    int i;
    printf("Enter numbers: ");
    while (scanf("%d", &num) == 1){
        printf ("%d |", num);
        for (i = 0; i<num; i++) {
            printf("*");
        }
        printf(" \n");
    }
    return 0;
}