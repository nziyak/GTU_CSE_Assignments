#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define BOARD_SIZE 3
#define MAX_SIZE 1000

typedef struct{
   char cells[BOARD_SIZE][BOARD_SIZE]; //this array holds the numbers in board. to be able to hold the '_' character i created it as char array
}PuzzleBoard;

PuzzleBoard puzzle;

FILE *score_reader;

void menu(void);
void userPlay(void);
void auto_finish(void);
int best_score();
void initializeBoard(void);
void printBoard(void);
void shuffleArray(char* array, int size);
int takeMove(void);
void make_and_printMove(char direction, int move_num);
int illegal_check(char direction, int move_num);
int finish_check(void);


int main()
{
   menu(); //show the menu and offer the user selections
   return 0;
}


void menu()
{
   int sel;
   
   printf("Welcome to the 8-Puzzle Game!\nPlease select an option:\n1. Play game as a user\n2. Finish the game with PC\n3. Show the best score\n4. Exit\n> ");
   scanf("%d", &sel);

   switch(sel)
   {
      case 1: //user will play the game as a user
             initializeBoard(); //initializes the solvable board
             printBoard();
             userPlay();
             break;

      case 2: //user will finish the game with PC
             initializeBoard(); //initializes the solvable board
             printBoard();
             
             srand(time(NULL)); //seed srand with time in order to create random value
             
             auto_finish();
             
             break;

      case 3: //show the best score
             best_score();
             break;

      case 4: //exit
             printf("I hope see you at a other game!");
             break;

      default: 
              
              printf("invalid selection. please try again.\n");
              menu();                             
   }

}   


void userPlay()
{
    takeMove();
}


void initializeBoard() 
{
    char numbers[BOARD_SIZE * BOARD_SIZE + 1] = {'1', '2', '3', '4', '5', '6', '7', '8', '_'}; //this array holds the numbers in board. to be able to hold the '_' character i created it as char array
    
    int c = 0;

    do{ //counting the inversions to create solvable puzzle board. if inversion count is even it is solvable else unsolvable
        c = 0;
        
        shuffleArray(numbers, BOARD_SIZE * BOARD_SIZE); //then shuffle the elements of array with shuffleArray function
    
        for(int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++)
        {
            for(int j = 1; j < BOARD_SIZE*BOARD_SIZE; j++)
            {
                if(numbers[i] != '_') //this characters ASCII value is greater than the numbers and i want to compare just numbers
                   continue;
                
                if(numbers[i] > numbers[j]) //if a number preceeds some smaller numbers this numbers number is the inversion count
                   c++;
            }
        }
        
    }while(c % 2 != 0); //while count is odd recreate the board 
    
    //then assign the solvable boards elements to puzzle.cells[][] array
    int k = 0;
    
    for(int i = 0; i < BOARD_SIZE; i++) 
    {
        for(int j = 0; j < BOARD_SIZE; j++) 
        {
            puzzle.cells[i][j] = numbers[k++]; //assign shuffled numbers to cells array
        }
    }
}


