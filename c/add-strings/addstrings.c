#include <stdio.h>
#include <string.h>

int main() {
    char num1[100], num2[100], result[100];
    int i, j, k, len1, len2, carry = 0;

    printf("Enter the first number: ");
    scanf("%s", num1);

    printf("Enter the second number: ");
    scanf("%s", num2);

    len1 = strlen(num1);
    len2 = strlen(num2);

    // Ensure num1 is the larger number
    if (len2 > len1) {
        char temp[100];
        strcpy(temp, num1);
        strcpy(num1, num2);
        strcpy(num2, temp);

        int temp_len = len1;
        len1 = len2;
        len2 = temp_len;
    }

    // Reverse the strings for easier addition
    for (i = 0, j = len1 - 1; i < j; i++, j--) {
        char temp = num1[i];
        num1[i] = num1[j];
        num1[j] = temp;
    }

    for (i = 0, j = len2 - 1; i < j; i++, j--) {
        char temp = num2[i];
        num2[i] = num2[j];
        num2[j] = temp;
    }

    // Perform addition digit by digit
    k = 0;
    for (i = 0; i < len2; i++) {
        int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
        result[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    for (i = len2; i < len1; i++) {
        int sum = (num1[i] - '0') + carry;
        result[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    if (carry > 0) {
        result[k++] = carry + '0';
    }

    // Reverse the result string
    for (i = 0, j = k - 1; i < j; i++, j--) {
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }

    result[k] = '\0';

    printf("Sum: %s\n", result);

    return 0;
}