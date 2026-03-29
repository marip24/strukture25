#include "directory.h"

dirPosition createDirectory(const char* name) {
	dirPosition d = malloc(sizeof *d);
	if (!d) {
		printf("\ngreska pri alokaciji memorije.\n");
		return NULL;
	}
	strcpy(d->name,name);
	d->next = NULL;
	d->subDirPos = NULL;
	return d;
}
