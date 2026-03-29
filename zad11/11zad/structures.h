#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 100
#define HASH_SIZE 11

typedef struct cityTree* cityTreePos;
typedef struct country* countryPos;
typedef struct hashTable* hashTablePos;

struct cityTree {
	char name[MAX_NAME];
	int population;
	cityTreePos left;
	cityTreePos right;
};

struct country {
	char name[MAX_NAME];
	int key;
	cityTreePos root;
	countryPos next;
};

struct hashTable {
	int size;
	countryPos* list;
};

cityTreePos createCityTree(char* name, int pop);
cityTreePos insertCityTree(cityTreePos root, char* name, int pop);
int printCityTree(cityTreePos root, int limit);
int freeCityTree(cityTreePos root);

hashTablePos createHashTable(int size);
int findKey(char* name, int size);
int insertCountryHash(hashTablePos table, char* name);
countryPos findCountry(hashTablePos table, char* name);
int printHash(hashTablePos table);
int freeHash(hashTablePos table);

int loadData(hashTablePos table);
