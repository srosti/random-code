#include <stdio.h>
/**
 * @input A : Integer array
 * @input n1 : Integer array's ( A ) length
 * @input B : Integer
 *
 * @Output Integer
 */
int solve( int* A, int n1, int B) {

    int max_total = 0;

    printf("array size= %d, count=%d", n1, B);


    for(int i=0; i<B; i++) {
        max_total += A[i];
    }
    printf("left side max = %d\n", max_total);

    for(int i=1; i<=B; i++) {
        int left_total=0;
        int right_total=0;
        int new_total=0;
        if (i==46) {
            printf("break");
        }

        // calculate new left total
        for(int x=0; x<B-i; x++) {
           left_total+=A[x];
        }

        // calculate new right total
        for(int x=1; x<=i; x++) {
            right_total+=A[n1-x];
        }
        printf("i=%d left side = %d\n", i, left_total);
        printf("i=%d right max = %d\n", i, right_total);
        new_total = left_total + right_total;

        if (new_total > max_total) {
            max_total = new_total;
            printf("new max = %d\n", max_total);
        }


    }

    return max_total;
}

#define SIZE1 5
int array1[SIZE1] = {5, 3, -1, 0, 2};

#define SIZE2 10
int array2[SIZE2] = {5, 3, -1, 0, 2, 1, 3, 4, 5, 10};


int array_test[] = {-533, -666, -500, 169, 724, 478, 358, -38, -536, 705, -855, 281, -173, 961, -509, -5, 942, -173, 436, -609, -396, 902, -847, -708, -618, 421, -284, 718, 895, 447, 726, -229, 538, 869, 912, 667, -701, 35, 894, -297, 811, 322, -667, 673, -336, 141, 711, -747, -132, 547, 644, -338, -243, -963, -141, -277, 741, 529, -222, -684, 35};


void main() {

//    printf("max = %d\n", solve(array1, SIZE1, 3));
//    printf("max = %d\n", solve(array2, SIZE2, 2));
    printf("max = %d\n", solve(array_test, sizeof(array_test)/sizeof(array_test[0]), 48));

}