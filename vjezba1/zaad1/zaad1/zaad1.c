#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#define maxbodovi 120 

typedef struct { 
	char ime[50]; 
	char prezime[50]; 
	int bodovi;
}stud;

int prebroji(const char*); 
int ucitavanje(const char*, stud*, int); 
void ispis(stud*, int); 
int main() { 
	const char* zadatak1 = "zadatak1.txt"; 
	int brstudenata = prebroji(zadatak1);
	if (brstudenata <= 0) {
		printf("\nGreska pri citanju datoteke, nema studenata.\n");
		return 1;
	}
	stud* studenti = (stud*)malloc(brstudenata * sizeof(stud)); 
	if (!studenti) { 
		printf("\ngreska pri alokaciji memorije."); 
		return 1; 
	} 
	if (ucitavanje(zadatak1, studenti, brstudenata) != 0) {
		free(studenti);
		return 1;
	} 
	ispis(studenti, brstudenata); 
	free(studenti);
	return 0;
}
int prebroji(const char* zadatak1) {
	FILE* dat = fopen(zadatak1, "r"); 
	if (!dat) { 
		printf("greska pri otvaranju datoteke\n"); 
		return -1;
	} 
	int broj = 0; 
	char buffer[1024]; 
	while (fgets(buffer, sizeof(buffer), dat)) 
		broj++; 
	fclose(dat); 
	return broj; 
}

int ucitavanje(const char* zadatak1, stud* studenti, int broj) { 
	FILE* dat = fopen(zadatak1, "r"); 
	if (!dat) { 
		printf("greska pri otvaranju datoteke\n"); 
		return 1;
	}
	int i; 
	for (i = 0; i < broj; i++) { 
		if (fscanf(dat, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi) != 3) { 
			printf("greska pri ucitavanju retka %d\n", i + 1); 
			fclose(dat); 
			return 1; 
		} 
	} 
	fclose(dat); 
	return 0; 
}
void ispis(stud* studenti, int broj) { 
	int i; 
	for (i = 0; i < broj; i++) { 
		double relativni = (double)studenti[i].bodovi / maxbodovi * 100; 
		printf("\nime: %s\nprezime: %s\nbodovi: %d\n relativni bodovi: %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni); 
	} 
}