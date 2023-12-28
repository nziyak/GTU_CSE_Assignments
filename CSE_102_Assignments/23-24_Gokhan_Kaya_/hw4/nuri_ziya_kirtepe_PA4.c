#include <stdio.h>
#include <string.h>

#define MAX_ROW_LENGTH 250
#define MAX_ROW_NUM 100
#define MAX_WORD_LENGTH 10

char randoms[MAX_ROW_NUM][MAX_ROW_LENGTH];

int randomFileReader(FILE *reader); //read the input2.txt and assign to a 2D array
int searcher(FILE* writer, int i, int j, int wordLen, int lineLen, char *word, int direction); //search words, print their positions to output.txt

int main()
{
    FILE *reader = NULL; //first read input2.txt. then read the input1.txt
    FILE *writer = NULL; //write occurences to output.txt
    char word[MAX_WORD_LENGTH + 1];
    int wordLen = 0, //length of the word that is been searching for
        lineLen = 0, //length of the word that is been searching on
        searchRes; //result of the search

    if (!randomFileReader(reader)) return 0; //if randoms are could not been read terminate

    reader = fopen("input1.txt", "r");

    if (reader == NULL)
    {
        printf("input1.txt could not be opened\n");
        return 0;
    }

    writer = fopen("output.txt", "w");

    if (writer == NULL)
    {
        printf("output.txt could not be opened\n");
        return 0;
    }

    while (fscanf(reader, "%s", word) == 1) //take words one by one
    {
        wordLen = strlen(word);

        for (int i = 0; i < MAX_ROW_NUM; i++) //traverse rows
        {
            lineLen = strlen(randoms[i]);

            for (int j = 0; j < lineLen; j++) //traverse columns
            {
                if (randoms[i][j] == word[0]) //if the current element is same with the first letter of to be searched
                {
                    searchRes = searcher(writer, i, j, wordLen, lineLen, word, 1); //firstly look horizontally. the last argument indicates the search direction. 
                    
                    if(searchRes) continue; //if found horizontally, do not look in other directions.
                    
                    searchRes = searcher(writer, i, j, wordLen, lineLen, word, 2); //secondly look vertically
                    
                    if(searchRes) continue;

                    searchRes = searcher(writer, i, j, wordLen, lineLen, word, 3); //lastly look diagonally
                    
                    if(searchRes) continue;
                }
            }
        }
    }

    fclose(reader);
    fclose(writer);

    return 0;
}

int randomFileReader(FILE *reader)
{
    int rowIndex = 0; //counter that indicates row number
    
    reader = fopen("input2.txt", "r");

    if (reader == NULL)
    {
        printf("input2.txt could not be opened.\n");
        return 0;
    }

    while (fgets(randoms[rowIndex], MAX_ROW_LENGTH, reader) != NULL) //while fgets is not reached to end of the file, take each row
    {
        randoms[rowIndex][strcspn(randoms[rowIndex], "\n")] = '\0'; //replace new lines with null characters
        rowIndex++; //increment row index to be able to look at new line

        if (rowIndex >= MAX_ROW_NUM) break; //if row index is equal to max row num, stop taking
    }

    fclose(reader);
}

int searcher(FILE* writer, int i, int j, int wordLen, int lineLen, char *word, int direction)
{
    int k;
    
    switch (direction)
    {
        case 1:

            for (k = 0; k < wordLen; ++k) //look at every character
            {
                if (randoms[i][j + k] != word[k]) break; //if equality of horizontal search is not provided break
                if (k == 0 && ((lineLen - k) < wordLen)) break; //if looking for the first character and the number of characters between the end of line and current position is less than the length of word, do not look rest characters
            }
            
            if(k == wordLen) //if to be searched length is found
            {
                fprintf(writer, "%s (%d, %d) Horizontal\n", word, i+1, j+1);

                return 1;
            }    

            else return 0; //if correspendence could not been found, return 0

            break;
        
        case 2:

            for (k = 0; k < wordLen; ++k)
            {
                if (randoms[i + k][j] != word[k]) break; //if equality of vertical search is not provided break
            }
            
            if(k == wordLen)
            {
                fprintf(writer, "%s (%d, %d) Vertical\n", word, i+1, j+1);

                return 2;
            }    

            else return 0; 

            break;

        case 3:

            for (k = 0; k < wordLen; ++k)
            {
                if (randoms[i + k][j + k] != word[k]) break; //if equality of diagonal search is not provided break
            }
            
            if(k == wordLen)
            {
                fprintf(writer, "%s (%d, %d) Diagonal\n", word, i+1, j+1);

                return 3;
            }    

            else return 0;

            break;
    }
}