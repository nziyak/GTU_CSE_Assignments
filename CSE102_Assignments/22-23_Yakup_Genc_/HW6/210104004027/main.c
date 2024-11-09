#include <stdio.h>
#include <stdlib.h>

#define MAX 300

//main menu
void mainmenu();
//file operation functions
void fileop(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX], char branch[MAX][15], int curr_stock[MAX], int stock_pID[MAX]);
void add_new_p(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX], FILE *writer);
void delete_p(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX]);
void update_p(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX]);
void add_feature_to_p(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX]);
void new_stock_entry(char branch[MAX][15], int curr_stock[MAX], int stock_pID[MAX]);
void delete_stock_entry(char branch[MAX][15], int curr_stock[MAX], int stock_pID[MAX]);
void update_stock_entry(char branch[MAX][15], int curr_stock[MAX], int stock_pID[MAX]);
//query product functions
void query_product(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX]);
//check stock status functions
void check_stock_status(char branch[MAX][15],  int curr_stock[MAX], int stock_pID[MAX]);
//brand stock control
void brand_stock_control(char brand[MAX][5], int stock_pID[MAX], double price[MAX], int curr_stock[MAX], int pIDlist[150], int curr_stocklist[150], double pricelist[150]);
//stock report
void stock_report(int pIDlist[150], int curr_stocklist[150]);
//bubble sort
void bubbleSort(int arr[], int n);
//compare strings
int compareStrings(char string1[], char string2[]);

int main()
{
    mainmenu();
}


void mainmenu()
{
    int sel;
    
    static char type[MAX]; //product type
    static char name[MAX][8]; //product name
    static char brand[MAX][5]; //product brand
    static double price[MAX]; //product price
    
    static char branch[MAX][15]; //branch city name
    int curr_stock[MAX]; //current stock
    int stock_pID[MAX]; //pID values for stocks
    
    int pIDlist[150], curr_stocklist[150];
    double pricelist[150];
    
    printf("Welcome operator, please select an option to continue:\n\n1-File Operations\n2-Query products\n3-Check stock status\n4-Stock control by brand\n5-Brand Stock Control\n6-Export report\n7-Main menu\n");
    scanf("%d", &sel);
    
    switch(sel)
    {
        case 1:
               
               fileop(type, name, brand, price, branch, curr_stock, stock_pID);

               break;

        case 2:
               
               query_product(type, name, brand, price);

               break;

        case 3:
               
               check_stock_status(branch, curr_stock, stock_pID);
               
               break;

        case 4:
              
               brand_stock_control(brand, stock_pID, price, curr_stock, pIDlist, curr_stocklist, pricelist);
              
               break; 

        case 5:
               
               stock_report(pIDlist, curr_stocklist);
                
               break;

        case 6:
              
              mainmenu();
              
     }

}

void fileop(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX], char branch[MAX][15], int curr_stock[MAX], int stock_pID[MAX])
{
    FILE *writer;
    
    int sel, end = 0;
    
    do{
       
       printf("please select an operation:\n1)Add New Product\n2)Delete Product\n3)Update Product\n4)Add Feature to Product\n5)New Stock Entry\n6)Delete Stock Entry\n7)Update Stock Entry\n8)Main Menu\n9)exit");
       scanf("%d", &sel);
       
       switch(sel)
       {
           case 1:
               
                  add_new_p(type, name, brand, price, writer);
               
                  break;

           case 2:
               
                  delete_p(type, name, brand, price);

                  break;

           case 3:
               
                  update_p(type, name, brand, price);

                  break;

           case 4:
               
                  add_feature_to_p(type, name, brand, price);

                  break;

           case 5:
               
                  new_stock_entry(branch, curr_stock, stock_pID);

                  break;   
        
           case 6:
               
                  delete_stock_entry(branch, curr_stock, stock_pID);

                  break;

           case 7:
               
                  update_stock_entry(branch, curr_stock, stock_pID);

                  break;
       
           case 8:
               
                  mainmenu();

                  break;
        
           default:
                
                   exit(0);
                
      }
    
    }while(sel < 9 && sel > 0);
}

