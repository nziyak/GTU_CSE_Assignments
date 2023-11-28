#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPNUM 10
#define NUMOFBIGRAM 100

void randWriterToInp(void); // this function writes number of INPNUM random numbers(1-20) to input.txt
void reader(int* el1, int* el2);

int main()
{
    int /*counter[NUMOFBIGRAM],*/firsts[NUMOFBIGRAM], seconds[NUMOFBIGRAM];
    
    randWriterToInp();

    reader(firsts, seconds);
}

void randWriterToInp(void)
{
    FILE* writer;
    int num;
    
    srand(time(NULL));

    writer = fopen("input.txt", "w");

    if(writer == NULL)
    {
        printf("""input.txt"" could not been opened for writing random numbers 1-20.");
        exit(0);
    }

    for(int i = 0; i < INPNUM; i++) 
    {
        num = rand() % 20 + 1;
        fprintf(writer, "%d ", num);
    }  

    fclose(writer); 
}

void reader(int* el1, int* el2) // ctr is the array holds counters of bigrams, other parameters are element 1 and element 2 respectively
{
    FILE* reader;
    int index = 0;
    reader = fopen("input.txt", "r");

    if(reader == NULL)
    {
        printf("""input.txt"" could not been opened for counting the bigrams.");
        exit(0);
    }

    while(fscanf(reader, "%d %d", &el1[index], &el2[index]) == 2) 
    {
        printf("%d %d\n", el1[index], el2[index]);
        fseek(reader, -2, SEEK_CUR);
        index++;
    }

    for(int i = 0; i < index; i++)
    {
        printf("\nel1[%d]: %d el2[%d]: %d\n", i, el1[i], i, el2[i]);
    }

    fclose(reader);
}