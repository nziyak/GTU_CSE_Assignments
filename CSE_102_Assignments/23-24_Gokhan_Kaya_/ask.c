ask.c'de okuma işlemi için fscanf'i tercih etmemden dolayı boşlukların görmezden gelindiğini, bu sebeple language_1.txt'deki
aa bigramı sayısının 2 olması gerekirken 3 olarak sayılıyor. fscanf'e alternatif olarak hangi okuma fonksiyonlarını nasıl uygularsam
doğru sonuç elde ederim. işte bbahsettiğim dosyaların içerikleri:

language_1.txt içeriği: 

aa aa


ask.c içeriği: 

#include <stdio.h>
#include <stdlib.h>

#define CHARNUM 27 //number of letters in alphabet + 1 (space)

void fillMatrix(FILE*, char*, float(*)[CHARNUM]); //file ptr, file name, bigram array

int main()
{
    FILE* reader = NULL;
    
    //arrays that hold dissimilarities of bigrams
    float lang1[CHARNUM][CHARNUM];

    for(int row = 0; row < CHARNUM; row++) //initialize all elements of all matrices as 0
    {
        for(int col = 0; col < CHARNUM; col++)
        {
            lang1[row][col] = 0;
        }
    }

    fillMatrix(reader, "language_1.txt", lang1);
}

void fillMatrix(FILE* reader, char* filename, float (*biArray)[CHARNUM])
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
    
    printf("num of aa before reading: %lf\n", biArray[0][0]);

    while(fscanf(reader, "%c %c", &fEl, &sEl) == 2) // while 2 elements can be taken
    {
        row = fEl - 97, //distance between fEl and 'a'
        col = sEl - 97;

        if(fEl == ' ')
        {
            if(sEl == ' '); //if both elements of bigram are spaces do nothing
            else biArray[CHARNUM-1][col]++;
            
            printf("num of space-a after space-a occurence: %lf\n", biArray[0][0]);
        }
        
        else //TODO: CONSIDER THE CASE THAT THE SECOND ELEMENT OF BIGRAM IS SPACE AND THE FIRST IS NOT SPACE
        {
            if(sEl != ' ') biArray[row][col]++;
            else biArray[row][CHARNUM-1]++;

            printf("num of aa after a-a occurence: %lf\n", biArray[0][0]);
        } 

        fseek(reader, -1, SEEK_CUR); //take reader 1 char back
    }
    
    fclose(reader);
}