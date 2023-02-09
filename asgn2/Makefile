CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic

HEADER=asgn2_helper_funcs.h
CFILES=httpserver.c
LIBRARY=asgn2_helper_funcs.a

BINARY=httpserver

all: $(BINARY)

$(BINARY): $(CFILES) $(LIBRARY) $(HEADER)
	clang-format -i -style=file $(CFILES) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $(CFILES) $(LIBRARY)

clean:
	rm -rf $(BINARY)

