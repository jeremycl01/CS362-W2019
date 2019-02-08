CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme:	clean 
	gcc -o testme testme.c $(CFLAGS)
	./testme 

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme
