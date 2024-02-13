#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 100

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;

int menu(Position head);
int addPersonAtFrontOfTheList(Position P);
int addPersonAtTheEnd(Position P);
int printList(Position P);
Position findPerson(Position P);
Position FindBySurname(Position first, char* surname);
Position FindBefore(Position wantedPerson, Position head);
int DeleteAfter(char* surname, Position head);
int insertAfterPerson(Position P);
int insertBeforePerson(Position P);
int  sortedInput(Position P);

int main() {

    Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };

    menu(&head);

    return 0;
}

int menu(Position head) {

    char choice = '\0';
    Position resPerson = NULL;
    char surname[MAX_SIZE] = { 0 };

    while (1)
    {
        printf("\nZa dodati novi element na pocetak liste upisite: 1\n");
        printf("Za dodavanje novog elementa na kraj liste : 2\nZa ispis liste : 3\nZa pronalazenje elementa u listi po prezimenu : 4\n");
        printf("Za brisanje elementa iz liste : 5\n");
        printf("Za umetnuti novi element iza odredenog elementa : 6\n");
        printf("Za umetnuti novi element ispred odredenog elementa : 7\n");
        printf("Za sortirani unos(od manjeg prema vecem) : 8\n");
        printf("Za upis liste u datoteku : 9\nZa ispis liste iz datoteke upisite 'a'\n");
        printf("Za izlazak iz programa : 0\n");
        scanf("\n%c", &choice);
        switch (choice)
        {
        case '1':
            addPersonAtFrontOfTheList(head);
            break;
        case '2':
            addPersonAtTheEnd(head);
            break;
        case '3':
            printList(head->next);
            break;
        case '4':
            resPerson = findPerson(head->next);
            if (resPerson == NULL)
                printf("\nOsoba nije nadena u listi\n");
            else
                printf("\nOsoba po prezimenu %s je nadena na lokaciji %d\n", resPerson, resPerson->surname);
            break;
        case '5':
            printf("-------- Brisanje studenta po prezimenu. -------- \nUnesite prezime studenta kojeg zelite izbrisati iz liste: ");
            scanf(" %s", surname);
            DeleteAfter(surname, head);
            break;
        case '0':
            printf("\nKraj programa!\n");
            return 0;

        case '6':
            insertAfterPerson(head);
            break;
        case '7':
            insertBeforePerson(head);
            break;
        case '8':
            sortedInput(head);
            break;
        case '9':
            inputListToFIle(head->next);
            break;
        case 'a':
            inputListFromFile(head);
            break;
        default:
            printf("Unijeli ste nedozvoljeni broj! ");
            break;
        }
    }
    return 1;
}

int printList(Position P) {

    printf("\n------------\n");

    Position temp = P;

    if (P == NULL)
    {
        printf("Empty list!\n");
    }
    else {

        while (P != NULL) {
            printf("%s %s %d\n", P->name, P->surname, P->birthYear);
            P = P->next;
        }
    }

    printf("------------");

    return EXIT_SUCCESS;
}

