cc=gcc -Iinclude/ -Wall -Wextra -pedantic -o

SRC = src/*.c include/*.h
TEST = test/*.c

_CORE = main.c counterprop.c
CORE = $(patsubst %,src/%,$(_CORE))

_FILE_BASED = filePersistence.c fileInput.c
FILE_BASED = $(patsubst %,src/%,$(_FILE_BASED))

_RGB_BASED = filePersistence.c rgbInput.c
RGB_BASED = $(patsubst %,src/%,$(_RGB_BASED))

all:
	@echo "Please enter a build type (file_based, rgb_based)!"

file_based: $(SRC)
	$(cc) file_based $(CORE) $(FILE_BASED)

rgb_based: $(SRC)
	$(cc) rgb_based $(CORE) $(RGB_BASED)

test_all: $(SRC) $(TEST)
	$(cc) counterprop_test src/counterprop.c test/counterprop_test.c
	$(cc) filePersistence_test src/counterprop.c src/filePersistence.c test/filePersistence_test.c
	$(cc) rgbInput_test src/counterprop.c src/rgbInput.c test/rgbInput_test.c
	$(cc) fileInput_test src/counterprop.c src/fileInput.c test/fileInput_test.c
	./counterprop_test
	./filePersistence_test
	./rgbInput_test
	./fileInput_test

clean:
	rm -f *.exe *.stackdump