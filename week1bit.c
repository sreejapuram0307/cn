#include <stdio.h>
#include <string.h>

int main() {
    char a[100];
    int i, j, k, count = 0;

    printf("Enter the input binary string: ");
    scanf("%s", a);

    // Bit Stuffing
    for (i = 0; i < strlen(a); i++) {
        if (a[i] == '1') {
            count = 0;
            k = i;

            while (a[k] == '1') {
                count++;
                k++;

                if (count == 5) {
                    for (j = strlen(a); j >= k; j--)
                        a[j + 1] = a[j];

                    a[k] = '0';
                    i = k;
                    break;
                }
            }
        }
    }

    printf("The bit stuffed string is: %s\n", a);

    // Bit Unstuffing
    for (i = 0; i < strlen(a); i++) {
        if (a[i] == '1') {
            count = 0;
            k = i;

            while (a[k] == '1') {
                count++;
                k++;

                if (count == 5 && a[k] == '0') {
                    for (j = k; j < strlen(a); j++)
                        a[j] = a[j + 1];

                    break;
                }
            }
        }
    }

    printf("String after unstuffing: %s\n", a);

    return 0;
}