void add_new_p(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX], FILE *writer)
{
    static int pID = 1; 
    
    writer = fopen("products.txt", "a");
    
    printf("please type new product's type: ");
    scanf(" %c", &type[pID-1]); //decrement 1 because pID starts from 1 and array index starts from 0.
    
    getchar();
    
    printf("\nplease type new product's name: ");
    scanf("%8s", name[pID-1]);
    
    printf("\nplease type new product's brand: ");
    scanf("%5s", brand[pID-1]);
    
    printf("\nplease type new product's price: ");
    scanf("%lf", &price[pID-1]);
    
    getchar();
   
    fprintf(writer, "%d,%c,%s,%s,%lf\n", pID, type[pID-1], name[pID-1], brand[pID-1], price[pID-1]);
    
    fclose(writer);
    
    pID++;
}

void delete_p(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX])
{
    FILE *deleter;
    
    int delpID; //variable for selection of will be deleted product
    
    char *srcn = name[delpID]; //source name pointer points to greater index element
    char *destn = name[delpID-1]; //destination pointer points to greater index element
    char *srcb = brand[delpID]; //source brand pointer points to greater index element
    char *destb = brand[delpID-1]; //destination brand pointer points to greater index element
    
    printf("Enter the pID of the product you want to delete: ");
    scanf("%d", &delpID);
    
    while(delpID - 1 < MAX) //while delpID is smaller than MAX, carry each element after index delpID one left
    {
       type[delpID-1] = type[delpID];
       price[delpID-1] = price[delpID];
       
       delpID++;
       
       if(delpID == MAX)
          break;
    }
    
    while (*srcn != '\0') 
    {
       *destn++ = *srcn++;
    }
    
    *destn = '\0';

    while (*srcb != '\0') 
    {
       *destb++ = *srcb++;
    }
    
    *destb = '\0';
    
    deleter = fopen("products.txt", "w");
    
    fprintf(deleter, "pID,Type,Name,Brand,Price\n");

    for(int pID = 1; price[pID-1] != 0; pID++)
    {
       fprintf(deleter, "%d,%c,%s,%s,%lf\n", pID, type[pID-1], name[pID-1], brand[pID-1], price[pID-1]);
    }
    
    fclose(deleter);
}

void update_p(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX])
{
     FILE *updater;
     
     int updpID; //variable to hold pID of the to be updated product
     
     char updfeature[8];
    
     printf("Enter the pID of the product you want to update: ");
     scanf("%d", &updpID);
     
     printf("\nEnter the feature of the product you want to update: ");
     scanf("%s", updfeature);
     
     if(compareStrings(updfeature, "type") == 1)
     {
         printf("\nPlease give the new type: ");
         scanf(" %c", &type[updpID-1]);
     }
     
     else if(compareStrings(updfeature, "name") == 1)
     {
         printf("\nPlease give the new name: ");
         scanf("%8s", name[updpID-1]);
     }
     
     else if(compareStrings(updfeature, "brand") == 1)
     {
         printf("\nPlease give the new brand: ");
         scanf("%5s", brand[updpID-1]);
     }
     
     else if(compareStrings(updfeature, "price") == 1)
     {
         printf("\nPlease give the new price: ");
         scanf("%lf", &price[updpID-1]);
     }
    
     updater = fopen("products.txt", "a");
     
     for(updpID = 1; price[updpID-1] != 0; updpID++)
     {
        fprintf(updater, "%d,%c,%s,%s,%lf\n", updpID, type[updpID-1], name[updpID-1], brand[updpID-1], price[updpID-1]);
     }
     
     fclose(updater);
}

int compareStrings(char string1[], char string2[]) 
{
    int i = 0;
    
    while(string1[i] == string2[i]) 
    {
        if(string1[i] == '\0' || string2[i] == '\0') 
        {
            break;
        }
        
        i++;
    }
    
    if(string1[i] == '\0' && string2[i] == '\0') 
    {
        return 1;
    } 
    
    else 
    {
        return 0;
    }
}

