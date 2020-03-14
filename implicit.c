#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX 112
#define test0 112
#define velkost4 150
#define velkost5 50000
#define velkost6 100000
#define velkost7 100000

char* start;																				// Globalny pointer na zaciatok pola

// Pridat breakpoint, spustit dedugger, v zalozke Debug vybrat Windows --> Memory --> Memory 1 (ctrl + alt + m, 1)
// Do pola adress napisat nazov smernika, kliknut pravym do pola Memory a vybrat Reevaluate Automatically

void* memory_alloc(unsigned int size) {
																							// Obsadeny blok ma -, volny blok ma +
	char* pomocny;
	unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int), arraysize = *(unsigned int*)(start + offset0), checksize = offset0 + offset1;
																							// Nastavenie offsetov pre aktualne premenne
																							// arraysize je celkova velkost pola
																							// checksize je offset pri posune po hlavickach

	int bestheader = *(unsigned int*)((char*)start + checksize);							// Hodnota najlepsie vyhovujucej hlavicky
	int diff = arraysize, enough = 0, bestchecksize = checksize;							// diff urcuje rozdiel velkosti medzi hlavickou a pozadovanou velkostou
																							// enough je boolean, ktory oznacuje, ci sa nachadza v poli aspon jeden blok dostatocnej velkosti na alokovanie
																							// bestchecksize je hodnota najlepsieho najdeneho posunu od zaciatku pola
	while (checksize < arraysize)
	{
		int header = *(unsigned int*)((char*)start + checksize);							// Hodnota aktualnej hlavicky
		
		if (header > 0 && header >= size)
		{
			enough = 1;																		// Bolean oznacujuci existenciu aspon jedneho vyhovujuceho bloku
			if (header - size < diff)														// Ak je rozdiel headera a velkosti mensi ako predosly rozdiel
			{
				bestheader = header;														// Priebezne najlepsia hodnota hlavicky
				diff = header - size;														// Priebezne najlepsi rozdiel
				bestchecksize = checksize;													// Priebezne najlepsi offset voci zaciatku pola
			}
		}
		checksize += abs(header)+2*offset1;													// Posun na dalsiu hlavicku
	}

	if (enough)
	{
		int b = 1;
		if (bestheader - size < 8 + 2 * offset1)											// Minimalna velkost bloku je 8, preto ak by bol zostatok po bloku mensi ako 8, bok sa alokuje vacsi
		{
			size = bestheader;
			b = 0;
		}
		*(unsigned int*)((char*)start + bestchecksize) = -1 * size;							// Hlavicka bloku zmenena
		*(unsigned int*)((char*)start + bestchecksize + size + offset1) = -1 * size;		// Paticka bloku zmenena

		if (b && arraysize - bestchecksize - 2 * offset1 - size >= 2 * offset1)				// Ak zostava volny blok aspon o velkosti 1; sposobuje chybu stacku ak tu nie je
		{
			*(unsigned int*)((char*)start + bestchecksize + size + 2 * offset1) = bestheader - size - 2 * offset1;								
																							// Nasledujuca hlavicka
			*(unsigned int*)((char*)start + bestchecksize + size + 2 * offset1 + bestheader - size - offset1) = bestheader - size - 2 * offset1;	
																							// Nasledujuca paticka
		}
		return (char*)start + bestchecksize + offset1;
	}

	return NULL;
}

