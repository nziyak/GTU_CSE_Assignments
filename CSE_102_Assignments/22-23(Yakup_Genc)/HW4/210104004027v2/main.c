#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//each number corresponds to a play mode
#define Stone 1
#define Paper 2
#define Scissors 3


void order(void); //function that makes order operations

double receipt(int, int, FILE *); //function that prints receipt to receipt.txt

void stpasci(void);


int main()
{
   
   //beginning of the restaurant program 
   order();
   
   //beginning of the stone paper scissors
   stpasci();                              
    
}
    

void order(void)
{
    
    FILE *outp_m, *outp_r; //menu output, receipt output
    
    int product, servings;
    char stu; //student or not variable 
    double total; //total price
    
    //file openings
    outp_m = fopen("menu.txt", "w");
    outp_r = fopen("receipt.txt", "w");
    
    if (outp_m == NULL) 
    {
       printf("Dosya açma hatası!");
    }
    
    else//printing the menu
    {
	
	fprintf(outp_m, "1. Beyran\n\n");
	fprintf(outp_m, "2. Kelle Paça\n\n");
	fprintf(outp_m, "3. Tırnak Paça\n\n");
	fprintf(outp_m, "4. Klasik Tavuk Dürüm\n\n");
	fprintf(outp_m, "5. Boru Dürüm\n\n");
	fprintf(outp_m, "6. Zurna Dürüm\n\n");
	fprintf(outp_m, "7. Et Dürüm\n\n");
	fprintf(outp_m, "8. Cağ Kebap(5 şiş)\n\n");
	fprintf(outp_m, "9. Pesto Spagetti\n\n");
	fprintf(outp_m, "10. Napoliten Fettucine\n\n");
	fprintf(outp_m, "11. Su\n\n");
	fprintf(outp_m, "12. Limonata\n\n");
	fprintf(outp_m, "13. Ayran\n\n");
	fprintf(outp_m, "14. Damla Sakızlı Muhallebi\n\n");
	fprintf(outp_m, "15. Kadayıf Dolması\n\n");
	fprintf(outp_m, "16. Sütlaç\n\n");
        
        //before asking products and their servings, asking if the customer is student or not
        fprintf(outp_r, "Are you student? (Y/N): ");
        scanf(" %c", &stu);
        fprintf(outp_r, "%c\n\n", stu);
        
        //printing the receipt
        //printing the student no
        fprintf(outp_r, "210104004027");
        
        //printing the current date and time
        time_t now = time(NULL);    // get the current time
        struct tm *t = localtime(&now);   // convert to local time

        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d / %H:%M:%S", t);   // format the time as a string
        
        fprintf(outp_r, "           %s\n", buf);   // write the string to the file
        fprintf(outp_r, "--------------------------------------------\n\n");
        fprintf(outp_r, "Product                       Price (TL)\n\n");
        fprintf(outp_r, "--------------------------------------------\n\n");
        
        //taking products and their servings
        do
        {	   
	    
	     fprintf(outp_m, "Please choose a product(1-16): ");
	     scanf("%d", &product);
	     
	     if(product == 0)
	     {
                break;	       
	     }
	     
	     fprintf(outp_m, "%d\n", product);
	     
	     fprintf(outp_m, "How many servings do you want? ");
	     scanf("%d", &servings);
	     fprintf(outp_m, "%d\n", servings);
             
             total += receipt(product, servings, outp_r); //summing the price that comes from receipt() in every loop
             
        }while(product != 0);
        
        fprintf(outp_r, "Total:                         %lf\n\n", total);
        
        if(stu == 'y' || stu == 'Y')
        {
            fprintf(outp_r, "Student Discount:             -%lf\n\n", (12.5 * total) / 100 );
            total -= (12.5 * total) / 100;
        }
        
        if(total >= 150)
        {
            fprintf(outp_r, "150 TL or more Discount:      -%lf\n\n", total / 10 );
            total -= total/10;
        }
        
        fprintf(outp_r, "--------------------------------------------\n\n");
        
        fprintf(outp_r, "Price:                         %lf\n\n", total);
        fprintf(outp_r, "Price + VAT:                   %lf\n", total + ((18*total) / 100));
        
        //closing files
        fclose(outp_m);
        fclose(outp_r);
    }

}


