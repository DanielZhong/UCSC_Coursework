EXECBIN = banhammer
 
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)
 
CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic -g
 
all: $(EXECBIN)
 
$(EXECBIN): $(OBJECTS)
	$(CC) -o $@ $^
 
%.o: %.c
	$(CC) $(CFLAGS) -c $<
 
clean:
	rm -f $(EXECBIN) *.o
 
format:
	clang-format -style=file -i *.c *.h
 
 
 


