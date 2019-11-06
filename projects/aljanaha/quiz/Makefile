CFLAGS= -Wall -fpic -coverage -lm -std=c99

build: testme.c 
		gcc -o testme -g  testme.c   $(CFLAGS)

test: testme.c 
	gcc -o testme -g  testme.c   $(CFLAGS)
	./testme >>test.out
	gcov -b -c testme.c >> testme.out

clean:
	rm testme *.gcda *.gcno *.gcov *.out