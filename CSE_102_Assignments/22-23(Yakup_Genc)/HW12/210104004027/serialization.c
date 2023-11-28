#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "serialization.h"


void fillLinkedList(struct  Node**  head)
{
    int assetType, assetNum; // type of asset that will be filled into linked list, number of assets of that asset type
    //FILE *writertxt = fopen("check.txt", "w");
    assetNum = rand() % 11 + 10; //generating number of assets 10-20
   
    printf("Generated Linked List:\n\n");
   
    for(int i = 0; i < assetNum; i++)
    {
        assetType = rand() % 4 + 1; //there are four asset types

        switch(assetType)
        {
            case 1:
                    Asset1* newAsset1 = (Asset1*)malloc(sizeof(Asset1)); //allocating memory for new asset
                    
                    strcpy(newAsset1->type, "Asset1"); //assigning the type of the asset to type string
                    printf("%s\n", newAsset1->type);
                    
                    newAsset1->ivals[0] = rand() % 30; //generating the int value of new asset1 randomly
                    printf("ivals[0]: %d\n", newAsset1->ivals[0]);

                    newAsset1->svals[0] = drand48(); //generating the double value of new asset1 randomly
                    printf("svals[0]: %lf\n\n", newAsset1->svals[0]);
                
                    if((*head) == NULL) //if head is NULL, add the new node to head of the list 
                    {
                        (*head) = (Node*)malloc(sizeof(Node)); //allocate memory for head
                        (*head)->data = newAsset1; //assign new asset1 to head
                        (*head)->next = NULL; //next of that node is NULL
                    }

                    else //if head is not NULL, add the new node to the end of the list
                    {
                        Node* current = (*head);

                        while(current->next != NULL) //traverse the list
                        {
                            current = current->next;
                        }

                        Node* newNode = (Node*)malloc(sizeof(Node)); //allocate memory for new node

                        newNode->data = newAsset1; //assign the newAsset to new nodes data
                        newNode->next = NULL; 

                        current->next = newNode; //add this new node to end of the list
                    }

                    break;

            case 2: //little differences with case 1
                    
                    Asset2* newAsset2 = (Asset2*)malloc(sizeof(Asset2));
                    
                    strcpy(newAsset2->type, "Asset2"); //generating a string value randomly and assigning it to string of new asset1
                    printf("%s\n", newAsset2->type);

                    //there are two int and double values in asset2 despite asset1 has one from each of them
                    newAsset2->ivals[0] = rand() % 30;
                    newAsset2->ivals[1] = rand() % 30;
                    printf("ivals[0]: %d\n", newAsset2->ivals[0]);
                    printf("ivals[1]: %d\n", newAsset2->ivals[1]);

                    newAsset2->svals[0] = drand48();
                    newAsset2->svals[1] = drand48(); 
                    printf("svals[0]: %lf\n", newAsset2->svals[0]);
                    printf("svals[1]: %lf\n\n", newAsset2->svals[1]);
                
                    //adding to the list part is exactly same
                    if((*head) == NULL)
                    {
                        (*head) = (Node*)malloc(sizeof(Node));
                        (*head)->data = newAsset2;
                        (*head)->next = NULL;
                    }

                    else
                    {
                        Node* current = (*head);

                        while(current->next != NULL)
                        {
                            current = current->next;
                        }

                        Node* newNode = (Node*)malloc(sizeof(Node));

                        newNode->data = newAsset2;
                        newNode->next = NULL;

                        current->next = newNode;
                    }

                    break;

            case 3:
                    Asset3* newAsset3 = (Asset3*)malloc(sizeof(Asset3));
                    
                    strcpy(newAsset3->type, "Asset3"); //generating a string value randomly and assigning it to string of new asset1
                    printf("%s\n", newAsset3->type);

                    //there are two string values in asset3 
                    strcpy(newAsset3->string1, generateRandomString(49)); //creating the strings 49 characters part randomly 
                    printf("string1: %s\n", newAsset3->string1);
                
                    strcpy(newAsset3->string2, generateRandomString(49)); //creating the strings 49 characters part randomly 
                    printf("string2: %s\n\n", newAsset3->string2);

                    //adding to the list part is exactly same
                    if((*head) == NULL)
                    {
                        (*head) = (Node*)malloc(sizeof(Node));
                        (*head)->data = newAsset3;
                        (*head)->next = NULL;
                    }

                    else
                    {
                        Node* current = (*head);

                        while(current->next != NULL)
                        {
                            current = current->next;
                        }

                        Node* newNode = (Node*)malloc(sizeof(Node));

                        newNode->data = newAsset3;
                        newNode->next = NULL;

                        current->next = newNode;
                    }
                   
                    break;

            case 4: 
                    Asset4* newAsset4 = (Asset4*)malloc(sizeof(Asset4));
                    
                    strcpy(newAsset4->type, "Asset4"); //generating a string value randomly and assigning it to string of new asset1
                    printf("%s\n", newAsset4->type);

                    //there are two double and one float values in asset4
                    newAsset4->value1 = drand48();
                    printf("value1: %lf\n", newAsset4->value1);
                    
                    newAsset4->value2 = drand48();
                    printf("value2: %f\n", newAsset4->value2);
                    
                    newAsset4->value3 = drand48();
                    printf("value3: %lf\n\n", newAsset4->value3);

                    //adding to the list part is exactly same
                    if((*head) == NULL)
                    {
                        (*head) = (Node*)malloc(sizeof(Node));
                        (*head)->data = newAsset4;
                        (*head)->next = NULL;
                    }

                    else
                    {
                        Node* current = (*head);

                        while(current->next != NULL)
                        {
                            current = current->next;
                        }

                        Node* newNode = (Node*)malloc(sizeof(Node));

                        newNode->data = newAsset4;
                        newNode->next = NULL;

                        current->next = newNode;
                    }
        }
    }
    //fclose(writertxt);
    printf("\n-------------------------------------------------\n");    
}


