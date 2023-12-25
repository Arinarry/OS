#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct List *head = NULL;
struct List *tail = NULL;

void addinlist(char surname[], double mark) {
    struct List *newNode = (struct List*)malloc(sizeof(struct List));
    strcpy(newNode->surname, surname);
    newNode->mark = mark;
    newNode->next = NULL;
    
    if (head == NULL) {
        head = newNode;
        tail = newNode;   
    } 
    else {
        tail->next = newNode;
        tail = tail->next;
    }
}

void printlist() {
    struct List *current = head;

    while (current != NULL) {
        printf("Surname: %s\n", current->surname);
        printf("Mark: %.2lf\n", current->mark);
        current = current->next;
    }
}

void serialize() {
    FILE* file = fopen("file.bin","wb");
    struct List *current = head;

    while (current != NULL) {
        fwrite(current->surname, sizeof(current->surname), 1, file);
        fwrite(&(current->mark), sizeof(current->mark), 1, file);
        current = current->next;
    } 
    fclose(file);
}

void deserialize() {
    FILE* file = fopen("file.bin","rb");

    if (file == NULL) {
        return;
    }
    char surname[15];
    double mark;

    while (fread(surname, sizeof(surname),1,file) && fread(&(mark),sizeof(mark),1,file)) 
	{
        addinlist(surname, mark);
    }
    fclose(file);
}

void searchinlist(char surname[]) {
    struct List *current = head;
    int found = 0;
    
    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            printf("Surname: %s\n", current->surname);
            printf("Mark: %.2lf\n", current->mark);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("The surname %s was not found \n", surname);
    }
}

void deleteinList(char surname[]) {
    struct List *current = head;
    struct List *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            if (prev == NULL) {
                head = head->next;
                free(current);
                return;
            }
            else {
                prev->next = current->next;
                if (current == tail) {
                    tail = prev;
                }
                free(current);
                return;
            }
        }
        prev = current;
        current = current->next;
    }
}

void sortmark(struct List *start) {
    int swap;
    struct List *ptr1;
    struct List *lptr = NULL;
    
    if (start == NULL)
        return;
    do {
        swap = 0;
        ptr1 = start;
        while (ptr1->next != lptr) {
            if (ptr1->mark > ptr1->next->mark) {
                double tempmark = ptr1->mark;
                ptr1->mark = ptr1->next->mark;
                ptr1->next->mark = tempmark;
                
                char tempsurname[15];
                strcpy(tempsurname, ptr1->surname);
                strcpy(ptr1->surname, ptr1->next->surname);
                strcpy(ptr1->next->surname, tempsurname);

                swap = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swap);
}

