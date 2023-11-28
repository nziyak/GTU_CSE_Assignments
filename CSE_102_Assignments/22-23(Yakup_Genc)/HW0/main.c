#include <stdio.h>
#include "util.h"


int main() {

    //two number will be taken from user and the third one is uninitialized 
    int num1, num2, num3 , den1, den2, den3;
    
    printf("please give the numerator and denominator of the first fractional number: ");
    scanf("%i %i", &num1, &den1);
    fraction_print(num1, den1); //prints the numerator and denominator of the first fractional number
    printf("\n");
    
    printf("please give the numerator and denominator of the second fractional number: ");
    scanf("%i %i", &num2, &den2);
    fraction_print(num2, den2); //prints the numerator and denominator of the second fractional number
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3); //addition function is called
    fraction_print(num3, den3); // prints the resultant fractional number
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3); //substraction function is called
    fraction_print(num3, den3); // prints the resultant fractional number
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3); //multiplication function is called
    fraction_print(num3, den3); // prints the resultant fractional number
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3); //division function is called
    fraction_print(num3, den3); // prints the resultant fractional number
    printf("\n"); 

    return(0);
}
