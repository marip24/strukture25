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

int findArticle(billList* list);
int priciest(billList* list);
int cheapest(billList* list);
int mostCommon(billList* list);
int rarest(billList* list);
int total(billList* list);
int printAllArticlesSorted(billList* list);
int maxConsumption(billList* list);
int minConsumption(billList* list);
int averagePrice(billList* list);