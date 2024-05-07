/*unit tests exercise 2*/
#include "unity.h"
#include "edit_distance.h"
static char *s1, *s2;

void setUp(void){
	s1 = "Quando";
	s2 = "a";
}

void tearDown(void){
}

static void test_edit_distance_two_empty_string(void){
	s1 = "";
	s2 = "";
	TEST_ASSERT_EQUAL_UINT(0, edit_distance(s1,s2));
}

static void test_edit_distance_one_empty_string(void){
	s2 = "";
	TEST_ASSERT_EQUAL_UINT(6, edit_distance(s1,s2));
}

static void test_edit_distance_generic(void){
	TEST_ASSERT_EQUAL_UINT(5, edit_distance(s1,s2));
}

static void test_edit_distance_equal_string(void){
	TEST_ASSERT_EQUAL_UINT(0, edit_distance(s1,s1));
}
static void test_edit_distance_two_empty_string_dyn(void){
	s1 = "";
	s2 = "";
	TEST_ASSERT_EQUAL_UINT(0, edit_distance_dyn(s1,s2));
}

static void test_edit_distance_one_empty_string_dyn(void){
	s2 = "";
	TEST_ASSERT_EQUAL_UINT(6, edit_distance_dyn(s1,s2));
}

static void test_edit_distance_generic_dyn(void){
	TEST_ASSERT_EQUAL_UINT(5, edit_distance_dyn(s1,s2));
}

static void test_edit_distance_equal_string_dyn(void){
	TEST_ASSERT_EQUAL_UINT(0, edit_distance_dyn(s1,s1));
}
int main(){
	UNITY_BEGIN();
	RUN_TEST(test_edit_distance_two_empty_string);
	RUN_TEST(test_edit_distance_one_empty_string);
	RUN_TEST(test_edit_distance_generic);
	RUN_TEST(test_edit_distance_equal_string);
	RUN_TEST(test_edit_distance_two_empty_string_dyn);
	RUN_TEST(test_edit_distance_one_empty_string_dyn);
	RUN_TEST(test_edit_distance_generic_dyn);
	RUN_TEST(test_edit_distance_equal_string_dyn);

	return UNITY_END();
}