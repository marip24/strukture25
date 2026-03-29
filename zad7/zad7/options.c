#include "options.h"

int runOptions(dirPosition rootDir, stackPosition headStack) {
	int option;
	do {
		printf("\nunesite: 1 - md\n2 - cd\n3 - cd..\n4 - dir\n5 - izlaz\nizbor: ");
		if (scanf("%d", &option) != 1) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			option = 0;
		}
		switch (option) {
		case 1:
			mdCommand(headStack);
			break;
		case 2: {
			char dirName[MAX];
			int c;
			while ((c = getchar()) != '\n');
			printf("\nime direktorija u koji zelite uci: ");
			fgets(dirName, MAX, stdin);
			dirName[strcspn(dirName, "\n")] = 0;
			cdCommand(headStack, dirName);
			break;
		}
		case 3:
			cdBackCommand(headStack);
			break;
		case 4:
			dir(rootDir);
			break;
		case 5:
			printf("\nizasli ste iz programa");
			break;
		default:
			printf("\nunijeli ste krivi broj.\n");
			break;
		}
	} while (option ==1 || option == 2 || option == 3|| option == 4);
	return 0;
}