int memory_free(void* valid_ptr) {															// vracia 0 ak sa podarilo uvolnit pamat, inak vracia 1

	if (valid_ptr == NULL || memory_check(valid_ptr) == 0)									// Kontrola platnosti pointera										
		return 1;

	unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int), arraysize = *(unsigned int*)((char*)start + offset0);
	char* header = ((char*)valid_ptr - offset1);											// Nastavenie sa na hlavicku daneho bloku
	char* footer = ((char*)valid_ptr + abs(*(unsigned int*)((char*)header)));				// Nastavenie sa na paticku daneho bloku

	*(int*)((char*)header) = abs(*(int*)((char*)header));									// Oznacim hlavicku aj paticku kladnym cislom, co znamena, ze su volne
	*(int*)((char*)footer) = abs(*(int*)((char*)footer));


	if (*(int*)((char*)footer+offset1) > 0 && (int*)((char*)footer) != (int*)((char*)start + arraysize - offset1))					
		// Zlucovanie zlava doprava; vpravo je urcite iba jeden volny blok
		// Kontrolujem hranicu pola tak, ze porovnam, ci nie je footer patickou posledneho bloku vobec
	{
		int new = *(int*)((char*)footer) + *(int*)((char*)footer + offset1) + 2 * offset1;
																							// Hodnota novej velkosti hlavicky a paticky
		*(int*)((char*)header) = new;														// Nastavenie hodnoty pre hlavicku
		footer = ((char*)valid_ptr + *(unsigned int*)((char*)header));						// Posun na novu paticku
		*(int*)((char*)footer) = new;														// Nastavenie hodnoty novej paticke
	}

	if (*(int*)((char*)header - offset1) > 0 && *(int*)((char*)header - offset1) != arraysize)				
		// Zlucovanie sprava dolava; vlavo je urcite iba jeden volny blok
		// Kontrolujem hranice pola tak, ze overim, ci hodnota zapisana pred hlavickou nie je absolutna velkost pola
	{
		int new = *(int*)((char*)header) + *(int*)((char*)header - offset1) + 2 * offset1;
																							// Hodnota novej velkosti hlavicky a paticky
		*(int*)((char*)footer) = new;														// Nastavenie hodnoty pre paticku
		header = ((char*)valid_ptr - *(int*)((char*)header - offset1) - 3 * offset1);		// Posun na novu hlavicku
		*(int*)((char*)header) = new;														// Nastavenie hodnoty novej hlavicke
	}
	return 0;
}

int memory_check(void* ptr) {
	// Vracia 0 ak je ukazovatel neplatny, 1 ak je platny

	unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int), arraysize = *(unsigned int*)(start + offset0), checksize = offset0 + offset1;
																							// Nastavenie hodnot premenyych rovnako ako v predoslych funkciach
	int boolean = 0;																		// Premenna oznacujuca zhodu smernikov

	if ((char*)ptr == (char*)start || (unsigned int*)ptr == ((char*)start+offset0))			// Ak je smernik smernikom na zaciatok pola alebo na hodnotu jeho velkosti, je neplatny
		return 0;

	int* header = (unsigned int*)((char*)ptr - offset1);									// Hlavicka nachadzajuca sa pred smernikom

	if (*header > 0)																		// Ak je kladna, nebola alokovana, pretoze alokovane bloky maju zapornu hlavicku
		return 0;

	while (checksize < arraysize)															// Kym nie som na konci pola
	{
		int *testheader = (unsigned int*)((char*)start + checksize);						// Hlavicka v poli
		if (header == testheader)															// Ak sa smerniky rovnaju, vyskocim z pola a nastavim boolean na jedna
		{
			boolean = 1;
			break;
		}
		checksize += abs(*testheader) + 2 * offset1;
	}

	if (boolean == 0)																		// Ak sa smernik na hlavicku nenasiel, vraciam 0
		return 0;

	int *footer = (unsigned int*)((char*)ptr + abs(*header));								// Smernik na predpokladanu paticku

	if (*header == *footer)																	// Hodnota hlavicky a paticky sa musia rovnat
		return 1;																			// Ak sa rovnaju, vraciam 1
	
	return 0;																				// Inak vraciam 0
}

