/*Napisati program koji èita datoteku koja sadrži podatke o kategorijama proizvoda ("kategorije.txt")
te kreirati vezanu listu kategorija sortiranu po abecedi. Uz kategoriju proizvoda u datoteci se nalazi
i podaci o minimalnoj i maksimalnoj cijeni proizvoda u toj kategoriji. Nakon toga iz datoteke
"proizvodi.txt" reba proèitati podatke o proizvodima i kategorijama kojim pripadaju. Svaki proizvod
treba smjestiti u dodatnu vezanu listu za pojedinu kategoriju, tj. svaka kategorija sadrži dodatnu
vezanu listu proizvoda koji spadaju u tu kategoriju. Za svaki proizvod iz kategorije treba izgenerirati
cijenu (sluèajan broj iz min. i maks. opsega kategorije) i ne smije biti ponavljanja brojeva unutar
iste kategorije. Ispisati konaènu listu da prvo ide naziv kategorije, pa naziv i cijene proizvoda
u toj kategoriji. Kategorija i proizvodi su definirani strukturama: */


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NAME_LEN (32)

struct _proizvod;
typedef struct _proizvod* ProizvodP;
typedef struct _proizvod {
    char proizvod[MAX_NAME_LEN];
    int cijena;
    ProizvodP next;
}Proizvod;

struct _kategorija;
typedef struct _kategorija* KategorijaP;
typedef struct _kategorija {
    char imeKategorija[MAX_NAME_LEN];
    int minCijena;
    int maxCijena;
    float avgCijena;
    KategorijaP next;
    ProizvodP child;
}Kategorija;

KategorijaP stvori(KategorijaP head, const char* kat);
KategorijaP sortK(KategorijaP nov, KategorijaP head);
KategorijaP dodajP(KategorijaP head, const char* pro);
int ponavlja(int slucajan, ProizvodP head);
KategorijaP srednja(KategorijaP head);
int ispis(KategorijaP head);
int brisanje(KategorijaP head);

int main() {
    srand((unsigned)time(NULL));
    const char* kat = "kategorije.txt";
    const char* pro = "proizvodi.txt";
    KategorijaP head = NULL;
    head = stvori(head, kat);
    if (!head) {
        printf("\ngreska sa head");
        return -1;
    }
    head = dodajP(head, pro);
    head = srednja(head);
    ispis(head);
    brisanje(head);
    return 0;
}

