/*Napisati program koji iz datoteka memberships.txt i visits.txt (imena datoteka unosi korisnik)
èita podatke o mjeseènim èlanarinama korisnika i o posjetima teretani. Proèitati datoteke i
uvezati na naèin da se posjete povežu s èlanarinama (lista u listi). Posjeta se veže s
èlanarinom ako je userId isti i ako se posjeta dogodila u tom mjesecu. Lista èlanarina mora biti
sortirana po godini i mjesecu. Posjete moraju biti sortirane po danu u mjesecu. Ispisati sve
èlanarine i posjete u tom mjesecu. Posjeta u teretani i èlanarina su definirane strukturama:*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ID_LENGTH 64
#define MAX_NAME_LENGTH 64

struct _visit;
typedef struct _visit *VisitP;
typedef struct _visit {
    char userId[MAX_ID_LENGTH];
    int day;
    int month;
    int year;
    VisitP next;
} Visit;

struct _membership;
typedef struct _membership *MembershipP;
typedef struct _membership {
    char userId[MAX_ID_LENGTH];
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int month;
    int year;
    int price;
    VisitP visits;
    MembershipP next;
} Membership;

MembershipP stvoriM(MembershipP head, const char* mem);
MembershipP sortM(MembershipP head, MembershipP nov);
MembershipP dodajV(MembershipP head, const char* vis);
VisitP sortV(VisitP nov, VisitP headV);
int brisi(MembershipP head);
int ispis(MembershipP head);

int main() {
    const char* mem = "memberships.txt";
    const char* vis = "visits.txt";
    MembershipP head = NULL;
    head = stvoriM(head, mem);
    head = dodajV(head, vis);
    ispis(head);
    brisi(head);
    return 0;
}

int brisi(MembershipP head) {
    while (head) {
        VisitP v = head->visits;
        while (v) {
            VisitP curr = v;
            v = v->next;
            free(curr);
        }
        MembershipP temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

int ispis(MembershipP head) {
    MembershipP temp = head;
    while (temp) {
        VisitP v = temp->visits;
        printf("\n%s %s %s %d %d %d: ", temp->userId, temp->firstName, temp->lastName, temp->month, temp->year, temp->price);
        while (v) {
            printf("%d %d %s, ", v->day, v->month,v->userId);
            v = v->next;
        }
        temp = temp->next;
    }
    return 0;
}

MembershipP dodajV(MembershipP head, const char* vis) {
    FILE* dat = fopen(vis, "r");
    if (!dat) {
        printf("\ngreska pri otvaranju vis");
        return NULL;
    }
    char id[MAX_ID_LENGTH];
    int d;
    int m;
    int g;
    while (fscanf(dat, "%s %d %d %d", id, &d, &m, &g) == 4) {
        MembershipP temp = head;
        while (strcmp(temp->userId, id) != 0 || temp->month != m)
            temp = temp->next;
        VisitP headV = temp->visits;
        VisitP nov = (VisitP)malloc(sizeof(Visit));
        if (!nov) {
            printf("\ngreska pri alokaciji");
            return NULL;
        }
        strcpy(nov->userId, id);
        nov->day = d;
        nov->month = m;
        nov->year = g;
        nov->next = NULL;
        headV = sortV(nov, headV);
        temp->visits = headV;
    }
    fclose(dat);
    return head;
}

VisitP sortV(VisitP nov, VisitP headV) {
    if (!headV || nov->day < headV->day) {
        nov->next = headV;
        return nov;
    }
    VisitP temp = headV;
    while (temp->next && nov->year > temp->next->day)
        temp = temp->next;
    nov->next = temp->next;
    temp->next = nov;
    return headV;
}

MembershipP stvoriM(MembershipP head,const char* mem) {
    FILE* fp = fopen(mem, "r");
    if (!fp) {
        printf("\ngreska pri otvaranju mem");
        return NULL;
    }
    while (1) {
        MembershipP nov = (MembershipP)malloc(sizeof(Membership));
        if (!nov) {
            printf("\ngreska pri alokaciji");
            return NULL;
        }
        if (fscanf(fp, "%s %s %s %d %d %d", nov->userId, nov->firstName, nov->lastName, &nov->month, &nov->year, &nov->price) != 6) {
            free(nov);
            fclose(fp);
            break;
        }
        nov->visits = NULL;
        nov->next = NULL;
        head = sortM(head, nov);
    }
    fclose(fp);
    return head;
}

MembershipP sortM(MembershipP head, MembershipP nov) {
    if (!head || nov->year < head->year || (nov->year == head->year && nov->month < head->month)) {
        nov->next = head;
        return nov;
    }
    MembershipP temp = head;
    while (temp->next && (nov->year > temp->next->year || (nov->year == temp->next->year && nov->month > temp->next->month)))
        temp = temp->next;
    nov->next = temp->next;
    temp->next = nov;
    return head;
}