void printBoard(void) 
{
    for(int i = 0; i < BOARD_SIZE; i++) //print the board to the terminal
    {
        for(int j = 0; j < BOARD_SIZE; j++) 
        {
            printf("%2c ", puzzle.cells[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    FILE *boardprinter;

    boardprinter = fopen("board.txt", "a");

    for(int i = 0; i < BOARD_SIZE; i++) //print the board to the board.txt file
    {
        for(int j = 0; j < BOARD_SIZE; j++) 
        {
            fprintf(boardprinter, "%2c ", puzzle.cells[i][j]);
        }
        fprintf(boardprinter, "\n");
    }
    fprintf(boardprinter, "\n");

    fclose(boardprinter);
}


void shuffleArray(char* array, int size) 
{
    srand(time(NULL)); //seed srand with time in order to create random value
    
    for(int i = size - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1); //creating j with random value and shuffle each element value with a random indexed element value
        
        char temp = array[i];
        
        array[i] = array[j];
        
        array[j] = temp;
    }
}

//take move. check legality. if legal, make move. else, go back to first step. 
int takeMove()
{
    int legality, move_num, g_status, move_count = 0, score; //to move number, game status, move counter, score
    char direction;

    do{
       
       printf("\nEnter your move (number-directon, e.g., 2-R): ");
       scanf("%d-%c", &move_num, &direction);
       
       legality = illegal_check(direction, move_num);

       if(legality == 1)
       {  
          make_and_printMove(direction, move_num); 
          move_count++;

          g_status = finish_check(); //take games finish status to g_status variable
           
          if(g_status == 1)
          {
            printf("Congratulations! You finished the game.\n\n");
            printf("Total number of moves: %d", move_count);
            score = 1000-10*move_count;
            printf("Your score: %d", score);
            
            score_reader = fopen("scores.txt", "a");
            
            if(score_reader == NULL)
            {
              printf("The file could not been opened.\n");
              return 1;
            }

            fprintf(score_reader, "%d\n", score);
            fclose(score_reader);
          }
       }

       else
       {
          printf("%d-%c is an illegal move!!! Make a legal move!!!\n\n", move_num, direction);
          printBoard();
          printf("\n");
          takeMove();
       }
       
    }while(g_status != 1);
}

//makes the legal move came from takeMove or auto_finish
void make_and_printMove(char direction, int move_num)
{
    int x = 0, y = 0; //to save coordinates of the to move number
    
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(puzzle.cells[i][j] - '0' == move_num) //find the position of the to move number
            {
               x = i;
               y = j;
            }   
        }
    }
    
    switch(direction)
    {
        case 'U':
        case 'u':
                
                puzzle.cells[x-1][y] = '0' + move_num; //converting integer to character by adding character '0'. it wokrs because '0' has ASCII value 48
                puzzle.cells[x][y] = '_';
                printBoard();
            
                break;

        case 'D':
        case 'd':
                
                puzzle.cells[x+1][y] = '0' + move_num;
                puzzle.cells[x][y] = '_';
                printBoard();
                
                break;

        case 'R':
        case 'r':
                
                
                puzzle.cells[x][y+1] = '0' + move_num;
                puzzle.cells[x][y] = '_';
                printBoard();
                
                break;

        case 'L':
        case 'l':
                
                puzzle.cells[x][y-1] = '0' + move_num;
                puzzle.cells[x][y] = '_';
                printBoard();
                
                break;                           
    }
}


int finish_check(void)
{
    int g_status = 1;
    
    char sample[BOARD_SIZE*BOARD_SIZE] = {'1', '2', '3', '4', '5', '6', '7', '8', '_'};
    
    int k = 0;

    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(puzzle.cells[i][j] != sample[k++])
            {
               g_status = 0;
            }
        }
        
    }

    return g_status;
}

int illegal_check(char direction, int move_num)
{
    int x = 0, y = 0; //to save coordinates of the to move number
    
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(puzzle.cells[i][j] - '0' == move_num) //find the position of the to move number
            {
               x = i;
               y = j;
            }   
        }
    }

    switch(direction)
    {
        case 'U':
        case 'u':
                
                if(puzzle.cells[x-1][y] == '_')//if move is legal, return 1
                    return 1; //legal
                
                else //if the move is illegal, return 0
                    return 0;
                
                break;

        case 'D':
        case 'd':
                
                if(puzzle.cells[x+1][y] == '_')
                    return 1; //legal            

                else
                    return 0;

                break;

        case 'R':
        case 'r':
                
                if(puzzle.cells[x][y+1] == '_')
                    return 1;            

                else
                    return 0;

                break;

        case 'L':
        case 'l':
                
                if(puzzle.cells[x][y-1] == '_')
                    return 1;            

                else
                    return 0;

                break;                           
    }    
}


int best_score()
{
    int scores[MAX_SIZE];
    int count = 0;
    int num;
    
    score_reader = fopen("scores.txt", "r");
    
    if(score_reader == NULL)
    {
      printf("The file could not been opened.\n");
      return 1;
    }

    // Read scores from the file and store them in the array
    while(fscanf(score_reader, "%d", &num) == 1) //read and assign the scores to scores array 
    {
        scores[count] = num;
        count++;

        if(count == MAX_SIZE) 
        {
            printf("Maximum array size reached.\n");
            break;
        }
    }

    // Close the file
    fclose(score_reader);
    
    int max_score = scores[MAX_SIZE-1];

    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(scores[i] > max_score)
          max_score = scores[i];
    }

    printf("The best score is: %d", max_score); //in sorted array the best score is the last one
}


