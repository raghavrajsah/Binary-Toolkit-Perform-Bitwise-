

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#define MAX_BINARY_LEN 32


void print_bits(int number, int size, char* result) { 
    //prints a decimal as its binary equivalent    
    printf("0b");
    //sprintf(result, "0b");
    
    for (int i = size - 1; i >= 0; i--) {
        printf("%c", '0' + ((number >> i) & 1));
        sprintf(result + 2 + size - 1 - i, "%c", '0' + ((number >> i) & 1));
    }
}

// ******************************************* PART 1 ****************************************************** //

/*
   This function converts a binary representation to decimal, and optionally prints details.
   
   Arguments:
   - number: Binary representation of the number
   - option: Additional options for the conversion signed or unsigned
   - printDetails: Flag indicating whether to print conversion details (1 for true, 0 for false)
   
   Returns:
   - The decimal equivalent of the binary number. We need this for Bitwise Operations
*/
int B2D(char number[], char option[], int printDetails) {
    //converts binary to decimal by iterating through the binary string, left shifting a 1 into 
    //the appropriate place based on the string, and then adding the contribution to the final sum

    int sum = 0;
    int power[MAX_BINARY_LEN];
    int decimal[MAX_BINARY_LEN];
    int len = 0;
    int j = 0;

    //concverting the numer:
    for (int i = 2; i < strlen(number); i++) {
        if (number[i] == '1') { //if the ith place is a number
            int contribution = 1 << (strlen(number) - i - 1); //shift the contribution into the ith place
            if (i == 2 && *option == 's') { //if it's the MSD of a signed number, the contribution should
                contribution = -contribution; //be negative
            }
            sum += contribution; //add contribution to final sum
            power[j] = (strlen(number) - i - 1); //keep track of power and contribution
            decimal[j] = contribution;
            j++;
            len++;
        }
    }

    //printing the number:
    if (printDetails) {
        for (int i = 0; i < len; i++) {
            if (*option == 's' && power[i] == strlen(number) - 3 && i == 0) {
                if(i != len -1){
                    printf("-2^%d + ", power[i]);
                }
                else{
                    printf("-2^%d ", power[i]);
                }
            } else if (i != len - 1) {
                printf("2^%d + ", power[i]);
            } else {
                printf("2^%d", power[i]);
            }
        }
        printf("\n");
        for (int i = 0; i < len; i++) {
            if(i != len - 1){
                printf("%d + ", decimal[i]);
            } else {
                printf("%d", decimal[i]);
            }
                
        }
        printf("\n");
        printf("%d\n", sum);
    }

    return sum;
}

// ******************************************* PART 2 ****************************************************** //
/*
   This function converts a decimal number to binary and prints the specified number of bits.
   
   Arguments:
   - number: Decimal number to be converted
   - bits: Number of bits to print in the binary representation
*/
void D2B(int number, int bits){; 
        //converts decimal to binary by mimicking the subtracting powers of two method, but using the 
        //left shift operator instead of pow or exp2
        char result[MAX_BINARY_LEN+3];
        int numT = number;
        //if(number > 0){numT = numT / 2;} //makes sure MSD is 0 if number is neg
        int tracker = 0;
        int final = 0;
        int powers[MAX_BINARY_LEN];
        int finals[MAX_BINARY_LEN];
        //calculates number:
        while(final != number && tracker <= bits){
            int contribution = 1;
            int place = 0;
            if(tracker == 0 && number < 0){ //makes sure MSD is 1 if number is negative
            contribution = contribution << (bits -1);
                contribution = -contribution;
                place = bits - 1;
            }
            else{
                while(contribution <= (numT / 2)){ //while contribution is less than the num/2     
                contribution = contribution<<1;  //keep shifting it left
                place++;  
                } 
            } 
            powers[tracker] = place; //keeps track of powers and the partial sums
            finals[tracker] = final;
            final += contribution;
            numT = numT - contribution;
            tracker++;
                
        }
        tracker--;

        //prints number:
        if(powers[0] >= bits || final < number || (number > 0 && powers[0] == bits -1)){
            printf("overflow\n");
        } else if(final > number){
            printf("underflow\n");
        } else {
            int j = 0;
            int cond = 1;
            char str[] = "-2";
            for(int i = 0; i < bits; i++){
                if(i != 0){
                    str[0] = '2';
                    str[1] = '\0';
                }
                if(j < tracker && powers[j] == bits - i - 1){         
                    printf("%d + %s^%d = %d\n", finals[j], str, powers[j], finals[j+1]);
                    j++;
                } else if(j != tracker || powers[j] != bits - i - 1) {
                    printf("%s^%d doesn't fit\n", str, bits - 1 - i);
                } 
                    
                else if (j == tracker && cond){
                    printf("%d + %s^%d = %d\n", finals[j], str, powers[tracker], final);
                    cond = !cond;
                } 
            }
            print_bits(final, bits, result);
            printf("\n");
        }
}

