CC=gcc-4.9
CFLAGS= -Wall -Wextra -pedantic -std=c99
LDFLAGS= `sdl-config --libs`
EXEC=snake

all: $(EXEC)

snake: main.o snake.o
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: const.h
snake.o: const.h

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)