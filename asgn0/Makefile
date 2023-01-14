CC=clang


CFILES=hello.c
OBJECTS=hello.o

BINARY=hello 

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJECTS): $(CFILES)
	$(CC) -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJECTS)
