#ifndef PRACTICE_SHA_H
#define PRACTICE_SHA_H
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include <stdbool.h>

#define rotateLeft(x,n) ((x<<n) | (x>>(32-n)))
void writeMessageToFile(char* message);
char* readFromFile();
unsigned int innerTransformation(unsigned int j, unsigned int x, unsigned int y, unsigned int z);
void extension(char* message, unsigned long long* bitLen);
void addingLength(char* message, unsigned long long bitLen);
void messageProcessing(char* message, unsigned int* h0, unsigned int* h1,
                       unsigned int* h2, unsigned int* h3, unsigned int* h4);
void tempSHA();

#endif