// ******************************************* PART 3 ****************************************************** //
/*
   This function performs bitwise operations based on the given arguments.
   It takes two binary representations, performs the specified operation, 
   and prints the results in a formatted manner.
   
   Arguments:
   - firstNum: Binary representation of the first number
   - operation: Binary operation to be performed (&, |, <<, >>)
   - secondNum: Binary representation of the second number
*/
void perform_bitwise_operation(char firstNum[], char operation[], char secondNum[]) {
    char s[] = {'u'};
    int size =0;

    // Convert binary representations to decimal
    int decFirstNum = B2D(firstNum, s, 0);
    int decSecondNum = B2D(secondNum, s, 0);

    // Determine the size for formatting
    if(strlen(firstNum)<strlen(secondNum)){
        size=strlen(secondNum)-2;;
    }
    else{
        size=strlen(firstNum)-2;;
    }

    // Array to store the binary result from print_bits function
    char result[MAX_BINARY_LEN + 3];

    // Handle bitwise AND and OR operations
    if (*operation == '&' || *operation == '|') {
        printf("  ");
        print_bits(decFirstNum, size,result);
        printf("\n");
        printf("%c ", *operation);
        print_bits(decSecondNum, size,result);
        printf("\n");

        // Print a line of dashes for separation
        for (int i = 0; i <= size + 3; i++) {
            printf("-");
        }
        printf("\n");

        // Print the result of the bitwise operation
        if (*operation == '&') {
            printf("  ");
            print_bits(decFirstNum & decSecondNum, size, result);
        } else if (*operation == '|') {
            printf("  ");
            print_bits(decFirstNum | decSecondNum, size, result);
        }

        // Print the final decimal result
        printf(" = ");
        printf("%d ", B2D(result, s, 0));
    } 
    
    // Handle bitwise shift operations
    else if (*operation == '<' || *operation == '>') {
        print_bits(decFirstNum, size,result);

        if (*operation == '<') {
            printf(" << ");
            printf("%d", decSecondNum);
            printf(" = ");
            print_bits(decFirstNum << decSecondNum, size,result);
            printf(" = ");     
            printf("%d ", B2D(result, s, 0));
        } else {
            printf(" >> ");
            printf("%d", decSecondNum);
            printf(" = ");
            print_bits(decFirstNum >> decSecondNum, size,result);
            printf(" = ");
            printf("%d ", B2D(result, s, 0));
        }
    }

    // Print a newline for formatting
    printf("\n");
}


// ******************************************* MAIN ****************************************************** //
int main(int argc, char *argv[]) {

    if (argc == 3) {
        // Store first argument in array
        char number[MAX_BINARY_LEN + 2 + 1];
        strcpy(number, argv[1]);

        // Store second argument in array
        char option[3];
        strcpy(option, argv[2]);

        if(number[0]=='0' && number[1]=='b'){
            B2D(number, option, 1);   // Converts Binary to Decimal
        }
        else{
            int num = atoi(number);
            int bits = atoi(option);
            D2B(num, bits); //converts decimal to binary
        }
    }
    else if (argc == 4){
        char firstNum[MAX_BINARY_LEN + 2 + 1];
        strcpy(firstNum, argv[1]);

        char operation[3];
        strcpy(operation, argv[2]);

        char secondNum[MAX_BINARY_LEN + 2 + 1];
        strcpy(secondNum, argv[3]);

        perform_bitwise_operation(firstNum, operation, secondNum);
    }
    else {
        printf("Invalid number of arguments\n");
        return 1;
    }
}
