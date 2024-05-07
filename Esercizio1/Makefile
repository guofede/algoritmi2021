CC = gcc

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/merge_binaryinsertion_sort_tests: src/merge_binaryinsertion_sort_tests.c build/unity.o
	$(CC) -o bin/merge_binaryinsertion_sort_tests src/merge_binaryinsertion_sort_tests.c build/unity.o

bin/application_record_sort: build/application_record_sort.o build/merge_binaryinsertion_sort.o
	$(CC) -o bin/application_record_sort build/application_record_sort.o build/merge_binaryinsertion_sort.o

clean :
	rm -f bin/* build/*