void auto_finish()
{
    int g_status = 0, temp;
    static int move_count = 0;
    static double execution_time = 0;
    char direction;
    
    int x = 0, y = 0; //to save coordinates of the to character '_'
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(puzzle.cells[i][j] == '_') //find the position of the '_'
            {
               x = i;
               y = j;
            }   
        }
    }   
    
    int move_num = rand() % 4 + 1; //generate move_num randomly

    switch(move_num)
    {
        case 1: //if one upward character of '_' is number, swap them
               
               if(isdigit(puzzle.cells[x-1][y]))
               {
                  temp = puzzle.cells[x-1][y];
                  puzzle.cells[x-1][y] = puzzle.cells[x][y];
                  puzzle.cells[x][y] = temp;
                  
                  direction = 'd';
                  
                  printf("Computer move: %c-%c\n", puzzle.cells[x][y], direction);

                  printBoard();
                        
                  move_count++;

                  printf("\nmove count: %d\n", move_count);
    
                  g_status = finish_check(); //take games finish status to g_status variable

                  if(g_status == 1) 
                  {
                    printf("Computer finished the game.\n");
                    printf("Total number of moves: %d\n", move_count);
          
                    return; 
                  }

                  else auto_finish();
               }
               
               else auto_finish();

               break;

        case 2: //if one downward character of '_' is number, swap them
               
               if(isdigit(puzzle.cells[x+1][y]))
               {
                  temp = puzzle.cells[x+1][y];
                  puzzle.cells[x+1][y] = puzzle.cells[x][y];
                  puzzle.cells[x][y] = temp;
                  
                  direction = 'u'; 

                  printf("Computer move: %c-%c\n", puzzle.cells[x][y], direction);

                  printBoard();
                        
                  move_count++;

                  printf("\nmove count: %d\n", move_count);
    
                  g_status = finish_check(); //take games finish status to g_status variable

                  if(g_status == 1) 
                  {
                    printf("Computer finished the game.\n");
                    printf("Total number of moves: %d\n", move_count);
                    return; 
                  }

                  else auto_finish();
               }
               
               else auto_finish();

               break;

        case 3: //if one rightward character of '_' is number, swap them
               
               if(isdigit(puzzle.cells[x][y+1]))
               {
                  temp = puzzle.cells[x][y+1];
                  puzzle.cells[x][y+1] = puzzle.cells[x][y];
                  puzzle.cells[x][y] = temp;
                  
                  direction = 'l';

                  printf("Computer move: %c-%c\n", puzzle.cells[x][y], direction);

                  printBoard();
                        
                  move_count++;

                  printf("\nmove count: %d\n", move_count);
    
                  g_status = finish_check(); //take games finish status to g_status variable

                  if(g_status == 1) 
                  {
                    printf("Computer finished the game.\n");
                    printf("Total number of moves: %d\n", move_count);
          
                    return; 
                  }

                  else auto_finish();
               }
               
               else auto_finish();

               break;

        case 4:
               
               if(isdigit(puzzle.cells[x][y-1]))
               {
                  temp = puzzle.cells[x][y-1];
                  puzzle.cells[x][y-1] = puzzle.cells[x][y];
                  puzzle.cells[x][y] = temp;
                  
                  direction = 'r';

                  printf("Computer move: %c-%c\n", puzzle.cells[x][y], direction);

                  printBoard();
                        
                  move_count++;

                  printf("\nmove count: %d\n", move_count);
    
                  g_status = finish_check(); //take games finish status to g_status variable

                  if(g_status == 1) 
                  {
                    printf("Computer finished the game.\n");
                    printf("Total number of moves: %d\n", move_count);
          
                    return; 
                  }

                  else auto_finish();
               }
               
               else auto_finish();                                    
    }
}