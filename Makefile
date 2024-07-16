
%.o : %.c cliculator.h
	g++ -c -o $@ $<

main: cliculator.o parsing.o test.o
	g++ -o cliculator cliculator.o parsing.o
	g++ -o test test.o parsing.o
	rm -f *.o