void serializeLinkedList(struct Node* head)
{
    FILE* writer = fopen("linkedlist.bin", "wb");
    FILE* writertxt = fopen("check.txt", "w");

    if(writer == NULL)
    {
        printf("The file could not been opened for serialization.");

        return;
    }

    Node* current = head;

    while(current != NULL)
    {
        if(strcmp(((Asset1*)current->data)->type, "Asset1") == 0)
        {
            fwrite(current->data, sizeof(Asset1), 1, writer);
            fprintf(writertxt, "%s\n", ((Asset1*)current->data)->type);
            fprintf(writertxt, "%d\n", ((Asset1*)current->data)->ivals[0]);
            fprintf(writertxt, "%lf\n\n", ((Asset1*)current->data)->svals[0]);
        }
        
        else if(strcmp(((Asset2*)current->data)->type, "Asset2") == 0)
        {
            fwrite(current->data, sizeof(Asset2), 1, writer);
            fprintf(writertxt, "%s\n", ((Asset2*)current->data)->type);
            fprintf(writertxt, "%d\n", ((Asset2*)current->data)->ivals[0]);
            fprintf(writertxt, "%d\n", ((Asset2*)current->data)->ivals[1]);
            fprintf(writertxt, "%lf\n", ((Asset2*)current->data)->svals[0]);
            fprintf(writertxt, "%lf\n\n", ((Asset2*)current->data)->svals[1]);
        }

        else if(strcmp(((Asset3*)current->data)->type, "Asset3") == 0)
        {
            fwrite(current->data, sizeof(Asset3), 1, writer);
            fprintf(writertxt, "%s\n", ((Asset3*)current->data)->type);
            fprintf(writertxt, "%s\n", ((Asset3*)current->data)->string1);
            fprintf(writertxt, "%s\n\n", ((Asset3*)current->data)->string2);
        }

        else if(strcmp(((Asset4*)current->data)->type, "Asset4") == 0)
        {
            fwrite(current->data, sizeof(Asset4), 1, writer);
            fprintf(writertxt, "%s\n", ((Asset4*)current->data)->type);
            fprintf(writertxt, "%lf\n", ((Asset4*)current->data)->value1);
            fprintf(writertxt, "%f\n", ((Asset4*)current->data)->value2);
            fprintf(writertxt, "%lf\n\n", ((Asset4*)current->data)->value3);
        }

        current = current->next;
    }

    fclose(writer);
    fclose(writertxt);
}


