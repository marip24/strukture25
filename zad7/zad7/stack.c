#include "stack.h"

int push(stackPosition head, dirPosition d) {
	stackPosition newNode = malloc(sizeof * newNode);
	if (!newNode) {
		printf("\ngreska pri alokaciji memorije.\n");
		return -1;
	}
	newNode->dirLevel = d;
	newNode->next = head->next;
	head->next = newNode;
	return 0;
}

dirPosition pop(stackPosition head) {
	if (!head->next)
		return NULL;
	stackPosition temp;
	temp= head->next;
	dirPosition dir;
	dir = temp->dirLevel;
	head->next = temp->next;
	free(temp);
	return dir;
}

dirPosition top(stackPosition head) {
	stackPosition first;
	first = head->next;
	if (first == NULL)
		return NULL;
	return first->dirLevel;
}

int freeStack(stackPosition head) {
	while (head->next)
		pop(head);
	return 0;
}