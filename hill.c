#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define N 3 // Size of the key matrix (can be changed)
#define MAX_TEXT_LENGTH 10

void processText(int isEncrypt);
void multiplyKeyMatrix(int keyMatrix[N][N], int messageVector[N], int resultVector[N]);
int findInverse(int keyMatrix[N][N], int inverseMatrix[N][N]);
int modInverse(int a, int m);

int main(){
    int option;
    while(1){
        printf("Options: (1 - 3)\n\n\t1.Encryption\n\t2.Decryption\n\t3.Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch(option){
            case 1:
                processText(1);
                break;
            case 2:
                processText(0);
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid option\n");
        }
    }
    return 0;
}

void processText(int isEncrypt){
    char text[MAX_TEXT_LENGTH + 1];
    int keyMatrix[N][N], inverseMatrix[N][N], vector[MAX_TEXT_LENGTH], resultVector[MAX_TEXT_LENGTH];
    int i, j, k, textLength;

    printf("Enter text (The length should me multiple of %d for Hill cipher with max length %d): ",N, MAX_TEXT_LENGTH);
    scanf("%s", text);

    textLength = strlen(text);
    if (textLength % N != 0) {
        printf("Text length should be a multiple of %d for Hill cipher.\n", N);
        return;
    }

    printf("Enter key matrix (%dx%d): \n", N, N);
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            scanf("%d", &keyMatrix[i][j]);
        }
    }

    if (!isEncrypt && !findInverse(keyMatrix, inverseMatrix)) {
        printf("Key matrix is not invertible.\n");
        return;
    }

    for(i = 0; i < textLength; i++){
        vector[i] = toupper(text[i]) - 'A';
    }

    for(i = 0; i < textLength; i += N){
        for(j = 0; j < N; j++){
            resultVector[j] = 0;
            for(k = 0; k < N; k++){
                if (isEncrypt) {
                    resultVector[j] += keyMatrix[j][k] * vector[i + k];
                } else {
                    resultVector[j] += inverseMatrix[j][k] * vector[i + k];
                }
            }
            resultVector[j] %= 26;
        }
        for(j = 0; j < N; j++){
            printf("%c", resultVector[j] + 'A');
        }
    }
    printf("\n");
}

int findInverse(int keyMatrix[N][N], int inverseMatrix[N][N]){
    int det = (keyMatrix[0][0] * (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1])) -
              (keyMatrix[0][1] * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0])) +
              (keyMatrix[0][2] * (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]));

    det = (det % 26 + 26) % 26; // Modulo to ensure positive value

    int detInverse = modInverse(det, 26);
    if(detInverse == -1){
        return 0; // Not invertible
    }

    // Adjugate matrix
    inverseMatrix[0][0] = (keyMatrix[1][1] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][1]) % 26;
    inverseMatrix[0][1] = (-1 * (keyMatrix[0][1] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][1])) % 26;
    inverseMatrix[0][2] = (keyMatrix[0][1] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][1]) % 26;
    inverseMatrix[1][0] = (-1 * (keyMatrix[1][0] * keyMatrix[2][2] - keyMatrix[1][2] * keyMatrix[2][0])) % 26;
    inverseMatrix[1][1] = (keyMatrix[0][0] * keyMatrix[2][2] - keyMatrix[0][2] * keyMatrix[2][0]) % 26;
    inverseMatrix[1][2] = (-1 * (keyMatrix[0][0] * keyMatrix[1][2] - keyMatrix[0][2] * keyMatrix[1][0])) % 26;
    inverseMatrix[2][0] = (keyMatrix[1][0] * keyMatrix[2][1] - keyMatrix[1][1] * keyMatrix[2][0]) % 26;
    inverseMatrix[2][1] = (-1 * (keyMatrix[0][0] * keyMatrix[2][1] - keyMatrix[0][1] * keyMatrix[2][0])) % 26;
    inverseMatrix[2][2] = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) % 26;

    // Multiply by determinant inverse
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            inverseMatrix[i][j] = (inverseMatrix[i][j] * detInverse) % 26;
            if(inverseMatrix[i][j] < 0){
                inverseMatrix[i][j] += 26; // Modulo to ensure positive value
            }
        }
    }

    return 1; // Invertible
}

int modInverse(int a, int m){
    a = a % m;
    for(int x = 1; x < m; x++){
        if((a * x) % m == 1){
            return x;
        }
    }
    return -1; // Not found
}

