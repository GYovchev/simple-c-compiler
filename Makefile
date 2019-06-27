HEADERS = file_reader.h utils.h tokens.h tokenizer.h
OBJECTS = main.o file_reader.o utils.o tokenizer.o
default: main

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

main: $(OBJECTS)
	gcc $(OBJECTS) -o $@

test:
	-./main "example/fake.c"

clean:
	-rm -f $(OBJECTS)
	-rm -f main

run: main test clean