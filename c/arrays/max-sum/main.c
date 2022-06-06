#include <stdio.h>

/**
 * @input A : Read only ( DON'T MODIFY ) Integer array
 * @input n1 : Integer array's ( A ) length
 * 
 * @Output Integer
 */


int maxSubArray(const int* A, int n1) {

    int maxSum=A[0];
    int curSum=0;
    int i;

    for(i=0; i<n1; i++) {
        curSum += A[i];

        if (curSum<=0) {
            if (A[i] > maxSum) {
                maxSum = A[i];
            }
            curSum=0;
        }
        else if (curSum > maxSum ) {
            maxSum = curSum;
        }

    }

    return maxSum;
}

int test1[] = {1, 2, 3, 4, -10};
int test2[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
int test3[] = {-500};
int test4[] = {-163, -20};


void main() {

//    printf("max sub array=%d\n", maxSubArray(test1, 5));
//    printf("max sub array=%d\n", maxSubArray(test2, sizeof(test2)/sizeof(test2[0])));
//    printf("max sub array=%d\n", maxSubArray(test3, sizeof(test3)/sizeof(test3[0])));
   printf("max sub array=%d\n", maxSubArray(test4, sizeof(test4)/sizeof(test4[0])));

}