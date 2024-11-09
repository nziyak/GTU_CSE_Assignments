#include <stdio.h>
#include <stdlib.h> //for srand()
#include <time.h> //for random seeds to generate completely random numbers i will use time as seed.
#include "zia.h"

//movement macros. in case user enter lower or upper case i defined both of them
#define up 'w'
#define UP 'W'
#define down 's'
#define DOWN 'S'
#define right 'd'
#define RIGHT 'D'
#define left 'a' 
#define LEFT 'A'

//before start, i should indicate that i am not counting the moves to the wall. because they are not real moves. character stays in same place. 
void game(int menusel)
{
    
    switch(menusel)
    {
    
        case 1: 
              
                drawroom();
              
                break;
        
        case 2:          
              
                printf("The game consists of a dark room of size NxN, as shown below.\n");
                printf("The objective of the game is to free the character by leading her/him to the door.\n");
                printf("The game is over when the character reaches the door.\n"); 
                printf("The locations of the character and the door will randomly appear at each run of the game.\n"); 
                printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right.\n"); 
                printf("Diagonal moves are not allowed.\n");  
                printf("The user will input their desired move using the following keys:\n");  
                printf("'a' for left, 'd' for right, 'w' for up, and 's' for down.\n");
                printf("Have Fun!\n");
              
                printf("1. New Game\n2. Help\n3. Exit\n");
                scanf("%d", &menusel);
    
                game(menusel);
              
                break;
              
        case 3: 
              
                printf("Goodbye!");
                exit(0);          
    }
    
}


void drawroom(void)
{
     int size, xd, yd, xc, yc; //room size variable, x coordinate of the room, y coordinate of the room, x coordinate of the character, y coordinate of the room.
     
     printf("please select the room size(5-10)");
     scanf("%d", &size);
     
     srand(time(NULL)); // i am giving the seeds to srand() from time itself so it can give randomly numbers
     
     switch(size)
     {
         
         case 5:
         case 6:
         case 7:
         case 8:
         case 9:
         case 10: 
         
                 xd = rand() % size + 1; // choosing a random number for x positions of door between 1-size because map is sizexsize
                 yd = rand() % size + 1; // choosing a random number for y positions of door between 1-size because map is sizexsize
                 xc = rand() % size + 1; // choosing a random number for x positions of character between 1-size because map is sizexsize
                 yc = rand() % size + 1; // choosing a random number for y positions of character between 1-size because map is sizexsize
                 
                 
                 while(((xc == xd) && (yc == yd))) //at the beginning positions of door and characters shouldn't be same so if they are same, generate position of character again. and coordinates cant be 0. 
                 {
                      xc = rand() % size + 1; 
                      yc = rand() % size + 1;
                 }
                 
                 for(int i = 0; i < (2 * size) + 1; i++) //the header lines. 2*size+1 '-' character is enough for each size.
                 {
                    printf("-"); 
                 }
                 
                 printf("\n");
    
                 for(int i = 1; i < (size + 1); i++) 
                 {
                  
                     for(int j = 1; j < (size + 1); j++) //this nested for loop provides us to draw the game room
                     {
            
                          if(i == (size - yd + 1) && j == xd) //if coordinates belongs to the randomly chosen position, print D. i did size-yd+1 operation because this for loops cause counting y coordinates from top. 
                          { 
                                printf("|D");
                          } 
            
                          else if(i == (size - yc + 1) && j == xc) //if coordinates belongs to the randomly chosen position, print C. i did size-yc+1 operation because this for loops cause counting y coordinates from top.
                          { 
                                printf("|C");
                          } 
            
                          else //else print wall and space
                          {
                                printf("| ");
                          }
                          
                     }
        
                     printf("|\n");
              
                 }
            
                 for(int i = 0; i < (2 * size) + 1; i++) //the ending lines
                 {
                    printf("-"); 
                 }
                 
                 printf("\n"); 
              
                 printf("'D' at (%d, %d)\n", xd, yd);
                 printf("'C' at (%d, %d)\n", xc, yc);
             
                 gplay(xd, yd, xc, yc, size);
                 
                 break;
              
         
         default:
                 
                 printf("Invalid size! Try again.\n");
                 
                 drawroom(); //in case user entered invalid size, call drawroom() to reentering size        
                                    
     }
}


