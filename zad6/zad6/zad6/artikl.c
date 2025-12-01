#include "artikl.h"

articleList* listFroArticles() {
	articleList* list = malloc(sizeof(articleList));
	list->First = NULL;
	return list;
}

Articles newArticle(const char* sort, int amount, double price) {
	Articles x = malloc(sizeof(struct Articles));
	strcpy(x->sort, sort);
	x->amount=amount;
	x->price = price;
	x->Next = NULL;
	return x;
}

int sortedArticle(articleList* list, Articles fresh) {
	if (!list->First || strcmp(fresh->sort, list->First->sort) < 0) {
		fresh->Next = list->First;
		list->First = fresh;
		return 0;
	}
	Articles p = list->First;
	while (p->Next && strcmp(p->Next->sort, fresh->sort) < 0) {
		p = p->Next;
	}
	fresh->Next = p->Next;
	p->Next = fresh;
	return 0;
}

int freeArticle(articleList* list) {
	Articles p = list->First;
	while (p) {
		Articles temp = p;
		p = p->Next;
		free(temp);
	}
	free(list);
	return 0;
}