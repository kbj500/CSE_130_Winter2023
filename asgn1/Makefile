CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic

CFILES=memory.c
OBJECTS=memory.o

BINARY=memory

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

$(OBJECTS): $(CFILES)
	clang-format -i -style=file $(CFILES)
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJECTS)

