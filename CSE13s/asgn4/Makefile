CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: tsp
 
tsp: tsp.o graph.o path.o stack.o danielz.o
	$(CC)  -o tsp tsp.o graph.o path.o stack.o danielz.o
    
tsp.o: tsp.c graph.h path.h vertices.h 
	$(CC) $(CFLAGS) -c tsp.c
    
graph.o: graph.c graph.h vertices.h
	$(CC) $(CFLAGS) -c graph.c  
    
path.o: path.c path.h stack.h
	$(CC) $(CFLAGS) -c path.c
    
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
    
    
danielz.o: danielz.c danielz.h
	$(CC) $(CFLAGS) -c danielz.c
 
clean: 
	rm -rf  *.o tsp
    
scan-build: clean
	scan-build make
    
format:
	clang-format -style=file -i *.c *.h
 
 


