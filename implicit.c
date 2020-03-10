#include <stdio.h>
#define MAX 112

char* start;																			// Globalny pointer na zaciatok pola

// Pridat breakpoint, spustit dedugger, v zalozke Debug vybrat Windows --> Memory --> Memory 1 (ctrl + alt + m, 1)
// Do pola adress napisat nazov smernika, kliknut pravym do pola Memory a vybrat Reevaluate Automatically

void* memory_alloc(unsigned int size) {
	// Obsadeny blok ma -, volny blok ma +
	char* pomocny;
	unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int), arraysize = *(unsigned int*)(start + 1), checksize = offset0 + offset1;

//	printf("%d\n", *(unsigned int*)((char*)start + chcecksize));

	while (checksize + size < arraysize)
	{
//		printf("checksize %d\n", checksize);
		int header = *(unsigned int*)((char*)start + checksize);						// Hodnota aktualnej hlavicky

		if (header > 0 && header >= size)
		{
//			printf("Som v podmienke\n");
			int b = 1;
			if (header - size < 8)														// Minimalna velkost bloku je 8, preto ak by bol zostatok po bloku mensi ako 8, bok sa alokuje vacsi
			{
				size = header;
				b = 0;
			}
			*(unsigned int*)((char*)start + checksize) = -1*size;						// Hlavicka bloku zmenena
			*(unsigned int*)((char*)start + checksize + size + offset1) = -1 *size;		// Paticka bloku zmenena

			if (b && arraysize - checksize - 2*offset1 - size >= 2*offset1)					// Ak zostava volny blok aspon o velkosti 1; sposobuje chybu stacku ak tu nie je
			{
				*(unsigned int*)((char*)start + checksize + size + 2 * offset1) = header - size - 2 * offset1;								// Nasledujuca hlavicka
				*(unsigned int*)((char*)start + checksize + size + 2 * offset1 + header - size - offset1) = header - size - 2 * offset1;	// Nasledujuca paticka
			}
//			printf("------------------------------\n");
			return (char*)start + checksize + offset1;
		}
		checksize += abs(header)+2*offset1;
	}
	return NULL;
}

int memory_free(void* valid_ptr) {
	// vraciam 0 ak som sa podaril, ak som nepodareny, vraciam 1
	printf("---------------Zacina free---------------\n");
	unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int), arraysize = *(unsigned int*)((char*)start + offset0);
	char* header = ((char*)valid_ptr - offset1);
	char* footer = ((char*)valid_ptr + abs(*(unsigned int*)((char*)header)));

	*(int*)((char*)header) = abs(*(int*)((char*)header));
	*(int*)((char*)footer) = abs(*(int*)((char*)footer));

	if (*(int*)((char*)footer+offset1) > 0)
	{
		int new = *(int*)((char*)footer) + *(int*)((char*)footer + offset1) + 2 * offset1;
//		printf("%d je nova velkost\n", new);
		*(int*)((char*)header) = new;
		footer = ((char*)valid_ptr + abs(*(unsigned int*)((char*)header)));
		*(int*)((char*)footer) = new;

		//printf("Blok doprava ma hlavicku %d \n", *(int*)((char*)footer + offset1));
	}

//	printf("Header %d a footer %d\n", *header, *footer);

	//int check = offset0 + offset1;
	//while (check + abs(*(unsigned int*)((char*)start + check)) + offset1 < arraysize) {
	//	if ((unsigned int*)((char*)start + check) == (unsigned int*)((char*)header))
	//		break;

	//	check += abs(*(unsigned int*)((char*)start + check)) + 2*offset1;

	//	if (check >= arraysize - 2 * offset1) {
	//		printf("Teraz som zlyhal vo free(). :( \n");
	//		return 1;
	//	}	
	//}





	return 0;
}

int memory_check(void* ptr) {
	// vo funkcii dostanem vzdy iba pointer na validny alokovany alebo nealokovany blok
	// nikdy nie pointer do stredu prazdna, lebo by som nevedel zistit, ci som v poli

	//posunies sa o jedna dolava a skontrolujes a posunies sa k paticke a skontrolujes aj ju
}

