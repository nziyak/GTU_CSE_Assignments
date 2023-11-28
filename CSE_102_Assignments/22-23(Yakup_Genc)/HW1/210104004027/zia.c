#include <stdio.h>
#include "zia.h"

int part1(int a, int b)
{
     
     if (a == 0) 
     {
          return b; //if one of the numbers is 0, automatically their gcd is other
     }
     
     
     else if( a != 0 && b != 0)
     {
          
          while (b > 0) 
          {
                int c; //integer which holds remainder of a on b
            
                c = a % b;
                a = b;
                b = c;    
          }
          
          return a; //in result, a is holding GCD value
     }       
              
     
}


int part2(int a, int b)
{
     printf("\nfirst number: %d\nsecond number: %d\nResult:\n%20d\n%20d\n+\n--------------------\n%20d\n\n", a, b, a, b, a+b); //gives 10 digits to each number and print numbers with their sum
     printf("----------------------------------------------------\n");
}


int part3(int a, int b) 
{
     
     int temp;
     
     temp = b;
     
     printf("\nfirst number: %d\nsecond number: %d\nResult:\n%20d\n%20d\n*\n--------------------\n%20d\n", a, b, a, b, a*(b%10)); //gives appropriate digits to each number and print numbers with their product
     
     for(int i = 19; temp > 1; --i)//I started the loop from i=19 because first multiplication( a*(b%10 ) is printed with 20 character width
     {
     
          temp /= 10; //if a number is divided by 10, it's last digit will be deleted. if number is equated to that, it will be one digit less same number. i did it for can multiply first number with second numbers greater digits.
          printf("%*d", i, ((temp%10)*a));//taking modulus of number with 10 gives last digit of the number. thanks to that, we can multiply first number with the last digit of the second number. because it is the format that is wanted. and in every loop, i decreases so that it will print 1 character left. it provides the wanted format.
          printf("\n");//i add new line for making the same thing or continue according to if number is zero after previous divisions or not.
     
     }
     
     printf("+\n--------------------\n"); //the reason of these lines are so width is allow the user make more aesthetic operations due to desired format
     
     printf("%20d\n\n", a*b); //result is printed
     
     printf("----------------------------------------------------\n");
     
}


int part4(int a)
{
    if(a < 1 || 10 < a)
    {
       printf("entered number is: %d\n", a);//i added this because you can see what i entered in output screenshots
       printf("Invalid input\n"); //if number is less than 1 or greater than 10 print Invalid input.
    }
    
    else
    {
       if(a > 5)
       {
          printf("entered number is: %d\n", a);
          printf("The integer you entered is greater than 5\n"); 
       }
       
       else
       {
          printf("entered number is: %d\n", a);
          printf("The integer you entered is less than or equal to 5\n");
       }
    }
}
