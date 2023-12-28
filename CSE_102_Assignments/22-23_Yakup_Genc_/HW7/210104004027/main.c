#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_WORD_NUMBER 300000
#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 12
#define DELIMITERS " .,;:!?-_\"'"

int read_dict(const char *dictionary, char dict[][MAX_WORD_SIZE+1]);
int read_text(const char  *text, const char  *ignore, char words_in_text[][MAX_WORD_SIZE+1]);
double dissimilarity(char *w1, char *w2, char dict[MAX_WORD_NUMBER][MAX_WORD_SIZE+1], float threshold);
int histogram(const char words_in_text[MAX_WORD_NUMBER][MAX_WORD_SIZE],const int occurrences[], const char hist[][MAX_WORD_SIZE+5+20]);
int check_for_same(char  *w1, char words_in_text[MAX_WORD_NUMBER][MAX_WORD_SIZE+1], int num_textwords);
void mystrcpy(char *dest, const char *src);

char inputwords[MAX_WORD_NUMBER][MAX_WORD_SIZE+1];
char dict[MAX_WORD_NUMBER][MAX_WORD_SIZE+1];

const char *dictionary = "dictionary.txt";
const char *text = "input.txt";
const char *ignore = "ignore.txt";

int main() 
{
    char input[MAX_WORD_COUNT * (MAX_WORD_SIZE)]; // create a char array to store up to 100 words with a max length of 12
    char user_inputwords[MAX_WORD_NUMBER][MAX_WORD_SIZE+1];
    char w1[MAX_WORD_SIZE], w2[MAX_WORD_SIZE];

    int num_textwords = read_text(text, ignore, inputwords); //taking number of words of text to num_textwords variable
    
    float threshold = 1;
        
    printf("Enter one or more words (separated by spaces): ");
    
    fgets(input, sizeof(input), stdin); // read in a line of text (including spaces)
    
    int num_inpwords = 0;
    
    char *token = strtok(input, " \t\n"); // split the line into words using whitespace characters as delimiters
    
    while(token != NULL && num_inpwords < MAX_WORD_COUNT) 
    {
        strncpy(user_inputwords[num_inpwords], token, MAX_WORD_SIZE-1); // copy the token into the words array
        user_inputwords[num_inpwords][MAX_WORD_SIZE-1] = '\0'; // add null terminator at the end
        num_inpwords++;
        token = strtok(NULL, " \t\n");
    }
    
    printf("\nThe word(s) you entered are:\n");
    
    for(int i = 0; i < num_inpwords; i++) 
    {
        printf("%s\n", user_inputwords[i]);
    }

    int m;
    
    int num_dictwords = read_dict(dictionary, dict);

    for(m = 0; m < num_inpwords; m++) //copy input words to w1 respectively
    {
       //assign the input word to w1 char pointer then it will be sent check_for_same and dissimilarity functions        
       int occurence_in_text, occurence_in_dict;
       
       occurence_in_text = check_for_same(user_inputwords[m], inputwords, num_textwords);

       if(occurence_in_text > 0)//if there is/are occurences of the word in the text file print its occurence
       {
          printf("""%s"" appears in ""input.txt"" %d times.\n", user_inputwords[m], occurence_in_text);
       }
       
       else
       {
          occurence_in_dict = check_for_same(user_inputwords[m], dict, num_dictwords);

          if(occurence_in_dict == 0)
          {
              printf("there is no matches in both input.txt and dictionary.txt");
          }

          else if(occurence_in_dict > 0)
          {
              dissimilarity(user_inputwords[m], NULL, dict, threshold);
          } 
       }
    }
    
    return 0;
}


int read_dict(const char *dictionary, char dict[][MAX_WORD_SIZE+1])
{
    FILE *dict_reader;
    
    char word[100];
    
    dict_reader = fopen(dictionary, "r");
    
    if(dict_reader == NULL) 
    {
        printf("Error: Could not open file dictionary.txt");
        
        return 1;
    }
    
    int word_counter = 0;  //word counter
    
    int i = 0; //array index
    
    while (fscanf(dict_reader, "%s", word) != EOF) //take input to word char array until the space(fscanf takes input until space)
    {
        if(isalpha(word[0])) //if word's first character is letter copy this input in word to dict[i]
        {
            //printf("%s\n", word);
            mystrcpy(dict[i], word);
            word_counter++;
            i++;
        }
    }
    
    dict[i+1][0] = '-';

    fclose(dict_reader);
    
    return word_counter;
}


int read_text(const char  *text_file, const char  *ignore_file, char inputwords[MAX_WORD_NUMBER][MAX_WORD_SIZE+1])
{
    FILE *ignore_reader;
    FILE *text_reader;
    
    char ignore_words[200][MAX_WORD_SIZE];
    char line[100];
    
    int num_ignore_words = 0;
    int num_words = 0;
   
    //reading the ignore.txt and taking the to be ignore words to an array
    ignore_reader = fopen(ignore_file, "r");

    if(ignore_reader == NULL) 
    {
        printf("Error: Could not open file ignore.txt");
        
        return 1;
    }
    
    while(fscanf(ignore_reader, "%s", line) != EOF) //take input to word char array until the space(fscanf takes input until space)
    {
        if(isalpha(line[0])) //if word's first character is letter copy this input in word to ignore_words[i]
        {
            //printf("%s\n", line);
            mystrcpy(ignore_words[num_words], line);
            num_words++;
        }
    }
    
    fclose(ignore_reader);
    
    //reading the input.txt and taking the words in it to an array
    text_reader = fopen(text_file, "r");
    
    if(text_reader == NULL) 
    {
        printf("Error: Could not open file input.txt");
        
        return 1;
    }
    
    num_words = 0; //initializing to 0 because we are looking for the number of words in input.txt

    while(fscanf(text_reader, "%s", line) == 1)
    {
        char *token = strtok(line, DELIMITERS);

        while(token != NULL)
        {
            mystrcpy(inputwords[num_words], token);
            
            num_words++;
            
            token = strtok(NULL, DELIMITERS); 
        }
    }
    
    fclose(text_reader);

    for(int j = 0; j < num_words; j++)
    {
        for(int k = 0; k < num_ignore_words; k++) //this loops loops the number of words that ignore.txt has
        {
           if(inputwords[j] == ignore_words[k]) //if an element of words_in_text array is same as ignore_words, change that element to 0 and decrease word_number 1
           {
               int m = 0;

               while(inputwords[j][m] != '\0')
               {  
                  inputwords[j][m] = 0;
                  m++; 
               }  
               
               num_words--;         
           }
        }

        //printf("%s\n", inputwords[j]);
    }
    
    return num_words;
}


double dissimilarity(char *w1, char *w2, char dict[MAX_WORD_NUMBER][MAX_WORD_SIZE+1], float threshold)
{
    int index_of_input, num_word, vector_size; //index of the input word in the dictionary, number of words in dictionary, number of vectors that each word has

    char the_closest[MAX_WORD_SIZE];
     
    double distances[1003]; //array to hold distances
    
    FILE *dict_reader;
    
    dict_reader = fopen(dictionary, "r");

    fscanf(dict_reader, "num_word=%d, vector_size=%d", &num_word, &vector_size);
    
    double vector[num_word+3][vector_size]; //to hold vector components of the words in the dictionary
    
    char line[1500];
    
    int i = 0, j;

    if(dict_reader == NULL) 
    {
        printf("dictionary.txt açılamadı.\n");
        return 1;
    }
    
    while(!feof(dict_reader) && i < num_word) 
    {
        fscanf(dict_reader, "%lf", &vector[i][0]);
        
        for(j = 1; j < vector_size; j++) 
        {
            fscanf(dict_reader, ",%lf", &vector[i][j]);
        }
        i++;
    }

    fclose(dict_reader);
    
    /*for(int u = 0; u < num_word; u++)
    {
        for(int v = 0; v < vector_size; v++)
        { 
            printf("%lf", vector[u][v]);
        }
    }*/

    for(int m = 0; m < num_word+3; m++) //finding the index of the input word in the dictionary
    {
        if(strcmp(w1, dict[m]) == 0)
        {
            index_of_input = m;
            break; //dont have to look for matches after one match
        }
    }

    for(int i = 0; i < num_word+3; i++) //calculate and assign the distances between the input word and the other words in the dictionary
    {
        for(int j = 0; j < vector_size; j++)
        {
           distances[i] += pow(vector[index_of_input][j] - vector[i][j], 2);
           distances[i] = sqrt(distances[i]);
        }
    }
        
    double min_dist; //minimum distance, index of the min distance
    int index_of_min;

    min_dist = distances[0];

    for(int m = 0; m < 1003; m++)
    {
        if(distances[m] < min_dist && distances[m] > 0) //if the distances element is less then distances[0] and is not equal 0 new min is that element because equality to 0 means it is the same word.
        {
            min_dist = distances[m];
            index_of_min = m;
        }  
    }
    
    int num_textwords = read_text(text, ignore, inputwords); //taking number of words of text to num_textwords variable
    
    int occ_time_in_text = check_for_same(the_closest, inputwords, num_textwords); //find how many times occurs in text

    mystrcpy(the_closest, dict[index_of_min]); //copy the the closest word to the_closest variable

    printf("\n%s doesn’t appear in “input.txt” but “%s” appears %d times", w1, the_closest, occ_time_in_text);
  
    return min_dist;
}
     

//returns occurence number. if it is diff. from 0, dont call the dissimilarity
int check_for_same(char  *w1, char words_in_text[MAX_WORD_NUMBER][MAX_WORD_SIZE+1], int num_checkwords)
{
    int occ_num = 0; //occurence number

    for(int i = 0; i < num_checkwords; i++)
    {
        if(strcmp(w1, words_in_text[i]) == 0)
        {
            occ_num++;
        }   
    }

    return occ_num;   
}


void mystrcpy(char *dest, const char *src)
{
    while(*dest++ = *src++) //copies the string in source to destination
    {}
}


