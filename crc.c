
#include <stdio.h>
#include <string.h>

#define MAX 100

char g[] = "10011";

void crc(char data[], char remainder[]) {
    int i, j;
    int n = strlen(g);
    char temp[MAX];

    strcpy(temp, data);

    for (i = 0; i < strlen(data) - n + 1; i++) {
        if (temp[i] == '1') {
            for (j = 0; j < n; j++) {
                temp[i + j] =
                    (temp[i + j] == g[j]) ? '0' : '1';
            }
        }
    }

    for (i = 0; i < n - 1; i++) {
        remainder[i] = temp[strlen(data) - n + 1 + i];
    }

    remainder[n - 1] = '\0';
}

int main() {
    char data[MAX], remainder[MAX];
    char codeword[MAX], received[MAX];
    int i, len, error, pos;

    printf("Enter data: ");
    scanf("%99s", data);

    len = strlen(data);

    // Append n-1 zeros
    for (i = 0; i < strlen(g) - 1; i++) {
        data[len + i] = '0';
    }
    data[len + strlen(g) - 1] = '\0';

    printf("\nGenerating polynomial: %s", g);
    printf("\nModified data: %s", data);

    // Calculate CRC checksum
    crc(data, remainder);

    printf("\nChecksum: %s", remainder);

    // Generate final codeword
    strcpy(codeword, data);

    for (i = 0; i < strlen(g) - 1; i++) {
        codeword[len + i] = remainder[i];
    }
    codeword[len + strlen(g) - 1] = '\0';

    printf("\nFinal codeword: %s", codeword);

    // Error detection
    strcpy(received, codeword);

    printf("\n\nTest error detection? (0 = Yes, 1 = No): ");
    scanf("%d", &error);

    if (error == 0) {
        printf("Enter position to insert error (1 to %d): ",
               (int)strlen(received));
        scanf("%d", &pos);

        if (pos < 1 || pos > strlen(received)) {
            printf("Invalid position!");
            return 1;
        }

        received[pos - 1] =
            (received[pos - 1] == '0') ? '1' : '0';

        printf("\nErroneous data: %s", received);
    }

    // Check received data
    crc(received, remainder);

    printf("\nRemainder: %s", remainder);

    if (strspn(remainder, "0") == strlen(remainder)) {
        printf("\nNo error detected.\n");
    } else {
        printf("\nError detected.\n");
    }

    return 0;
}
