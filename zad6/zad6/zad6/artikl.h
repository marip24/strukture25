#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Articles* Articles;

struct Articles {
	char sort[61];
	int amount;
	double price;
	struct Articles* Next;
};

typedef struct articleList {
	Articles First;
}articleList;

articleList* listFroArticles();
Articles newArticle(const char* sort, int amount, double price);
int sortedArticle(articleList* list, Articles fresh);
int freeArticle(articleList* list);