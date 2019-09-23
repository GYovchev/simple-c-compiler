HEADERS = file_reader.h utils.h types.h tokenizer.h parser.h generator.h
OBJECTS = main.o file_reader.o utils.o tokenizer.o parser.o generator.o
default: main

%.o: %.c $(HEADERS)
	gcc -g -std=c11 -c $< -o $@

main: $(OBJECTS)
	gcc -g -std=c11 $(OBJECTS) -o $@

test:
	-./main "example/fake.c"

clean:
	-rm -f $(OBJECTS)
	-rm -f main

run: main test clean