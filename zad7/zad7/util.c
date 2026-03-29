#include "util.h"
#define MAX_STACK 100

int dir(dirPosition root) {
	if (!root)
		return -1;
	dirPosition stack[MAX_STACK];
	int level[MAX_STACK];
	int top = -1;
	stack[++top] = root;
	level[top] = 0;
	dirPosition curr;
	int currLevel;
	while (top >= 0) {
		curr = stack[top];
		currLevel = level[top--];
		for (int i = 0; i < currLevel; i++)
			printf(" ");
		printf(" %s\n", curr->name);

		dirPosition child;
		dirPosition children[MAX_STACK];
		int childCount = 0;
		child = curr->subDirPos;
		while (child) {
			children[childCount++] = child;
			child = child->next;
		}
		for (int i = childCount - 1; i >= 0; i--) {
			stack[++top] = children[i];
			level[top] = currLevel + 1;
		}
	}
}

int freeTree(dirPosition root) {
	if (!root)
		return -1;
	dirPosition* stack = malloc(sizeof(dirPosition) * MAX_STACK);
	if (!stack) {
		printf("\ngreska pri alokaciji memorije\n");
		return -1;
	}
	int top = -1;
	stack[++top] = root;
	dirPosition curr, child;
	while (top >= 0) {
		curr = stack[top--];
		child = curr->subDirPos;
		while (child) {
			if (top + 1 >= MAX_STACK) {
				printf("\nstog je prepun\n");
				free(stack);
				return -1;
			}
			stack[++top] = child;
			child = child->next;
		}
		free(curr);
	}
	free(stack);
	return 0;
}
