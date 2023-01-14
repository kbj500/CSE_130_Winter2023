CC=clang
CFLAGS=-Wall -Wextra -g

CFILES=hello.c
OBJECTS=hello.o

BINARY=hello 

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJECTS): $(CFILES)
	$(CC) $(CFLAGS) -c -o $@ $^

$(CFILES):
	clang-format -i -style=file $(CFILES)

clean:
	rm -rf $(BINARY) $(OBJECTS)
