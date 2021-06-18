CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: encode decode
 
encode: encode.o pq.o node.o code.o danielz.o io.o huffman.o stack.o
	$(CC)  -o encode encode.o pq.o node.o code.o danielz.o io.o huffman.o stack.o
 
decode: decode.o pq.o node.o code.o danielz.o io.o huffman.o stack.o
	$(CC)  -o decode decode.o pq.o node.o code.o danielz.o io.o huffman.o stack.o
 
encode.o :encode.c
	$(CC) $(CFLAGS) -c encode.c
    
decode.o :decode.c
	$(CC) $(CFLAGS) -c decode.c
 
pq.o: pq.c pq.h
	$(CC) $(CFLAGS) -c pq.c
    
node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c
    
code.o: code.c code.h defines.h
	$(CC) $(CFLAGS) -c code.c
 
io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c
    
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
    
huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -c huffman.c
    
danielz.o: danielz.c danielz.h
	$(CC) $(CFLAGS) -c danielz.c
    
    
clean: 
	rm -rf  *.o encode decode
    
scan-build: clean
	scan-build make
    
format:
	clang-format -style=file -i *.c *.h
 



