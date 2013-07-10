cc=gcc -Iinclude/ -Wall -Wextra -pedantic -o

SRC = src/*.c include/*.h
TEST = test/*.c

test_all: $(SRC) $(TEST)
	$(cc) counterprop_test test/counterprop_test.c test/testPersistence.c
	$(cc) filePersistence_test src/filePersistence.c test/filePersistence_test.c
	./counterprop_test
	./filePersistence_test

clean:
	rm -f *.exe *.stackdump