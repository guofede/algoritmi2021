#ifndef MERGE_BINARYINSERTION_SORT_efeoifjeDEDAfsfsf
#define MERGE_BINARYINSERTION_SORT_efeoifjeDEDAfsfsf

/*
*	@input array ,array di puntatori
*	@input size, dimensione dell'array
*	@input compare funzione di comparazione definito come int [function](void *,void *)
*		la funzione prende come input due (void *) e ritorna un intero <0 se il primo elemento è minore del secondo,
		0 se i due elementi sono uguali, >0 se il primo è maggiore del secondo.
*	la funzione riordina un array di tipo generico di dimensione size passata come parametro
*	secondo un criterio compare definito dall'utente
*	tale criterio deve accettare due puntatori a elementi dell'array e
*	deve ritornare un valore diverso da 0 se il primo elemento precede il secondo, 0 altrimenti
*/
void merge_binaryinsertion_sort(void **array, unsigned int size, int (*compare)(void *, void *));

#endif