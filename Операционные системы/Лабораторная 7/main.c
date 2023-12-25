#include <stdio.h>
#include "list.h"

int main() {
    addinlist("lol", 4);
    addinlist("kokakola", 3);
    addinlist("pepsi", 5);
    printf("Before sort: \n");
    printlist();
    printf("\n");
    serialize();
    // deserialize();
    sortmark(head);
    printf("After sort: \n");
    printlist();
    printf("\n");
    char searchSurname[15];
    char deleteSurname[15];
    printf("Enter the surname: ");
    scanf("%s", searchSurname);
    searchinlist(searchSurname);

    printf("\nEnter the surname for delete: ");
    scanf("%s", deleteSurname);
    deleteinList(deleteSurname);
    printf("After delete: \n");
    printlist();
    printf("\n");

    return 0;
}
