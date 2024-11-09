#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "serialization.h"

int main()
{
    srand(time(0)); //seeding srand with time
    srand48(time(NULL)); //seeding srand48 with time (using that function to generate random double numbers)

    Node* head = NULL;

    fillLinkedList(&head);
    serializeLinkedList(head);
    
    Node* newhead = NULL;

    deserializeLinkedList(&newhead);

    freeLinkedList(&head);

    return 0;
}