void add_feature_to_p(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX])
{
    FILE *feature_adder;

    double x = 1; // this variable will hold prices with for loop and when it is 0 it means that product has not been entered because any product cant have 0 price
    int i;
    
    for(i = 0; x != 0; i++)
    {
       x = price[i];
    }
    
    char nfeature[i][5]; //char array for new feature

    for(int j = 0; j < i; j++)
    {
       nfeature[j][0] = 'N';
       nfeature[j][1] = 'o'; 
       nfeature[j][2] = 'n';
       nfeature[j][3] = 'e';
       nfeature[j][4] = '\0';
    }
    
    feature_adder = fopen("products.txt", "w");
     
    fprintf(feature_adder, "pID,Type,Name,Brand,Price,New Feature\n");

    for(int pID = 1; price[pID-1] != 0; pID++)
    {
        fprintf(feature_adder, "%d,%c,%s,%s,%lf,%s\n", pID, type[pID-1], name[pID-1], brand[pID-1], price[pID-1], nfeature[pID-1]);
    }

    fclose(feature_adder);
}

void new_stock_entry(char branch[MAX][15], int curr_stock[MAX], int stock_pID[MAX])
{
     FILE *stock_entry;
     
     static int sID = 1; //sID

     stock_entry = fopen("stocks.txt", "a");
     
     printf("enter the pID of the new stock entry: ");
     scanf("%d", &stock_pID[sID-1]);
     
     printf("enter the branch of the new stock entry: ");
     scanf("%15s", branch[sID-1]);

     printf("enter the current stock of the new stock entry: ");
     scanf("%d", &curr_stock[sID-1]);

     fprintf(stock_entry, "\n%d,%d,%s,%d", sID, stock_pID[sID-1], branch[sID-1], curr_stock[sID-1]);
     
     sID++;

     fclose(stock_entry);
}

void delete_stock_entry(char branch[MAX][15], int curr_stock[MAX], int stock_pID[MAX])
{
    FILE *deleter;
    
    int delpID; //variable for selection of to be deleted product
    
    char *srcn = branch[delpID]; //source name pointer points to greater index element
    char *destn = branch[delpID-1]; //destination pointer points to less index element
    
    printf("Enter the pID of the product you want to delete: ");
    scanf("%d", &delpID);
    
    while (*srcn != '\0') 
    {
       *destn++ = *srcn++;
    }
    
    *destn = '\0';
    
    deleter = fopen("stocks.txt", "w");
    
    fprintf(deleter, "sID,pID,branch,current stock\n");

    for(int sID = 1; curr_stock[sID-1] != 0; sID++)
    {
       fprintf(deleter, "%d,%d,%s,%d\n", sID, stock_pID[sID-1], branch[sID-1], curr_stock[sID-1]);
    }
    
    fclose(deleter);  
}

void update_stock_entry(char branch[MAX][15], int curr_stock[MAX], int stock_pID[MAX])
{
     FILE *updater;
     
     int updsID; //variable to hold pID of the to be updated product
     
     char updfeature[8];
     
     double nprice;
     
     printf("Enter the sID of the product you want to update: ");
     scanf("%d", &updsID);
     
     printf("\nEnter the feature of the stock entry you want to update: ");
     scanf("%s", updfeature);
     
     if(compareStrings(updfeature, "branch") == 1)
     {
         printf("\nPlease give the new branch: ");
         scanf("%s", branch[updsID-1]);
     }
     
     else if(compareStrings(updfeature, "current stock") == 1)
     {
         printf("\nPlease give the new current stock: ");
         scanf("%d", &curr_stock[updsID-1]);
     }
     
     updater = fopen("stocks.txt", "a");
     
     for(updsID = 1; stock_pID[updsID-1] != 0; updsID++)
     {
        fprintf(updater, "\n%d,%d,%s,%d", updsID, stock_pID[updsID-1], branch[updsID-1], curr_stock[updsID-1]);
     }
     
     fclose(updater);
}

