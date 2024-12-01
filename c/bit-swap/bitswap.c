#include <stdio.h>

unsigned int reverse_bits(unsigned int num) {

    unsigned int rev_num = 0;
    int i;

    for (i=0; i<32; i++) {
        int bit = (num & 1);
        rev_num <<= 1;
        rev_num |= bit;
        num >>= 1;
    }

    return rev_num;

}

int main() {
    unsigned int val = 0b10101010;
    int rev_val = reverse_bits(val);

    printf("original val= %b\n", val);
    printf("reversed val= %b\n", rev_val);

    return 0;
}