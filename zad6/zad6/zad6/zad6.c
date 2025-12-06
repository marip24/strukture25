/*6. Napisati program koji èita datoteku racuni.txt u kojoj su zapisani nazivi svih datoteka koji
predstavljaju pojedini raèun. Na poèetku svake datoteke je zapisan datum u kojem vremenu je
raèun izdat u formatu YYYY-MM-DD. Svaki sljedeæi red u datoteci predstavlja artikl u formatu
naziv, kolièina, cijena. Potrebno je formirati vezanu listu raèuna sortiranu po datumu. Svaki èvor
vezane liste sadržava vezanu listu artikala sortiranu po nazivu artikla. Nakon toga potrebno je
omoguæiti upit kojim æe korisnik saznati koliko je novaca sveukupno potrošeno na specifièni
artikl u odreðenom vremenskom razdoblju i u kojoj je kolièini isti kupljen.
*/

#include "racuni.h"
#include "artikl.h"

int main() {

	billList* list = listForBills();
	FILE* fp = fopen("racuni.txt", "r");
	if (!fp) {
		printf("\ndatoteka nije otvorena.\n");
		return -1;
	}
	char fileName[50];
	while (fscanf(fp, "%49s", fileName) == 1) {
		Bill fresh = billFromFile(fileName);
		if (fresh)
			sortBill(list, fresh);
		else
			printf("\nnemoze se otvoriti %s\n", fileName);
	}
	fclose(fp);
	int choice;
	do{
		printf("\n-----------MENU-----------\n");
		printf("1 - pronadi potrosnju za artikl u nekom periodu\n");
		printf("2 - najskuplji artikl\n");
		printf("3 - najjeftiniji artikl\n");
		printf("4 - najcesci artikl\n");
		printf("5 - najrjedi artikl\n");
		printf("6 - ukupna potrosnja\n");
		printf("7 - ispisi sortirano sve artikle\n");
		printf("8 - artikl s najvecom potrosnjom\n ");
		printf("9 - artikl s najmanjom potrosnjom\n ");
		printf("10 - prosjecna cijena artikla\n ");
		printf("0 - izlaz\n");
		printf("-----------------------------\n");
		printf("odaberi: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1: {
			findArticle(list);
		}break;
		case 2: {
			priciest(list);
		}break;
		case 3: {
			cheapest(list);
		}break;
		case 4:
			mostCommon(list);
			break;
		case 5:
			rarest(list);
			break;
		case 6:
			total(list);
			break;
		case 7:
			printAllArticlesSorted(list);
			break;
		case 8: {
			maxConsumption(list);
		}break;
		case 9: {
			minConsumption(list);
		}break;
		case 10:{
			averagePrice(list);
		}break;
		case 0:
			printf("\nizasli ste iz programa.");
			break;
		default:
			printf("\novaj broj nije ni jedna opcija\n");
			break;
		}
	} while (choice != 0);
	freeBill(list);
	return 0;
}