CC = gcc

CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

bin/test_edit_distance: build/test_edit_distance.o build/unity.o build/edit_distance.o
	$(CC) -o bin/test_edit_distance build/test_edit_distance.o build/unity.o build/edit_distance.o

bin/application : build/application.o build/edit_distance.o
	$(CC) -o bin/application build/application.o build/edit_distance.o

clean :
	rm -f bin/* build/*