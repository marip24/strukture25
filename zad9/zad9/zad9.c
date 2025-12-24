/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u èvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraæa
pokazivaè na korijen stabla.
b) Napisati funkciju replace koja æe svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat æe se u stablo na
slici Slika 2.
c) Prepraviti program na naèin da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira sluèajne brojeve u rasponu <10, 90>. Takoðer, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct tree* treePos;

struct tree {
	int value;
	treePos left;
	treePos right;
};

treePos insertTree(treePos, int);
int replace(treePos);
int inorder(treePos);
int inorderFile(treePos, FILE*);
treePos freeTree(treePos);


int main() {
	treePos root = NULL;
	int value,n,i;
	FILE* fp = NULL;
	fp = fopen("inorder.txt", "w");
	if (fp == NULL)
		return 0;
	int arr[] = { 2,5,7,8,11,1,4,2,3,7 };
	int size;
	size = sizeof(arr) / sizeof(arr[0]);
	for (i = 0; i < size; i++)
		root = insertTree(root, arr[i]);
	printf("\ninorder prije replace: ");
	inorder(root);
	fprintf(fp, "\ninorder prije replace: ");
	inorderFile(root, fp);

	replace(root);
	printf("\ninorder izad replace: ");
	inorder(root);
	fprintf(fp, "\ninorder izad replace: ");
	inorderFile(root, fp);
	root = freeTree(root);

	srand((unsigned int)time(NULL));
	n = 10 + rand() % 6;
	for (i = 0; i < n; i++) {
		value = 10 + rand() % 80;
		root = insertTree(root, value);
	}
	replace(root);
	printf("\ninorder random stabla: ");
	inorder(root);
	fprintf(fp, "\ninorder random stabla: ");
	inorderFile(root, fp);
	fclose(fp);
	root = freeTree(root);
	return 0;
}

treePos insertTree(treePos root, int value) {
	if (root == NULL) {
		root = (treePos)malloc(sizeof(struct tree));
		if (root == NULL)
			return NULL;
		root->value = value;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	if (value >= root->value)
		root->left = insertTree(root->left, value);
	else
		root->right = insertTree(root->right, value);
	return root;
}

int inorder(treePos root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->value);
		inorder(root->right);
	}
	return 0;
}

int replace(treePos root) {
	if (root == NULL)
		return 0;
	int old;
	old = root->value;
	root->value = replace(root->left) + replace(root->right);
	return old + root->value;
}

int inorderFile(treePos root, FILE* fp) {
	if (root != NULL) {
		inorderFile(root->left, fp);
		fprintf(fp, "%d ", root->value);
		inorderFile(root->right, fp);
	}
	return 0;
}

treePos freeTree(treePos root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
	return NULL;
}