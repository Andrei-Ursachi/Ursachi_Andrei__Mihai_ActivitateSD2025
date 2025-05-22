#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

#define CAPACITATE_STOCARE_HEAP 10


int* realocare_structura_heap(int* heap_agregat, unsigned char* capacitate_heap_agregat, unsigned char nr_eleme_aditionale)
{
	unsigned char nr_chei = *capacitate_heap_agregat;
	*capacitate_heap_agregat += nr_eleme_aditionale;
	int* new_heap = malloc(*capacitate_heap_agregat * sizeof(int));

	for (unsigned char i = 0; i < nr_chei; i++)
	{
		new_heap[i] = heap_agregat[i];
	}

	free(heap_agregat);
	return new_heap;
}

int* agregare_structuri_heap(int cheie_noua, int* heap1, unsigned char size_heap1,
	int* heap2, unsigned char size_heap2,
	int* heap_agregat, unsigned char* size_heap_agregat,
	unsigned char* capacitate_heap_agregat)
{
	heap_agregat = malloc(*capacitate_heap_agregat * sizeof(int));

	unsigned char i = 0;
	unsigned char j = 0;
	unsigned char k = 0;

	heap_agregat[k++] = cheie_noua;
	*size_heap_agregat += 1;

	if (size_heap1 < size_heap2)
	{
		int* paux = heap1;
		heap1 = heap2;
		heap2 = paux;

		unsigned char daux = size_heap1;
		size_heap1 = size_heap2;
		size_heap2 = daux;
	}

	unsigned char nr_h = 1;
	unsigned char gata = 1;
	while (gata)
	{
		unsigned char l = i;
		for (; i < size_heap1 && i < nr_h + l; i++)
		{
			heap_agregat[k++] = heap1[i];
			*size_heap_agregat += 1;
			if (*size_heap_agregat == *capacitate_heap_agregat)
			{
				heap_agregat = realocare_structura_heap(heap_agregat, capacitate_heap_agregat,
					CAPACITATE_STOCARE_HEAP);
			}
		}


		for (; j < size_heap2 && j < nr_h + l; j++)
		{
			heap_agregat[k++] = heap2[j];
			*size_heap_agregat += 1;
			if (*size_heap_agregat == *capacitate_heap_agregat)
			{
				heap_agregat = realocare_structura_heap(heap_agregat, capacitate_heap_agregat,
					CAPACITATE_STOCARE_HEAP);
			}
		}

		if (i >= size_heap1 && j >= size_heap2)
			gata = 0;
		nr_h = nr_h * 2;
	}


	return heap_agregat;
}

int main()
{
	int struct_heap1[] = { 32, 12, 24, 7, 9, 17 };
	int struct_heap2[] = { 8, 2, 3 };

	int* heap_rezultat = NULL;
	unsigned char capacitate_heap = CAPACITATE_STOCARE_HEAP;
	unsigned char nr_noduri_heap = 0;

	heap_rezultat = agregare_structuri_heap(23, struct_heap2, sizeof(struct_heap2) / sizeof(int),
		struct_heap1, sizeof(struct_heap1) / sizeof(int),
		heap_rezultat, &nr_noduri_heap, &capacitate_heap);

	printf("Vector structura heap dupa agregare: ");
	for (unsigned char i = 0; i < nr_noduri_heap; i++)
	{
		printf("%d ", heap_rezultat[i]);
	}
	printf("\n");

	return 0;
}