/*7. Napisati program koji pomoæu vezanih listi(stabala) predstavlja strukturu direktorija.
Omoguæiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij.Toènije program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#include "directory.h"
#include "stack.h"
#include "options.h"

int main() {
	
	dirPosition rootDir;
	rootDir = createDirectory("C");
	if (!rootDir)
		return -1;
	stackPosition headStack = malloc(sizeof(struct stack));
	if (!headStack)
		return -1;
	headStack->dirLevel = NULL;
	headStack->next = NULL;
	push(headStack, rootDir);
	runOptions(rootDir, headStack);
	freeStack(headStack);
	free(headStack);
	freeTree(rootDir);
	return 0;
}