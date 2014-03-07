CFLAGS=-std=c11 -O3

fact: main.o Arb.o
	$(CC) $(CFLAGS) -o fact $^

Arb.o: Arb.c

main.o: main.c

clean:
	rm -f fact *.o
