#include "racuni.h"

Date readDate(const char* file);
int compareDates(Date a, Date b);

billList* listForBills() {
	billList* p = malloc(sizeof(billList));
	p->First = NULL;
	return p;
}

Date readDate(const char*file) {
	Date d;
	sscanf(file, "%d-%d-%d", &d.year, &d.month, &d.day);
	return d;
}

int compareDates(Date a, Date b) {
	if (a.year != b.year) 
		return a.year - b.year;
	if (a.month != b.month)
		return a.month - b.month;
	return a.day - b.day;
}

Bill billFromFile(const char* name) {
	FILE* fp = fopen(name, "r");
	if (!fp)
		return NULL;
	Bill p = malloc(sizeof(struct Bill));
	char buffer[31];
	fscanf(fp, "%30s", buffer);
	p->date = readDate(buffer);
	p->articles = listFroArticles();
	p->Next = NULL;
	char sort[61];
	int amount;
	double price;
	while (fscanf(fp, "%60s %d %lf", sort, &amount, &price) == 3) {
		Articles x = newArticle(sort, amount, price);
		sortedArticle(p->articles, x);
	}
	return p;
}

int sortBill(billList* list, Bill fresh) {
	if (!list->First || compareDates(fresh->date, list->First->date) < 0) {
		fresh->Next = list->First;
		list->First = fresh;
		return 0;
	}
	Bill p = list->First;
	while (p->Next && compareDates(p->Next->date, fresh->date) < 0) {
		p = p->Next;
	}
	fresh->Next = p->Next;
	p->Next = fresh;
	return 0;
}

int freeBill(billList* list) {
	Bill p = list->First;
	Bill prev;
	while (p) {
		prev= p;
		p = p->Next;
		freeArticle(prev->articles);
		free(prev);
	}
	free(list);
	return 0;
}

int findArticle(billList* list, const char* name, const char* from1, const char* till1, double* wPrice, int* wAmount){ //w-whole 
	Date from = readDate(from1);
	Date till = readDate(till1);
	Bill p = list->First;
	Articles x;
	while (p) {
		if (compareDates(p->date, from) >= 0 && compareDates(p->date, till) <= 0) {
			x = p->articles->First;
			while (x) {
				if (strcmp(x->sort, name) == 0) {
					*wAmount += x->amount;
					*wPrice += x->amount * x->price;
				}
				x = x->Next;
			}
		}
		p = p->Next;
	}
	return 1;
}

Articles priciest(billList* list) {
	Bill p = list->First;
	Articles max = NULL;
	Articles x;
	while (p) {
		x = p->articles->First;
		while (x) {
			if (!max || x->price > max->price)
				max = x;
			x = x->Next;
		}
		p = p->Next;
	}
	return max;
}

Articles cheapest(billList* list) {
	Bill p = list->First;
	Articles min = NULL;
	Articles x;
	while (p) {
		x = p->articles->First;
		while (x) {
			if (!min || x->price < min->price)
				min = x;
			x = x->Next;
		}
		p = p->Next;
	}
	return min;
}

int mostCommon(billList* list) {
	Bill p = list->First;
	Bill q;
	char maxName[61] = "";
	int maxAmount = 0;
	Articles x,y;
	while (p) {
		x = p->articles->First;
		while (x) {
			int total = 0;
			q = list->First;
			while (q) {
				y = q->articles->First;
				while (y) {
					if (strcmp(y->sort, x->sort) == 0)
						total += y->amount;
					y = y->Next;
				}
				q = q->Next;
			}
			if (total > maxAmount) {
				maxAmount = total;
				strcpy(maxName, x->sort);
			}
			x = x->Next;
		}
		p = p->Next;
	}
	printf("Najcesci artikl je %s, akolicina je %d\n", maxName, maxAmount);
	return 0;
}
int rarest(billList* list) {
	Bill p = list->First;
	Bill q;
	char minName[61] = "";
	int minAmount = -1;
	Articles x, y;
	while (p) {
		x = p->articles->First;
		while (x) {
			int total = 0;
			q = list->First;
			while (q) {
				y = q->articles->First;
				while (y) {
					if (strcmp(y->sort, x->sort) == 0)
						total += y->amount;
					y = y->Next;
				}
				q = q->Next;
			}
			if (minAmount==-1||total<minAmount) {
				minAmount = total;
				strcpy(minName, x->sort);
			}
			x = x->Next;
		}
		p = p->Next;
	}
	printf("Najrjedi artikl je %s, akolicina je %d\n", minName, minAmount);
	return 0;
}
double total(billList* list) {
	double all = 0;
	Bill p = list->First;
	Articles x;
	while (p) {
		x = p->articles->First;
		while (x) {
			all += x->amount * x->price;
			x = x->Next;
		}
		p = p->Next;
	}
	return all;
}

int printAllArticlesSorted(billList* list) {
	articleList*global= listFroArticles();
	Bill p = list->First;
	Articles x,g,copy,temp;
	while (p) {
		x = p->articles->First;
		while (x) {
			g = global->First;
			while (g && strcmp(g->sort, x->sort) != 0)
				g = g->Next;
			if (!g) {
				copy = newArticle(x->sort, x->amount, x->price);
				sortedArticle(global, copy);
			}
			else
				g->amount += x->amount;
			x = x->Next;
		}
		p = p->Next;
	}
	printf("\n----SVI ARTIKLI SORTIRANI----\n");
	temp = global->First;
	while (temp) {
		printf(" %s, %d komada\n", temp->sort, temp->amount);
		temp = temp->Next;
	}
	freeArticle(global);
	return 0;
}

Articles maxConsumption(billList* list) {
	Bill p = list->First;
	Articles result = NULL;
	Articles x;
	double maxCons = -1;
	double earnings;
	while (p) {
		x = p->articles->First;
		while (x) {
			earnings = x->amount * x->price;
			if (earnings > maxCons) {
				maxCons = earnings;
				result = x;
			}
			x = x->Next;
		}
		p = p->Next;
	}
	return result;
}

Articles minConsumption(billList* list) {
	Bill p = list->First;
	Articles result = NULL;
	Articles x;
	double minCons = -1;
	double earnings;
	while (p) {
		x = p->articles->First;
		while (x) {
			earnings = x->amount * x->price;
			if (minCons == -1 || earnings < minCons) {
				minCons = earnings;
				result = x;
			}
			x = x->Next;
		}
		p = p->Next;
	}
	return result;
}

double averagePrice(billList* list, const char* name) {
	Bill p = list->First;
	int totalAmount = 0;
	double totalPrice = 0;
	Articles x;
	while (p) {
		x = p->articles->First;
		while (x) {
			if (strcmp(x->sort, name) == 0) {
				totalAmount += x->amount;
				totalPrice += x->amount * x->price;
			}
			x = x->Next;
		}
		p = p->Next;
	}
	if (totalAmount == 0)
		return 0;
	return totalPrice / totalAmount;
}