int brisanje(KategorijaP head) {
    while (head) {
        ProizvodP p = head->child;
        while (p) {
            ProizvodP curr = p;
            p = p->next;
            free(curr);
        }
        KategorijaP temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

int ispis(KategorijaP head) {
    KategorijaP temp = head;
    while (temp) {
        printf("\n kategorija %s s avg %.2f:", temp->imeKategorija, temp->avgCijena);
        ProizvodP p = temp->child;
        while (p) {
            printf("\n%s %d", p->proizvod, p->cijena);
            p = p->next;
        }
        printf("\n");
        temp = temp->next;
    }
    return 0;
}

KategorijaP srednja(KategorijaP head) {
    KategorijaP temp = head;
    while (temp) {
        float suma = 0;
        int br = 0;
        ProizvodP curr = temp->child;
        while (curr) {
            suma += curr->cijena;
            ++br;
            curr = curr->next;
        }
        temp->avgCijena = (float)suma / br;
        temp = temp->next;
    }
    return head;
}

KategorijaP dodajP(KategorijaP head, const char* pro) {
    FILE* dat = fopen(pro, "r");
    if (!dat) {
        printf("\ngreska pri otvaranju proiz");
        return NULL;
    }
    char ime[MAX_NAME_LEN];
    char kateg[MAX_NAME_LEN];
    KategorijaP temp;
    while (fscanf(dat, "%s %s", ime, kateg) == 2) {
        temp = head;
        while (temp && strcmp(temp->imeKategorija, kateg) != 0)
            temp = temp->next;
        ProizvodP headP = temp->child;
        ProizvodP nov = (ProizvodP)malloc(sizeof(Proizvod));
        if (!nov) {
            printf("\ngreska pri alokaciji");
            return NULL;
        }
        int slucajan;
        do {
            slucajan = rand() % (temp->maxCijena - temp->minCijena + 1) + temp->minCijena;
        } while (ponavlja(slucajan, temp->child));
        nov->cijena = slucajan;
        strcpy(nov->proizvod, ime);
        nov->next = headP;
        headP = nov;
        temp->child = headP;
    }
    fclose(dat);
    return head;
}

int ponavlja(int slucajan, ProizvodP head) {
    ProizvodP temp = head;
    while (temp) {
        if (temp->cijena == slucajan)
            return 1;
        temp = temp->next;
    }
    return 0;
}

KategorijaP stvori(KategorijaP head, const char* kat) {
    FILE* fp = fopen(kat, "r");
    if (!fp) {
        printf("\ngreska pri otvaranju kateg");
        return NULL;
    }
    while (1) {
        KategorijaP nov = (KategorijaP)malloc(sizeof(Kategorija));
        if (!nov) {
            printf("\ngreska pri alokaciji");
            return NULL;
        }
        if (fscanf(fp, "%s %d %d", nov->imeKategorija, &nov->minCijena, &nov->maxCijena) != 3) {
            free(nov);
            fclose(fp);
            break;
        }
        nov->child = NULL;
        nov->next = NULL;
        nov->avgCijena = 0;
        head = sortK(nov, head);
    }
    fclose(fp);
    return head;
}

KategorijaP sortK(KategorijaP nov, KategorijaP head) {
    if (!head || strcmp(nov->imeKategorija, head->imeKategorija) < 0) {
        nov->next = head;
        return nov;
    }
    KategorijaP temp = head;
    while (temp->next && strcmp(nov->imeKategorija, temp->next->imeKategorija) > 0)
        temp = temp->next;
    nov->next = temp->next;
    temp->next = nov;
    return head;
}

DRUGI NACIIIIN::

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NAME_LEN (32)

struct _proizvod;
typedef struct _proizvod* ProizvodP;
typedef struct _proizvod {
    char proizvod[MAX_NAME_LEN];
    int cijena;
    ProizvodP next;
}Proizvod;

struct _kategorija;
typedef struct _kategorija* KategorijaP;
typedef struct _kategorija {
    char imeKategorija[MAX_NAME_LEN];
    int minCijena;
    int maxCijena;
    float avgCijena;
    KategorijaP next;
    ProizvodP child;
}Kategorija;

KategorijaP stvoriKat(KategorijaP head, const char* kat);
KategorijaP sortK(KategorijaP head, KategorijaP nov);
KategorijaP dodajP(KategorijaP head, const char* pro);
int cijenaP(int maksi, int mini);
int isti(int rendom, ProizvodP kategorija1);
KategorijaP srednja(KategorijaP head);
int ispis(KategorijaP head);
int brisi(KategorijaP head);

int main() {
    srand((unsigned)time(NULL));
    KategorijaP head = NULL;
    const char* kat = "kategorije.txt";
    head = stvoriKat(head, kat);
    const char* pro = "proizvodi.txt";
    head = dodajP(head, pro);
    head = srednja(head);
    ispis(head);
    brisi(head);
    return 0;
}

int brisi(KategorijaP head) {
    while (head) {
        ProizvodP p = head->child;
        while (p) {
            ProizvodP curr = p;
            p = p->next;
            free(curr);
        }
        KategorijaP temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

int ispis(KategorijaP head) {
    KategorijaP temp = head;
    while (temp) {
        printf("\nu kategoriji %s sa avg cijenon %.2f su: ", temp->imeKategorija, temp->avgCijena);
        ProizvodP p = temp->child;
        while (p) {
            printf("\n%s %d", p->proizvod, p->cijena);
            p = p->next;
        }
        printf("\n");
        temp = temp->next;
    }
    return 0;
}

KategorijaP srednja(KategorijaP head) {
    KategorijaP temp = head;
    while (temp) {
        float suma = 0;
        int br = 0;
        float srednja;
        ProizvodP headP = temp->child;
        while (headP) {
            suma += headP->cijena;
            ++br;
            headP = headP->next;
        }
        srednja = (float)suma / br;
        temp->avgCijena = srednja;
        temp = temp->next;
    }
    return head;
}

KategorijaP dodajP(KategorijaP head, const char* pro) {
    FILE* dat = fopen(pro, "r");
    if (!dat) {
        printf("\ngreska pri otvaranju pro");
        return NULL;
    }
    char kateg[MAX_NAME_LEN];
    char stvar[MAX_NAME_LEN];
    while (fscanf(dat, "%s %s", stvar, kateg) == 2) {
        KategorijaP tempK = head;
        while (tempK && strcmp(tempK->imeKategorija, kateg) != 0)
            tempK = tempK->next;
        if (tempK) {
            ProizvodP nov = (ProizvodP)malloc(sizeof(Proizvod));
            if (!nov) {
                printf("\ngreska pri alokaciji nov");
                fclose(dat);
                return head;
            }
            strcpy(nov->proizvod, stvar);
            int rendom;
            do {
                rendom = cijenaP(tempK->maxCijena, tempK->minCijena);
            } while (isti(rendom, tempK->child));
            nov->cijena = rendom;
            nov->next = tempK->child;
            tempK->child = nov;
        }
    }
    fclose(dat);
    return head;
}

int isti(int rendom, ProizvodP kategorija1) {
    ProizvodP temp = kategorija1;
    while (temp) {
        if (rendom == temp->cijena)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int cijenaP(int maksi, int mini) {
    return rand() % (maksi - mini + 1) + mini;
}

KategorijaP stvoriKat(KategorijaP head, const char* kat) {
    FILE* fp = fopen(kat, "r");
    if (!fp) {
        printf("\ngreska pri otvaranju kat");
        return NULL;
    }
    while (1) {
        KategorijaP nov = (KategorijaP)malloc(sizeof(Kategorija));
        if (!nov) {
            printf("\ngreska pri alokaciji");
            return NULL;
        }
        if (fscanf(fp, "%s %d %d", nov->imeKategorija, &nov->minCijena, &nov->maxCijena) != 3) {
            free(nov);
            fclose(fp);
            break;
        }
        nov->next = NULL;
        nov->avgCijena = 0;
        nov->child = NULL;
        head = sortK(head, nov);
    }
    return head;
}

KategorijaP sortK(KategorijaP head, KategorijaP nov) {
    if (!head || strcmp(nov->imeKategorija, head->imeKategorija) < 0) {
        nov->next = head;
        return nov;
    }
    KategorijaP temp = head;
    while (temp->next && strcmp(nov->imeKategorija, temp->next->imeKategorija) > 0)
        temp = temp->next;
    nov->next = temp->next;
    temp->next = nov;
    return head;
}

