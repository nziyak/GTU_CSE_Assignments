#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Book{
    char isbn[20];
    char title[50];
    char author[50];
    int publicationYear;
    struct Book* next;
};

struct Book* head_book = NULL;

struct Student{
    char name[50];
    char ID[20];
    char borrowedBooks[20][20]; //each student can have max 20 books on him/her
    struct Student* next;
};

struct Student* head_student = NULL;

struct filteredBooks{ 
    char isbn[20];
    char title[50];
    char author[50];
    int publicationYear;
    struct filteredBooks* next;
};

struct filteredBooks* filtered_head = NULL;

void menu(void);
void addBook(char* isbn, char* title, char* author, int publicationYear, int method);
void deleteBook(char* isbn);
void updateBook(char* isbn, char* feature, char* value);

void filterAndSortBooks(int filterChoice, char* filter, int sortChoice);
void swap(struct filteredBooks* a, struct filteredBooks* b);
struct Book* reverseBookList(struct Book* head_book);
void searchBooks(int searchChoice, char* searchValue);

void borrowedBooks();
void borrowBook(char* isbn); 
void returnBook(char* isbn);

int main()
{
    menu();

    return 0;
}

void menu(void)
{
    int selection, publicationYear, method;
    char isbn[20];
    char title[50];
    char author[50];

    do{ 
        printf("------------------------------------------------------------------\nWelcome to the Ziya's Library Management System!\nPlease select an operation:\n");
        printf("1 to add, delete, update books\n");
        printf("2 to filter and sort books, reverse the book list, search books\n");
        printf("3 to borrow and return books, list a students borrowed books\n");
        printf("4 to Exit.\n");
        
        scanf("%d", &selection);
        
        switch(selection)
        {
            case 1:
                
                printf("\n-------------------\n1 to add book\n");
                printf("2 to delete book\n");
                printf("3 to update book\n");
                printf("4 to turn back to main menu.\n");
                printf("5 to Exit.");
                
            // int sel;
                
                scanf("%d", &selection);
                
                switch(selection)
                {
                    case 1: //add book
                        
                        printf("enter the ISBN: ");
                        scanf(" %[^\n]", isbn);

                        printf("\nenter the title: ");
                        scanf(" %[^\n]", title);

                        printf("\nenter the author: ");
                        scanf(" %[^\n]", author);

                        printf("\nenter the publication year: ");
                        scanf("%d", &publicationYear);

                        printf("\nenter the adding method(0 for FIFO / 1 for LIFO): ");
                        scanf("%d", &method);

                        addBook(isbn, title, author, publicationYear, method);    
                        
                        break;

                    case 2: //delete book

                        printf("\nPlease enter the ISBN of the book will be removed: ");   
                        scanf("%20s", isbn); 

                        deleteBook(isbn);

                        break;

                    case 3: //update book
                        
                        char feature[17], strvalue[50];
                        int intvalue;

                        printf("\nPlease enter the ISBN number of the book to be updated: ");
                        scanf("%20s", isbn);

                        printf("\nPlease enter the feature you want to update: ");
                        scanf(" %[^\n]", feature);

                        if(!strcmp(feature, "publication year"))
                        {
                            printf("\nPlease enter the new publication year: ");
                            scanf("%d", &intvalue);
                            
                            sprintf(strvalue, "%d", intvalue);
                                                                 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                            updateBook(isbn, feature, strvalue); //bu değeri atarken yeniden integera çevirmeyi unutma!!!!!
                        }

                        else
                        {
                            printf("\nPlease enter the new %s: ", feature);
                            scanf(" %[^\n]", strvalue);
                            
                            updateBook(isbn, feature, strvalue);
                        }
                        break;

                    case 4:
                        
                        menu();
                        break;

                    case 5:

                        exit(0); 

                }

                break;

            case 2:
                
                printf("\n----------------------------\n1 to filter and sort books\n");
                printf("2 to reverse the book list\n");
                printf("3 to search book\n");
                printf("4 to turn back to main menu.\n");
                printf("5 to Exit.");
                
                scanf("%d", &selection);
                
                switch(selection)
                {
                    case 1: //filter and sort books

                        int filterChoice, sortChoice;
                        char filter[50];
 
                        printf("\nenter the filter choice(0 for author, 1 for publication year): ");
                        scanf("%d", &filterChoice);
                        
                        printf("\nenter the filter: ");
                        scanf(" %[^\n]", filter);

                        printf("\n enter the sort choice(0 for title, 1 for author, 2 for publication year): "); 
                        scanf("%d", &sortChoice);
                         
                        filterAndSortBooks(filterChoice, filter, sortChoice);

                        break;

                    case 2: // reverse the book list

                        FILE* reader = fopen("books.txt", "r");
                        struct Book* current = head_book;

                        char line[256];
                        
                        while(fgets(line, sizeof(line), reader) != NULL) 
                        {
                            struct Book* new_book = (struct Book*)malloc(sizeof(struct Book));
                            
                            fscanf(line, "%[^,],%[^,],%[^,],%d", new_book->isbn, new_book->title, new_book->author, &new_book->publicationYear);
                            
                            new_book->next = NULL;

                            if(head_book == NULL) 
                            {
                                head_book = new_book;
                                current = new_book;
                            } 
                            
                            else 
                            {
                                current->next = new_book;
                                current = new_book;
                            }
                        }

                        fclose(reader);
                        //BURAYA BAK YETİŞİRSE YENİDEN
                        head_book = reverseBookList(head_book);
                        current = head_book;

                        printf("%s %s %s %d", head_book->isbn, head_book->title, head_book->author, head_book->publicationYear);
                        
                        while(current != NULL)
                        {
                            printf("%s, %s, %s, %d\n", current->isbn, current->title, current->author, current->publicationYear);
                            current = current->next;
                        }

                        // Free allocated memory for each book
                        current = head_book;
                        while(current != NULL) 
                        {
                            struct Book* temp = current;
                            current = current->next;
                            free(temp);
                        }
                        
                        break;

                    case 3: //search books

                        int searchChoice;
                        char value[50];

                        printf("please enter the search choice of what you are going to search the book with\n 0 for searching by ISBN number, 1 for searching by author, 2for searching by title: ");
                        scanf("%d", &searchChoice);

                        printf("please enter the value: ");
                        scanf(" %[^\n]", value);

                        searchBooks(searchChoice, value);

                        break;

                    case 4:
                        
                        menu();
                        break;

                    case 5:

                        exit(0); 

                }

                break;

            case 3:
                
                printf("\n-------------------\n1 to borrow book\n");
                printf("2 to return book\n");
                printf("3 to list borrowed books of a student\n");
                printf("4 to turn back to main menu.\n");
                printf("5 to Exit.");
                
                scanf("%d", &selection);
                
                switch(selection)
                {
                    case 1:

                        break;

                    case 2:

                        break;
                    
                    case 3:

                        break;
                
                    case 4:
                        
                        menu();
                        break;

                    case 5:
                        
                        exit(0);
                        break;
                }

                break;
        }

    }while(selection != 4);    
}


