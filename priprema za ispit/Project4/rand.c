#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MIN1 50
#define MAX1 75
#define MIN2 60
#define MAX2 85

typedef struct lista {
	int clan;
	struct lista* next;
}Lista;

typedef struct vez {
	int broj;
	Lista* list;
	struct vez* next;
}Vez;

Vez* stvori(int i);
Lista* stvoriListu(int i);
int postoji(Lista* headL, int slucajan);
Vez* spoji(Vez* head, Vez* nov);
int ispis(Vez* head);
Vez* brisi(Vez* head);
Vez* brisiIsto(Vez* head);
Lista* brisanje(Lista* head, int isti);

int main() {
	srand((unsigned)time(NULL));
	Vez* head = NULL;
	for (int i = 1; i < 3; i++) {
		Vez* nov = stvori(i);
		if (!nov) {
			printf("\ngreska pri alokaciji");
			return -1;
		}
		head = spoji(head, nov);
	}
	ispis(head);
	printf("\n");
	head = brisiIsto(head);
	printf("\n");
	ispis(head);
	head = brisi(head);
	return 0;
}

Vez* brisiIsto(Vez* head) {
	Lista* jedna = head->list;
	Lista* druga = head->next->list;
	while (jedna) {
		int isti = jedna->clan;
		jedna = jedna->next;
		if (postoji(druga,isti)) {
			printf("\nisti clan %d u listama se brise",isti);
			head->list = brisanje(head->list, isti);
			head->next->list = brisanje(head->next->list, isti);
		}
	}
	return head;
}

Lista* brisanje(Lista* head, int isti) {
	Lista* temp = head;
	Lista* prev = NULL;
	while (temp) {
		if (temp->clan == isti) {
			if (prev == NULL) {
				head = temp->next;
				free(temp);
				return head;
			}
			else {
				prev->next= temp->next;
				free(temp);
				return head;
			}
		}
		prev = temp;
		temp = temp->next;
	}

	return head;
}

Vez* brisi(Vez* head) {
	Vez* temp;
	while (head) {
		Lista* curr = head->list;
		Lista* l;
		while (curr) {
			l = curr;
			curr = curr->next;
			free(l);
		}
		temp = head;
		head = head->next;
		free(temp);
	}
	return NULL;
}

int ispis(Vez* head) {
	Vez* temp = head;
	while (temp) {
		printf("\nclanovi %d liste su: ", temp->broj);
		Lista* l = temp->list;
		while (l) {
			printf(" %d", l->clan);
			l = l->next;
		}
		temp = temp->next;
	}
	return 0;
}

Vez* spoji(Vez* head, Vez* nov) {
	if (head == NULL) {
		nov->next = head;
		head = nov;
	}
	else {
		head->next = nov;
		nov->next = NULL;
	}
	return head;
}

Vez* stvori(int i) {
	Vez* nov = (Vez*)malloc(sizeof(Vez));
	if (!nov) {
		printf("\ngreska pri alokaciji");
		return NULL;
	}
	nov->broj = i;
	nov->next = NULL;
	nov->list = stvoriListu(i);
	return nov;
}

Lista* stvoriListu(int i) {
	Lista* headL = NULL;
	int ucitaj = 0;
	while (ucitaj < 20) {
		Lista* nov = (Lista*)malloc(sizeof(Lista));
		if (!nov) {
			printf("\ngreska pri alokaciji");
			return NULL;
		}
		int slucajan;
		if (i == 1)
			slucajan = rand() % (MAX1 - MIN1 + 1) + MIN1;
		else
			slucajan = rand() % (MAX2 - MIN2 + 1) + MIN2;
		if (!postoji(headL,slucajan)) {
			nov->clan = slucajan;
			nov->next = headL;
			headL = nov;
			++ucitaj;
		}
		else {
			free(nov);
		}
	}
	return headL;
}

int postoji(Lista* headL, int slucajan) {
	Lista* temp = headL;
	if (headL != NULL) {
		while (temp!=NULL) {
			if (temp->clan == slucajan)
				return 1;
			temp = temp->next;
		}
	}
	return 0;
}