void memory_init(void* ptr, unsigned int size) {
	start = (char*)ptr;																		// Nastavim hodnotu globalnej premennej
	memset(start, 0, size);																	// Nastavim hodnotu celeho pola na 0

//	memset(start + size, 255, size);

	unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int);					// Nastavenie offsetov podla aktualne pouzivanych premennych

	*(char*)start = 0;																		// Flag oznacujuci, ake premenne pouzivam
	*(unsigned int*)((char*)start + offset0) = size;										// Celkova velkost
	*(unsigned int*)((char*)start + offset0 + offset1) = (size - offset0 - 3 * offset1);	// Hlavicka jedineho volneho bloku
	*(unsigned int*)((char*)start + size - offset1)= (size - offset0 - 3 * offset1);		// Paticka jedineho volneho bloku

}

void test_integrity() {
	char region[test0];
	memory_init(region, test0);


}

void test4() {
	char region[velkost4];
	memset(region, 0, velkost4);
	memory_init(region, velkost4);


	srand(time(0));
	int horna_hranica = 24;
	int dolna_hranica = 8;
	char* x;
	unsigned int total = 0;
	int ziadana_velkost;
	do {
		ziadana_velkost = (rand() % (horna_hranica - dolna_hranica)) + dolna_hranica;
		total += ziadana_velkost;
		printf("%d\n", ziadana_velkost);
		x = memory_alloc(ziadana_velkost);
	} while (x != NULL);
	total -= ziadana_velkost;
	printf("alokovane: %d\n", total);
	printf("velkost: %d\n", velkost4);
	printf("pomer: %f\n", (float)total / velkost4);

}

void test5() {

	char region[velkost5];
	memset(region, 0, velkost5);
	memory_init(region, velkost5);


	srand(time(0));
	int horna_hranica = 5000;
	int dolna_hranica = 500;
	char* x;
	unsigned int total = 0;
	int ziadana_velkost;
	do {
		ziadana_velkost = (rand() % (horna_hranica - dolna_hranica)) + dolna_hranica;
		total += ziadana_velkost;
		printf("%d\n", ziadana_velkost);
		x = memory_alloc(ziadana_velkost);
	} while (x != NULL);
	total -= ziadana_velkost;
	printf("alokovane: %d\n", total);
	printf("velkost: %d\n", velkost5);
	printf("pomer: %f\n", (float)total / velkost5);

}

void test6() {

	char region[velkost6];
	memset(region, 0, velkost6);
	memory_init(region, velkost6);


	srand(time(0));
	int horna_hranica = 10000;
	int dolna_hranica = 5000;
	char* x;
	unsigned int total = 0;
	int ziadana_velkost;
	do {
		ziadana_velkost = (rand() % (horna_hranica - dolna_hranica)) + dolna_hranica;
		total += ziadana_velkost;
		printf("%d\n", ziadana_velkost);
		x = memory_alloc(ziadana_velkost);
	} while (x != NULL);
	total -= ziadana_velkost;
	printf("alokovane: %d\n", total);
	printf("velkost: %d\n", velkost6);
	printf("pomer: %f\n", (float)total / velkost6);
}

void test7() {

	char region[velkost7];
	memset(region, 0, velkost7);
	memory_init(region, velkost7);


	srand(time(0));
	int horna_hranica = 10000;
	int dolna_hranica = 8;
	char* x;
	unsigned int total = 0;
	int ziadana_velkost;
	do {
		ziadana_velkost = (rand() % (horna_hranica - dolna_hranica)) + dolna_hranica;
		total += ziadana_velkost;
		printf("%d\n", ziadana_velkost);
		x = memory_alloc(ziadana_velkost);
	} while (x != NULL);
	total -= ziadana_velkost;
	printf("alokovane: %d\n", total);
	printf("velkost: %d\n", velkost7);
	printf("pomer: %f\n", (float)total / velkost7);
}

int rer_test(int size) {
	int amnt = size / 2, max = 20, min = 8, i, block = 0, counter = 0;
	unsigned char* region = (unsigned char*)malloc(size);
	char** test_ptrs = (char**)malloc(amnt * sizeof(char*));
	for (i = 0; i < amnt; i++) test_ptrs[i] = NULL;
	memory_init(region, size);

	for (i = 1; i < amnt; i++)
	{
		srand((unsigned int)time(0) + i + block);
		block = rand() % (max - min) + min;
		test_ptrs[i] = (char*)memory_alloc(block);
		if (test_ptrs[i] == NULL) break;
		counter += block;
	}

	free(region);
	free(test_ptrs);
	return 10 * ((int)(1000 * (double)counter) / size);
 }

