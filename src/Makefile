CC=gcc
CFLAGS=-O0 -Wall
LIBS=pilwgpio


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

keypad: keypad.o
	$(CC) -o $@ -L/usr/local/lib/ $^ -l$(LIBS) $(CFLAGS)

clean:
	rm -f *.o

.PHONY:
	clean
