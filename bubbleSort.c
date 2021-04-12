#include <stdlib.h>
#include <stdio.h>
int
int_swap(int *a , int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void
bubble(int A[], int n){
    int i,j;
    int n = 7;
    int A = {1,3,4,2,6,7,8};
    int tmp;
    int j = 0;
    for(i = 0, j < n, j++)
        for (j = 0, j < n - 1 - i, j++)
            if (A[j] > A[j+1]){
                int_swap(A[j], A[j+1]);
            }
        }
    }

    return 0;
}