void gplay(int xd, int yd, int xc, int yc, int size)
{
    
    char move; //holds move selection
    int c = 0; //move counter
    
    while(!((xc == xd) && (yc == yd))) //while character reaches the door, offering new move process should continue
    {
        
         printf("next move? ");
         scanf(" %c", &move);
      
         switch(move)
         {
         
            case UP:
            case up: 
                    
                    if((yc == size)) //if character is in the most upper line print him/her in same place.
                    {
                            
		            printf("YOU CAN NOT GO MORE UP!\n");
		            
		    }
                    
                    else //if character is not in the most upper line
                    {
		            yc++; //y coordinate of the character should increment
		            
		            c++; //count 1 move
		    }
                    
                    break;
            
            
            case DOWN:
            case down:
                      
                      if((yc == 1)) //if character is in the most lower line print him/her in same place.
                      {
                              printf("YOU CAN NOT GO MORE DOWN!\n");
		      }
                      
                      else
                      {
		              yc--; //y coordinate of the character should decrement
		                
		              c++; //count 1 move   
                      }
                      
                      break;  
                        
                         
            case RIGHT:
            case right:
                       
                       if((xc == size)) //if the character is at most right column print him/her at same place
                       {
                                printf("YOU CAN NOT GO MORE RIGHT!\n");
                       }
                        
                        else //if the character is not at most right column
                        {
                                
                                xc++;//x coordinate of the character should increment
		                		                
		                c++; //count 1 move 

		        }        
		              
                        break;
                        
                          
            
            case LEFT:
            case left:                                
                      
                      if(xc == 1)//if the character is at the most left column print him/her at same place
                      {
		              
		            printf("YOU CAN NOT GO MORE LEFT!\n");
		                
                      }
                         
                      else
                      {
		              xc--; //x coordinate of the character should decrement
		              
		              c++; //count 1 move   
                      }  
                      
                      break;
                          
           }
           
            //printing room with the character in his/her new location. (if in borders, prints in same location)
            for(int i = 0; i < (2 * size) + 1; i++) //top lines
            {
               printf("-"); 
            }
         
            printf("\n");

            for(int i = 1; i < (size + 1); i++) 
            {
          
                 for(int j = 1; j < (size + 1); j++) //this nested for loop provides us to draw the game room
                 {
    
                      if(i == (size - yd + 1) && j == xd) //the door stays in same location
                      { 
                            printf("|D");
                      } 
    
                      else if(i == (size - yc + 1) && j == xc) //print C in new coordinates (if in the top line, because yc is not incremented, print in same location)
                      { 
                            printf("|C");
                      } 
    
                      else //else print wall and space
                      {
                            printf("| ");
                      }
                  
                 }

                 printf("|\n");
      
            }
    
            for(int i = 0; i < (2 * size) + 1; i++) //the ending lines
            {
                printf("-"); 
            }
         
            printf("\n"); 
            
            if(((xc == xd) && (yc == yd)))
            {
                 printf("Character succesfully escaped. Game is over. Congratulations!\n");
                 printf("Total moves: %d\n\n", c);

                 status(1);//the game is over
            }

	    else
	    {
	         printf("'D' at (%d, %d)\n", xd, yd);
	         printf("'C' at (%d, %d)\n", xc, yc); 
	            
	         status(0); //the game is not over
	    } 
  }       //by the way, i am not counting the moves to the wall. because they are not real moves. character stays in same place.
    
}

int status(int a) 
{
     if(a == 0) //actually status() takes 0 or 1. if 0, game is not over
     {
        return 0;
     }
     
     else if(a == 1) //if 0, game is over
     {
        return 1; 
     }
}