void rer_main() {
	int temp = 0, sum = 0, x = 0;
	for (int i = 0; i < 100000; i++)
	{
		srand(i + temp + x);
		x = rand() % 10 + 50 + ((double)i / 150) * ((double)i / 150);
		temp = rer_test(x);
		sum += temp;
		printf("%05d:\t size %05d curr: %4.2f avg: %4.2f\n", i, x, (double)((double)temp / 100), (double)sum / (100 * ((double)i + 1)));
	}
}

void vypis(void* ptr) {
	printf("+++++++++++++++Zaciatok funkcie vypis+++++++++++++++\n");
	unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int);
	printf("Flag je %d\n", *(char*)start);
	unsigned int arraysize = *(unsigned int*)((char*)start + sizeof(char));
	printf("Celkova velkost je %u\n", arraysize);

	int check = offset0 + offset1, i = 1;
	while (check + abs(*(unsigned int*)((char*)start + check)) + offset1 < arraysize) {
		printf("Hlavicka %d. bloku je %d\n", i, *(unsigned int*)((char*)start + check));
		check += abs(*(unsigned int*)((char*)start + check)) + offset1;
		printf("Paticka %d. bloku je %d\n", i, *(unsigned int*)((char*)start + check));
		check += offset1;
		i++;
		printf("Priebezne je vyuzitych %d bajtov\n", check);
		if (check >= arraysize - 2 * offset1)
			break;
	}
	printf("Odpad je %d\n", arraysize - check);
}

int main() {

	char region[MAX];
	memory_init(region, MAX);

	vypis(start);

	int a = 8;
	char* pole0 = memory_alloc(a);
	if (pole0 != NULL)
	{
		for (int i = 0; i < a; i++)
			pole0[i] = 1;

		if (memory_check(pole0))
			printf("Som platny\n");
		else
			printf("Nie som platny\n");
	}
	else
	{
		printf("---------------------------Som NULL\n");
	}

	vypis(start);

	int b = 9;
	char* pole1 = memory_alloc(b);
	if (pole1 != NULL)
	{
		for (int i = 0; i < b; i++)
			pole1[i] = 2;
	}
	else
	{
		printf("---------------------------Som NULL\n");
	}
	vypis(start);

	int c = 10;
	char* pole2 = memory_alloc(c);
	if (pole2 != NULL)
	{
		for (int i = 0; i < c; i++)
			pole2[i] = 3;
	}
	else
	{
		printf("---------------------------Som NULL\n");
	}
	vypis(start);

	int d = 11;
	char* pole3 = memory_alloc(d);
	if (pole3 != NULL)
	{
		for (int i = 0; i < d; i++)
			pole3[i] = 4;
	}
	else
	{
		printf("---------------------------Som NULL\n");
	}
	vypis(start);

	int e = 30;
	char* pole4 = memory_alloc(e);
	if (pole4 != NULL)
	{
		for (int i = 0; i < e; i++)
			pole4[i] = 5;
	}
	else
	{
		printf("---------------------------Som NULL\n");
	}

	vypis(start);

	if (memory_free(pole0))
		printf("----------------------------Neuvolnil som pole0.\n");
	if (memory_free(pole4))
		printf("----------------------------Neuvolnil som pole4.\n");
	if (memory_free(pole1))
		printf("----------------------------Neuvolnil som pole1.\n");
	if (memory_free(pole3))
		printf("----------------------------Neuvolnil som pole3.\n");
	if (memory_free(pole2))
		printf("----------------------------Neuvolnil som pole2.\n");

	vypis(start);

	test4();

	test5();

	test6();

	test7();

	//rer_main();
	return 0;
}