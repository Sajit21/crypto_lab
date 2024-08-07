//normal push on rail fance cipher

//this code rarely works on any code application.
// simply run on online complier



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void rail_fence_encrypt(char* plaintext, int rails) {
    int len = strlen(plaintext);
    char** fence = (char**)malloc(rails * sizeof(char*));
    for (int i = 0; i < rails; i++) {
        fence[i] = (char*)malloc(len * sizeof(char));
        memset(fence[i], ' ', len * sizeof(char));
    }

    int row = 0, dir = 1;
    for (int i = 0; i < len; i++) {
        fence[row][i] = plaintext[i];
        row += dir;
        if (row == 0 || row == rails - 1)
            dir = -dir;
    }

    printf("Encrypted text: ");
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (fence[i][j] != ' ')
                printf("%c", fence[i][j]);
        }
    }
    printf("\n");

    for (int i = 0; i < rails; i++) {
        free(fence[i]);
    }
    free(fence);
}

int main() {
    char plaintext[100];
    int rails;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;

    printf("Enter number of rails: ");
    scanf("%d", &rails);

    rail_fence_encrypt(plaintext, rails);

    return 0;
}

