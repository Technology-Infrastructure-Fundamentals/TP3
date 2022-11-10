#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Auxiliar functions --------------------------------------------------------------------

int decimalToBinary(int number){
    
    // This function converts a positive decimal number to a positive binary number.

    if(number < 2){
        // If the number is 0 or 1, the binary number is the same decimal number.
        return number;
    }else{
        // Else, convert the number with de division algorithm.
        return decimalToBinary(number/2) * 10 + number%2;
    }
    
}

char * positiveBinaryToNegativeBinary(char * positiveBinary, int rotations){
    
    // This function converts a positive decimal number to its negative binary number.
        
    bool negate = false;
    int rotationCount = 0;
    char *binaryNegativeNumber = malloc(32);
    for(int i = 31; i>=0; i--){
        // Look for the first from right to left 1 and when it is found, the rest of
        // numbers are negated.
        if(negate && rotationCount > rotations){
            if(positiveBinary[i] == '0'){
               binaryNegativeNumber[i] = '1'; 
            }
            else{
                binaryNegativeNumber[i] = '0';
            }
        }else{
            binaryNegativeNumber[i] = positiveBinary[i];
        }
        if(positiveBinary[i] == '1'){
            negate = true;
        }
        rotationCount++;
    } 

    return binaryNegativeNumber;
    
}

char * bitsCompletion(int number){
    
    // This function completes 32 bits for a binary number given as an integer number.
    
    // Convert the number into a string and create an empty string with 32
    // characters.
    char *string = malloc(32);
    sprintf(string, "%i", number);
    char *completed = malloc(32);
    
    int position = 31;
    for(int i = 31; i>=0; i--){
        if(string[i] != NULL){
            // Insert into the empty string the characters of the binary.
            completed[position] = string[i];
            position--;
        }
    }
    
    for(int i = 0; i<32; i++){
        // Once all the strings of the binary number are inserted to the empty
        // string, the NULL spaces i are filled with 0.
        if(completed[i] == NULL){
            completed[i] = '0';
        }
    }
    
    return completed;
}

char * decimalNumberToBinaryVector(int number){
    
    // This function converts a deciaml number to its binary in a string.
    
    if(number < 0){
        // If the number is negative, the function takes its absolute value.
        number = -1*number;   
    }
    
    char * binaryVector = malloc(32);
    int position = 0;
    char *binaryString;
    int binaryNumber = decimalToBinary(number);
    binaryString = bitsCompletion(binaryNumber); 
    for(int j = 0; j<32; j++){
        binaryVector[position] = binaryString[j];
        position++;
    }
    
    return binaryVector;
    
}

// Rotator--------------------------------------------------------------------------------

char * rotator(char* vector, int vectorSize){
    
    // This function performs the rotation proccess
    
    // The firts bit of a number is placed as the last bit of an empty string.
    char * resultVector = malloc(32*vectorSize);
    resultVector[(32*vectorSize)-1] = vector[0];
    
    int position = (32*vectorSize)-2;
    for(int i = (32*vectorSize)-1; i>0; i--){
        // The the rest of bits of the number are placed in the same order on the string.
        resultVector[position] = vector[i];
        position--;
    }
    
    return resultVector;
    
}

// Data structure-------------------------------------------------------------------------

struct programData
    {
        
        int vectorSize;
        int movesAmount;
        int *vector;
        
    };
    
// Main----------------------------------------------------------------------------------

void main()
{
    
    // Variables initialization
    struct programData data;
    bool accept = true;
    
    // Ask to the user for the size of vector and validate that the input value is larger
    // than 0
    while(accept){
        printf("Type the vector size: ");
        scanf("%d", &data.vectorSize);
       if(data.vectorSize <= 0){
        printf("The input number is incorrect, it must be larger than 0 \n");   
       }else{
            accept = false;
       }
    }
    
    // Initialize pointer to the vector of integers with the size asked to the user.
    data.vector = (int*)calloc(data.vectorSize, sizeof(int));

    // Initialize the vector
    for(int i = 1; i<=data.vectorSize; i++){
        int inputNumber;
        printf("Type the number for the position %d of the vector: ", i);
        scanf("%d", &inputNumber);
        data.vector[i-1] = inputNumber;
    }
    
    // Ask to user for the moves amount of the rotation and validate that the input value is
    // between 1 and 32
    accept = true;
    while(accept){
        printf("Type the moves amount: ");
        scanf("%d", &data.movesAmount);
       if(data.movesAmount < 1 || data.movesAmount > 32){
        printf("The input number is incorrect, it must be between 1 and 32 \n");   
       }else{
            accept = false;
       }
    }
    
    // Join in a string the bits of the numbers inserted.
    int insertPosition = 0;
    char * unifiedVector = malloc(32 * data.vectorSize);
    for(int j = 0; j < data.vectorSize; j++){
        int i = 0;
        char * binaryVector = decimalNumberToBinaryVector(data.vector[j]);
        if(data.vector[j] < 0){
            binaryVector = positiveBinaryToNegativeBinary(binaryVector, 0);   
        }
        for(int i = 0; i<32; i++){
            unifiedVector[insertPosition] = binaryVector[i];
            insertPosition++;
        };
    }
    
    // Rotate the string of bits.
    int i = 1;
    while(i <= data.movesAmount){
        unifiedVector = rotator(unifiedVector, data.vectorSize);
        i++;
    }
    
    // Print the output.
    i = 31;
    int bitsGroupPosition = 0;
    int numberPosition = 0;
    char * bitsGroup = malloc(32);
    for(int j = 0; j < 32*data.vectorSize; j++){
        bitsGroup[bitsGroupPosition] = unifiedVector[j];
        bitsGroupPosition++;
        if(j == i){
            printf("\n");
            printf("v[%d] = %s", numberPosition, bitsGroup);
            numberPosition++;
            bitsGroupPosition = 0;
            i += 32;
        }
    }
    
}