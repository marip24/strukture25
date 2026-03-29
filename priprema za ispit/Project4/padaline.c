/*Napisati program koji iz datoteke "gradovi.txt" èita podatke o ID i nazivu pojedinog grada.
Iz tih podataka se gradi vezana lista gradova. Nakon toga se iz datoteke "padaline.txt" èita ID
grada, datum (u formatu d. m. godina.) i kolièina padalina na taj datum. Od ovih podataka se 
gradi nova vezana lista koja sadrži naziv grada (preko ID se skuplja iz prve liste), datum i 
kolièinu padalina. Podatke sortirati po nazivu grada i datumu. Ispisati listu. (svi su datumi
u 1. i 2. mjesecu 2026. godine.) Unijeti neki datum i za taj datum pronaæi u kojem gradu je 
bilo najviše padalina. Ispisati ga. U izradi zadatka koristiti strukture: */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN (32)

struct _grad;
typedef struct _grad* GradP;
typedef struct _grad {
	int ID;
	char Naziv[MAX_NAME_LEN];
	GradP Next;
}Grad;

struct _date;
typedef struct _date {
	int day, month, year;
}Date;

struct _padaline;
typedef struct _padaline* PadalineP;
typedef struct _padaline {
	char grad[MAX_NAME_LEN];
	Date datum;
	float kolicina;
	PadalineP Next;
}Padaline;

GradP stvoriG(const char* fileG, GradP headG);
PadalineP stvoriP(const char* fileP, PadalineP headP, GradP headG);
PadalineP noviP(int id, Date d, float kol, GradP headG);
char* gradID(int id, GradP headG);
PadalineP sortP(PadalineP nov, PadalineP headP);
int ispisi(PadalineP head);
int compareDate(Date d1, Date d2);
int pronadiD(Date trazi, PadalineP headP);
int brisiG(GradP headG);
int brisiP(PadalineP headP);

int main() {
	GradP headG = NULL;
	PadalineP headP = NULL;
	const char* fileG = "gradovi.txt";
	const char* fileP = "padaline.txt";
	headG = stvoriG(fileG, headG);
	headP = stvoriP(fileP, headP, headG);
	ispisi(headP);
	Date trazi;
	printf("\nunesite neki datum DD MM YYYY: ");
	scanf("%d %d %d", &trazi.day, &trazi.month, &trazi.year);
	pronadiD(trazi, headP);
	brisiG(headG);
	brisiP(headP);
	return 0;
}

int brisiG(GradP headG) {
	GradP temp;
	while (headG) {
		temp = headG;
		headG = headG->Next;
		free(temp);
	}
	return 0;
}
int brisiP(PadalineP headP) {
	PadalineP temp;
	while (headP) {
		temp = headP;
		headP = headP->Next;
		free(temp);
	}
	return 0;
}

int pronadiD(Date trazi, PadalineP headP) {
	float maksi = -1;
	char gradT[50] = "";
	PadalineP temp = headP;
	while (temp) {
		if (compareDate(temp->datum,trazi)==0) {
			if (maksi < temp->kolicina) {
				maksi = temp->kolicina;
				strcpy(gradT, temp->grad);
			}
		}
		temp = temp->Next;
	}
	if (maksi < 0)
		printf("\nunijeli ste krivi datum!");
	else
		printf("\n tog datuma je palo najvise kise u %s i to %.2f", gradT, maksi);
	return 0;
}

PadalineP stvoriP(const char* fileP, PadalineP headP, GradP headG) {
	FILE* dat = fopen(fileP, "r");
	if (!dat) {
		printf("\ngreska pri otvaranju padalina");
		return NULL;
	}
	while (1) {
		int id;
		Date d;
		float kol;
		if (fscanf(dat, "%d %d. %d. %d. %f", &id, &d.day, &d.month, &d.year, &kol) != 5) {
			fclose(dat);
			break;
		}
		PadalineP nov = noviP(id, d, kol, headG);
		headP = sortP(nov, headP);
	}
	fclose(dat);
	return headP;
}

PadalineP sortP(PadalineP nov, PadalineP headP) {
	if (!headP || strcmp(nov->grad, headP->grad) < 0 || ((strcmp(nov->grad, headP->grad) == 0) && compareDate(nov->datum,headP->datum)<0)) {
		nov->Next = headP;
		return nov;
	}
	PadalineP temp = headP;
	while (temp->Next && (strcmp(nov->grad, temp->Next->grad) > 0 || ((strcmp(nov->grad, temp->Next->grad) == 0) && compareDate(nov->datum, temp->Next->datum) > 0)))
		temp = temp->Next;
	nov->Next = temp->Next;
	temp->Next = nov;
	return headP;
}

int compareDate(Date d1, Date d2) {
	if (d1.year != d2.year)
		return d1.year - d2.year;
	else if (d1.month != d2.month)
		return d1.month - d2.month;
	else
		return d1.day - d2.day;
}

PadalineP noviP(int id, Date d, float kol, GradP headG) {
	PadalineP nov = (PadalineP)malloc(sizeof(Padaline));
	if (!nov) {
		printf("\ngreska pri alokaciji");
		return NULL;
	}
	nov->datum = d;
	nov->kolicina = kol;
	nov->Next = NULL;
	const char *naziv;
	naziv = gradID(id, headG);
	strcpy(nov->grad, naziv);
	return nov;
}

char* gradID(int id,GradP headG) {
	while (headG) {
		if (headG->ID == id) {
			return headG->Naziv;
		}
		headG = headG->Next;
	}
	return NULL;
}

GradP stvoriG(const char* fileG, GradP headG) {
	FILE* fp = fopen(fileG, "r");
	if (!fp) {
		printf("\ngreska pri otvaranju gradova");
		return NULL;
	}
	while (1) {
		GradP nov = (GradP)malloc(sizeof(Grad));
		if (!nov) {
			printf("\ngreska pri alokaciji");
			return NULL;
		}
		if (fscanf(fp, "%d %s",&nov->ID,nov->Naziv) != 2) {
			free(nov);
			fclose(fp);
			break;
		}
		nov->Next = headG;
		headG = nov;
	}
	fclose(fp);
	return headG;
}

int ispisi(PadalineP head) {
	PadalineP temp = head;
	while (temp) {
		printf("\n %s %d. %d. %d. %.2f", temp->grad, temp->datum.day, temp->datum.month, temp->datum.year,temp->kolicina);
		temp = temp->Next;
	}
	return 0;
}
