#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct _poly* Position;
typedef struct _poly {
	int coeff;
	int pow;
	Position next;
}Poly;

Poly* element(int coeff, int pow);
int sortedInsert(Poly* head, int coeff, int pow);
int readFile(Poly* head, const char* filename);
int printPoly(Poly* head);
Poly* add(Poly* head, Poly* p1, Poly* p2);
Poly* multiply(Poly* head, Poly* p1, Poly* p2);
int freeMemory(Poly* head);

int main() {

	Poly Head = { .coeff = 0,.pow = 0,.next = NULL };
	Poly firstP = { .coeff = 0,.pow = 0,.next = NULL };
	Poly secondP = { .coeff = 0,.pow = 0,.next = NULL };

	readFile(&firstP, "poly1.txt");
	readFile(&secondP, "poly2.txt");

	printf("\nprvi polinom je: ");
	printPoly(&firstP);
	printf("\ndrugi polinom je: ");
	printPoly(&secondP);

	add(&Head, &firstP, &secondP);
	printf("\nzbroj: ");
	printPoly(&Head);
	freeMemory(&Head);

	multiply(&Head, &firstP, &secondP);
	printf("\numnozak: ");
	printPoly(&Head);

	freeMemory(&firstP);
	freeMemory(&secondP);
	freeMemory(&Head);

	return 0;
}

Poly* element(int coeff, int pow) {
	Poly* newEl = (Poly*)malloc(sizeof(Poly));
	if (!newEl)
		return NULL;
	newEl->coeff = coeff;
	newEl->pow = pow;
	newEl->next = NULL;
	return newEl;
}

int sortedInsert(Poly* head, int coeff, int pow) {
	if (coeff == 0)
		return 0;
	Poly* newEl = element(coeff, pow);
	if (!newEl)
		return -1;
	Poly* prev = head;
	Poly* curr = prev->next;
	while (curr != NULL && curr->pow > pow) {
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL && curr->pow == pow) {
		curr->coeff += coeff;
		if (curr->coeff == 0) {
			prev->next = curr->next;
			free(curr);
		}
		free(newEl);
		return 0;
	}
	newEl->next = curr;
	prev->next = newEl;

	return 0;
}

int readFile(Poly* head, const char* filename) {
	Poly* curr = head;
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("\ngreska pri otvaranju datoteke %s", filename);
		return -1;
	}
	int coeff, pow;
	while (fscanf(fp, "%d %d", &coeff, &pow) == 2)
		sortedInsert(curr, coeff, pow);
	fclose(fp);
	return 0;
}

int printPoly(Poly* head) {
	Poly* p = head->next;
	while (p) {
		printf(" %dx^%d", p->coeff, p->pow);
		if (p->next && p->next->coeff > 0)
			printf(" + ");
		else if (p->next)
			printf(" ");
		p = p->next;
	}
	printf("\n");
	return 0;
}

int freeMemory(Poly* head) {
	Poly* temp = head->next;
	while (temp) {
		Poly* del = temp;
		temp = temp->next;
		free(del);
	}
	head->next = NULL;
	return 0;
}

Poly* add(Poly* head, Poly* p1, Poly* p2) {
	Poly* temp = head;
	Poly* a = p1->next;
	Poly* b = p2->next;
	while (a != NULL && b != NULL) {
		if (a->pow > b->pow) {
			sortedInsert(temp, a->coeff, a->pow);
			a = a->next;
		}
		else if (a->pow < b->pow) {
			sortedInsert(temp, b->coeff, b->pow);
			b = b->next;
		}
		else {
			int sumaCoeff = a->coeff + b->coeff;
			sortedInsert(temp, sumaCoeff, a->pow);
			a = a->next;
			b = b->next;
		}
	}
	while (a != NULL) {
		sortedInsert(temp, a->coeff, a->pow);
		a = a->next;
	}
	while (b != NULL) {
		sortedInsert(temp, b->coeff, b->pow);
		b = b->next;
	}
	return head;
}

Poly* multiply(Poly* head, Poly* p1, Poly* p2) {
	Poly* temp = head;
	for (Poly* a = p1->next; a; a = a->next) {
		for (Poly* b = p2->next; b; b = b->next)
			sortedInsert(temp, a->coeff * b->coeff, a->pow + b->pow);
	}
	return head;
}