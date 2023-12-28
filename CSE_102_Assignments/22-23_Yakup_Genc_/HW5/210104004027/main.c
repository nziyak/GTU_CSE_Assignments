#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define RED r
#define GREEN g
#define BLUE b
#define YELLOW y
#define ORANGE o

enum Color{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE
};

// Declare and initialize an array of length-3 vectors to represent each color
float colors[5][3] = {
     {1.0, 0.0, 0.0}, // RED
     {0.0, 1.0, 0.0}, // GREEN
     {0.0, 0.0, 1.0}, // BLUE
     {0.5, 0.5, 0.0}, // YELLOW
     {0.5, 0.4, 0.2}  // ORANGE  
};

char board[3][3];

void LtrFreqy(void); //letter frequency

void myFunction(enum Color color1, enum Color color2, void (*funcp)(enum Color, enum Color));//takes two enum type variables and a function pointer
void mixColors(enum Color color1, enum Color color2); //the mixer function

void init_board(void); //board initializer function
void display_board(void); //displays the board
void get_move(int, int *, int *); //gets the move
void make_move(int, int, int); //prints move
int g_over(void); //checks the game status


int main()
{
   
   LtrFreqy(); //call letter frequency finder function
   
   printf("\n----------------------\n");
//BEGINNING OF THE COLOR MIXER PART
   char col1, col2;
   int c1, c2;
   
   printf("\nEnter color 1(r,g,b,y,o): ");
   scanf("%c", &col1);
  
   switch(col1)
   { 
      case 'r': 
               c1 = 0;
               break;
     
      case 'g':
               c1 = 1;
               break;
     
      case 'b':
               c1 = 2;
               break;
     
      case 'y':
               c1 = 3;
               break;
     
      case 'o':
               c1 = 4;
   } 
 
   printf("Enter color 2(r,g,b,y,o): ");
   scanf(" %c", &col2);
  
   switch(col2)
   {
      case 'r': 
               c2 = 0;
               break;
     
      case 'g':
               c2 = 1;
               break;
     
      case 'b':
               c2 = 2;
               break;
     
      case 'y':
               c2 = 3;
               break;
     
      case 'o':
               c2 = 4;
   }
  
   myFunction(c1, c2, &mixColors); //calling myFunction with two int values which are corresponding enum color values and address of mixColors func
   printf("\n----------------------\n");  
//END OF THE COLOR MIXER PART
   
//BEGINNING OF THE TIC TAC TOE PART
   
   int player = 1; //it is initialized to 1 because first player 1 will make move
   int row, col; //row, column
   int status; //game status
   char request; //variable to hold user decision for if he/she wants to play again or not
    
   init_board();
   display_board(); //calling the display board function to show the game board

   do{   
       
      do{
	
	  get_move(player, &row, &col); //getting move with get_move() function
	  make_move(player, row, col); //making move with the help of the values get_move() took 
	
       	  display_board();
	
	  status = g_over(); //status comes from g_over() function
	
          player = (player == 1) ? 2 : 1; //change the player number after one is moved

      }while(status == 0); //while game is not over
       
      if(status == 1) 
      {
         printf("Player %d wins!\n", player);
      } 

      else // 2
      {
         printf("It's a tie!\n");
      }
    
      printf("Do you want to play again?(y/n)"); 
      scanf(" %c", &request);
       
   }while(request == 'y' || request == 'Y'); //if y or Y play again
   
   //END OF THE TIC TAC TOE PART
   
   return 0;

}


void LtrFreqy(void)
{
    
    FILE *reader;
    FILE *writer;
    int letter[27]; //because of the english alphabet includes 26 letters, array that holds letters has 26 elements. one for guarantee
    char filename[100]; //string that holds file name
    char str[100];
    char ltr; // a character that holds fscanf input from the text
    
    printf("Enter filename: ");
    scanf("%s", filename);
    
    printf("Enter string to write: ");
    scanf("%s", str);
    
    writer = fopen(filename, "w"); //opening the file
    
    if(writer == NULL) 
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    fprintf(writer, "%s", str);
    
    fclose(writer);
    
    reader = fopen(filename, "r"); //opening the file
    
    if(reader == NULL) 
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    while((ltr = fgetc(reader)) != EOF)
    { 
          
        if(ltr >= 97 && ltr <= 122) //ASCII numbers of lower case letters. 97 is 'a', 122 is 'z'. if character is between them,
        {
           letter[ltr - 97]++; //increment appropriate array element. if 'a', letter[0] and so on.
        }
         
        else if(ltr >= 65 && ltr <= 90) //ASCII numbers of upper case letters. 65 is 'A, 90 is 'Z'. if character is between them, 
        {
           letter[ltr - 65]++; //increment appropriate array element. if 'A', letter[0] and so on.
        }
       
    }
    
    fclose(reader);
     
    for(int i = 65, k = 0; i < 90; i++, k++) //because of we are printing letter numbers with upper case i is initially 65.
    {
        printf("%c: %d\n", i, letter[k]);
    }
    
}


