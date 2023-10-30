// 2.zadatak.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX 100
#define EXIT_SUCCESS 0
#define SUCCESS 0
#define ERROR_ALLOC -4
#define NOT_FOUND -2
#define PERSON_NOT_FOUND -1
#define EMPTY_LIST -3
typedef struct Osoba* Pozicija;
typedef struct Osoba
{
	char ime[MAX];
	char prezime[MAX];
	int godinarodenja;
	Pozicija next;
}Osoba;
typedef struct Osoba Osoba;
Pozicija StvoriOsobu();
int UnosPrvoga(Pozicija P);
int Ispis(Pozicija P);
int IspisOsobe(Pozicija P);
int UnosNaKraj(Pozicija P);
Pozicija NadiZadnjeg(Pozicija P);
int NadiOsobu(Pozicija P);
char* upisiPrezime();
int izbrisiOsobu(Pozicija P);
Menu(Pozicija P);
int main()

{
	Osoba head = { 
		.next = NULL,
		.ime = {0},
		.prezime = {0}, 
		.godinarodenja = 0 
	};
	Menu(&head);
	return EXIT_SUCCESS;
	

}
Pozicija StvoriOsobu() {
	Pozicija osoba = NULL;
	char ime[MAX] = { 0 };
	char prezime[MAX] = { 0 };

	int godinarodenja = 0;
	osoba = (Pozicija)malloc(sizeof(Osoba));
	if (osoba == NULL)
	{

		return ERROR_ALLOC;
	}
	printf("Unesi ime: ");
	scanf(" %s", osoba->ime);

	printf("Unesi prezime: ");
	scanf(" %s", osoba->prezime);

	printf("Unesi godinu rodenja: ");
	scanf(" %d", osoba->godinarodenja);

	return osoba;
}
int UnosPrvoga(Pozicija P)
{

	Pozicija novaOsoba;

	printf("\nUnos na pocetak:\n");
	novaOsoba = StvoriOsobu();
	if (novaOsoba !=NULL) {

		novaOsoba->next = P->next;
		P->next = novaOsoba;
	}

	return EXIT_SUCCESS;

}
int Ispis(Pozicija P)
{

	Pozicija trenutno = P;
	if (P == NULL) {
		printf("Lista je prazna.\n");

	}
	while (trenutno != NULL)
	{
		IspisOsobe(trenutno);
		trenutno = trenutno->next;
	}

	return SUCCESS;
}
int IspisOsobe(Pozicija P) {
	printf("Ime: %s\t Prezime: %s\t Godina Rodenja: %d\t\n", P->ime, P->prezime, P->godinarodenja);
	return SUCCESS;
}
int UnosNaKraj(Pozicija P) {
	Pozicija novaOsoba = NULL;
	Pozicija zadnji = NULL;

	novaOsoba = StvoriOsobu();

	if (novaOsoba != NULL) {
		zadnji = NadiZadnjeg(P);
		novaOsoba->next = zadnji->next;
		zadnji->next = novaOsoba;
	}

	return SUCCESS;
}
Pozicija NadiZadnjeg(Pozicija P) {
	Pozicija trenutno = P;

	while (trenutno->next) {
		trenutno= trenutno->next;
	}

	return trenutno;
}
int NadiOsobu(Pozicija P)
{
	Pozicija trenutno = P;
	char Prezime[MAX] = { 0 };
	if (P == NULL)
	{
		printf("Lista je prazna\n");
		return NOT_FOUND;

	}
	strcpy(Prezime, upisiPrezime());

	do {

		if (strcmp(Prezime, trenutno->prezime) == 0)
		{

			return trenutno;
		}
		else
		{
			trenutno = trenutno->next;

		}
	} while (trenutno != NULL);
		return NOT_FOUND;

}
char* upisiPrezime() {
	char prezime[MAX] = { 0 };
	printf("Upisite prezime osobe: \n");
	scanf("%s", prezime);

	return prezime;
}
int izbrisiOsobu(Pozicija P)
{
	Pozicija trenutno = P;
	char prezime[MAX] = { 0 };

	if (P->next != NULL)
	{

		Pozicija prethodni = NULL;

		while (trenutno->next != NULL && (strcmp(prezime, trenutno->prezime) != 0))
		{

			prethodni = trenutno;
			trenutno = trenutno->next;
		}
		if (prethodni != NULL && prethodni->next != NULL && strcmp(trenutno->prezime, prezime) == 0) {
			IspisOsobe(trenutno);
			prethodni->next = trenutno->next;
			free(trenutno);
		}
		else
		{
			return PERSON_NOT_FOUND;
		}
		return EMPTY_LIST;
	}



}
int Menu(Pozicija Head) {
	char choice = "\0";
	while (1) {
		printf("IZBORNIK:\n");
		printf("Enter: A(Dodaj na pocetak)\n\tE(Dodaj na kraj)\n\tF(Nadi osobu)\n\tD(izbrisi)\n\tP(ispisi)\n\tX(izadi iz programa)\n");
		scanf(" %c", &choice);
		switch (choice) {
		case 'A':
		case 'a':
			UnosPrvoga(Head);
			continue;
		case 'E':
		case 'e':
			UnosNaKraj(Head);
			continue;
		case 'F':
		case 'f':
			NadiOsobu(Head->next);
		case 'D':
		case 'd':
			switch (IzbrisiOsobu(Head)) {
			case SUCCESS:
				printf("Izbrisan!\n");
				break;
			case EMPTY_LIST:
				printf("Lista je prazna!\n");
				break;
			case PERSON_NOT_FOUND:
				printf("Osoba ne postoji!\n");
				break;
			}
			continue;
		case 'P':
		case 'p':
			Ispis(Head->next);
			continue;

		case 'X':
		case 'x':
			break;
		default:
			printf("Krivo slovo!\n");
			continue;
		}
		break;
	}
}
