#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 64

typedef struct directory* dirPosition;

struct directory {
	char name[MAX];
	dirPosition next;
	dirPosition subDirPos;
};

dirPosition createDirectory(const char* name);