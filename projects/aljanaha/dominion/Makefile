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

randomtest1: dominion.o randomtestcard1.c
		  gcc -o randomtest1 -g randomtestcard1.c   dominion.o rngs.o $(CFLAGS)

randomtest2: dominion.o randomtestcard2.c
		  gcc -o randomtest2 -g randomtestcard2.c   dominion.o rngs.o $(CFLAGS)

randomtest3: dominion.o randomtestcard3.c
		  gcc -o randomtest3 -g randomtestcard3.c   dominion.o rngs.o $(CFLAGS)


randomtestresults: randomtest1 randomtest2 randomtest3
	./randomtest1 >> test.out
	./randomtest2 >> test.out
	./randomtest3 >> test.out
	gcov -b -f -c dominion.c >> randomtestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  randomtest1 randomtest1.exe randomtest2 randomtest2.exe  randomtest3 randomtest3.exe  *.gcov *.gcda *.gcno *.so *.out testdrawcard testdrawcard.exe