void vypis(void* ptr, unsigned int size) {
	printf("++++++++++++++++++++++++++++++\n");
	unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int);
	printf("Flag je %d\n", *(char*)start);
	unsigned int arraysize = *(unsigned int*)((char*)start + sizeof(char));
	printf("Celkova velkost je %u\n", arraysize);

	//printf("Hlavicka prveho bloku je %d\n", *(unsigned int*)((char*)start + sizeof(char) + sizeof(unsigned int)));
	//printf("Paticka prveho bloku je %d\n", *(unsigned int*)((char*)start + sizeof(char) + 2*sizeof(unsigned int) + prvy));
	//printf("Hlavicka druheho bloku je %d\n", *(unsigned int*)((char*)start + sizeof(char) + 3*sizeof(unsigned int) + prvy));
	//printf("Paticka druheho bloku je %d\n", *(unsigned int*)((char*)start + sizeof(char) + 4 * sizeof(unsigned int) + prvy + druhy));
	//printf("Hlavicka posledneho bloku je %d\n", *(unsigned int*)((char*)start + sizeof(char) + 5 * sizeof(unsigned int) + prvy + druhy));
	//printf("Paticka posledneho bloku je %d\n", *(unsigned int*)((char*)start + size - sizeof(unsigned int)));


	int check = offset0 + offset1, i = 1;
	while (check + abs(*(unsigned int*)((char*)start + check)) + offset1 < arraysize) {
		printf("Hlavicka %d. bloku je %d\n",i, *(unsigned int*)((char*)start + check));
		check += abs(*(unsigned int*)((char*)start + check)) + offset1;
		printf("Paticka %d. bloku je %d\n",i, *(unsigned int*)((char*)start + check));
		check += offset1;
		i++;
		printf("Priebezne je vyuzitych %d bajtov\n", check);
		if (check >= arraysize - 2 * offset1)
			break;
	}
	printf("Odpad je %d\n", arraysize - check);
}



void memory_init(void* ptr, unsigned int size) {
	start = (char*)ptr;
	for (int i = 0; i < size; i++)
	{
		start[i] = 0;
	}


	for (int i = size; i < 2 * size; i++)			// Pomocna alokacia pre prehladnejsi vypis; sposobuje chybu stacku
	{
		start[i] = 255;								// 255 je ff v 16-sustave - je to dobre vidiet
	}

	*(char*)start = 0;
//	printf("Flag je %d\n", *(char*)start);

	*(unsigned int*)((char*)start + sizeof(char)) = size;
//	printf("Celkova velkost je %u\n", *(unsigned int*)((char*)start + sizeof(char)));

	*(unsigned int*)((char*)start + sizeof(char) + sizeof(unsigned int)) = (size - sizeof(char) - 3 * sizeof(unsigned int));
//	printf("Hlavicka bloku je %d\n", *(unsigned int*)((char*)start + sizeof(char) + sizeof(unsigned int)));

	*(unsigned int*)((char*)start + size - sizeof(unsigned int))= (size - sizeof(char) - 3 * sizeof(unsigned int));
//	printf("Paticka bloku je %d\n", *(unsigned int*)((char*)start + size - sizeof(unsigned int)));

}

int main() {

	char region[MAX];
	memory_init(region, MAX);

	printf("smernik %p\n", start);
	printf("pole %p\n", region);

//	vypis(start, MAX);

	int a = 8;
	char* pole0 = memory_alloc(a);
	for (int i = 0; i < a; i++)
		pole0[i] = 1;

//	vypis(start, MAX);

	int b = 10;
	char* pole1 = memory_alloc(b);
	for (int i = 0; i < b; i++)
		pole1[i] = 2;

	vypis(start, MAX);

	int c = 11;
	char* pole2 = memory_alloc(c);
	for (int i = 0; i < c; i++)
		pole2[i] = 3;

	vypis(start, MAX);

	if (memory_free(pole1))
		printf("----------------------------Neuvolnil som pole1.\n");
	if (memory_free(pole0))
		printf("----------------------------Neuvolnil som pole0.\n");
	vypis(start, MAX);

	int d = 18;
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

	vypis(start, MAX);

	return 0;
}