void deserializeLinkedList(struct  Node**  head)
{
    FILE* reader;
    Asset1* asset1Data; //four type of data pointers to use according to type of the read asset
    Asset2* asset2Data;
    Asset3* asset3Data;
    Asset4* asset4Data;
    char currentType[20]; //temporary string to hold current type of the read asset

    reader = fopen("linkedlist.bin", "rb");

    if(reader == NULL)
    {
        printf("The file could not been opened for deserialization.");

        return;
    }

    printf("\nReaded and reconstructed linked list:\n\n");

    while(fread(currentType, sizeof(char), 20, reader)) 
    {
        //printf("%s", currentType);
        
        fseek(reader, -20, SEEK_CUR); //after reading the type go back 20 characters to read whole current asset

        if(strcmp(currentType, "Asset1") == 0) //if type of the current asset is Asset1,
        {
            asset1Data = malloc(sizeof(Asset1)); //create a memory which has size Asset1 then asset1Data points it
            
            fread(asset1Data, sizeof(Asset1), 1, reader); //reading the Asset1 data from the file to memory pointed by asset1Data
            
            //add this read asset to the linked list
            if((*head) == NULL) //if head is null create memory for head and add the new datas to head
            {
                *head = malloc(sizeof(Node));
                (*head)->data = asset1Data;
                (*head)->next = NULL;
            }
            
            else //if not add to the end of the list
            {
                Node* newNode;
                Node* current = (*head);

                newNode = malloc(sizeof(Node));

                newNode->data = asset1Data;
                newNode->next = NULL;

                while(current->next != NULL)
                {
                    current = current->next;
                }

                current->next = newNode;
            }

            printf("%s\n", asset1Data->type);
            printf("ivals[0]: %d\n", asset1Data->ivals[0]);
            printf("svals[0]: %lf\n\n", asset1Data->svals[0]);
        }
        
        //doing same stuff for other types
        else if(strcmp(currentType, "Asset2") == 0) 
        {
            asset2Data = malloc(sizeof(Asset2));

            fread(asset2Data, sizeof(Asset2), 1, reader); //reading the Asset2 data from the file
            
            if((*head) == NULL) //add this read asset to the linked list
            {
                (*head) = malloc(sizeof(Node));
                (*head)->data = asset2Data;
                (*head)->next = NULL;
            }
            
            else
            {
                Node* newNode;
                Node* current = (*head);

                newNode = malloc(sizeof(Node));

                newNode->data = asset2Data;
                newNode->next = NULL;

                while(current->next != NULL)
                {
                    current = current->next;
                }

                current->next = newNode;
            }

            printf("%s\n", asset2Data->type);
            printf("ivals[0]: %d\n", asset2Data->ivals[0]);
            printf("ivals[1]: %d\n", asset2Data->ivals[1]);
            printf("svals[0]: %lf\n", asset2Data->svals[0]);
            printf("svals[1]: %lf\n\n", asset2Data->svals[1]);
        }
        
        else if(strcmp(currentType, "Asset3") == 0) 
        {
            asset3Data = malloc(sizeof(Asset3));

            fread(asset3Data, sizeof(Asset3), 1, reader); //reading the Asset3 data from the file
            
            if((*head) == NULL) //add this read asset to the linked list
            {
                (*head) = malloc(sizeof(Node));
                (*head)->data = asset3Data;
                (*head)->next = NULL;
            }
            
            else
            {
                Node* newNode;
                Node* current = (*head);

                newNode = malloc(sizeof(Node));

                newNode->data = asset3Data;
                newNode->next = NULL;

                while(current->next != NULL)
                {
                    current = current->next;
                }

                current->next = newNode;
            }

            printf("%s\n", asset3Data->type);
            printf("string1: %s\n", asset3Data->string1);
            printf("string2: %s\n\n", asset3Data->string2);
        }
        
        else if(strcmp(currentType, "Asset4") == 0) 
        {
            asset4Data = malloc(sizeof(Asset4));

            fread(asset4Data, sizeof(Asset4), 1, reader); //reading the Asset4 data from the file
            
            if((*head) == NULL) //add this read asset to the linked list
            {
                (*head) = malloc(sizeof(Node));
                (*head)->data = asset4Data;
                (*head)->next = NULL;
            }
            
            else
            {
                Node* newNode;
                Node* current = (*head);

                newNode = malloc(sizeof(Node));

                newNode->data = asset4Data;
                newNode->next = NULL;

                while(current->next != NULL)
                {
                    current = current->next;
                }

                current->next = newNode;
            }

            printf("%s\n", asset4Data->type);
            printf("value1: %lf\n", asset4Data->value1);
            printf("value2: %f\n", asset4Data->value2);
            printf("value3: %lf\n\n", asset4Data->value3);
        }
    }

    fclose(reader);
}


char* generateRandomString(int length) 
{
    char* randomString = (char*)malloc((length + 1) * sizeof(char));

    static const char charset[] = "abcdefghijklmnopqrst";
    
    int charsetLength = sizeof(charset) - 1;

    for(int i = 0; i < length; i++) 
    {
        int index = rand() % charsetLength;
        randomString[i] = charset[index];
    }

    randomString[length] = '\0';

    return randomString;
}


void freeLinkedList(struct Node** head)
{
    Node* current = *head;
    Node* next;

    while(current != NULL)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    *head = NULL;
}