void query_product(char type[MAX], char name[MAX][8], char brand[MAX][5], double price[MAX])
{
     FILE *product_lister;
     int sel;
     
     printf("please select an operation:\n1. List all products\n2. Filter products by brand, type, price, or a user-defined feature\n3. Back to main menu\n");
     scanf("%d", &sel);

     switch(sel)
     {
         case 1: //takes products.txt and prints to console to list all products
                
                char line[100]; //to read products.txt contents

                product_lister = fopen("products.txt", "r");
                
                if(product_lister == NULL) 
                {
                    printf("Error opening file!\n");
                    exit(0);
                }
              
                while(fgets(line, sizeof(line), product_lister)) 
                {
                     printf("%s", line);
                }
                
                fclose(product_lister);

                break; 

         case 2:
                //creating arrays for storing the products that are filtered
                char filteredtype[3], filteredname[3][8], filteredbrand[3][5], filtertype1[8], filter1[8], filtertype2[8], filter2[8]; //filtered strings, filtered char
                double filteredprice[3];  

                printf("What type of filter do you want to apply?");
                scanf("%[^,],%[^,],%[^,],%[^,]", filtertype1, filter1, filtertype2, filter2);
                
                if(compareStrings(filtertype1, "type") == 1)
                {
                   for(int i = 0; i < MAX; i++)
                   {
                       if(filter1 == type[i])
                       {
                           filteredtype[0] = type[i];
                           filteredprice[0] = price[i];

                           for(int i = 0; i < 8; i++)
                           {
                               filteredname[0][i] = name[0][i];
                               
                           }
                           
                           for(int i = 0; i < 5; i++)
                           {
                                filteredbrand[0][i] = brand[0][i];
                           }
                       }
                    }
                    
                }

                else if(compareStrings(filtertype1, "name") == 1) //if filter is name
                {
                   for(int i = 0; i < MAX; i++)
                   {
                       if(compareStrings(filter1, name[i]) == 1) //if filter1 matches with name array element
                       {
                           filteredtype[0] = type[i];
                           filteredprice[0] = price[i];

                           for(int i = 0; i < 8; i++)
                           {
                               filteredname[0][i] = name[0][i];
                           }
                           
                           for(int i = 0; i < 5; i++)
                           {
                                filteredbrand[0][i] = brand[0][i];
                           }
                       }
                   }
                }

                else if(compareStrings(filtertype1, "brand") == 1)
                {
                   for(int i = 0; i < MAX; i++)
                   {
                       if(compareStrings(filter1, brand[i]) == 1)
                       {
                           filteredtype[0] = type[i];
                           filteredprice[0] = price[i];

                           for(int i = 0; i < 8; i++)
                           {
                               filteredname[0][i] = name[0][i];
                           }
                           
                           for(int i = 0; i < 5; i++)
                           {
                                filteredbrand[0][i] = brand[0][i];
                           }
                       }
                   }
                }
                
                if(compareStrings(filtertype2, "type") == 1) //if filter type 2 matches with "type"
                {
                   for(int i = 0; i < MAX; i++)
                   {
                       if(filter1 == "type[i]")
                       {
                           filteredtype[1] = type[i];
                           filteredprice[1] = price[i];

                           for(int i = 0; i < 8; i++)
                           {
                               filteredname[1][i] = name[0][i];
                           }
                           
                           for(int i = 0; i < 5; i++)
                           {
                                filteredbrand[1][i] = brand[0][i];
                           }
                       }
                   }
                }

                else if(compareStrings(filtertype2, "name") == 1)
                {
                   for(int i = 0; i < MAX; i++)
                   {
                       if(compareStrings(filter2, name[i]) == 1)
                       {
                           filteredtype[1] = type[i];
                           filteredprice[1] = price[i];

                           for(int i = 0; i < 8; i++)
                           {
                               filteredname[1][i] = name[0][i];
                           }
                           
                           for(int i = 0; i < 5; i++)
                           {
                                filteredbrand[1][i] = brand[0][i];
                           }
                       }
                   }
                }

                else if(compareStrings(filtertype2, "brand") == 1)
                {
                   for(int i = 0; i < MAX; i++)
                   {
                       if(compareStrings(filter2, brand[i]) == 1)
                       {
                           filteredtype[1] = type[i];
                           filteredprice[1] = price[i];

                           for(int i = 0; i < 8; i++)
                           {
                               filteredname[1][i] = name[0][i];
                           }
                           
                           for(int i = 0; i < 5; i++)
                           {
                                filteredbrand[1][i] = brand[0][i];
                           }
                       }
                   }
                }
                
                for(int i = 0; i < 3; i++)
                {
                   printf("%c,%s,%s,%lf", filteredtype[i], filteredname[i], filteredbrand[i], filteredprice[i]);
                }
                
                break; 

         case 3: 
                
                mainmenu();
      }
}

