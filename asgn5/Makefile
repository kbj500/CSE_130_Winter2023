CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic 

QHEADER=queue.h
QCFILES=queue.c
CHEADER=LinkedList.h
CCFILES=cacher.c LinkedList.c

OBJ=queue.o
BINARY=cacher

all: $(BINARY) 

$(BINARY): $(OBJ) $(CCFILES) $(CHEADER)
	clang-format -i -style=file $(CCFILES) $(CHEADER)
	 $(CC) $(CFLAGS) -o $@ $(CCFILES) $(QCFILES)

$(OBJ): $(QCFILES) $(QHEADER)
	clang-format -i -style=file $(QCFILES) $(QHEADER)
	$(CC) $(CFLAGS) -c $(QCFILES) 


clean: 
	rm -rf queue.o cacher 



