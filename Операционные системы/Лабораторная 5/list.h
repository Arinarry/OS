#ifndef LIST_H
#define LIST_H

struct List {
    struct List *next;
    char surname[15];
    double mark;
};

extern struct List *head;
extern struct List *tail;

void addinlist(char surname[], double mark);
void printlist();
void serialize();
void deserialize();
void searchinlist(char surname[]);
void deleteinList(char surname[]);
void sortmark(struct List *start);

#endif
