cc=gcc -Iinclude/ -o

SRC = src/*.c include/*.h
TEST = test/*.c

test_all: $(SRC) $(TEST)
	$(cc) counterprop_test test/counterprop_test.c
	./counterprop_test

clean:
	rm -f *.exe *.stackdump