/*exercise 2 edit_distance library*/
/*
*	se card(s1) = 0 -> e_d ret s2
*	se card(s2) = 0 -> e_d ret s1
* 	se s1[0] == s2[0] distance_no_op = edit_distance(s1+1, s2+1)
*		altrimenti
*	si ha edit_distance = min(dcanc, dins); con
*	dcanc = 1 + edit_distance(s1+1,s2);
*	dins = 1+ edit_distance(s1, s2+1);
*	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edit_distance.h"
struct matrix{
	int *mat;
	unsigned int width;
	unsigned int height;
};
static unsigned int edit_distance_dyn_core(char *s1, char *s2, struct matrix m, unsigned int, unsigned int);

unsigned int edit_distance(char *s1, char *s2){
	if(s1 == NULL || s2 == NULL){
		fprintf(stderr, "edit_distance : parameters cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(strlen(s1) == 0)
		return strlen(s2);
	if(strlen(s2) == 0)
		return strlen(s1);
	if(s1[0] == s2[0])
		return edit_distance(s1+1, s2+1);
	else{
		unsigned int d_canc = 1 + edit_distance(s1, s2+1);
		unsigned int d_ins = 1 + edit_distance(s1+1, s2);
		if(d_canc < d_ins)
			return d_canc;
		return d_ins;
	}
}

unsigned int edit_distance_dyn(char *s1, char *s2){
	if(s1 == NULL || s2 == NULL){
		fprintf(stderr, "edit_distance : parameters cannot be NULL");
		exit(EXIT_FAILURE);
	}
	unsigned int len1, len2;
	if((len1 = strlen(s1)) == 0)
		return strlen(s2);
	if((len2 = strlen(s2)) == 0)
		return strlen(s1);
	struct matrix m;
	m.mat = malloc((len1+1) * (len2+1) * sizeof(int));
	if(m.mat == NULL){
		fprintf(stderr,"edit_distance_dyn : unable to allocate matrix");
		exit(EXIT_FAILURE);
	}
	m.width = len1+1;
	m.height = len2+1;
	for(unsigned int i = 0; i < m.width; i++)
		m.mat[i] = (int)i;
	
	for(unsigned int i = 1; i < m.height; i++)
		m.mat[i*m.width] = (int)i;
	
	for(unsigned int i = 1; i < m.width; i++)
		for(unsigned int j = 1; j < m.height; j++)
			m.mat[m.width*j+i] = -1;

	unsigned int res = edit_distance_dyn_core(s1,s2,m, len1, len2);
	free(m.mat);
	return res;
}

static unsigned int edit_distance_dyn_core(char *s1, char *s2, struct matrix m, unsigned int s1_len, unsigned int s2_len){
	if(s1 == NULL || s2 == NULL){
		fprintf(stderr, "edit_distance : parameters cannot be NULL");
		exit(EXIT_FAILURE);
	}
	
	unsigned int cur_pos = s2_len*m.width + s1_len;
	unsigned int res;

	if(s1[0] == s2[0]){
		if(m.mat[cur_pos-(m.width+1)] == -1){
			res = edit_distance_dyn_core(s1+1, s2+1, m, s1_len-1, s2_len-1);
		}else{
			res =(unsigned int) m.mat[cur_pos-(m.width+1)];
		}
		m.mat[cur_pos] =(int) res;
		return res;
	}else{
		unsigned int d_canc,d_ins;
		if(m.mat[cur_pos-m.width] == -1){
			d_canc = 1 + edit_distance_dyn_core(s1, s2+1,m,s1_len, s2_len-1);
		}else{
			d_canc = 1 + (unsigned int) m.mat[cur_pos-m.width];
		}
		if(m.mat[cur_pos-1] == -1){
			d_ins = 1 + edit_distance_dyn_core(s1+1, s2,m,s1_len-1, s2_len);
		}else{
			d_ins = 1 + (unsigned int) m.mat[cur_pos-1];
		}
		if(d_canc < d_ins){
			m.mat[cur_pos] = (int) d_canc;
			return d_canc;
		}
		m.mat[cur_pos] = (int) d_ins;
		return d_ins;
	}
}