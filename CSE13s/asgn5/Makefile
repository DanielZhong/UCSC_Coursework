CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
MATHLIB = -lm
 
all: encode decode
 
encode: encode.o bm.o bv.o hamming.o danielz.o
	$(CC)  -o encode encode.o bm.o bv.o hamming.o danielz.o
    
decode: decode.o bm.o bv.o hamming.o danielz.o
	$(CC)  -o decode decode.o bm.o bv.o hamming.o danielz.o
    
entropy: entropy.c
	$(CC) $(CFLAGS) $(MATHLIB) -o entropy entropy.c
    
error: error.c
	$(CC) $(CFLAGS) -o error error.c
    
encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c
 
decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c
    
bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c
 
bm.o: bm.c bm.h
	$(CC) $(CFLAGS) -c bm.c
 
hamming.o: hamming.c hamming.h
	$(CC) $(CFLAGS) -c hamming.c
 
danielz.o: danielz.c danielz.h
	$(CC) $(CFLAGS) -c danielz.c
 
clean: 
	rm -rf  *.o entropy error encode decode
    
scan-build: clean
	scan-build make
    
format:
	clang-format -style=file -i *.c *.h
 
 