void check_stock_status(char branch[MAX][15],  int curr_stock[MAX], int stock_pID[MAX])
{
     int sel;

     printf("Please make a selection:\n1)query the stock of a given product in a specified branch by using the product ID and branch name.\n2)list the stock of all products in a specified branch.\n3)list the out-of-stock products in a specified branch\n4)return to the main menu.\n");
     scanf("%d", &sel);

     switch(sel)
     {
         case 1: //query the stock of a given product in a specified branch by using the product ID and branch name.
                
                char brn[15]; 
                int pID;
              
                printf("Enter the to be search branch: ");
                scanf("%s", brn);
                
                printf("Enter the pId of the searching product: ");
                scanf("%d", &pID);

                for(int i = 0; i < MAX; i++)//compare pID with stockPID and to be searched branch with branch string array with same index.
                {                           //if two conditions above are satisfied, it is the be searching product.
                    if(pID == stock_pID[i] && compareStrings(brn, branch[i]) == 1)
                    {
                        printf("Stock of this product in this branch is: %d\n", curr_stock[i]);//then print its stock
                    }
                }

                break;

         case 2: //list the stock of all products in a specified branch.
                
                char br[15]; 
                
                printf("Enter the to be search branch: ");
                scanf("%s", br);

                for(int j = 0; j < MAX; j++)
                {
                    if(compareStrings(br, branch[j]) == 1) //if entered branch is same with branch string in branch string array, 
                    {
                        printf("Stock of this product in this branch is: %d\n", curr_stock[j]); //print that elements' stocks
                    }
                }
                
                break;

         case 3: //list the out-of-stock products in a specified branch.
                    
                char bra[15]; 
                
                printf("Enter the to be search branch: ");
                scanf("%s", bra);
                
                for(int j = 0; j < MAX; j++)
                {
                    if(curr_stock[j] == 0 && compareStrings(bra, branch[j]) == 1) //if entered branch is same with branch string in branch string array and stock status is zero,
                    {
                        printf("pID of out-of-stock product: %d\n", stock_pID[j]); //print that elements' stock pIDs
                    }
                }
                
                break;

         case 4:
                
                mainmenu();

                break;                      
     }
}

void brand_stock_control(char brand[MAX][5], int stock_pID[MAX], double price[MAX], int curr_stock[MAX], int pIDlist[150], int curr_stocklist[150], double pricelist[150])
{
     char brandtolist[5];
     
     printf("enter the brand to list its products: ");
     scanf("%5s", brandtolist);

     for(int j = 0; j < MAX; j++)
     {
         if(compareStrings(brandtolist, brand[j]) == 1) //if entered branch is same with branch string in branch string array and stock status is zero,
         {
            pIDlist[j] = stock_pID[j];
            pricelist[j] = price[j];
            curr_stocklist[j] = curr_stock[j];
            printf("pID:%d\nprice:%lf\ncurrent stock:%d", pIDlist[j], pricelist[j], curr_stocklist[j]);
         }
     } 
}

void stock_report(int pIDlist[150], int curr_stocklist[150])
{
     FILE *reportwriter;

     int min_stock_val, max_stock_val;
     double median;
     
     int i;
     
     i = 0;
     
     while(pIDlist[i] != 0) //this loop gives us the element number of pıdlist and currenstocklist without last 0 elements
     {               //pID value cant be 0 normally because it starts from 1.        
         i++;
     } 

     //to sort current stock list array elements from the smallest to the greatest, i'm gonna use the bubble sort algorithm
     bubbleSort(curr_stocklist, i); //i send this array with i because all of the array may not be filled and it causes empty elements to fill first indexs because they would be assigned as 0 by default
     
     if(i % 2 == 0)
     {
        median = ((i / 2) + ((i / 2) + 1)); // if total index is even median is average of the middle and middle+1 elements
     }
     
     else
     {
        median = (i / 2) + 1; // if total index is odd median is the (index/2)+1. element.
     }
     
     min_stock_val = curr_stocklist[0];
     max_stock_val = curr_stocklist[i];

     reportwriter = fopen("report.txt", "w");
     
     for(int j = 0; curr_stocklist[j] != 0; j++)
     {
        fprintf(reportwriter, "%d,%d,%d,%lf\n", pIDlist[j], min_stock_val, max_stock_val, median); 
     } 
     
     fclose(reportwriter);
}

void bubbleSort(int arr[], int n) 
{
    int i, j, temp;
    
    for (i = 0; i < n-1; i++) 
    {
        for (j = 0; j < n-i-1; j++) 
        {
            if (arr[j] > arr[j+1]) 
            {
                //swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}