#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Auxiliar functions --------------------------------------------------------------------

int decimalToBinary(int number){
    
    if(number < 2){
        return number;
    }
    else{
        return decimalToBinary(number/2) * 10 + number%2;
    }
    
}

char * positiveBinaryToNegativeBinary(char * positiveBinary, int rotations){
        
    bool negate = false;
    int rotationCount = 0;
    
    char *binaryNegativeNumber = malloc(32);
    for(int i = 31; i>=0; i--){
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
    char *string = malloc(32);
    sprintf(string, "%i", number);
    char *completed = malloc(32);
    int position = 31;
    for(int i = 31; i>=0; i--){
        if(string[i] == NULL){
        }else{
            completed[position] = string[i];
            position--;
        }
    }
    for(int i = 0; i<32; i++){
        if(completed[i] == NULL){
            completed[i] = '0';
        }
    }
    return completed;
}

char * decimalNumberToBinaryVector(int number){
    
    if(number < 0){
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

char * rotator(char* vector, int vectorSize){
    
    char * resultVector = malloc(32);
    resultVector[31] = vector[0];
    int position = 30;
    for(int i = 31; i>0; i--){
        resultVector[position] = vector[i];
        position--;
    }
    return resultVector;
}

char * bitsGrouper(char* vector, int startIndex){
    char * resultVector = malloc(32);
    int position = 0;
    for(int i = startIndex; i<startIndex+32; i++){
        resultVector[position] = vector[i];
        position++;
    } 
    printf("%c", resultVector[31]);
    return resultVector;
}
    
long long int binaryToDecimal(long long int numero){
    long long int digito, poscion=0, resultado = 0;
    int vector[] = {1,2,4,8,16,32,64,128,256};
    while(numero>0){
        digito = numero%10;
        if(digito==1){
            resultado = resultado+vector[poscion];
        }
        poscion++;
        numero = numero/10;
    }
    return resultado;
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
    
    printf("\n");
    
    for(int j = 0; j < data.vectorSize; j++){
        int i = 0;
        char * binaryVector = decimalNumberToBinaryVector(data.vector[j]);
        while(i < data.movesAmount){
            binaryVector = rotator(binaryVector, data.vectorSize);
            i++;
        }

        if(data.vector[j] < 0){
            binaryVector = positiveBinaryToNegativeBinary(binaryVector, data.movesAmount);   
        }
        printf("v[%d] = %s\n", j, binaryVector);


    }
    
}