void myFunction(enum Color color1, enum Color color2, void (*funcp)(enum Color, enum Color)) 
{
  //Call the function pointer with the two colors
  funcp(color1, color2);
  
}


//the mixer function definition
void mixColors(enum Color color1, enum Color color2) 
{
  float mixedColor[3]; //array holds vector components of mixed color
  float distance[5]; //array holds the differences as euclidean distances between the mixed color and colors 
  
  for(int i = 0; i < 3; i++) 
  {
      mixedColor[i] = (colors[color1][i] + colors[color2][i]) / 2.0;
  }
  
  for(int i = 0; i < 5; i++) //colors array has 5 colors. we find the distances between mixer color and initial colors and assigning this distances to distance[] array
  {
      distance[i] = sqrt( pow((mixedColor[0] - colors[i][0]), 2) + pow((mixedColor[1] - colors[i][1]), 2) + pow((mixedColor[2] - colors[i][2]), 2));
  } 
  
  //finding the minimum distance in distance[] array
  float min = distance[0]; //first assign the value of distance[0] to min and compare it wiht other elements
  for(int i = 1; i < 5; i++) //colors array has 5 colors. we find the distances between mixer color and initial colors and assigning this distances to distance[] array
  {
      if(distance[i] < min) 
      {
          printf("Mixed Color: ");
          
          switch(i)
          {
             case 0: 
                    
                    printf("RED[1.0, 0.0, 0.0]\n");
                    break;
             
             case 1:
                    
                    printf("GREEN[0.0, 1.0, 0.0]\n");
                    break;
                    
             case 2:
                   
                    printf("BLUE[0.0, 0.0, 1.0]\n");        
                    break;
             
             case 3:
                    
                    printf("YELLOW[0.5, 0.5, 0.0]\n");        
                    break;
                    
             case 4:
             
                    printf("ORANGE[0.5, 0.4, 0.2]\n");        
                           
           }
           
           break;         
      }
  }
  
}


// Initialize the game board
void init_board() 
{
 
    int i, j;
    
    for(i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            board[i][j] = '_'; //initially every position is filled with '_'
        }
    }

}


// Display the game board
void display_board() 
{
    int i, j;
    
    printf("\n");
    printf("   %c  %c  %c\n\n", board[0][0], board[0][1], board[0][2]);
    printf("   %c  %c  %c\n\n", board[1][0], board[1][1], board[1][2]);
    printf("   %c  %c  %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");

}


// Get the player's move
void get_move(int player, int *row, int *col) 
{
    printf("Player %d, enter your move(row, column): ", player);     
    scanf("%d %d", row, col);
}            


// Make a move on the game board
void make_move(int player, int row, int col) 
{
     
    if(board[row][col] == '_') 
    {
        board[row][col] = (player == 1) ? 'X' : 'O'; //if it is player 1, print X to indicated location, else it is player 2 so print O.
    } 
         
    else //if it is previously selected position, warn the user. and ask for a new move again
    {
        printf("That square is already taken. Please try again.\n");
        get_move(player, &row, &col);
        make_move(player, row, col);
    }

}


// Check if the game is over
int g_over() 
{
    int i, j;
    
    // Check rows
    for (i = 0; i < 3; i++) 
    {
        if (board[i][0] != '_' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) //i added != '_' because empty locations doesn't affect the winning status
        {
            return 1;
        }
    }
    
    // Check columns
    for (j = 0; j < 3; j++) 
    {
        if (board[0][j] != '_' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) 
        {
            return 1;
        }
    }
    
    // Check diagonals
    if (board[0][0] != '_' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) //diagonals from left have same i j coordinates.
    {
        return 1;
    }
    
    if (board[0][2] != '_' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
    {
        return 1;
    }
    
    // Check for a tie
    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            if (board[i][j] == '_') 
            {
                return 0; // There are still empty squares, so the game is not over
            }
        }
    }
    
    return 2; // It's a tie
}
