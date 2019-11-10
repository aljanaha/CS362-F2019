CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testdrawcard: testdrawcard.c dominion.o rngs.o
	gcc  -o testdrawcard -g  testdrawcard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testdrawcard 
	./testdrawcard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom unittest1 unittest1.exe player player.exe  *.gcov *.gcda *.gcno *.so *.out testdrawcard testdrawcard.exe

testdominion: dominion.o unittest1.c
	gcc -o unittest1 -g  unittest1.c   dominion.o rngs.o $(CFLAGS)
	./unittest1 >>test.out
	gcov -b -f -c unittest1.c >> unittestresults.out

