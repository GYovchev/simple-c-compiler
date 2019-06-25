HEADERS = file_reader.h utils.h
OBJECTS = main.o file_reader.o utils.o

default: main

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

main: $(OBJECTS)
	gcc $(OBJECTS) -o $@

test:
	-./main main.c

clean:
	-rm -f $(OBJECTS)
	-rm -f main

run: main test clean