#include <stdlib.h>
#include <stdio.h>
#include "merge_binaryinsertion_sort.h"

#define BINARY_INSERTION_CONST 10

/*
*	@input array, array formato da due sottoarray ordinati A[0..pivot-1],A[pivot...size-1]
*	@input pivot, indice perno che divide i due sottoarray ordinati A[0..pivot-1],A[pivot...size-1]
*	@input size, dimensione dell'array
*	@input compare funzione di comparazione definito come int [function](void *,void *)
*		la funzione prende come input due (void *) e ritorna un intero <0 se il primo elemento è minore del secondo,
		0 se i due elementi sono uguali, >0 se il primo è maggiore del secondo.
*	questa funzione ordina un array formato da due sottoarray ordinati A[0..pivot-1],A[pivot...size-1] secondo il criterio compare.
*/
static void merge(void **array, unsigned int pivot, unsigned int size, int (*compare)(void*,void*));

/*
*	@input array, array non ordinato
*	@input size, dimensione dell'array
*	@input compare funzione di comparazione definito come int [function](void *,void *)
*		la funzione prende come input due (void *) e ritorna un intero <0 se il primo elemento è minore del secondo,
		0 se i due elementi sono uguali, >0 se il primo è maggiore del secondo.
*	questa funzione ordina l'array secondo il criterio compare
*/
static void binaryinsertion_sort(void **array, unsigned int size, int (*compare)(void*,void*));

/*
*	@input array, array da riordinare
*	@input n_elem, dimensione dell'array
*	@input compare funzione di comparazione definito come int [function](void *,void *)
*		la funzione prende come input due (void *) e ritorna un intero <0 se il primo elemento è minore del secondo,
		0 se i due elementi sono uguali, >0 se il primo è maggiore del secondo.
*	questa funzione ritorna la posizione corretta di array[n_elem] all'interno del sottoarray[0...n_elem]
*/
static unsigned int binaryinsertion_search_pos(void **array,unsigned int n_elem, int (*compare)(void*,void*));

void merge_binaryinsertion_sort(void **array,unsigned int size, int (*compare)(void*,void*)){
	if(array == NULL){
		fprintf(stderr, "merge_binaryinsertion_sort : the array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(compare == NULL){
		fprintf(stderr, "merge_binaryinsertion_sort : the compare function parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(size<2){
		return;
	}else if(size <= BINARY_INSERTION_CONST){
		binaryinsertion_sort(array, size, compare);
	}else{
		unsigned int mid = size/2;
		merge_binaryinsertion_sort(array, mid, compare);
		merge_binaryinsertion_sort(array+mid, size-mid, compare);
		merge(array, mid, size, compare);
	}
}

static void merge(void **array,unsigned int pivot,unsigned int size, int (*compare)(void *, void*)){
	unsigned int i, j, k;
	void **buf;
	if(array == NULL){
		fprintf(stderr, "merge : the array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(compare == NULL){
		fprintf(stderr, "merge : the compare function parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(pivot>size){
		fprintf(stderr, "merge : parameter pivot cannot be bigger than parameter size");
		exit(EXIT_FAILURE);
	}
	buf = malloc(sizeof(void*)*size);
	if(buf == NULL){
		fprintf(stderr, "merge : (malloc) unable to allocate temporary array");
		exit(EXIT_FAILURE);
	}
	k = i = 0;
	j = pivot;
	while(i<pivot && j<size){
		if(compare(array[i],array[j])<0){
			buf[k++] = array[i++];
		}else{
			buf[k++] = array[j++];
		}
	}
	if(i<pivot){
		for(unsigned int aus = 0; i<pivot; aus++, i++){
			array[k+aus] = array[i];
		}
	}
	for(i=0; i<k; i++){
		array[i] = buf[i];
	}
	free(buf);
}

static void binaryinsertion_sort(void **array, unsigned int size, int (*compare)(void*,void*)){
	if(array == NULL){
		fprintf(stderr, "binaryinsertion_sort : the array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(compare == NULL){
		fprintf(stderr, "binaryinsertion_sort : the compare function parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(size<2){
		return;
	}else{
		unsigned int i,j, pos;
		void *aus;
		for(i=1;i<size;i++){
			aus = array[i];
			pos = binaryinsertion_search_pos(array, i, compare);
			for(j=i;j>pos;j--){
				array[j] = array[j-1];
			}
			array[pos] = aus;
		}
		return;
	}
}

static unsigned int binaryinsertion_search_pos(void **array, unsigned int pos_elem, int (*compare)(void*,void*)){
	if(array == NULL){
		fprintf(stderr, "binaryinsertion_search_pos : the array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(compare == NULL){
		fprintf(stderr, "binaryinsertion_search_pos : the compare function parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	unsigned int bin_ref , first, last;
	int compare_value;
	first = 0;
	last = pos_elem;
	while(first<last){
		bin_ref = (last+first)/2;
		compare_value = compare(array[pos_elem],array[bin_ref]);
		if(compare_value==0){
			return bin_ref + 1;
		}else if(compare_value<1){
			last = bin_ref;
		}else{
			first = ++bin_ref;
		}
	}
	return first;
}