//#include <stdio.h>
//#include <string.h>
//#include <time.h>
//#include <stdlib.h>
//
//
//#define t50 50
//#define t100 100
//#define t200 200
//#define t1k 1000
//#define t10k 10000
//#define t100k 100000
//#define t1m 1000000
//
//#define MAX 50
//#define velkost4 150
//#define velkost5 50000
//#define velkost6 100000
//#define velkost7 100000
//
//// Vypracoval: Peter Smrecek
//// Zadanie cislo 1
//// Letny semester 2020
//
//char* start;																				// Globalny pointer na zaciatok pola
//
//void* memory_alloc(unsigned int size) {
//	// Obsadeny blok ma -, volny blok ma +
//	char flag = *(char*)start;
//	//	printf("Flag je %d\n", flag);
//
//	if (flag == 0)
//	{
//		unsigned char offset0 = sizeof(char), offset1 = sizeof(unsigned char), arraysize = *(unsigned char*)(start + offset0), checksize = offset0 + offset1;
//		// Nastavenie offsetov pre aktualne premenne
//		// arraysize je celkova velkost pola
//		// checksize je offset pri posune po hlavickach
//
//		char bestheader = *(unsigned char*)((char*)start + checksize);							// Hodnota najlepsie vyhovujucej hlavicky
//		char diff = arraysize, enough = 0, bestchecksize = checksize;							// diff urcuje rozdiel velkosti medzi hlavickou a pozadovanou velkostou
//																								// enough je boolean, ktory oznacuje, ci sa nachadza v poli aspon jeden blok dostatocnej velkosti na alokovanie
//																								// bestchecksize je hodnota najlepsieho najdeneho posunu od zaciatku pola
//		while (checksize < arraysize)
//		{
//			char header = *(unsigned char*)((char*)start + checksize);							// Hodnota aktualnej hlavicky
//
//			if (header > 0 && header >= size)
//			{
//				enough = 1;																		// Bolean oznacujuci existenciu aspon jedneho vyhovujuceho bloku
//				if (header == size)																// Ak sa nasla presne zhodna hlavicka, cysklus konci
//				{
//					bestheader = header;														// Oznacenie najlepsej hlavicky
//					bestchecksize = checksize;													// Oznacenie najlepsieho offsetu voci zaciatku pola
//					break;
//				}
//				if (header - size < diff)														// Ak je rozdiel headera a velkosti mensi ako predosly rozdiel
//				{
//					bestheader = header;														// Priebezne najlepsia hodnota hlavicky
//					diff = header - size;														// Priebezne najlepsi rozdiel
//					bestchecksize = checksize;													// Priebezne najlepsi offset voci zaciatku pola
//				}
//			}
//			checksize += abs(header) + 2 * offset1;												// Posun na dalsiu hlavicku
//		}
//
//		if (enough)
//		{
//			char b = 1;
//			if (bestheader - size < 8 + 2 * offset1)											// Minimalna velkost bloku je 8, preto ak by bol zostatok po bloku mensi ako 8, bok sa alokuje vacsi
//			{
//				size = bestheader;
//				b = 0;
//			}
//			*(unsigned char*)((char*)start + bestchecksize) = -1 * size;						// Hlavicka bloku zmenena
//			*(unsigned char*)((char*)start + bestchecksize + size + offset1) = -1 * size;		// Paticka bloku zmenena
//
//			if (b && arraysize - bestchecksize - 2 * offset1 - size >= 8)
//			{
//				*(unsigned char*)((char*)start + bestchecksize + size + 2 * offset1) = bestheader - size - 2 * offset1;
//				// Nasledujuca hlavicka
//				*(unsigned char*)((char*)start + bestchecksize + size + 2 * offset1 + bestheader - size - offset1) = bestheader - size - 2 * offset1;
//				// Nasledujuca paticka
//			}
//			return (char*)start + bestchecksize + offset1;
//		}
//
//		return NULL;
//	}
//
//	if (flag == 1)
//	{
//		unsigned short offset0 = sizeof(char), offset1 = sizeof(unsigned short), arraysize = *(unsigned short*)(start + offset0), checksize = offset0 + offset1;
//		// Nastavenie offsetov pre aktualne premenne
//		// arraysize je celkova velkost pola
//		// checksize je offset pri posune po hlavickach
//
//		short bestheader = *(unsigned short*)((char*)start + checksize);							// Hodnota najlepsie vyhovujucej hlavicky
//		short diff = arraysize, enough = 0, bestchecksize = checksize;							// diff urcuje rozdiel velkosti medzi hlavickou a pozadovanou velkostou
//																								// enough je boolean, ktory oznacuje, ci sa nachadza v poli aspon jeden blok dostatocnej velkosti na alokovanie
//																								// bestchecksize je hodnota najlepsieho najdeneho posunu od zaciatku pola
//		while (checksize < arraysize)
//		{
//			short header = *(unsigned short*)((char*)start + checksize);							// Hodnota aktualnej hlavicky
//
//			if (header > 0 && header >= size)
//			{
//				enough = 1;																		// Bolean oznacujuci existenciu aspon jedneho vyhovujuceho bloku
//				if (header == size)																// Ak sa nasla presne zhodna hlavicka, cysklus konci
//				{
//					bestheader = header;														// Oznacenie najlepsej hlavicky
//					bestchecksize = checksize;													// Oznacenie najlepsieho offsetu voci zaciatku pola
//					break;
//				}
//				if (header - size < diff)														// Ak je rozdiel headera a velkosti mensi ako predosly rozdiel
//				{
//					bestheader = header;														// Priebezne najlepsia hodnota hlavicky
//					diff = header - size;														// Priebezne najlepsi rozdiel
//					bestchecksize = checksize;													// Priebezne najlepsi offset voci zaciatku pola
//				}
//			}
//			checksize += abs(header) + 2 * offset1;													// Posun na dalsiu hlavicku
//		}
//
//		if (enough)
//		{
//			short b = 1;
//			if (bestheader - size < 8 + 2 * offset1)											// Minimalna velkost bloku je 8, preto ak by bol zostatok po bloku mensi ako 8, bok sa alokuje vacsi
//			{
//				size = bestheader;
//				b = 0;
//			}
//			*(unsigned short*)((char*)start + bestchecksize) = -1 * size;							// Hlavicka bloku zmenena
//			*(unsigned short*)((char*)start + bestchecksize + size + offset1) = -1 * size;		// Paticka bloku zmenena
//
//			if (b && arraysize - bestchecksize - 2 * offset1 - size >= 8)
//			{
//				*(unsigned short*)((char*)start + bestchecksize + size + 2 * offset1) = bestheader - size - 2 * offset1;
//				// Nasledujuca hlavicka
//				*(unsigned short*)((char*)start + bestchecksize + size + 2 * offset1 + bestheader - size - offset1) = bestheader - size - 2 * offset1;
//				// Nasledujuca paticka
//			}
//			return (char*)start + bestchecksize + offset1;
//		}
//
//		return NULL;
//	}
//
//	if (flag == 2)
//	{
//		unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int), arraysize = *(unsigned int*)(start + offset0), checksize = offset0 + offset1;
//		// Nastavenie offsetov pre aktualne premenne
//		// arraysize je celkova velkost pola
//		// checksize je offset pri posune po hlavickach
//
//		int bestheader = *(unsigned int*)((char*)start + checksize);							// Hodnota najlepsie vyhovujucej hlavicky
//		int diff = arraysize, enough = 0, bestchecksize = checksize;							// diff urcuje rozdiel velkosti medzi hlavickou a pozadovanou velkostou
//																								// enough je boolean, ktory oznacuje, ci sa nachadza v poli aspon jeden blok dostatocnej velkosti na alokovanie
//																								// bestchecksize je hodnota najlepsieho najdeneho posunu od zaciatku pola
//		while (checksize < arraysize)
//		{
//			int header = *(unsigned int*)((char*)start + checksize);							// Hodnota aktualnej hlavicky
//
//			if (header > 0 && header >= size)
//			{
//				enough = 1;																		// Bolean oznacujuci existenciu aspon jedneho vyhovujuceho bloku
//				if (header == size)																// Ak sa nasla presne zhodna hlavicka, cysklus konci
//				{
//					bestheader = header;														// Oznacenie najlepsej hlavicky
//					bestchecksize = checksize;													// Oznacenie najlepsieho offsetu voci zaciatku pola
//					break;
//				}
//				if (header - size < diff)														// Ak je rozdiel headera a velkosti mensi ako predosly rozdiel
//				{
//					bestheader = header;														// Priebezne najlepsia hodnota hlavicky
//					diff = header - size;														// Priebezne najlepsi rozdiel
//					bestchecksize = checksize;													// Priebezne najlepsi offset voci zaciatku pola
//				}
//			}
//			checksize += abs(header) + 2 * offset1;													// Posun na dalsiu hlavicku
//		}
//
//		if (enough)
//		{
//			int b = 1;
//			if (bestheader - size < 8 + 2 * offset1)											// Minimalna velkost bloku je 8, preto ak by bol zostatok po bloku mensi ako 8, bok sa alokuje vacsi
//			{
//				size = bestheader;
//				b = 0;
//			}
//			*(unsigned int*)((char*)start + bestchecksize) = -1 * size;							// Hlavicka bloku zmenena
//			*(unsigned int*)((char*)start + bestchecksize + size + offset1) = -1 * size;		// Paticka bloku zmenena
//
//			if (b && arraysize - bestchecksize - 2 * offset1 - size >= 8)
//			{
//				*(unsigned int*)((char*)start + bestchecksize + size + 2 * offset1) = bestheader - size - 2 * offset1;
//				// Nasledujuca hlavicka
//				*(unsigned int*)((char*)start + bestchecksize + size + 2 * offset1 + bestheader - size - offset1) = bestheader - size - 2 * offset1;
//				// Nasledujuca paticka
//			}
//			return (char*)start + bestchecksize + offset1;
//		}
//
//		return NULL;
//	}
//
//	return NULL;
//}
//
//int memory_check(void* ptr) {
//	// Vracia 0 ak je ukazovatel neplatny, 1 ak je platny
//
//	char flag = *(char*)start;
//
//	if (flag == 0)
//	{
//		unsigned char offset0 = sizeof(char), offset1 = sizeof(unsigned char), arraysize = *(unsigned char*)(start + offset0), checksize = offset0 + offset1;
//		// Nastavenie hodnot premenyych rovnako ako v predoslych funkciach
//		char boolean = 0;																		// Premenna oznacujuca zhodu smernikov
//
//		if (ptr == NULL || (char*)ptr == (char*)start || (char*)ptr == ((char*)start + offset0))
//			// Ak je NULL, smernik smernikom na zaciatok pola alebo na hodnotu jeho velkosti, je neplatny
//			return 0;
//
//		char* header = (char*)((char*)ptr - offset1);												// Hlavicka nachadzajuca sa pred smernikom
//
//		if (*header > 0)																		// Ak je kladna, nebola alokovana, pretoze alokovane bloky maju zapornu hlavicku
//			return 0;
//
//		while (checksize < arraysize)															// Kym nie som na konci pola
//		{
//			char* testheader = (char*)((char*)start + checksize);									// Hlavicka v poli
//			if (header == testheader)															// Ak sa smerniky rovnaju, vyskocim z pola a nastavim boolean na jedna
//			{
//				boolean = 1;
//				break;
//			}
//			checksize += abs(*testheader) + 2 * offset1;
//		}
//
//		if (boolean == 0)																		// Ak sa smernik na hlavicku nenasiel, vraciam 0
//			return 0;
//
//		char* footer = (char*)((char*)ptr + abs(*header));										// Smernik na predpokladanu paticku
//
//		if (*header == *footer)																	// Hodnota hlavicky a paticky sa musia rovnat
//			return 1;																			// Ak sa rovnaju, vraciam 1
//
//		return 0;																				// Inak vraciam 0
//	}
//
//	if (flag == 1)
//	{
//		unsigned short offset0 = sizeof(char), offset1 = sizeof(unsigned short), arraysize = *(unsigned short*)(start + offset0), checksize = offset0 + offset1;
//		// Nastavenie hodnot premenyych rovnako ako v predoslych funkciach
//		short boolean = 0;																		// Premenna oznacujuca zhodu smernikov
//
//		if (ptr == NULL || (char*)ptr == (char*)start || (char*)ptr == ((char*)start + offset0))
//			// Ak je NULL, smernik smernikom na zaciatok pola alebo na hodnotu jeho velkosti, je neplatny
//			return 0;
//
//		short* header = (short*)((char*)ptr - offset1);												// Hlavicka nachadzajuca sa pred smernikom
//
//		if (*header > 0)																		// Ak je kladna, nebola alokovana, pretoze alokovane bloky maju zapornu hlavicku
//			return 0;
//
//		while (checksize < arraysize)															// Kym nie som na konci pola
//		{
//			short* testheader = (short*)((char*)start + checksize);									// Hlavicka v poli
//			if (header == testheader)															// Ak sa smerniky rovnaju, vyskocim z pola a nastavim boolean na jedna
//			{
//				boolean = 1;
//				break;
//			}
//			checksize += abs(*testheader) + 2 * offset1;
//		}
//
//		if (boolean == 0)																		// Ak sa smernik na hlavicku nenasiel, vraciam 0
//			return 0;
//
//		short* footer = (short*)((char*)ptr + abs(*header));										// Smernik na predpokladanu paticku
//
//		if (*header == *footer)																	// Hodnota hlavicky a paticky sa musia rovnat
//			return 1;																			// Ak sa rovnaju, vraciam 1
//
//		return 0;																				// Inak vraciam 0
//	}
//
//	if (flag == 2)
//	{
//		unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int), arraysize = *(unsigned int*)(start + offset0), checksize = offset0 + offset1;
//		// Nastavenie hodnot premenyych rovnako ako v predoslych funkciach
//		int boolean = 0;																		// Premenna oznacujuca zhodu smernikov
//
//		if (ptr == NULL || (char*)ptr == (char*)start || (char*)ptr == ((char*)start + offset0))
//			// Ak je NULL, smernik smernikom na zaciatok pola alebo na hodnotu jeho velkosti, je neplatny
//			return 0;
//
//		int* header = (int*)((char*)ptr - offset1);												// Hlavicka nachadzajuca sa pred smernikom
//
//		if (*header > 0)																		// Ak je kladna, nebola alokovana, pretoze alokovane bloky maju zapornu hlavicku
//			return 0;
//
//		while (checksize < arraysize)															// Kym nie som na konci pola
//		{
//			int* testheader = (int*)((char*)start + checksize);									// Hlavicka v poli
//			if (header == testheader)															// Ak sa smerniky rovnaju, vyskocim z pola a nastavim boolean na jedna
//			{
//				boolean = 1;
//				break;
//			}
//			checksize += abs(*testheader) + 2 * offset1;
//		}
//
//		if (boolean == 0)																		// Ak sa smernik na hlavicku nenasiel, vraciam 0
//			return 0;
//
//		int* footer = (int*)((char*)ptr + abs(*header));										// Smernik na predpokladanu paticku
//
//		if (*header == *footer)																	// Hodnota hlavicky a paticky sa musia rovnat
//			return 1;																			// Ak sa rovnaju, vraciam 1
//
//		return 0;																				// Inak vraciam 0
//	}
//	return 0;
//}
//
//int memory_free(void* valid_ptr) {															// vracia 0 ak sa podarilo uvolnit pamat, inak vracia 1
//
//	if (valid_ptr == NULL || memory_check(valid_ptr) == 0)									// Kontrola platnosti pointera										
//		return 1;
//
//	char flag = *(char*)start;
//
//	if (flag == 0)
//	{
//		unsigned char offset0 = sizeof(char), offset1 = sizeof(unsigned char), arraysize = *(unsigned char*)((char*)start + offset0);
//		char* header = ((char*)valid_ptr - offset1);											// Nastavenie sa na hlavicku daneho bloku
//		char temp = *(char*)((char*)header);
//		char* footer = ((char*)valid_ptr + abs(temp));											// Nastavenie sa na paticku daneho bloku
//
//		*(char*)((char*)header) = abs(*(char*)((char*)header));									// Oznacim hlavicku aj paticku kladnym cislom, co znamena, ze su volne
//		*(char*)((char*)footer) = abs(*(char*)((char*)footer));
//
//
//		if (*(char*)((char*)footer + offset1) > 0 && (char*)((char*)footer) != (char*)((char*)start + arraysize - offset1))
//			// Zlucovanie zlava doprava; vpravo je urcite iba jeden volny blok
//			// Kontrolujem hranicu pola tak, ze porovnam, ci nie je footer patickou posledneho bloku vobec
//		{
//			char newsize = *(char*)((char*)footer) + *(char*)((char*)footer + offset1) + 2 * offset1;
//			// Hodnota novej velkosti hlavicky a paticky
//			*(char*)((char*)header) = newsize;													// Nastavenie hodnoty pre hlavicku
//			footer = ((char*)valid_ptr + *(unsigned char*)((char*)header));						// Posun na novu paticku
//			*(char*)((char*)footer) = newsize;													// Nastavenie hodnoty novej paticke
//		}
//
//		if (*(char*)((char*)header - offset1) > 0 && *(char*)((char*)header - offset1) != arraysize)
//			// Zlucovanie sprava dolava; vlavo je urcite iba jeden volny blok
//			// Kontrolujem hranice pola tak, ze overim, ci hodnota zapisana pred hlavickou nie je absolutna velkost pola
//		{
//			char newsize = *(char*)((char*)header) + *(char*)((char*)header - offset1) + 2 * offset1;
//			// Hodnota novej velkosti hlavicky a paticky
//			*(char*)((char*)footer) = newsize;													// Nastavenie hodnoty pre paticku
//			header = ((char*)valid_ptr - *(char*)((char*)header - offset1) - 3 * offset1);		// Posun na novu hlavicku
//			*(char*)((char*)header) = newsize;													// Nastavenie hodnoty novej hlavicke
//		}
//		return 0;
//	}
//
//	if (flag == 1)
//	{
//		unsigned short offset0 = sizeof(char), offset1 = sizeof(unsigned short), arraysize = *(unsigned short*)((char*)start + offset0);
//		char* header = ((char*)valid_ptr - offset1);											// Nastavenie sa na hlavicku daneho bloku
//		short temp = *(short*)((char*)header);
//		char* footer = ((char*)valid_ptr + abs(temp));											// Nastavenie sa na paticku daneho bloku
//
//		*(short*)((char*)header) = abs(*(short*)((char*)header));									// Oznacim hlavicku aj paticku kladnym cislom, co znamena, ze su volne
//		*(short*)((char*)footer) = abs(*(short*)((char*)footer));
//
//
//		if (*(short*)((char*)footer + offset1) > 0 && (short*)((char*)footer) != (short*)((char*)start + arraysize - offset1))
//			// Zlucovanie zlava doprava; vpravo je urcite iba jeden volny blok
//			// Kontrolujem hranicu pola tak, ze porovnam, ci nie je footer patickou posledneho bloku vobec
//		{
//			short newsize = *(short*)((char*)footer) + *(short*)((char*)footer + offset1) + 2 * offset1;
//			// Hodnota novej velkosti hlavicky a paticky
//			*(short*)((char*)header) = newsize;													// Nastavenie hodnoty pre hlavicku
//			footer = ((char*)valid_ptr + *(unsigned short*)((char*)header));						// Posun na novu paticku
//			*(short*)((char*)footer) = newsize;													// Nastavenie hodnoty novej paticke
//		}
//
//		if (*(short*)((char*)header - offset1) > 0 && *(short*)((char*)header - offset1) != arraysize)
//			// Zlucovanie sprava dolava; vlavo je urcite iba jeden volny blok
//			// Kontrolujem hranice pola tak, ze overim, ci hodnota zapisana pred hlavickou nie je absolutna velkost pola
//		{
//			short newsize = *(short*)((char*)header) + *(short*)((char*)header - offset1) + 2 * offset1;
//			// Hodnota novej velkosti hlavicky a paticky
//			*(short*)((char*)footer) = newsize;													// Nastavenie hodnoty pre paticku
//			header = ((char*)valid_ptr - *(short*)((char*)header - offset1) - 3 * offset1);		// Posun na novu hlavicku
//			*(short*)((char*)header) = newsize;													// Nastavenie hodnoty novej hlavicke
//		}
//		return 0;
//	}
//
//	if (flag == 2)
//	{
//		unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int), arraysize = *(unsigned int*)((char*)start + offset0);
//		char* header = ((char*)valid_ptr - offset1);											// Nastavenie sa na hlavicku daneho bloku
//		int temp = *(int*)((char*)header);
//		char* footer = ((char*)valid_ptr + abs(temp));											// Nastavenie sa na paticku daneho bloku
//
//		*(int*)((char*)header) = abs(*(int*)((char*)header));									// Oznacim hlavicku aj paticku kladnym cislom, co znamena, ze su volne
//		*(int*)((char*)footer) = abs(*(int*)((char*)footer));
//
//
//		if (*(int*)((char*)footer + offset1) > 0 && (int*)((char*)footer) != (int*)((char*)start + arraysize - offset1))
//			// Zlucovanie zlava doprava; vpravo je urcite iba jeden volny blok
//			// Kontrolujem hranicu pola tak, ze porovnam, ci nie je footer patickou posledneho bloku vobec
//		{
//			int newsize = *(int*)((char*)footer) + *(int*)((char*)footer + offset1) + 2 * offset1;
//			// Hodnota novej velkosti hlavicky a paticky
//			*(int*)((char*)header) = newsize;													// Nastavenie hodnoty pre hlavicku
//			footer = ((char*)valid_ptr + *(unsigned int*)((char*)header));						// Posun na novu paticku
//			*(int*)((char*)footer) = newsize;													// Nastavenie hodnoty novej paticke
//		}
//
//		if (*(int*)((char*)header - offset1) > 0 && *(int*)((char*)header - offset1) != arraysize)
//			// Zlucovanie sprava dolava; vlavo je urcite iba jeden volny blok
//			// Kontrolujem hranice pola tak, ze overim, ci hodnota zapisana pred hlavickou nie je absolutna velkost pola
//		{
//			int newsize = *(int*)((char*)header) + *(int*)((char*)header - offset1) + 2 * offset1;
//			// Hodnota novej velkosti hlavicky a paticky
//			*(int*)((char*)footer) = newsize;													// Nastavenie hodnoty pre paticku
//			header = ((char*)valid_ptr - *(int*)((char*)header - offset1) - 3 * offset1);		// Posun na novu hlavicku
//			*(int*)((char*)header) = newsize;													// Nastavenie hodnoty novej hlavicke
//		}
//		return 0;
//	}
//	return 1;
//}
//
//
//void memory_init(void* ptr, unsigned int size) {
//	start = (char*)ptr;																			// Nastavim hodnotu globalnej premennej
//	memset(start, 0, size);																		// Nastavim hodnotu celeho pola na 0
//
//	if (size < 127)
//	{
//		unsigned char offset0 = sizeof(char), offset1 = sizeof(unsigned char);					// Nastavenie offsetov podla aktualne pouzivanych premennych
//
//		*(char*)start = 0;																		// Flag oznacujuci, ake premenne pouzivam
//		*(unsigned char*)((char*)start + offset0) = size;										// Celkova velkost
//		*(unsigned char*)((char*)start + offset0 + offset1) = (size - offset0 - 3 * offset1);	// Hlavicka jedineho volneho bloku
//		*(unsigned char*)((char*)start + size - offset1) = (size - offset0 - 3 * offset1);		// Paticka jedineho volneho bloku
//	}
//	else if (size < 32767) {
//		unsigned short offset0 = sizeof(char), offset1 = sizeof(unsigned short);				// Nastavenie offsetov podla aktualne pouzivanych premennych
//
//		*(char*)start = 1;																		// Flag oznacujuci, ake premenne pouzivam
//		*(unsigned short*)((char*)start + offset0) = size;										// Celkova velkost
//		*(unsigned short*)((char*)start + offset0 + offset1) = (size - offset0 - 3 * offset1);	// Hlavicka jedineho volneho bloku
//		*(unsigned short*)((char*)start + size - offset1) = (size - offset0 - 3 * offset1);		// Paticka jedineho volneho bloku
//	}
//	else
//	{
//		unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int);					// Nastavenie offsetov podla aktualne pouzivanych premennych
//
//		*(char*)start = 2;																		// Flag oznacujuci, ake premenne pouzivam
//		*(unsigned int*)((char*)start + offset0) = size;										// Celkova velkost
//		*(unsigned int*)((char*)start + offset0 + offset1) = (size - offset0 - 3 * offset1);	// Hlavicka jedineho volneho bloku
//		*(unsigned int*)((char*)start + size - offset1) = (size - offset0 - 3 * offset1);		// Paticka jedineho volneho bloku
//	}
//}
//
////void vypis() {
////	printf("+++++++++++++++Zaciatok funkcie vypis+++++++++++++++\n");
////	char flag = *(char*)start;
////
////	if (flag == 0)
////	{
////		unsigned char offset0 = sizeof(char), offset1 = sizeof(unsigned char);
////		printf("Flag je %d\n", *(char*)start);
////		unsigned char arraysize = *(unsigned char*)((char*)start + sizeof(char));
////		printf("Celkova velkost je %u\n", arraysize);
////
////		char check = offset0 + offset1, i = 1;
////		char temp = *(char*)((char*)start + check);
////		while (check + abs(temp) + offset1 < arraysize) {
////			printf("Hlavicka %d. bloku je %d\n", i, *(char*)((char*)start + check));
////			temp = *(unsigned char*)((char*)start + check);
////			check += abs(temp) + offset1;
////			printf("Paticka %d. bloku je %d\n", i, *(char*)((char*)start + check));
////			check += offset1;
////			i++;
////			printf("Priebezne je vyuzitych %d bajtov\n", check);
////			if (check >= arraysize - 2 * offset1)
////				break;
////			temp = *(char*)((char*)start + check);
////		}
////		printf("Zvysok na konci pola je %d\n", arraysize - check);
////	}
////
////	if (flag == 1)
////	{
////		unsigned short offset0 = sizeof(char), offset1 = sizeof(unsigned short);
////		printf("Flag je %d\n", *(char*)start);
////		unsigned short arraysize = *(unsigned short*)((char*)start + sizeof(char));
////		printf("Celkova velkost je %u\n", arraysize);
////
////		short check = offset0 + offset1, i = 1;
////		short temp = *(short*)((char*)start + check);
////		while (check + abs(temp) + offset1 < arraysize) {
////			printf("Hlavicka %d. bloku je %d\n", i, *(short*)((char*)start + check));
////			temp = *(unsigned short*)((char*)start + check);
////			check += abs(temp) + offset1;
////			printf("Paticka %d. bloku je %d\n", i, *(short*)((char*)start + check));
////			check += offset1;
////			i++;
////			printf("Priebezne je vyuzitych %d bajtov\n", check);
////			if (check >= arraysize - 2 * offset1)
////				break;
////			temp = *(short*)((char*)start + check);
////		}
////		printf("Odpad je %d\n", arraysize - check);
////	}
////
////	if (flag == 2)
////	{
////		unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int);
////		printf("Flag je %d\n", *(char*)start);
////		unsigned int arraysize = *(unsigned int*)((char*)start + sizeof(char));
////		printf("Celkova velkost je %u\n", arraysize);
////
////		int check = offset0 + offset1, i = 1;
////		int temp = *(int*)((char*)start + check);
////		while (check + abs(temp) + offset1 < arraysize) {
////			printf("Hlavicka %d. bloku je %d\n", i, *(int*)((char*)start + check));
////			temp = *(unsigned int*)((char*)start + check);
////			check += abs(temp) + offset1;
////			printf("Paticka %d. bloku je %d\n", i, *(int*)((char*)start + check));
////			check += offset1;
////			i++;
////			printf("Priebezne je vyuzitych %d bajtov\n", check);
////			if (check >= arraysize - 2 * offset1)
////				break;
////			temp = *(int*)((char*)start + check);
////		}
////		printf("Odpad je %d\n", arraysize - check);
////	}
////
////
////}
//
//float test_1(float* frag) {
//	//Test 1: Bloky rovnekj velkosti 8 az 24
//
//	char region[t50];
//	int test = t50;
//
//	memory_init(region, test);
//
//	int min = 8, max = 24, i = 0;
//
//	int size = (rand() % (max - min + 1)) + min;
//
//	char* x;
//
//	do
//	{
//		x = (char*)memory_alloc(size);
//		i++;
//	} while (x != NULL);
//
//	int real = (i - 1) * size;
//	float ratio = 100 * (float)real / test;
//
//	//printf("Celkova velkost: %d\n", test);
//	//printf("Velkost bloku: %d\n", size);
//	//printf("Alokovane: %d\n", real);
//	//printf("Uspesnost: %2.2f%%\n", ratio);
//
//	char flag = *(char*)start;
//	int offset1 = 0;
//	if (flag == 0)
//		offset1 = 1;
//	if (flag == 1)
//		offset1 = 2;
//	if (flag == 2)
//		offset1 = 4;
//
//	i--;
//	int fragm = 1 + offset1 + i * 2 * offset1;
//	*frag = 100 * (float)fragm / test;
//	//printf("Na reziu je pouzitych %d bajtov\n", fragm);
//
//	return ratio;
//}
//
//float test_2(float* frag) {
//	//Test 2: Bloky NErovnakej velkosti 8 az 24
//
//	char region[t50];
//	int test = t50;
//
//	memory_init(region, test);
//
//	int min = 8, max = 24, i = 0, total = 0, size;
//	char* x;
//
//	do
//	{
//		size = (rand() % (max - min + 1)) + min;
//		x = (char*)memory_alloc(size);
//		total += size;
//		i++;
//	} while (x != NULL);
//
//	total -= size;
//
//	float ratio = 100 * (float)total / test;
//
//	//printf("Celkova velkost: %d\n", test);
//	//printf("Alokovane: %d\n", total);
//	//printf("Uspesnost: %2.2f%%\n", ratio);
//
//	char flag = *(char*)start;
//	int offset1 = 0;
//	if (flag == 0)
//		offset1 = 1;
//	if (flag == 1)
//		offset1 = 2;
//	if (flag == 2)
//		offset1 = 4;
//
//	i--;
//	int fragm = 1 + offset1 + i * 2 * offset1;
//	*frag = 100 * (float)fragm / test;
//	//printf("Na reziu je pouzitych %d bajtov\n", fragm);
//
//	return ratio;
//}
//
//float test_3(float* frag) {
//	//Test 3: Bloky NErovnakej velkosti 500 az 5000
//
//	char region[t10k];
//	int test = t10k;
//
//	memory_init(region, test);
//
//	int min = 500, max = 5000, i = 0, total = 0, size;
//	char* x;
//
//	do
//	{
//		size = (rand() % (max - min + 1)) + min;
//		//printf("Pokusam sa alokovat: %d\n", size);
//		x = (char*)memory_alloc(size);
//		total += size;
//		i++;
//	} while (x != NULL);
//
//	total -= size;
//
//	float ratio = 100 * (float)total / test;
//
//	//printf("Celkova velkost: %d\n", test);
//	//printf("Alokovane: %d\n", total);
//	//printf("Uspesnost: %2.2f%%\n", ratio);
//
//	char flag = *(char*)start;
//	int offset1 = 0;
//	if (flag == 0)
//		offset1 = 1;
//	if (flag == 1)
//		offset1 = 2;
//	if (flag == 2)
//		offset1 = 4;
//
//	i--;
//	int fragm = 1 + offset1 + i * 2 * offset1;
//	*frag = 100 * (float)fragm / test;
//	//printf("Na reziu je pouzitych %d bajtov\n", fragm);
//
//	return ratio;
//}
//
//float test_4(float* frag) {
//	//Test 4: Bloky NErovnakej velkosti 8 az 50000
//
//	char region[t1m];
//	int test = t1m;
//
//	memory_init(region, test);
//
//	int min = 8, max = 50000, i = 0, total = 0, size;
//	char* x;
//
//	do
//	{
//		size = (rand() % (max - min + 1)) + min;
//		//printf("Pokusam sa alokovat: %d\n", size);
//		x = (char*)memory_alloc(size);
//		total += size;
//		i++;
//	} while (x != NULL);
//
//	total -= size;
//
//	float ratio = 100 * (float)total / test;
//
//	//printf("Celkova velkost: %d\n", test);
//	//printf("Alokovane: %d\n", total);
//	//printf("Uspesnost: %2.2f%%\n", ratio);
//
//	char flag = *(char*)start;
//	int offset1 = 0;
//	if (flag == 0)
//		offset1 = 1;
//	if (flag == 1)
//		offset1 = 2;
//	if (flag == 2)
//		offset1 = 4;
//
//	i--;
//	int fragm = 1 + offset1 + i * 2 * offset1;
//	*frag = 100 * (float)fragm / test;
//	//printf("Na reziu je pouzitych %d bajtov\n", fragm);
//
//	return ratio;
//}
//
//int fragmentation() {
//	char flag = *(char*)start;
//	int free_block = 0;
//
//	if (flag == 0)
//	{
//		unsigned char offset0 = sizeof(char), offset1 = sizeof(unsigned char);
//		unsigned char arraysize = *(unsigned char*)((char*)start + sizeof(char));
//
//		char check = offset0 + offset1, i = 1;
//		char temp = *(char*)((char*)start + check);
//		while (check + abs(temp) + offset1 < arraysize) {
//			if (*(char*)((char*)start + check) > 0)
//			{
//				free_block += *(char*)((char*)start + check);
//			}
//			temp = *(unsigned char*)((char*)start + check);
//			check += abs(temp) + offset1;
//			check += offset1;
//			i++;
//			if (check >= arraysize - 2 * offset1)
//				break;
//			temp = *(char*)((char*)start + check);
//		}
//	}
//
//	if (flag == 1)
//	{
//		unsigned short offset0 = sizeof(char), offset1 = sizeof(unsigned short);
//		unsigned short arraysize = *(unsigned short*)((char*)start + sizeof(char));
//
//		short check = offset0 + offset1, i = 1;
//		short temp = *(short*)((char*)start + check);
//		while (check + abs(temp) + offset1 < arraysize) {
//			if (*(short*)((char*)start + check) > 0)
//			{
//				free_block += *(short*)((char*)start + check);
//			}
//			temp = *(unsigned short*)((char*)start + check);
//			check += abs(temp) + offset1;
//			check += offset1;
//			i++;
//			if (check >= arraysize - 2 * offset1)
//				break;
//			temp = *(short*)((char*)start + check);
//		}
//	}
//
//	if (flag == 2)
//	{
//		unsigned int offset0 = sizeof(char), offset1 = sizeof(unsigned int);
//		unsigned int arraysize = *(unsigned int*)((char*)start + sizeof(char));
//
//		int check = offset0 + offset1, i = 1;
//		int temp = *(int*)((char*)start + check);
//		while (check + abs(temp) + offset1 < arraysize) {
//			if (*(int*)((char*)start + check) > 0)
//			{
//				free_block += *(int*)((char*)start + check);
//			}
//			temp = *(unsigned int*)((char*)start + check);
//			check += abs(temp) + offset1;
//			check += offset1;
//			i++;
//			if (check >= arraysize - 2 * offset1)
//				break;
//			temp = *(int*)((char*)start + check);
//		}
//	}
//	return free_block;
//}
//
//float test_fragmentacie() {
//	// Bloky NErovnakej velkosti 8 az 256
//	char region[t10k];
//	int test = t10k;
//
//	memory_init(region, test);
//
//	int min = 8, max = 256, i = 0, total = 0, size;
//	char* x = NULL, * y = NULL, * z = NULL;
//
//	do
//	{
//		if (memory_check(x))
//			memory_free(x);
//		if (memory_check(y))
//			memory_free(y);
//
//		size = (rand() % (max - min + 1)) + min;
//		x = (char*)memory_alloc(size);
//		total += size;
//
//		size = (rand() % (max - min + 1)) + min;
//		y = (char*)memory_alloc(size);
//		total += size;
//
//		size = (rand() % (max - min + 1)) + min;
//		z = (char*)memory_alloc(size);
//		total += size;
//
//		i++;
//	} while (x != NULL || y != NULL || z != NULL);
//
//	float fragm = 100 * fragmentation() / (float)test;
//	return fragm;
//}
//
//int main() {
//
//	float average1 = 0, average2 = 0, average3 = 0, average4 = 0, globalaverage = 0;
//	float frag1 = 0, frag2 = 0, frag3 = 0, frag4 = 0, globalfrag = 0, globalfrag1 = 0, globalfrag2 = 0, globalfrag3 = 0, globalfrag4 = 0;
//
//	average1 = test_1(&frag1);
//	average2 = test_2(&frag2);
//	average3 = test_3(&frag3);
//	average4 = test_4(&frag4);
//	printf("Vysledky testov s konstantnym seedom\n");
//	printf("Priemerna uspesnost pre bloky rovnakych malych velkosti je: %2.2f%% s fragmentaciou %2.2f%%\n", average1, frag1);
//	printf("Priemerna uspesnost pre bloky NErovnakych malych velkosti je: %2.2f%% s fragmentaciou %2.2f%%\n", average2, frag2);
//	printf("Priemerna uspesnost pre bloky NErovnakych velkych velkosti je: %2.2f%% s fragmentaciou %2.2f%%\n", average3, frag3);
//	printf("Priemerna uspesnost pre bloky NErovnakych zmiesanych velkosti je: %2.2f%% s fragmentaciou %2.2f%%\n", average4, frag4);
//	globalaverage = (average1 + average2 + average3 + average4) / 4;
//	globalfrag = (frag1 + frag2 + frag3 + frag4) / 4;
//	printf("Celkova priemerna uspesnost je: %2.2f%% s celkovou priemernou fragmentaciou %2.2f%%\n", globalaverage, globalfrag);
//
//	printf("Velkost vonkajsej fragmentacie je %2.2f%%\n", test_fragmentacie());
//
//	printf("\nVysledky testov s NEkonstantnym seedom\n");
//	srand(time(0));
//	int count = 1000;
//	average1 = 0, average2 = 0, average3 = 0, average4 = 0, globalaverage = 0;
//	frag1 = 0, frag2 = 0, frag3 = 0, frag4 = 0, globalfrag = 0;
//
//	for (int i = 0; i < count; i++)
//	{
//		average1 += test_1(&frag1);
//		globalfrag1 += frag1;
//	}
//	average1 /= count;
//	globalfrag1 /= count;
//	printf("Priemerna uspesnost pre bloky rovnakych malych velkosti je: %2.2f%% s fragmentaciou %2.2f%%\n", average1, globalfrag1);
//
//	for (int i = 0; i < count; i++)
//	{
//		average2 += test_2(&frag2);
//		globalfrag2 += frag2;
//	}
//	average2 /= count;
//	globalfrag2 /= count;
//	printf("Priemerna uspesnost pre bloky NErovnakych malych velkosti je: %2.2f%% s fragmentaciou %2.2f%%\n", average2, globalfrag2);
//
//	for (int i = 0; i < count; i++)
//	{
//		average3 += test_3(&frag3);
//		globalfrag3 += frag3;
//	}
//	average3 /= count;
//	globalfrag3 /= count;
//	printf("Priemerna uspesnost pre bloky NErovnakych velkych velkosti je: %2.2f%% s fragmentaciou %2.2f%%\n", average3, globalfrag3);
//
//	for (int i = 0; i < count; i++)
//	{
//		average4 += test_4(&frag4);
//		globalfrag4 += frag4;
//	}
//	average4 /= count;
//	globalfrag4 /= count;
//	printf("Priemerna uspesnost pre bloky NErovnakych zmiesanych velkosti je: %2.2f%% s fragmentaciou %2.2f%%\n", average4, globalfrag4);
//
//	globalaverage = (average1 + average2 + average3 + average4) / 4;
//	globalfrag = (globalfrag1 + globalfrag2 + globalfrag3 + globalfrag4) / 4;
//	printf("Celkova priemerna uspesnost je: %2.2f%% s celkovou priemernou fragmentaciou %2.2f%%\n", globalaverage, globalfrag);
//
//	float fragm = 0;
//	for (int i = 0; i < count; i++)
//	{
//		fragm += test_fragmentacie();
//	}
//
//	printf("Priemerna velkost vonkajsej fragmentacie je %2.2f%%\n", fragm / count);
//
//	return 0;
//}
