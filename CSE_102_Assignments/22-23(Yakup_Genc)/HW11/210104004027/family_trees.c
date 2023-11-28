#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define MAX_FILE_NAME_LENGTH 100


typedef struct Person{
    char name[MAX_NAME_LENGTH];
    int age;
    struct Person* mother;
    struct Person* father;
}Person;

 
void menu(void);
void addPerson(Person** tree);
void removePerson(Person** tree);
void saveFamilyTreeToFile(const Person* tree, const char* fileName);
void savePersonToFile(const Person* person, FILE* file);
const Person* findYoungestGrandchild(const Person* person);
void freeFamilyTree(Person* person); 


int main()
{
    menu();
    return 0;
}


void menu(void)
{
    Person* familyTree = NULL;

    int sel;
    
    printf("*******************************\n\n");
    printf("Family Tree System Menu:\n");

    do{
       
        printf("1-Add Family Tree\n");
        printf("2-Remove Family Tree\n");
        printf("3-Load Family Tree\n");
        printf("4-Exit\n");
        scanf("%d", &sel);

        switch(sel)
        {
            case 1: 
                    printf("1-Add person\n");
                    printf("2-Save Family Tree\n");
                    printf("3-Return to Main Menu.\n"); 
                    printf("4-Exit");
                    scanf("%d", &sel);

                    switch(sel)
                    {
                        case 1: //add person

                                addPerson(&familyTree);

                                break;

                        case 2: //save family tree
                                char c;

                                printf("If you have not added any persons please first add them to build family tree before saving it.\n");
                                printf("Have you added person(s)?(y/n): ");
                                getchar();
                                scanf(" %c", &c);

                                if(c == 'y')
                                {
                                    char fileName[MAX_FILE_NAME_LENGTH];
                                    
                                    printf("Enter the name of the file: ");
                                    scanf("%s", fileName);

                                    saveFamilyTreeToFile(familyTree, fileName);
                                    freeFamilyTree(familyTree);
                                }

                                else if(c == 'n')
                                {
                                    menu();
                                }

                                break;

                        case 3: //return to main menu

                                break;

                        case 4: //exit

                                break;                        
                    }   

                   break;

            case 2:
                    printf("Enter,\n");
                    printf("1 for load a family from a file,\n");
                    printf("2 for add a person to a loaded family tree,\n"); 
                    printf("3 for remove a person from a loaded family tree,\n");
                    printf("4 for print a person's nuclear family,");
                    printf("5 for search  relatives  of  given  person.");
                    printf("6 for returning to main menu.\n");
                    scanf("%d", &sel);

                    switch(sel)
                    {
                        case 1: //load a family from a file

                                break;

                        case 2: //add a person to a loaded family tree

                                break;

                        case 3: //remove a person from a loaded family tree

                                break;

                        case 4: //print a person's nuclear family

                                break;

                        case 5: //search  relatives  of  given  person

                                break;

                        case 6:
                                menu();
                                break;                                        
                    }

                    break;       
        }
   
    }while(sel != 3);
}


// Function to add a person to the family tree
void addPerson(Person** tree) 
{
    Person* newPerson = (Person*)malloc(sizeof(Person));
    
    printf("Enter the name of the person: ");
    scanf("%s", newPerson->name);
    
    printf("Enter the age of the person: ");
    scanf("%d", &newPerson->age);
    
    // Set mother and father pointers
    newPerson->mother = NULL;
    newPerson->father = NULL;
    
    char motherName[MAX_NAME_LENGTH];
    char fatherName[MAX_NAME_LENGTH];
    
    printf("Enter the name of the mother: ");
    scanf("%s", motherName);
    
    printf("Enter the name of the father: ");
    scanf("%s", fatherName);
    
    Person* mother = NULL;
    Person* father = NULL;
    
    // Search for mother and father in the tree
    Person* currentNode = *tree;
    
    while(currentNode != NULL) 
    {
        if(strcmp(currentNode->name, motherName) == 0) 
        {
            mother = currentNode;
        }
        
        if(strcmp(currentNode->name, fatherName) == 0) 
        {
            father = currentNode;
        }
        
        if(mother != NULL && father != NULL) 
        {
            break;
        }
        
        currentNode = currentNode->father; //Traverse up the tree
    }
    
    // Add the newPerson to the tree
    if(mother == NULL && father == NULL) 
    {
        // The newPerson is the root of the tree 
        *tree = newPerson;
    } 
    
    else 
    {
        // Add the newPerson as a child to the mother and father
        if(mother != NULL) 
        {
            newPerson->mother = mother;
        }

        if(father != NULL) 
        {
            newPerson->father = father;
        }
    }
    
    printf("Person added to the family tree succesfully.\n");
    
    /*// Update the corresponding text file
    char fileName[MAX_FILE_NAME_LENGTH];
    snprintf(fileName, MAX_FILE_NAME_LENGTH, "family%d.txt", newPerson->age); // Use age as a unique identifier
    
    FILE* file = fopen(fileName, "a");
    
    if(file != NULL) 
    {
        fprintf(file, "Name: %s\n", newPerson->name);
        fprintf(file, "Age: %d\n", newPerson->age);
        fprintf(file, "Mother: %s\n", newPerson->mother != NULL ? newPerson->mother->name : "Unknown");
        fprintf(file, "Father: %s\n", newPerson->father != NULL ? newPerson->father->name : "Unknown");
        fclose(file);
    } 
    
    else 
    {
        printf("Failed to update the text file for the new person.\n");
    }*/
}


void saveFamilyTreeToFile(const Person* tree, const char* fileName) 
{
    FILE* file = fopen(fileName, "a");
   
    if(file != NULL) 
    {
        // En küçük torunu bul ve ondan başlayarak ağacı kaydet
        const Person* youngestGrandchild = findYoungestGrandchild(tree);
        savePersonToFile(youngestGrandchild, file);

        fclose(file);
        printf("Family tree saved to %s.\n", fileName);
    } 

    else 
    {
        printf("Failed to save the family tree to the file.\n");
    }
}


void savePersonToFile(const Person* person, FILE* file) 
{
    if (person == NULL) 
    {
        return;
    }

    fprintf(file, "Name: %s,", person->name);
    fprintf(file, "Age: %d,", person->age);
    fprintf(file, "Mother: %s,", person->mother == NULL ? "Unknown" : person->mother->name);
    fprintf(file, "Father: %s\n", person->father == NULL ? "Unknown" : person->father->name);
    
    // Save the mother
    savePersonToFile(person->mother, file);

    // Save the father
    savePersonToFile(person->father, file);
}


const Person* findYoungestGrandchild(const Person* person)
{
    // Eğer kişi yoksa veya hiç çocuğu yoksa, kişi kendisi en küçük torundur
    if (person == NULL || (person->mother == NULL && person->father == NULL))
    {
        return person;
    }

    // En küçük torunu aramak için önce anne tarafına bak
    const Person* youngestGrandchildMother = findYoungestGrandchild(person->mother);

    // En küçük torun anne tarafındaysa, onu döndür
    if (youngestGrandchildMother != NULL)
    {
        return youngestGrandchildMother;
    }

    // Anne tarafında en küçük torun yok, baba tarafına bak
    return findYoungestGrandchild(person->father);
}


void freeFamilyTree(Person* person) 
{
    if(person == NULL) 
    {
        return;
    }

    // Recursively free the memory for the person's mother and father
    freeFamilyTree(person->mother);
    freeFamilyTree(person->father);

    // Free the memory for the person
    free(person);
}
