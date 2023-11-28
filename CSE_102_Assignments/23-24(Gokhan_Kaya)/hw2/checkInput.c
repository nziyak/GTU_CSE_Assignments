#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPNUM 10
#define NUMOFBIGRAM 100

void randWriterToInp(void); // writes number of INPNUM random numbers(1-20) to input.txt
void reader(int* el1, int* el2, int* count); // reads the file and take bigrams to arrays according to their previous existences
int searchAndCount(int* arr, int* arr2, int* count, int elNum, int target1, int target2); //checks if the input bigram is previously added to arrays, if so increments related counter

int main()
{
    int counter[NUMOFBIGRAM],firsts[NUMOFBIGRAM], seconds[NUMOFBIGRAM];
    
    //randWriterToInp();

    reader(firsts, seconds, counter);
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

void reader(int* el1, int* el2, int* count) // ctr is the array holds counters of bigrams, other parameters are element 1 and element 2 respectively
{
    FILE* reader; // to read the file and take bigrams to arrays
    FILE* checker; // to check that if a bigram exists previously or not

    int index = 0, check1, check2, isExist; // index of arrays, temporary variables to check, existing of a bigram 
    
    reader = fopen("input.txt", "r");
    checker = fopen("input.txt", "r");

    if(reader == NULL || checker == NULL)
    {
        printf("""input.txt"" could not been opened for reading the bigrams.");
        exit(0);
    }

    // first take bigram elements and check if exists before, 
    // if exists, increment the counter, dont take to arrays
    // else take to arrays
    while(fscanf(checker, "%d %d", &check1, &check2) == 2) // while 2 inputs can be taken
    {
        //printf("%d %d\n", check1, check2);
        fseek(checker, -2, SEEK_CUR); // take back the file pointer 2 bytes (compiler optimizes the memory for a integer from 4 bytes to 2 bytes)

        isExist = searchAndCount(el1, el2, count, INPNUM, check1, check2);
        
        if(!isExist) // if the bigram is not existing previously, take it to arrays
        {
            fscanf(reader, "%d %d", &el1[index], &el2[index]);
            fseek(reader, -2, SEEK_CUR);
            index++;
        }
    }

    /*for(int i = 0; i < index; i++)
    {
        printf("\nel1[%d]: %d el2[%d]: %d\n", i, el1[i], i, el2[i]);
    }*/

    fclose(reader);
    fclose(checker);
}

int searchAndCount(int* arr1, int* arr2, int* count, int elNum, int target1, int target2)
{
    int i;
    
    for(i = 0; i < elNum; i++) // first checks if the first input exists in arr1
        if(arr1[i] == target1) break;

    //if first input exists in the first array then check if the second input 
    //exists in the second array at the same index i.
    if(arr2[i] == target2) 
    {
        count[i]++; // if the input bigram exists previously, count++ (counting in this function, not in the reader because counting in reader function requires returning searchAndCount function the index of occurence)
        printf("\n%d %d exists %d times\n", arr1[i], arr2[i], count[i]);
        return 1; // if exists there, return 1 to indicate that
    }

    else return 0; // does not exist
}