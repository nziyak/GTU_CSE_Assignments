#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) 
{
     printf("%d//%d", numerator, denominator);
} /* end fraction_print */


void fraction_add(int n1, int d1, int n2, int d2, int *n3, int *d3) 
{
    
    *n3 = n1*d2 + n2*d1; //to add two fractional number; numerator of first number should be multiplied by denominator of second one, and this should be added with (numerator of second * denominator of first)
    
    *d3 = d1*d2; //then the denominator is equal to product of denominators
     
     fraction_simplify(n3, d3); //simplifies the resultant fractional number

} /* end fraction_add */


void fraction_sub(int n1, int d1, int n2, int d2, int *n3, int *d3) 
{
    
    *n3 = n1*d2 - n2*d1; //to subtract two fractional number; numerator of first number should be multiplied by denominator of second one, and this should be subtracted by (numerator of second * denominator of first)
    
    *d3 = d1*d2; //then the denominator is equal to product of denominators
     
     fraction_simplify(n3, d3); //simplifies the resultant fractional number

} /* end fraction_sub */


void fraction_mul(int n1, int d1, int n2, int d2, int *n3, int *d3) 
{
    
    *n3 = n1*n2; //to multiply a fractional number with other, basically their numerators should be multiplied
    
    *d3 = d1*d2; //then their denominators are should be multiplied, too
     
     fraction_simplify(n3, d3); //simplifies the resultant fractional number

} /* end fraction_mul */


void fraction_div(int n1, int d1, int n2, int d2, int *n3, int *d3) 
{
    
    *n3 = n1*d2; //to divide a fractional number by other, basically one of their numerators should be divided by other
    
    *d3 = n2*d1; //then their denominators are should be divided, too
     
     fraction_simplify(n3, d3); //simplifies the resultant fractional number

} /* end fraction_div */


/* Simplifies the given fraction such that they are divided by their GCD */
void fraction_simplify(int *n, int *d) 
{
     
     int gcd;
     
     for(int i = 1; i <= *n && i <= *d; ++i)
     {
        // Checks if i is factor of both numerator and denominator
        if(*n % i == 0  &&  *d % i == 0)
        {
            gcd = i; //gcd is found
        }    
     }
     
     *n = *n / gcd;  //numerator is simplified
     *d = *d / gcd;  //denominator is simplified
     
} /* end fraction_simpl*/
