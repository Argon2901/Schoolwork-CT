#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prog4.h"

int main(){
    char originalString[9];
    char overflowString[] = {0};
    char stringSize = 0;


    for(int i = 0; i < (int)sizeof(originalString); i++){
        originalString[i] = 0;
    }
    scanf("%9[^\n]", originalString);

    if(overflowString[0] != 0){
        printf("String must have no whitespace characters\n");
        exit(-1);
    }

    //validate string
    stringSize = validateString(originalString, (int)sizeof(originalString));


    //to lower case 
    for(int i = 0; i < (int)sizeof(originalString); i++){
        originalString[i] = tolower(originalString[i]);
    }
    
    //creating permutations
    int totalPermutations = factorial(stringSize);
    char** permutationArray = malloc(sizeof(char*) * totalPermutations); //d
    int uniquePermutations = 0; 
    createPermutations(permutationArray, 0, stringSize - 1, originalString, &uniquePermutations);

    //sort permutations
    qsort(permutationArray, uniquePermutations, sizeof(char*), compStrings);


    //print permutations
    for(int i = 0; i < uniquePermutations; i++){
        printf("%s\n", permutationArray[i]);
    }
    
    //deallocation of memory
    for(int i = 0; i < uniquePermutations; i++){
        free(permutationArray[i]);
    }
    free(permutationArray);

    return 0;
}
