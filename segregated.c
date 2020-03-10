//#include <stdio.h>
//
//char* zaciatok;
//
//int memory_free(void* valid_ptr) {
//
//}
//
//int memory_check(void* ptr) {
//	// vo funkcii dostanem vzdy iba pointer na validny alekovany alebo nealokovany blok
//	// nikdy nie pointer do stredu prazdna, lebo bz som nevedel zistit, ci som v poli
//
//	//posunies sa o jedna dolava a skontrolujes a posunies sa k paticke a skontrolujes aj ju
//}
//
//void* memory_alloc(unsigned int size) {
//
//}
//
//void memory_init(void* ptr, unsigned int size) {
//	zaciatok = (char*)ptr;
//	for (int i = 0; i < size; i++)
//	{
//		zaciatok[i] = 0;
//	}
//
//	*(char*)zaciatok = 0;
//	printf("Flag je %d\n", *(char*)zaciatok);
//
//	*(unsigned int*)((char*)zaciatok + sizeof(char)) = size;
//	printf("Celkova velkost je %u\n", *(unsigned int*)((char*)zaciatok + sizeof(char)));
//
//	*(unsigned int*)((char*)zaciatok + sizeof(char) + sizeof(unsigned int)) = 0;
//	printf("Zoznam 1 je %u\n", *(unsigned int*)((char*)zaciatok + sizeof(char) + sizeof(unsigned int)));
//
//	*(unsigned int*)((char*)zaciatok + sizeof(char) + 2 * sizeof(unsigned int)) = sizeof(char) + 4 * sizeof(unsigned int);
//	printf("Zoznam 2 je %u\n", *(unsigned int*)((char*)zaciatok + sizeof(char) + 2 * sizeof(unsigned int)));
//
//	*(unsigned int*)((char*)zaciatok + sizeof(char) + 3 * sizeof(unsigned int)) = -1 * (size - sizeof(char) - 5 * sizeof(unsigned int));
//	printf("Hlavicka bloku je %d\n", *(unsigned int*)((char*)zaciatok + sizeof(char) + 3 * sizeof(unsigned int)));
//
//	*(unsigned int*)((char*)zaciatok + size - sizeof(unsigned int))= -1 * (size - sizeof(char) - 5 * sizeof(unsigned int));
//	printf("Paticka bloku je %d\n", *(unsigned int*)((char*)zaciatok + size - sizeof(unsigned int)));
//
//	// log so zakladom 2 hodnoty size, -3 je pocet blokov zoznamu
//
//}
//
//int main() {
//	
//	char region[50];
//	memory_init(region, 50);
//
//	printf("smernik %p\n", zaciatok);
//	printf("pole %p\n", region);
//
//	return 0;
//}