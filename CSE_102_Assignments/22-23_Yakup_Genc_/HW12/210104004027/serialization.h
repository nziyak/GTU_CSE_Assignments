#ifndef _SERIALIZATION_H_
#define _SERIALIZATION_H_

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
}Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
}Asset4;


void fillLinkedList(struct  Node**  head); //fills the linked list with random values and prints it to the terminal
void serializeLinkedList(struct Node* head); //serializes the filled linked list to linkedlist.bin and prints it to check.txt to see if it is the same list with which is created in fillLinkedList()
void deserializeLinkedList(struct  Node**  head); //deserializes the ll from linkedlist.bin and prints that to terminal to check
char* generateRandomString(int length); //generates random string from a pre-defined constant character set
void freeLinkedList(struct Node** head); //frees all the linked list


#endif /* _SERIALIZATION_H_ */