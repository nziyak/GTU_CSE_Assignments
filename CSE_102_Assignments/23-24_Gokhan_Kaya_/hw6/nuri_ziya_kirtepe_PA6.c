#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define CHARNUM 27 //number of letters in alphabet + 1 (space)

void fillWCounts(FILE*, char*, float***); //file ptr, file name, bigram array
void fillWFreqs(int, ...); //fills every cell of matrix with freq. of the bigram in that cell
float calcDiss(float**, float**); //calculates dissimilarities of two language matrix and returns it
float myAbs(float); //takes absolute and returns
float** alloc2d(void); //allocates memory for 0-initialized 2d matrix
void dealloc2d(float***); //deallocates memory for 2d matrix

int main()
{
    FILE* reader = NULL;
    
    float** langx = alloc2d(); //matrix of langx, initialized to 0
    float** langc = alloc2d(); //matrix of current language. it will be allocated and deallocated dynamically for each language

    fillWCounts(reader, "language_1.txt", &langc); //read the file and increment values of cells
    fillWCounts(reader, "language_x.txt", &langx);

    fillWFreqs(2, &langc, &langx); //now fill langc and langx matrices with frequencies

    printf("%f\n", calcDiss(langc, langx)); //print dissimilarity

    dealloc2d(&langc); //deallocate current language matrix 
//---------------------------------------------------
    langc = alloc2d(); //allocate and initialize current language matrix again
    
    fillWCounts(reader, "language_2.txt", &langc); //filling just the current language's matrix is enough because langx matrix is already filled
    
    fillWFreqs(1, &langc); //filling just the current language's matrix is enough because langx matrix is already filled

    printf("%f\n", calcDiss(langc, langx));

    dealloc2d(&langc);
//---------------------------------------------------
    langc = alloc2d();
    
    fillWCounts(reader, "language_3.txt", &langc);
    
    fillWFreqs(1, &langc);

    printf("%f\n", calcDiss(langc, langx));

    dealloc2d(&langc);
//---------------------------------------------------
    langc = alloc2d();
    
    fillWCounts(reader, "language_4.txt", &langc);
    
    fillWFreqs(1, &langc);

    printf("%f\n", calcDiss(langc, langx));

    dealloc2d(&langc);
//---------------------------------------------------
    langc = alloc2d();
    
    fillWCounts(reader, "language_5.txt", &langc);
    
    fillWFreqs(1, &langc);

    printf("%f\n", calcDiss(langc, langx));

    dealloc2d(&langc);
    dealloc2d(&langx);
}

void fillWCounts(FILE* reader, char* filename, float*** bigrams)
{
    char fEl, sEl; //first and second elements of a bigram
    int row, //distance between fEl and 'a'
        col; //distance between sEl and 'a'

    reader = fopen(filename, "r");

    if(reader == NULL) 
    {    
        printf("%s could not been opened", filename);
        exit(0);
    }
    
    for(fEl = fgetc(reader); fEl != EOF; fEl = sEl) //first take to fEl. until fEl is null, continue reading the file. at the end of every loop, assign sEl to fEl.  
    {
        sEl = fgetc(reader);

        if(sEl == EOF) break; //if sEl is EOF, break.
        
        row = fEl - 97;
        col = sEl - 97;
        
        if ((fEl == ' ' || fEl == '\n' || fEl == '\r') && (sEl != ' ' && sEl != '\n' && sEl != '\r')) //if fEl is (space OR newline) AND sEl is (not space OR not newline) 
        {
            (*bigrams)[CHARNUM - 1][col]++; //increase space-letter cell
        } 
        
        else if (!(fEl == ' ' || fEl == '\n' || fEl == '\r') && (sEl != ' ' && sEl != '\n' && sEl != '\r')) //if fEl IS NOT (space OR newline) AND sEl is (not space AND not newline)
        {
            (*bigrams)[row][col]++; //increase letter-letter cell
        } 
        
        else if (!(fEl == ' ' || fEl == '\n' || fEl == '\r') && (sEl == ' ' || sEl == '\n' || sEl != '\r')) //if fEl IS NOT (space OR newline) AND sEl is (space OR newline)
        {
            (*bigrams)[row][CHARNUM - 1]++; //increase letter-space cell
        }
    }
    
    fclose(reader);
}

