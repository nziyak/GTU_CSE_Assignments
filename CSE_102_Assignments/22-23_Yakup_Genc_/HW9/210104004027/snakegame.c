#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Point{ //row and column values of the parts of the snakes
    int row, col; 
} point_of_snake;

point_of_snake* snake; //declaring the snake array which consist of point_of_snake structures

typedef struct block{
    char type; //block type
    int value; //represents the height of the obstacle, and it is zero for empty and bait blocks
}Block;


Block*** init_board(int x, int y, int z);
void free_board(Block*** board, int x, int y, int z);
void draw_board(Block*** board);
void play(Block*** board);
int check_status(Block*** board, point_of_snake* snake);
int update(Block*** board, point_of_snake** snake);
void move(point_of_snake** snake);

int snake_length = 1;

int main()
{
    srand(time(NULL)); //seed srand with time 
    
    int x = 10; //this and
    int y = 10; //this is 11 because one character more is needed for the walls of the board
    int z = 11; //to hold height. it can be changed dynamically, according to need 

    Block*** board = init_board(x,y,z); //generating and initializing the board and return into board array
    
    play(board);

    free_board(board, x, y, z); //free the board

    free(snake); //free the snake

    return 0;
}


Block*** init_board(int x, int y, int z)
{
    //Allocating memory for 3D dynamic array of type Block
    Block ***board = (Block***)malloc(x * sizeof(Block**)); //the first dimension array 
    
    for(int i = 0; i < x; i++) 
    {
        board[i] = (Block**)malloc(y * sizeof(Block*)); //the second dimension array 
        
        for(int j = 0; j < y; j++) 
        {
            board[i][j] = (Block*)malloc(z * sizeof(Block)); //the third dimension array
        }
    }

    for(int i = 0; i < x; i++) 
    {
        for(int j = 0; j < y; j++) 
        {
            board[i][j]->type = 'e'; //each board cell is initialized to empty type
            board[i][j]->value = 0; //each board cell's height is initialized to empty type
        }    
    }
    
    int xo, yo, xb, yb;

    do{
        
        xo = rand() % 9 + 1; //generate a random value 1-9 for x component of the obstacle
        yo = rand() % 9 + 1; //generate a random value for y component of the obstacle
        xb = rand() % 9 + 1; //generate a random value for x component of the bait
        yb = rand() % 9 + 1; //generate a random value for y component of the bait
    
    }while((xo == 1 && yo == 1) || (xb == 1 && yb == 1)); //if obstacle or bait is at the top-left block, regenerate coordinates
    
    board[xo][yo]->type = 'o';
    board[xo][yo]->value = rand() % 9 + 1; //generating obstacle height between 1-9 

    board[xb][yb]->type = 'b';
 
    return board;
}


void play(Block*** board)
{
    snake = (point_of_snake*)malloc(1 * sizeof(point_of_snake)); //initialize the snake with a length of 1 block  
    
    //create the snake's head in the top-left cell
    snake[0].row = 0;
    snake[0].col = 0;
    
    do{
        
        draw_board(board);
        
        move(&snake);

        if(check_status(board, snake)) 
        {
            printf("Game is over.\n");
            break;
        }

        update(board, &snake);

    }while(!check_status(board, snake)); //while the game status is 0, loop again 
}


void move(point_of_snake** snake)
{
    for(int l = snake_length - 1; l > 0; l--)
    {
        (*snake)[l] = (*snake)[l-1];
    }

    char nextmove; //to hold next move  

    printf("Enter the next move: ");
    scanf(" %c", &nextmove);
    
    switch(nextmove)
    {
        case 'w':
        case 'W':
            
            (*snake)[0].row--;
            break;

        case 's':
        case 'S':
            
            (*snake)[0].row++;
            break;

        case 'd':
        case 'D':
        
            (*snake)[0].col++;
            break;

        case 'a':
        case 'A':
           
            (*snake)[0].col--;
    }
}    


