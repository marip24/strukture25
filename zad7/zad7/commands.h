#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directory.h"
#include "stack.h"

typedef struct {
	dirPosition headDir;
	dirPosition root;
	stackPosition headStack;
}programState;

int mdCommand(stackPosition headStack);
int cdCommand(stackPosition headStack, const char*name);
int cdBackCommand(stackPosition headStack);