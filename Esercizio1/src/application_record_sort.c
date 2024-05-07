#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge_binaryinsertion_sort.h"

struct record{
	int id;
	char *field1;
	int field2;
	double field3;
};

/*
*	the function generate an array of pointers to struct record that are written in the file <pathname> as string of format
*	"<id>,<string>,<integer>,<float>"
*	if the function successfully load the entire file into the array, it returns the array and the size in the int pointer size_p,
*	if the function fail, it prints the error and terminates the process.
*/
struct record ** load_array(unsigned int *size_p, char *pathname);

/*
*	the function free the memory dinamically allocated for the array, the records and the string fields
*/
void free_array(struct record **array, unsigned int size);

#ifdef PRINT_ARRAY
/*
*	the function print on terminal 
*/
void print_array(struct record **array, unsigned int size);
#endif
/*esegue il test con il criterio di ordinamento passato*/
void test_sort_with_compare(char *file_pathname, int (*compare)(void*,void*));

/*criteri di ordinamento per campi di record*/
int compare_record_field1_string(void*,void*);
int compare_record_field2_int(void*,void*);
int compare_record_field3_float(void*,void*);



int compare_record_field1_string(void* el1, void* el2){
	char *str1, *str2;
	str1 = ((struct record *) el1)->field1;
	str2 = ((struct record *) el2)->field1;
	return strcmp(str1,str2);
}

int compare_record_field2_int(void* el1, void* el2){
	int int1, int2;
	int1 = ((struct record *) el1)->field2;
	int2 = ((struct record *) el2)->field2;
	return int1-int2;
}

int compare_record_field3_float(void* el1, void* el2){
	double float1, float2;
	float1 = ((struct record *) el1)->field3;
	float2 = ((struct record *) el2)->field3;
	if(float1 == float2)
		return 0;
	if(float1<float2)
		return -1;
	return 1;
}
#ifdef PRINT_ARRAY
void print_array(struct record **array, unsigned int size){
	if(array == NULL){
		fprintf(stderr,"print_array : array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	unsigned int i = 0;
	for(i = 0; i<size; i++){
		printf("%d,	%s,	%d,	%f\n", array[i]->id, array[i]->field1,array[i]->field2,array[i]->field3);
	}
}
#endif
void free_array(struct record **array, unsigned int size){
	if(array == NULL){
		fprintf(stderr, "free_array : array parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	unsigned int i;
	for(i = 0; i<size; i++){
		free(array[i]->field1);
		free(array[i]);
	}
	free(array);
}

struct record ** load_array(unsigned int *size, char *file_pathname){
	struct record **array;
	char buf[1024];
	char *read_line_p, *tokens[4], *str_field1;
	unsigned int max_size = 2;
	int buf_size = 1024, int_field2, int_id;
	double float_field3;
	FILE *fp;
	struct record *rec_p;
	
	array = malloc(2*sizeof(struct record *));
	if(array == NULL){
		fprintf(stderr,"load_array : unable to allocate array");
		exit(EXIT_FAILURE);
	}
	fp = fopen(file_pathname, "r");
	*size = 0;
	if(fp == NULL){
		fprintf(stderr,"load_file : unable to open the file");
		exit(EXIT_FAILURE);
	}
	
	while(fgets(buf,buf_size,fp) != NULL){
		if(*size>=max_size){
			max_size = max_size*2;
			array = realloc(array, sizeof(void *)*max_size);
			if(array == NULL){
				fprintf(stderr,"load_array : unable to expand array size");
				exit(EXIT_FAILURE);
			}
		}
		read_line_p = malloc((strlen(buf)+1)*sizeof(char));
		if(read_line_p == NULL){
			fprintf(stderr,"load_array : unable to allocate tokens");
			exit(EXIT_FAILURE);
		}
		strcpy(read_line_p, buf);
		tokens[0] = strtok(read_line_p,",");
		if (tokens[0] == NULL){
				fprintf(stderr,"load_array : tokens not read");
				exit(EXIT_FAILURE);
			}
		for(int i = 1; i<4; i++){
			tokens[i] = strtok(NULL,",");
			if (tokens[i] == NULL){
				fprintf(stderr,"load_array : tokens not read");
				exit(EXIT_FAILURE);
			}
		}
		str_field1 = malloc((strlen(tokens[1])+1)*sizeof(char));
		if(str_field1 == NULL){
			fprintf(stderr, "load_array : unable to allocate field1 string");
			exit(EXIT_FAILURE);
		}
		strcpy(str_field1, tokens[1]);
		int_id = atoi(tokens[0]);
		int_field2 = atoi(tokens[2]);
		float_field3 = atof(tokens[3]);
		rec_p = malloc(sizeof(struct record));
		if(rec_p == NULL){
			fprintf(stderr, "load_array : unable to allocate record");
			exit(EXIT_FAILURE);
		}
		rec_p->id = int_id;
		rec_p->field1 = str_field1;
		rec_p->field2 = int_field2;
		rec_p->field3 = float_field3;
		array[*size] = rec_p;
		
		(*size)++;
		free(read_line_p);
	}
	
	fclose(fp);
	return array;
}

void test_sort_with_compare(char *file_pathname, int (*compare)(void*,void*)){
	struct record **array = NULL;
	unsigned int size = 0;
	double diff;
	clock_t begin, end;
	array = load_array(&size, file_pathname);
	fprintf(stderr,"test : array loaded\n");
	fflush(stderr);
	begin = clock();
	merge_binaryinsertion_sort((void **) array, size, compare);
	end = clock();
	diff =  (double) (end - begin) / CLOCKS_PER_SEC;
	fprintf(stderr,"test : array sorted in : %f seconds\n", diff);
	fflush(stderr);
#ifdef PRINT_ARRAY
	print_array(array,size);
#endif
	free_array(array,size);
	fprintf(stderr,"test : array cleaned\n");
	fflush(stderr);
}

int main(int argc, char *argv[]){
	if(argc <2){
		fprintf(stderr, "application main : execution must have at least one parameter");
		exit(EXIT_FAILURE);
	}
	test_sort_with_compare(argv[1], compare_record_field1_string);
	test_sort_with_compare(argv[1], compare_record_field2_int);
	test_sort_with_compare(argv[1], compare_record_field3_float);
}