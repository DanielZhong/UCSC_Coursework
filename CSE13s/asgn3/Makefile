CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic
 
all: sorting
 
sorting: sorting.o bubble.o shell.o quick.o stack.o queue.o set.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o stack.o queue.o set.o
 
sorting.o: sorting.c bubble.h shell.h quick.h
	$(CC) $(CFLAGS) -c sorting.c
 
bubble.o: bubble.c bubble.h
	$(CC) $(CFLAGS) -c bubble.c
 
shell.o: shell.c shell.h gaps.h
	$(CC) $(CFLAGS) -c shell.c
 
quick.o: quick.c stack.h queue.h
	$(CC) $(CFLAGS) -c quick.c
 
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
    
queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c
 
set.o: set.c set.h
	$(CC) $(CFLAGS) -c set.c
 
clean: 
	rm -rf  *.o sorting
    
scan-build: clean
	scan-build make
    
format:
	clang-format -style=file -i *.c *.h
 
 


