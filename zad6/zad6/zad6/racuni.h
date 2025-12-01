#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "artikl.h"

typedef struct Date {
	int year;
	int month;
	int day;
}Date;

typedef struct Bill* Bill;

struct Bill {
	Date date;
	articleList* articles;
	Bill Next;
};

typedef struct billList {
	Bill First;
}billList;

billList* listForBills();
Bill billFromFile(const char* name);
int sortBill(billList* list, Bill fresh);
int freeBill(billList* list);

int findArticle(billList* list, const char* name, const char* from1, const char* till1, double* wPrice, int* wAmount); //w-whole
Articles priciest(billList* list);
Articles cheapest(billList* list);
int mostCommon(billList* list);
int rarest(billList* list);
double total(billList* list);
int printAllArticlesSorted(billList* list);
Articles maxConsumption(billList* list);
Articles minConsumption(billList* list);
double averagePrice(billList* list, const char* name);