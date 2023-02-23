CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -pthread

HEADER=queue.h
CFILES=queue.c

OBJ=queue.o

all: $(OBJ)

$(OBJ): $(CFILES) $(HEADER)
	clang-format -i -style=file $(CFILES) $(HEADER)
	$(CC) $(CFLAGS) -c $(CFILES) 


clean:
	rm -rf *.o  

