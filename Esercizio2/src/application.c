/*application*/
#define CHECK(ptr, print) if(ptr == NULL){fprintf(stderr, print); exit(EXIT_FAILURE);}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "edit_distance.h"

/*array di puntatori a stringhe(parole di dictionary.txt)*/
char **dictionary;
/*array di puntatori a stringhe(parole del file argv[1])*/
char **text_words;
/*
*	@input : file è il pathname del file
*	questa funzione carica in dictionary il contenuto del file specificato in input
*	il file deve contenere una parola per linea
*/
static unsigned long load_dictionary(char *file);
/*
*	@input : file è il pathname del file
*	questa funzione carica in text_words le parole della prima riga del file specificato in input
*/
static unsigned int load_text(char *file);
/*
*	@input : size_text numero di parole di text_words da confrontare
*	@input : size_dictionary numero di parole del dizionario
*	questa funzione stampa, per ogni parola di text_words la lista delle parole in dictionary con edit distance minima
*/
static void test_distance(unsigned int size_text, unsigned int size_dictionary);
/*
*	@input : size_text dimensione array text_words
*	@input : size_dictionary dimensione array dictionary
*	questa funziona disalloca lo spazio occupato dagli array dictionary e text_words.
*/
static void free_string_arrays(unsigned int size_text, unsigned int size_dictionary);
/*
*	@input : str è una stringa
*	questa funzione converte l'input in formato lowercase
*/
static void to_lower(char *str);

int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr, "main : file argument must be specified");
		exit(EXIT_FAILURE);
	}
	unsigned long dictionary_size;
	unsigned int text_words_size;
	dictionary_size = load_dictionary("dictionary.txt");
	text_words_size = load_text(argv[1]);
	
	test_distance(text_words_size,dictionary_size);
	free_string_arrays(text_words_size,dictionary_size);
}

static unsigned long load_dictionary(char *file){
	FILE *fp;
	char buf[1024];
	unsigned long size = 0, capacity = 2;
	fp = fopen(file, "r");
		CHECK(fp,"load_dictionary : unable to open file")
	dictionary = malloc(capacity * sizeof(char *));
		CHECK(dictionary,"load_dictionary : unable to allocate dictionary")
	while(fgets(buf, 1024, fp) != NULL){
		strtok(buf, "\n");
		if(size==capacity){
			capacity = capacity * 2;
			dictionary = realloc(dictionary, capacity * sizeof(char *));
				CHECK(dictionary,"load_dictionary : unable to expand dictionary")
		}
		char *word = malloc(strlen(buf)+1);
			CHECK(word ,"load_dictionary : unable to allocate word")
		strcpy(word, buf);
		dictionary[size] = word;
		size++;
	}
	fclose(fp);
	return size;
}

static unsigned int load_text(char *file){
	FILE *fp;
	char buf[1024], *token, *word;
	unsigned int capacity = 2, size = 0;
	fp = fopen(file, "r");
	CHECK(fp , "load_text : unable to open file")
	if(fgets(buf, 1024, fp) == NULL){
		fprintf(stderr, "load_text : unable to read file");
		exit(EXIT_FAILURE);
	}
	text_words = malloc(capacity*sizeof(char *));
		CHECK(text_words , "load_text : unable to allocate array")
	token = strtok(buf, ",;:. \n");
	word = malloc((strlen(token)+1)*sizeof(char));
		CHECK(word, "load_text : unable to allocate word")
	strcpy(word,token);
	text_words[size] = word;
	size++;
	while((token = strtok(NULL, ",;:. \n")) != NULL){
		if(size == capacity){
			capacity = capacity*2;
			text_words = realloc(text_words, capacity*sizeof(char *));
				CHECK(text_words ,"load_text : unable to reallocate array")
		}
		word = malloc((strlen(token)+1)*sizeof(char));
			CHECK(word, "load_text : unable to allocate word")
		strcpy(word,token);
		text_words[size] = word;
		size++;
	}
	fclose(fp);
	return size;
}

static void test_distance(unsigned int size_text, unsigned int size_dictionary){
	unsigned int *buf, min;
	clock_t begin, end;
	double diff;
	buf = malloc(size_dictionary*sizeof(unsigned int));
		CHECK(buf,"test_distance : unable to allocate buffer")
	for(unsigned int i = 0; i<size_text; i++){
		begin = clock();
		for(unsigned int j = 0; j<size_dictionary; j++){
			char * word = malloc((strlen(text_words[i]) + 1) * sizeof(char));
				CHECK(word, "test_distance : unable to allocate word");
			strcpy(word, text_words[i]);
			to_lower(word);
			buf[j] = edit_distance_dyn(word, dictionary[j]);
			free(word);
		}
		end = clock();
		diff =  (double) (end - begin) / CLOCKS_PER_SEC;
		min = buf[0];
		for(unsigned int j = 0; j<size_dictionary; j++){
			if(buf[j]<min)
				min = buf[j];
		}
		printf("%s : edit_distance_dyn minima %d. tempo ricerca %f\n", text_words[i], min, diff);
		fflush(stdout);
		for(unsigned int j = 0; j<size_dictionary; j++){
			if(buf[j] == min){
				printf("%s\n", dictionary[j]);
				fflush(stdout);
			}
		}
	}
	free(buf);
}

static void free_string_arrays(unsigned int size_text, unsigned int size_dictionary){
	for(unsigned int i = 0; i<size_text;i++){
		free(text_words[i]);
	}
	for(unsigned int i = 0; i<size_dictionary; i++){
		free(dictionary[i]);
	}
	free(text_words);
	free(dictionary);
}

static void to_lower(char *str){
	for(unsigned int i = 0; i < strlen(str); i++){
		if(str[i] <= 'Z' && str[i] >= 'A')
			str[i] =(char) (str[i] +'a'-'A');
	}
}