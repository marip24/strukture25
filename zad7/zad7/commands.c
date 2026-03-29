#include "commands.h"

int mdCommand(stackPosition headStack) {
	dirPosition current;
	current = top(headStack);
	if (!current) {
		printf("\ngreska pri alokaciji\n");
		return -1;
	}
	char name[MAX];
	int c;
	while ((c = getchar()) != '\n');
	printf("\nUnesi ime novog direktorija: ");
	fgets(name, MAX, stdin);
	name[strcspn(name, "\n")] = 0;
	dirPosition newDir;
	newDir = createDirectory(name);
	if (!newDir) {
		printf("\ngreska pri alokaciji memorije.\n");
		return -1;
	}
	newDir->next = current->subDirPos;
	current->subDirPos = newDir;
	return 0;
}

int cdCommand(stackPosition headStack, const char* name) {
	dirPosition curr;
	curr = top(headStack);
	if (!curr)
		return -1;
	dirPosition temp;
	temp = curr->subDirPos;
	while (temp) {
		if (strcmp(temp->name, name) == 0) {
			push(headStack, temp);
			return 0;
		}
		temp = temp->next;
	}
	printf("\ndirektorij %s ne postoji\n", name);
	return 0;
}

int cdBackCommand(stackPosition headStack) {
	if (!headStack->next || !headStack->next->next) {
		printf("\nvec ste u root direktoriju\n");
		return -1;
	}
	pop(headStack);
	return 0;
}
