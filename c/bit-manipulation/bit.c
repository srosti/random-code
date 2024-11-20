#include <stdio.h>

// clear bit from number
int clear_bit(int num, int bit) {
    int mask = ~(1 << bit);
    return num & mask; 

}

// set bit in number
int set_bit(int num, int bit) {
    int mask = 1 << bit;
    return num | mask;

}

void main() {
    int result;

    result = clear_bit(5,2);
    printf("[5,2]=%d\n",result);
    printf("[5,2]=0x%04x\n",result);

    result = clear_bit(8,1);
    printf("[8,1]=%d\n",result);
    printf("[8,1]=0x%04x\n",result);
    
    result = set_bit(8,0);
    printf("[8,0]=%d\n",result);
    printf("[8,0]=0x%04x\n",result);
    
    result = set_bit(8,1);
    printf("[8,1]=%d\n",result);
    printf("[8,1]=0x%04x\n",result);
}