double receipt(int product, int servings, FILE *outp_r)
{
    
    double sum = 0; //price should be initialized to 0 in every loop to print next product's price correctly
  
    switch(product)
    {
        case 1:
        
               fprintf(outp_r, "%d* Beyran                     %lf\n\n", servings, 35.5*servings);
               
               sum = 35.5*servings; 
               
               break;
               
        case 2:
        
               fprintf(outp_r, "%d* Kelle Paça                 %lf\n\n", servings, 37.5*servings);
               
               sum = 37.5*servings; 
               
               break;
        
        case 3:
        
               fprintf(outp_r, "%d* Tırnak Paça                %lf\n\n", servings, 37.5*servings);
               
               sum = 37.5*servings; 
               
               break;
        
        case 4:
        
               fprintf(outp_r, "%d* Klasik Tavuk Dürüm         %lf\n\n", servings, 26.0*servings);
               
               sum = 26.0*servings; 
               
               break;
               
        case 5:
               
               fprintf(outp_r, "%d* Boru Dürüm                 %lf\n\n", servings, 30.0*servings);
               
               sum = 30.0*servings;
               
               break;
               
        case 6:
               
               fprintf(outp_r, "%d* Zurna Dürüm                %lf\n\n", servings, 34.0*servings);
               
               sum = 34.0*servings;
               
               break;
               
        case 7:
               
               fprintf(outp_r, "%d* Et Dürüm                   %lf\n\n", servings, 36.5*servings);
               
               sum = 36.5*servings;
               
               break;
               
        case 8:
               
               fprintf(outp_r, "%d* Cağ Kebap(5 şiş)           %lf\n\n", servings, 80.0*servings);
               
               sum = 80.0*servings;
               
               break;
               
        case 9:
                
               fprintf(outp_r, "%d* Pesto Spagetti             %lf\n\n", servings, 42.5*servings);
               
               sum = 42.5*servings;
               
               break;
               
        case 10:
                 
               fprintf(outp_r, "%d* Napoliten Fettucine        %lf\n\n", servings, 44.35*servings);
               
               sum = 44.35*servings;
               
               break;
        
        case 11:
                 
               fprintf(outp_r, "%d* Su                         %lf\n\n", servings, 5.0*servings);
               
               sum = 5.0*servings;
               
               break;
               
        case 12:
                 
               fprintf(outp_r, "%d* Limonata                   %lf\n\n", servings, 15.0*servings);
               
               sum = 15.0*servings;
               
               break;
               
        case 13:
                 
               fprintf(outp_r, "%d* Ayran                      %lf\n\n", servings, 8.0*servings);
               
               sum = 8.0*servings;
               
               break;
               
        case 14:
                 
               fprintf(outp_r, "%d* Damla Sakızlı Muhallebi    %lf\n\n", servings, 28.5*servings);
               
               sum = 28.5*servings;
               
               break;
               
        case 15:
                  
               fprintf(outp_r, "%d* Kadayıf Dolması            %lf\n\n", servings, 35.0*servings);
               
               sum = 35.0*servings;
               
               break;                                                                             
        
        case 16:
                  
               fprintf(outp_r, "%d* Sütlaç                     %lf\n\n", servings, 33.4*servings);
               
               sum = 33.4*servings;
               
               break;                                                         
    }
     
    return sum;   

}


void stpasci(void)
{

    int usel, csel; //user selection, computer selection
    
    printf("\n----------beginning of the stone paper and scissors.----------");
    printf("\n\nPlease make a choice!\n");
    printf("1: Stone, 2: Paper, 3: Scissors  ");
    scanf("%d", &usel); //user selects
    
    csel = rand() % 3 + 1; //computer selects randomly by generating random number 1-3
    
    switch(usel)
    {
    
          case 1: //case user is stone
          
                 switch(csel)
                 {
                 
                       case 1: //case computer is stone
                              
                              printf("You chose Stone. I chose Stone. It's a tie!\n");
                              
                              break;
                       
                       case 2: //case computer is paper
                              
                              printf("You chose Stone. I chose Paper. Paper covers stone. I won!\n");
                              
                              break;
                       
                       case 3: //case computer is scissors
                              
                              printf("You chose Stone. I chose Scissors. Stone crushes scissors. You won!\n");
                              
                              break;               
                 
                 }
                 
                 break;
                             
          
          case 2: //case user is paper
          
                 switch(csel)
                 {
                 
                       case 1: //case computer is stone
                              
                              printf("You chose Paper. I chose Stone. You won!\n");
                              
                              break;
                       
                       case 2: //case computer is paper
                              
                              printf("You chose Paper. I chose Paper. It's a tie!\n");
                              
                              break;
                       
                       case 3: //case computer is scissors
                              
                              printf("You chose Paper. I chose Scissors. Scissors cuts paper. I won!\n");
                              
                              break;               
                 
                 }
                 
                 break;
                 
          
          case 3: //case user is scissors
          
                 switch(csel)
                 {
                 
                       case 1: //case computer is stone
                              
                              printf("You chose Scissors. I chose Stone. Stone crushes scissors. I won!\n");
                               
                              break;
                       
                       case 2: //case computer is paper
                              
                              printf("You chose Scissors. I chose Paper. Scissors cuts paper. You won!\n");
                              
                              break;
                       
                       case 3: //case computer is scissors
                              
                              printf("You chose Scissors. I chose Scissors. It's a tie!\n");
                              
                              break;               
                 
                 } 
                 
                 break;
    }
}