int check_status(Block*** board, point_of_snake* snake)
{
    int g_status = 0;
    
    //1.Does the head of the snake hit its own body?
    if(snake_length >= 4) //if it is not longer than 3 blocks it cant hit itself
    {    
        for(int i = 4; i < snake_length; i++) //index starts from the 2 because we are comparing the elements except the neck of the snake which has 1st index with the 0 index element
        {
            if(snake[0].row == snake[i].row && snake[0].col == snake[i].col) 
               g_status = 1;                
        }
    }
    
    //2.Does the snake collide with the wall?
    else if(snake[0].row > 10 || snake[0].col < 0 || snake[0].row < 0|| snake[0].col > 10)
       g_status = 1;
        
    //3.Does the snake encounter an obstacle that has x number of blocks, where x is greater than the length of the snake?
    else if(board[snake[0].row][snake[0].col]->type == 'o') //if the new position of the head is same as an obstacle's
    {
        if(board[snake[0].row][snake[0].col]->value > snake_length) //and if the obstacle height is greater than the length of the snake
           g_status = 1;
    }

    return g_status;
}


void draw_board(Block*** board)
{
    system("clear");
    
    printf("┌");
    
    for(int i = 0; i < 10; i++)
    {
        printf("─");
    }
    
    printf("┐");
    
    printf("\n");

    for(int i = 0; i < 10; i++) //this and
    {
        printf("│");
        
        for(int j = 0; j < 10; j++) //this loops starts with indices 1 and end at indices-1 because the most outer rows and columns are for wall characters  
        {
            if(i == snake[0].row && j == snake[0].col) printf("O"); //print the head 

            else if(board[i][j]->type == 'e') printf(" "); //if it is empty cell print space
            
            else if(board[i][j]->type == 'b') printf("."); //if it is bait cell print dot
            
            else if(board[i][j]->type == 'o') printf("%d", board[i][j]->value); //if it is obstacle cell print the height of the obstacle
            
            for(int m = 1; m < snake_length; m++)
            {
                if(i == snake[m].row && j == snake[m].col)
                {
                    printf("X");
                }
            }
        }

        printf("│");
        
        printf("\n");  
    }
        
    printf("└");
     
    for(int i = 0; i < 10; i++)
    {
        printf("─");
    }
    
    printf("┘");
    
    printf("\n");    
}


int update(Block*** board, point_of_snake** snake)
{
    static int move_c = 0, obstacle_c = 1; //move counter and obstacle counter
    
    if(board[(*snake)[0].row][(*snake)[0].col]->type == 'b') //if the new position of the head is same as an bait's
    {
        snake_length++;

        (*snake) = (point_of_snake*)realloc((*snake), snake_length * sizeof(point_of_snake)); //realloc the snake size to be able to hold tail which is one block
        
        (*snake)[snake_length-1] = (*snake)[snake_length-2];

        //regenerate a bait randomly 
        int xb, yb, bait_in_snake;
        
        do{   
            xb = rand() % 9 + 1; //generate a random value for x component of the bait
            yb = rand() % 9 + 1; //generate a random value for y component of the bait
            
            for(int i = 0; i < snake_length; i++) //checking for the match of the bait and the all snake elements
            {
                if(xb == (*snake)[i].row && yb == (*snake)[i].col)
                {
                    bait_in_snake = 1; //if they are at the same coordinates generate again
                }
            }
            
            board[xb][yb]->type = 'b'; //then assign the type of the randomly selected block as 'bait'
            board[(*snake)[0].row][(*snake)[0].col]->type = 'e';

        }while(bait_in_snake == 1); //if bait is at the top-left block or bait is generated in snake, regenerate coordinates
    }

    if(obstacle_c < 3) //if obstacle number is less than 3 and
    {
        if(move_c % 5 == 0) //if move number is a multiple of five, create new obstacle
        {
            int xo, yo;

            do{
                
                xo = rand() % 9 + 1; //generate a random value 1-9 for x component of the obstacle
                yo = rand() % 9 + 1; //generate a random value for y component of the obstacle
                
            }while(xo == 1 && yo == 1); //if obstacle or bait is at the top-left block, regenerate coordinates
            
            board[xo][yo]->type = 'o';
            board[xo][yo]->value = rand() % 9 + 1; //generating obstacle height between 1-9
            obstacle_c++;
        } 
    }

    move_c++;
}


void free_board(Block*** board, int x, int y, int z)
{
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            free(board[i][j]);
        }
        
        free(board[i]);
    }
    
    free(board);
}
