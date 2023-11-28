#include <stdio.h>
#include "zia.h"

int main()
{

    int menusel; //menu selection variable
    
    drawroom();
    
    printf("Welcome to The 2D Puzzle Game!\n1. New Game\n2. Help\n3. Exit\n");
    scanf("%d", &menusel);
    
    game(menusel);
    
}