void addBook(char* isbn, char* title, char* author, int publicationYear, int method)
{
    FILE *book_adder;
    
    struct Book* new_book = (struct Book*)malloc(sizeof(struct Book));
    struct Book* last = head_book;
    
    strcpy(new_book->isbn, isbn);
    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    
    new_book->publicationYear = publicationYear;

    new_book->next = NULL;
    
    if(method == 0) //if the adding method is FIFO
    {
        if(head_book == NULL) //if the head is NULL add the new book to head_book node
        {
            head_book = new_book;
        }
        
        else //else find the last node and add the new book to the last node
        {
            while(last->next != NULL)
            {
                last = last->next;
            }

            last->next = new_book;
        }
    }

    else //if the adding method is LIFO
    {
        new_book->next = head_book;
        head_book = new_book;
    }

    printf("Following book is added succesfully: %s\n", new_book->title);

    book_adder = fopen("books.txt", "a");

    if(book_adder == NULL) 
    {
        printf("File could not been opened.\n");
        return;
    }

    fprintf(book_adder, "\n%s,%s,%s,%d", new_book->isbn, new_book->title, new_book->author, new_book->publicationYear);

    fclose(book_adder);
}


void deleteBook(char* isbn)
{
    //part 1: deleting from the Book linked list
    struct Book* current = head_book;
    struct Book* previous = NULL;

    //Deleting the head_book if its isbn matches with input isbn
    if(current != NULL && strcmp(current->isbn, isbn) == 0) 
    {
        head_book = current->next;
        free(current);
        printf("book is deleted succesfully");
    }

    else //checking the other nodes
    {
        while(current != NULL && strcmp(current->isbn, isbn) != 0) 
        {
            previous = current;
            current = current->next;
        }

        if(current == NULL) 
        {
            printf("no match can be found for ISBN %s in linked list\n", isbn);
        }

        previous->next = current->next; //deleting the matched node by skipping that node
        
        printf("book is deleted succesfully from the linked list.\n");

        printf("deleteds isbn: %s", current->isbn);
        free(current);
    }

    //part 2: deleting from the books.txt file
    FILE *book_finder = fopen("books.txt", "r");
    
    if(book_finder == NULL) 
    {
        printf("books.txt could not been opened\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    
    if(tempFile == NULL) 
    {
        printf("temporary file could not been opened\n");
        fclose(book_finder);
        return;
    }

    char line[100];
    
    char* targetText = strdup(isbn);
    
    size_t targetLength = strlen(targetText);
    
    int matchFound = 0;

    while(fgets(line, 100, book_finder) != NULL) 
    {
        char *commaPos = strchr(line, ','); //take comma position
        
        if(commaPos != NULL) 
        {
            size_t length = commaPos - line; //take the length of that matched part
            
            if(length == targetLength && strncmp(line, targetText, targetLength) == 0) //if length and string match is provided they are same
            {
                matchFound = 1;
            } 
            
            else 
            {
                fputs(line, tempFile); //write that line to temporary file
                matchFound = 0;
            }
        } 
    }

    fclose(book_finder);
    fclose(tempFile);
    free(targetText);

    if(matchFound) 
    {
        remove("books.txt");
        rename("temp.txt", "books.txt");
        printf("The book with ISBN %s is deleted from books.txt\n", isbn);
    } 
    
    else 
    {
        remove("temp.txt");
        printf("The book could not been found\n");
    }
}


void updateBook(char* isbn, char* feature, char* value)
{
    int pub_year;

    if(!strcmp(feature, "publication year")) //if the to change feature is publication year, input is a number string. we should change it to integer because publicationYear variable is integer
    {
        pub_year = atoi(value);

        struct Book* current = head_book;
        
        //traverse the linked list and look for a match
        while(current != NULL) 
        {
            if(!strcmp(current->isbn, isbn))
            {
                current->publicationYear = pub_year; //if isbn is matched update the publication year
                printf("\npublication year of %s is been changed to %d in linked list succesfully", current->title, current->publicationYear);
                break;
            }

            current = current->next;
        }

        FILE* file = fopen("books.txt", "r");
        FILE* tempFile = fopen("temp.txt", "w");

        if(file == NULL || tempFile == NULL) 
        {
            printf("Files could not been opened!");
            return;
        }

        char line[100];

        while(fgets(line, sizeof(line), file) != NULL) 
        {
            char templine[100];
            strcpy(templine, line); // line'ı geçici bir diziye kopyala
            char* token = strtok(templine, ",");
            int foundMatch = 0;

            while (token != NULL) 
            {
                if(!strcmp(token, isbn)) 
                {
                    //if match is found, print it with its changed publication year
                    foundMatch = 1;
                    fprintf(tempFile, "%s,%s,%s,%d\n", token, strtok(NULL, ","), strtok(NULL, ","), pub_year);
                    break;
                }

                token = strtok(NULL, ",");
            }

            if(!foundMatch) 
            {
                //if no matches of isbn, print the line to temp.txt as it is 
                fputs(line, tempFile);
            }
        }

        fclose(file);
        fclose(tempFile);

        // Eski dosyayı sil
        remove("books.txt");

        // Geçici dosyayı eski dosyanın yerine taşı
        rename("temp.txt", "books.txt");
    }

   
    else if(!strcmp(feature, "title"))
    {
        struct Book* current = head_book;
        char old_title[50];
        
        //traverse the linked list and look for a match
        while(current != NULL) 
        {
            if(!strcmp(current->isbn, isbn))
            {
                strcpy(old_title, current->title);
                strcpy(current->title, value); //if isbn is matched update the title
                printf("\ntitle of %s is been changed to %s in linked list succesfully\n", old_title, current->title);
                break;
            }

            current = current->next;
        }

        FILE* file = fopen("books.txt", "r");
        FILE* tempFile = fopen("temp.txt", "w");

        if(file == NULL || tempFile == NULL) 
        {
            printf("Files could not been opened!");
            return;
        }

        char line[100];

        while(fgets(line, sizeof(line), file) != NULL) 
        {
            char templine[100];
            strcpy(templine, line); // line'ı geçici bir diziye kopyala
            char* token = strtok(templine, ",");
            int foundMatch = 0;

            while(token != NULL) 
            {
                if(!strcmp(token, isbn)) 
                {
                    //if match is found, print it with its changed title
                    foundMatch = 1;
                    
                    char* title = strtok(NULL, ",");
                    char* author = strtok(NULL, ",");
                    char* pub_year_str = strtok(NULL, ",");
                    int pub_year = atoi(pub_year_str);
                    fprintf(tempFile, "%s,%s,%s,%d\n", token, value, author, pub_year);
                    
                    break;
                }
                token = strtok(NULL, ",");
            }

            if(!foundMatch) 
            {
                //if no matches of isbn, print the line to temp.txt as it is 
                fputs(line, tempFile);
            }
            
        }

        fclose(file);
        fclose(tempFile);

        // Eski dosyayı sil
        remove("books.txt");

        // Geçici dosyayı eski dosyanın yerine taşı
        rename("temp.txt", "books.txt");
    }


    else if(!strcmp(feature, "author"))
    {
        struct Book* current = head_book;
        char old_author[50];
        
        //traverse the linked list and look for a match
        while(current != NULL) 
        {
            if(!strcmp(current->isbn, isbn))
            {
                strcpy(old_author, current->author);
                strcpy(current->author, value); //if isbn is matched update the author
                printf("\nauthor of %s is been changed to %s in linked list succesfully\n", old_author, current->author);
                break;
            }

            current = current->next;
        }

        FILE* file = fopen("books.txt", "r");
        FILE* tempFile = fopen("temp.txt", "w");

        if(file == NULL || tempFile == NULL) 
        {
            printf("Files could not been opened!");
            return;
        }

        char line[100];

        while(fgets(line, sizeof(line), file) != NULL) 
        {
            char templine[100];
            strcpy(templine, line); // line'ı geçici bir diziye kopyala
            char* token = strtok(templine, ",");
            int foundMatch = 0;

            while(token != NULL) 
            {
                if(!strcmp(token, isbn)) 
                {
                    //if match is found, print it with its changed title
                    foundMatch = 1;
                    
                    char* title = strtok(NULL, ",");
                    char* author = strtok(NULL, ",");
                    char* pub_year_str = strtok(NULL, ",");
                    int pub_year = atoi(pub_year_str);
                    fprintf(tempFile, "%s,%s,%s,%d\n", token, title, value, pub_year);
                    
                    break;
                }
                token = strtok(NULL, ",");
            }

            if(!foundMatch) 
            {
                //if no matches of isbn, print the line to temp.txt as it is 
                fputs(line, tempFile);
            }
            
        }

        fclose(file);
        fclose(tempFile);

        // Eski dosyayı sil
        remove("books.txt");

        // Geçici dosyayı eski dosyanın yerine taşı
        rename("temp.txt", "books.txt");
    }
}


void filterAndSortBooks(int filterChoice, char* filter, int sortChoice)
{
    FILE *reader;
    reader = fopen("books.txt", "r");
    
    char line[100];

    while(fgets(line, sizeof(line), reader) != NULL) 
    {
        char templine[100], pub_year_s[10];
        
        strcpy(templine, line); // line'ı geçici bir diziye kopyala
        
        char* isbn = strtok(templine, ",");
        char* title = strtok(NULL, ",");
        char* author = strtok(NULL, ",");
        char* pub_year_str = strtok(NULL, ",");
        int pub_year = atoi(pub_year_str);
        
        
        if((filterChoice == 0 && !strcmp(author, filter)) || (filterChoice == 1 && !strcmp(pub_year_str, filter))) //filtering by author and if match is found, take it into the linked list for filtered books
        {
            struct filteredBooks* new_node = (struct filteredBooks*)malloc(sizeof(struct filteredBooks));

            strcpy(new_node->isbn, isbn);
            strcpy(new_node->title, title);
            strcpy(new_node->author, author);
            new_node->publicationYear = pub_year;

            new_node->next = NULL;  

            if(filtered_head == NULL) //if ll is empty add new_node to head node
            {
                filtered_head = new_node;
            } 
            
            else //if ll is not empty add the new node to last node
            {
                struct filteredBooks* current = filtered_head;
                
                while(current->next != NULL) 
                {
                    current = current->next;
                }
                
                current->next = new_node;
            }

            printf("\n%s %s %s %d\n", new_node->isbn, new_node->title, new_node->author, new_node->publicationYear);
        }
        isbn = strtok(NULL, ",");
    
    }
    
    if(sortChoice == 0 || sortChoice == 1 || sortChoice == 2) //if sortChoice is by title or by author, sort the filtered books alphabetical
    {
        struct filteredBooks* current = filtered_head;
        struct filteredBooks* ptr1; //it traverses the list
        struct filteredBooks* lptr = NULL; //it holds the biggest elements position 

        int swapped;

        do
        {

            swapped = 0;
            ptr1 = filtered_head;

            while(ptr1->next != lptr)
            {
                if(sortChoice == 0) //if sort is by title,
                {
                    if(ptr1->title[0] > ptr1->title[0]) //compare titles' first letter and if one element is alphabetically greater than next of it
                    {
                        swap(ptr1, ptr1->next); //swap them
                        swapped = 1;
                    }
                }

                else if(sortChoice == 1) //if sort is by author,
                {
                    if(ptr1->author[0] > ptr1->author[0]) //compare titles' first letter and if one element is alphabetically greater than next of it
                    {
                        swap(ptr1, ptr1->next); //swap them
                        swapped = 1;
                    }
                }
                
                else if(sortChoice == 2) //if sort is by author,
                {
                    if(ptr1->publicationYear > ptr1->next->publicationYear) //compare publication years and if ones is greater than other
                    {
                        swap(ptr1, ptr1->next); //swap them
                        swapped = 1;
                    }
                }

                ptr1 = ptr1->next; //look for the next element
            
            }
            
            lptr = ptr1; //lptr points the biggests position to avoid swapping the biggest again
        
        }while(swapped);
    }
    
    struct filteredBooks* current = filtered_head; 
    
    printf("After filtering and sorting, results are:\n");

    while(current != NULL)
    {
        printf("%s\n", current->title);
        current = current->next;
    }

    fclose(reader);
}

void swap(struct filteredBooks* a, struct filteredBooks* b) 
{
    int tempi; //to hold publication year temporarily
    char tempc[50]; //to hold author and title temporarily
    
    //swap isbns
    strcpy(tempc, a->isbn);
    strcpy(a->isbn, b->isbn); 
    strcpy(b->isbn, tempc); 
    
    //swap titles
    strcpy(tempc, a->title);
    strcpy(a->title, b->title); 
    strcpy(b->title, tempc);
    
    //swap authors
    strcpy(tempc, a->author);
    strcpy(a->author, b->author); 
    strcpy(b->author, tempc);
    
    //swap publication years
    tempi = a->publicationYear; 
    a->publicationYear = b->publicationYear;
    b->publicationYear = tempi;
}


struct Book* reverseBookList(struct Book* head_book)
{
    struct Book* p;
    struct Book* q;

    if(head_book == NULL)
        return;

    p = head_book;
    q = p->next;

    if(q == NULL)
        return;

    q = reverseBookList(q);

    p->next->next = p;
    p->next = NULL;

    return q;
}


void searchBooks(int searchChoice, char* searchValue)
{
    FILE *reader = fopen("books.txt", "r");

    char line[100];

    if(searchChoice == 0) //if search choice is ISBN number look for match of it
    {
        while(fgets(line, sizeof(line), reader) != NULL) 
        {
            char templine[100];
            strcpy(templine, line); // line'ı geçici bir diziye kopyala
            char* token = strtok(templine, ",");
            char* title = strtok(NULL, ",");
            char* author = strtok(NULL, ",");
            char* pub_year_str = strtok(NULL, ",");
            int pub_year = atoi(pub_year_str);
  
            while(token != NULL) 
            {
                if(!strcmp(token, searchValue)) 
                {
                    //if match is found, print it
                    
                    printf("%s,%s,%s,%d\n", token, title, author, pub_year);
                    
                    break;
                }
                token = strtok(NULL, ",");
            }
        }
    }

    else if(searchChoice == 1) //if search choice is author look for match of it
    {
        while(fgets(line, sizeof(line), reader) != NULL) 
        {
            char templine[100];
            strcpy(templine, line); // line'ı geçici bir diziye kopyala
            char* token = strtok(templine, ",");
            char* title = strtok(NULL, ",");
            char* author = strtok(NULL, ",");
            char* pub_year_str = strtok(NULL, ",");
            int pub_year = atoi(pub_year_str);
            
            while(token != NULL) 
            {
                if(!strcmp(author, searchValue)) 
                {
                    //if match is found, print it 
                    
                    printf("%s,%s,%s,%d\n", token, title, author, pub_year);
                    
                    break;
                }
                token = strtok(NULL, ",");
            }
        }
    }
    
    else if(searchChoice == 2) //if search choice is title look for match of it
    {
        while(fgets(line, sizeof(line), reader) != NULL) 
        {
            char templine[100];
            strcpy(templine, line); // line'ı geçici bir diziye kopyala
            char* token = strtok(templine, ",");
            char* title = strtok(NULL, ",");
            char* author = strtok(NULL, ",");
            char* pub_year_str = strtok(NULL, ",");
            int pub_year = atoi(pub_year_str);
            
            while(token != NULL) 
            {
                if(!strcmp(title, searchValue)) 
                {
                    //if match is found, print it 
                    
                    printf("%s,%s,%s,%d\n", token, title, author, pub_year);
                    
                    break;
                }
                token = strtok(NULL, ",");
            }
        }
    }  

    fclose(reader);
}