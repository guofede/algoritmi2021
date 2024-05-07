#include "unity.h"
#include "merge_binaryinsertion_sort.c"
/*
*	test suite for merge_binaryinsertion_sort public and internal algorithms
*/

/*
*	precede function used in the test
*/

static int compare_int(void *el1, void*el2){
	int *int1 = (int *) el1;
	int *int2 = (int *) el2;
	return (*int1)-(*int2);
}

static int i1,i2,i3;

void setUp(void){
	i1 = 3;
	i2 = 0;
	i3 = -12;
}

void tearDown(void){
	return;
}

static void merge_test_one_element_array(void){
	int *array[] = {&i1};
	merge((void **) array, 0, 0, compare_int);
	TEST_ASSERT_EQUAL_PTR(&i1, array[0]);
}

static void merge_test_three_element_array(void){
	int *array[] = {&i1,&i3,&i2};
	int *expected[] = {&i3, &i2, &i1};
	merge((void **) array, 1, 3, compare_int);
	TEST_ASSERT_EQUAL_PTR_ARRAY(expected, array, 3);
}

static void binaryinsertion_search_pos_one_element_array(void){
	int *array[] = {&i1};
	TEST_ASSERT_EQUAL_INT(0, binaryinsertion_search_pos((void **)array, 0, compare_int));
}

static void binaryinsertion_search_pos_three_element_array(void){
	int *array[] = {&i2,&i1,&i3};
	TEST_ASSERT_EQUAL_INT(0, binaryinsertion_search_pos((void **)array, 2, compare_int));
}

static void binaryinsertion_search_pos_three_element_array_2(void){
	int *array[] = {&i3,&i1,&i2};
	TEST_ASSERT_EQUAL_INT(1, binaryinsertion_search_pos((void **)array, 2, compare_int));
}

static void binaryinsertion_sort_one_element_array(void){
	int *array[] = {&i1};
	binaryinsertion_sort((void **)array,1,compare_int);
	TEST_ASSERT_EQUAL_PTR(&i1, array[0]);
}

static void binaryinsertion_sort_three_element_array(void){
	int *array[] = {&i1,&i2,&i3};
	int *expected[] = {&i3, &i2, &i1};
	binaryinsertion_sort((void **)array,3,compare_int);
	TEST_ASSERT_EQUAL_PTR_ARRAY(expected, array, 3);
}

static void merge_binaryinsertion_sort_one_element_array(void){
	int *array[] = {&i1};
	merge_binaryinsertion_sort((void **)array,1,compare_int);
	TEST_ASSERT_EQUAL_PTR(&i1, array[0]);
}

static void merge_binaryinsertion_sort_three_element_array(void){
	int *array[] = {&i1,&i2,&i3};
	int *expected[] = {&i3, &i2, &i1};
	merge_binaryinsertion_sort((void **)array,3,compare_int);
	TEST_ASSERT_EQUAL_PTR_ARRAY(expected, array, 3);
}

int main(){
	UNITY_BEGIN();
	RUN_TEST(merge_test_one_element_array);
	RUN_TEST(merge_test_three_element_array);
	RUN_TEST(binaryinsertion_search_pos_one_element_array);
	RUN_TEST(binaryinsertion_search_pos_three_element_array);
	RUN_TEST(binaryinsertion_search_pos_three_element_array_2);
	RUN_TEST(binaryinsertion_sort_one_element_array);
	RUN_TEST(binaryinsertion_sort_three_element_array);
	RUN_TEST(merge_binaryinsertion_sort_one_element_array);
	RUN_TEST(merge_binaryinsertion_sort_three_element_array);
	return UNITY_END();
}