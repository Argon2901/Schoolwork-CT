
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "prog4.h"


int validateString(char input[], int length){
    char reachedEndString = 0;
    int stringSize = 0;

    for(int i = 0; i < length; i++){
        
        if(reachedEndString){
            if(input[i] == 0){
                continue;
            } else{
                printf("String must be 8 characters or less and not contain spaces.\n");
                exit(1);
            }
        }
        
        if(i == 8 && input[i] != 0){
            printf("String must be 8 characters or less.\n");
            exit(1);
        }

        if(input[i] == 0){
            reachedEndString = 1;
            stringSize = i;
            continue;
        }

        if(!isalpha(input[i])){
            printf("String must not contain non-alpha characters.\n");
            exit(1);
        }
    }

    return stringSize;
}

int factorial(int n){
    int factorial = 1;
    for(; n > 0; n--){
        factorial *= n;
    }
    return factorial;
}

void createPermutations(char* permArray[], int leftChar, int rightChar, char* string, int* arrayPosition){
    if (leftChar==rightChar){

        for(int i = 0; i < *arrayPosition; i++){
            if(!strcmp(string, permArray[i])){
                return;
            }
        }
        permArray[*arrayPosition] = malloc(rightChar + 1);
        strncpy(permArray[*arrayPosition], string, rightChar + 1);
        (*arrayPosition)++;


        return;
    } else {
        for (int i = leftChar; i <= rightChar; i++) {
            swap(&string[leftChar], &string[i]);
            createPermutations(permArray, leftChar+1, rightChar, string, arrayPosition);
            swap(&string[leftChar], &string[i]);
        }
    }
}

void swap(char* left, char* right){
    char temp = *left;
    *left = *right;
    *right = temp;
}

int compStrings(const void* str1, const void* str2){
    char* s1 = *(char**)str1;
    char* s2 = *(char**)str2;
    return strcmp(s1, s2);
}

