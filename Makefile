fact: main.o Arb.o
	gcc main.o Arb.o -O3 -o fact

Arb.o: Arb.c

main.o:main.c

clean:
	rm -f fact *.o
