#include "sha.h"
void writeMessageToFile(char* message){
    FILE* initialFile = fopen("input.txt", "w");
    if (initialFile == NULL || !initialFile){
        printf("Can't open the file.\n");
        return;
    }
    fprintf(initialFile, "%s", message);
    fclose(initialFile);
}
char* readFromFile(){
    FILE *initialFile = fopen("input.txt", "rb");
    char* messageFile = NULL;
    if (initialFile == NULL || !initialFile){
        printf("Can't open the file.\n");
        return NULL;
    }
    int pos = (int)ftell(initialFile);
    fseek(initialFile, 0, SEEK_END);
    long fileSize = (long)ftell(initialFile);
    fseek(initialFile, pos, SEEK_SET);
    messageFile = (char *)malloc(sizeof(char) * fileSize);
    fread(messageFile, fileSize, 1, initialFile);
    fclose(initialFile);
    return messageFile;
}
unsigned int innerTransformation(unsigned int j, unsigned int x, unsigned int y, unsigned int z){
    if (j < 20)
        return (x & y) | ((~x) & z);
    else if (j < 40)
        return x ^ y ^ z;
    else if (j < 60)
        return (x & y) | (x & z) | (y & z);
    else if (j < 80)
        return x ^ y ^ z;
    else
        return 0;
}
void extension(char* message, unsigned long long* bitLen){
    *bitLen = strlen(message)*8;
    message[*bitLen] = (char)0x80;
    (*bitLen)++;
    unsigned long long counter = *bitLen;

    while (counter % 512 != 448){
        message[counter] = 0;
        counter++;
    }
}
void addingLength(char* message, unsigned long long bitLen){
    unsigned int temp = strlen(message);
    message = (char *) realloc(message, (temp + 8 + 1) * sizeof(char));
    for (unsigned int i = strlen(message) - 1; i >= temp; i--){
        message[i] = (char)bitLen;
        bitLen >>= 8;
    }
}
void messageProcessing(char* message, unsigned int* h0, unsigned int* h1,
                       unsigned int* h2, unsigned int* h3, unsigned int* h4){
    unsigned char M[64];
    unsigned int W[80];
    unsigned int K[] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};
    unsigned int A, B, C, D, E, T;

    for (unsigned int i = 0; i < strlen(message); i += 64){
        for (int k = 0; k < 64; k++)
            M[k] = message[k + i];

        for (int k = 0; k < 16; k++){
            W[k] = ((unsigned int)M[k * 4]) << 24;
            W[k] |= ((unsigned int)M[k * 4 + 1]) << 16;
            W[k] |= ((unsigned int)M[k * 4 + 2]) << 8;
            W[k] |= ((unsigned int)M[k * 4 + 3]);
        }

        for (int k = 16; k < 80; k++)
            W[k] = rotateLeft((W[k - 3] ^ W[k - 8] ^ W[k - 14] ^ W[k - 16]), 1);

        A = *h0; B = *h1; C = *h2; D = *h3; E = *h4;

        for (int j = 0; j < 80; j++){
            T = rotateLeft(A, 5) + innerTransformation(j, B, C, D) + E + W[j] + K[j / 20];
            E = D;
            D = C;
            C = rotateLeft(B, 30);
            B = A;
            A = T;
        }
        *h0 += A; *h1 += B; *h2 += C; *h3 += D; *h4 += E;
    }
}
void tempSHA(){
    unsigned int H0 = 0x67452301,
            H1 = 0xEFCDAB89,
            H2 = 0x98BADCFE,
            H3 = 0x10325476,
            H4 = 0xC3D2E1F0;
    unsigned long long bitLen;
    char* message = readFromFile();
    extension(message, &bitLen);
    addingLength(message, bitLen);
    messageProcessing(message, &H0, &H1, &H2, &H3, &H4);
    printf("\nResult: %x %x %x %x %x",H0, H1, H2, H3, H4);
}