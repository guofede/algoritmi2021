#ifndef EDIT_DISTANCE_DWAWDAsdfadawd
#define EDIT_DISTANCE_DWAWDAsdfadawd
/*
*	@input : s1 è una string(char *) non NULL
*	@input : s2 è una string(char *) non NULL
*	questa funzione ritorna la quantità minima di edit(inserimento, cancellazione di caratteri) che distinguono le due stringhe s1, s2.
*	se uno dei due parametri è NULL la funzione esegue un exit() (vedi https://man7.org/linux/man-pages/man3/exit.3.html )
*	nel caso peggiore l'algoritmo ha complessità O(2^n), con n = lunghezza s1 + lunghezza s2;
*/
unsigned int edit_distance(char *s1, char *s2);

/*
*	@input : s1 è una string(char *) non NULL
*	@input : s2 è una string(char *) non NULL
*	questa funzione ritorna la quantità minima di edit(inserimento, cancellazione di caratteri) che distinguono le due stringhe s1, s2.
*	se uno dei due parametri è NULL la funzione esegue un exit() (vedi https://man7.org/linux/man-pages/man3/exit.3.html )
*	nel caso peggiore l'algoritmo ha complessità O(n^2), con n = lunghezza s1 + lunghezza s2;
*/
unsigned int edit_distance_dyn(char *s1, char *s2);
#endif