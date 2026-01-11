#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 100

typedef struct cityTree* cityTreePos;
typedef struct cityList* cityListPos;
typedef struct countryList* countryListPos;
typedef struct countryTree* countryTreePos;

struct cityTree {
	char name[MAX_NAME];
	int population;
	cityTreePos left;
	cityTreePos right;
};

struct cityList {
	char name[MAX_NAME];
	int population;
	cityListPos next;
};

struct countryList {
	char name[MAX_NAME];
	countryListPos next;
	cityTreePos root;
};

struct countryTree {
	char name[MAX_NAME];
	countryTreePos left;
	countryTreePos right;
	cityListPos head;
};


countryListPos createCountryList(char* name);
int insertCountryListSorted(countryListPos head, countryListPos newCountry);
countryListPos findCountryList(countryListPos head, char* name);
int printCountryList(countryListPos head);
int freeCountryList(countryListPos head);


cityTreePos createCityTree(char* name, int population);
cityTreePos insertCityTree(cityTreePos root, char* name, int population);
int printCityTree(cityTreePos root);
int searchCityTree(cityTreePos root, int limit);
int freeCityTree(cityTreePos root);

countryListPos createCountryList(char* name);
int insertCountryListSorted(countryListPos head, countryListPos newCountry);
countryListPos findCountryList(countryListPos head, char* name);
int printCountryList(countryListPos head);
int freeCountryList(countryListPos head);

countryTreePos createCountryTree(char* name);
countryTreePos insertCountryTree(countryTreePos root, char* name);
countryTreePos findCountryTree(countryTreePos root, char* name);
int printCountryTree(countryTreePos root);
int freeCountryTree(countryTreePos root);

int loadData(countryListPos headList, countryTreePos* rootTree);

int runMenu(countryListPos headList, countryTreePos rootTree);
int deleteAll(countryListPos headList, countryTreePos rootTree);