#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directory.h"

typedef struct stack* stackPosition;

struct stack {
	dirPosition dirLevel;
	stackPosition next;
};

int push(stackPosition head, dirPosition d);
dirPosition pop(stackPosition head);
dirPosition top(stackPosition head);
int freeStack(stackPosition head);