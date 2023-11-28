#include <stdio.h>
#include "zia.h"


int main()
{
   
   int a, b; //variables
   
   printf("please give two numbers to find their GCD: ");
   scanf("%d %d", &a, &b);
   
   if (a == 0 && b == 0) 
   {
      printf("invalid input.\n"); //if both are 0, because of 0 can not be in denominator, it is error   
   }
   
   else 
   {
      printf("GCD of the two number you entered is: %d\n\n", part1(a, b)); //because of part1 function returns directly the GCD, i mention it in printf.
   }
   
   printf("please give two numbers to find sum of them: ");
   scanf("%d %d", &a, &b);
   part2(a, b); //i have printf in part2 function so i wrote it seperately
   
   printf("please give two numbers to multiply them: ");
   scanf("%d %d", &a, &b);
   part3(a, b); ////i have printf in part3 function so i wrote it seperately
   
   printf("please give an integer between 1-10 (1 and 10 are valid) to compare it with 5: ");
   scanf("%d", &a);
   part4(a); //i have printf in part4 function so i wrote it seperately
   
   return 0;
}