int addPersonAtFrontOfTheList(Position P) {

    Position newPerson = NULL;

    newPerson = (Person*)malloc(sizeof(Person));
    newPerson->next = NULL;

    printf("\nUnesite ime, prezime i godinu rodenja nove osobe:\n");
    scanf("\n%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

    newPerson->next = P->next;
    P->next = newPerson;

    return EXIT_SUCCESS;
}

int addPersonAtTheEnd(Position P) {

    Position newPerson = NULL;

    newPerson = (Person*)malloc(sizeof(Person));

    printf("\nUnesite ime, prezime i godinu rodenja nove osobe: \n");
    scanf("\n%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

    while (P->next != NULL) {
        P = P->next;
    }

    newPerson->next = P->next;
    P->next = newPerson;

    return EXIT_SUCCESS;
}

Position findPerson(Position P) {

    char wantedPerson[MAX_SIZE];

    printf("Unesite prezime trazene osobe: ");
    scanf("%s", wantedPerson);

    while (strcmp(P->surname, wantedPerson) != 0)
    {
        P = P->next;
    }

    return P;
}

Position FindBySurname(Position first, char* surname) {

    Position temp = first;



    while (temp) {
        if (strcmp(temp->surname, surname) == 0) {
            return temp;
        }
        temp = temp->next;
    }



    return NULL;
}

Position FindBefore(Position wantedPerson, Position head) {


    Position temp = head;

    while (temp->next != NULL && temp->next != wantedPerson)
    {
        temp = temp->next;
    }



    if (temp->next == NULL)
        return NULL;
    else
        return temp;
}

int DeleteAfter(char* surname, Position head) {

    Position before = NULL;
    Position toDelete = NULL;

    toDelete = FindBySurname(head->next, surname);
    before = FindBefore(toDelete, head);
    if (!before) {

        printf("Greska u brisanju!\n");
        return -1;
    }

    toDelete = before->next;
    before->next = toDelete->next;
    free(toDelete);

    return EXIT_SUCCESS;
}

int insertAfterPerson(Position P) {

    Position newPerson = NULL;
    Person personBehind = { {0},{0},0 };

    newPerson = malloc(sizeof(Person));

    if (!newPerson) {
        printf("\nNeuspjesna alokacija memorije za newPerson\n");
        return EXIT_FAILURE;
    }
    printf("\nUnesite ime, prezime i godinu rodenja osobe iza koje zelite umetnuti novu osobu: \n");
    scanf("\n%s %s %d", personBehind.name, personBehind.surname, &personBehind.birthYear);

    printf("\nUnesite ime, prezime i godinu rodenja nove osobe: \n");
    scanf("\n%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

    while (P != NULL && strcmp(P->surname, personBehind.surname) != 0 && strcmp(P->name, personBehind.name) != 0 && P->birthYear != personBehind.birthYear) {
        P = P->next;
    }

    if (P == NULL)
        printf("\nmOsoba iza koje ste htjeli umetnuti novu osobu ne postoji u listi\n");

    else {
        newPerson->next = P->next;
        P->next = newPerson;
    }

    return EXIT_SUCCESS;
}

int insertBeforePerson(Position P) {
    Position newPerson = NULL;
    Person personInFront = { {0}, {0}, 0 };

    newPerson = malloc(sizeof(Person));

    if (!newPerson) {
        printf("\nNeuspjela alokacija memorije za newPerson\n");
        return EXIT_FAILURE;
    }

    printf("\nUnesite ime, prezime i godinu rodenja osobe ispred koje zelite umetnuti novu osobu: \n");
    scanf("\n%s %s %d", personInFront.name, personInFront.surname, &personInFront.birthYear);

    printf("\nUnesite ime, prezime i godinu rodenja nove osobe: \n");
    scanf("\n%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

    while (P != NULL && strcmp(P->next->surname, personInFront.surname) != 0 && strcmp(P->next->name, personInFront.name) != 0 && P->next->birthYear != personInFront.birthYear) {
        P = P->next;
    }

    if (P == NULL)
        printf("\nmOsoba ispred koje ste htjeli umetnuti novu osobu ne postoji u listi\n");

    else {
        newPerson->next = P->next;
        P->next = newPerson;
    }

    return EXIT_SUCCESS;
}

int sortedInput(Position P) {
    Position newPerson = NULL;

    newPerson = malloc(sizeof(Person));

    if (!newPerson) {
        printf("\nNeuspjela alokacija memorije za newPerson\n");
        return EXIT_FAILURE;
    }

    printf("\nUnesite ime, prezime i godinu rodenja nove osobe: \n");
    scanf("\n%s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

    while (P->next != NULL && strcmp(newPerson->surname, P->next->surname) > 0) {
        P = P->next;
    }

    newPerson->next = P->next;
    P->next = newPerson;

    return 0;
}
int inputListToFIle(Position P) {
    FILE* students = NULL;

    students = fopen("studenti.txt", "w");

    if (!students) {
        printf("\nFile students unsuccesfully opened!\n");
        return EXIT_FAILURE;
    }

    while (P != NULL) {
        fprintf(students, "%s %s %d\n", P->name, P->surname, P->birthYear);
        P = P->next;
    }

    fclose(students);

    return 0;
}

int inputListFromFile(Position P) {
    FILE* students = NULL;
    Position newPerson = NULL;

    students = fopen("studenti.txt", "r");

    if (!students) {
        printf("\nFile students unsuccesfully opened!\n");
        return EXIT_FAILURE;
    }

    while (!feof(students)) {

        newPerson = malloc(sizeof(Person));

        fscanf(students, "%s %s %d\n", newPerson->name, newPerson->surname, &newPerson->birthYear);

        newPerson->next = P->next;
        P->next = newPerson;

        P = P->next;
    }

    fclose(students);

    return 0;
}