void fillWFreqs(int numMatrices, ...)
{
    float sum1 = 0; //sum of the counts of bigrams
    
    va_list args; //use va_list to handle variable arguments
    va_start(args, numMatrices);

    float*** arr1 = va_arg(args, float***); //take the first matrix

    if(numMatrices == 1) //if just one matrix is passed, fill its cells then finish
    {
        for (int row = 0; row < CHARNUM; row++) 
        {
            for (int col = 0; col < CHARNUM; col++)
            {
                sum1 += (*arr1)[row][col]; //sum all counts to have numbers of all bigrams in the file
            }
        }

        for (int row = 0; row < CHARNUM; row++) //place to every cell frequency of each cell
        {
            for (int col = 0; col < CHARNUM; col++)
            {
                (*arr1)[row][col] /= sum1; //a cell's frequency is its count/sum of all counts
            }
        }
    }

    else if(numMatrices == 2) //if two matrices are passed, take the second too then fill their cells then finish
    {
        float*** arr2 = va_arg(args, float***); //take the second matrix
        float sum2 = 0;

        for (int row = 0; row < CHARNUM; row++) 
        {
            for (int col = 0; col < CHARNUM; col++) //initialize both to 0
            {
                sum1 += (*arr1)[row][col]; //sum all counts to have numbers of all bigrams in the file
                sum2 += (*arr2)[row][col]; //sum all counts to have numbers of all bigrams in the file
            }
        }

        for (int row = 0; row < CHARNUM; row++) 
        {
            for (int col = 0; col < CHARNUM; col++)
            {
                (*arr1)[row][col] /= sum1;
                (*arr2)[row][col] /= sum2;
            }
        }
    }
    
    va_end(args);
}

float calcDiss(float** lang1, float** lang2)
{
    float dissimilarity = 0;

    for (int row = 0; row < CHARNUM; row++) 
    {
        for (int col = 0; col < CHARNUM; col++)
        {
            dissimilarity += myAbs(lang1[row][col] - lang2[row][col]); //take difference of the values of same index cells, and assign that
        }
    }

    return dissimilarity;
}

float myAbs(float num)
{ 
    return (num < 0) ? -num : num; //if less than 0 return -num, else return num itself
}

float** alloc2d(void)
{
    float **langc = (float **)calloc(CHARNUM, sizeof(float *));
    
    if (langc == NULL) 
    {
        fprintf(stderr, "memory allocation is unsuccesful\n");
        exit(1);
    }

    for (int i = 0; i < CHARNUM; i++) 
    {
        langc[i] = (float *)calloc(CHARNUM, sizeof(float)); //then allocate every row
        
        if (langc[i] == NULL) 
        {
            fprintf(stderr, "memory allocation is unsuccesful\n");

            for (int j = 0; j < i; j++) //free unsuccesful memory allocations
            {
                free(langc[j]);
            }
            free(langc); 

            exit(0);
        }
    }

    return langc;
}

void dealloc2d(float ***matrix)
{
    for (int i = 0; i < CHARNUM; i++) free((*matrix)[i]); //first free every row
    free(*matrix); //then free all
    *matrix = NULL;
}

/*
    matrix usage options:
    1)with static matrices: 
        1)just one matrix: create one matrix for the current language. initialize it to 0. when you finished ur job with that lang, initialize matrix again and use.
            disadvantage: you have to initialize matrix everytime you want to use. it means CHARNUM X CHARNUM operations for every language after the first language.
        2)each language has its matrix: too many memory is used.
    2)with dynamic matrices:
        1)allocate memory for current language with calloc. when ur job is done with current, deallocate it and allocate for the next language.
*/