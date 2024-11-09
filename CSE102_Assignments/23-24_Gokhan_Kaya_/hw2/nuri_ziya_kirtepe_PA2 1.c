#include <stdio.h>
#include <stdlib.h>

#define NUMOFBIGRAM 100
#define INPNUM 5 

int main()
{
    FILE* reader;
    FILE* writer;
    
    int counters[NUMOFBIGRAM], firsts[NUMOFBIGRAM], seconds[NUMOFBIGRAM];
    int check1, check2; // temporary variables to check
    
    for(int i = 0; i < NUMOFBIGRAM; i++) // initialize the counters to 0s to prevent problems while checking the values of them
    	counters[i] = 0;

    reader = fopen("input.txt", "r");

    if(reader == NULL)
    {
        printf("""input.txt"" could not been opened for reading the bigrams.");
        exit(0);
    }

    int checkSame = 0, index = 0, firstLoop = 1; // to check if a bigram exists in arrays, index of arrays

    // first take bigram elements and check if bigram exists before, 
    while(fscanf(reader, "%d %d", &check1, &check2) == 2) // while 2 inputs can be taken
    {
        if(firstLoop) firstLoop = 0; // if the loop is the first one, do not check for the previous occurences. because there can not be any previous occurences
        
        else // check for the previous occurences in loops after the first loop
        {
            for(int m = 0; m < NUMOFBIGRAM; m++) 
            {   // first checks if the first input exists in arr1
                if(firsts[m] == check1 && seconds[m] == check2) //if first input exists in the first array then check if the second input exists in the second array at the same index i.
                {
                    counters[m]++; // increment counter by one at each occurence
                    checkSame = 1;
                    break;
                }   
            }
        }

        if(checkSame != 1) // if not exists; increment the index and counter, take to arrays
        {
            counters[index]++; // increment its counter by 1
            firsts[index] = check1;
            seconds[index] = check2;
            index++;
        }

        checkSame = 0;

        fseek(reader, -2, SEEK_CUR); // take back the file pointer 2 chars (compiler optimizes the memory for a integer from 4 bytes to 2 bytes)

        if(index >= NUMOFBIGRAM) break; // do not continue reading if number of bigrams in the txt file is greater than NUMOFBIGRAMS
    }

    fclose(reader);
    
    writer = fopen("output.txt", "w");

    if( writer == NULL ) 
    {
        printf("Error opening output.txt file.");
        exit(1);
    }

    for(int i = 0; i < index; i++)
    {
        fprintf(writer, "%d %d: %d\n", firsts[i], seconds[i], counters[i]);
    }

    fclose(writer);
    
    return 0;
}