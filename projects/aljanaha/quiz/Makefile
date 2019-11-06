CFLAGS= -Wall -fpic -coverage -lm -std=c99

build: testme.c 
		gcc -o testme -g  testme.c   $(CFLAGS)

run: build
	./testme

test: build 
	./testme >>test.out
	gcov -b -c testme.c >> testme.out

fail: testmefail.c
	gcc -o testmefail -g  testmefail.c   $(CFLAGS)
	./testmefail

clean:
	rm testme *.gcda *.gcno *.gcov *.out