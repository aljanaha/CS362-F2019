CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

unittest1: dominion.o unittest1.c
	gcc -o unittest1 -g  unittest1.c   dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o unittest2.c
	gcc -o unittest2 -g  unittest2.c   dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o unittest3.c
	gcc -o unittest3 -g  unittest3.c   dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o unittest4.c
	gcc -o unittest4 -g  unittest4.c   dominion.o rngs.o $(CFLAGS)

unittest5: dominion.o unittest5.c
	gcc -o unittest5 -g  unittest5.c   dominion.o rngs.o $(CFLAGS)

testdominion: unittest1 unittest2 unittest3 unittest4 unittest5
	./unittest1 >>test.out
	./unittest2 >>test.out
	./unittest3 >>test.out
	./unittest4 >>test.out
	./unittest5 >>test.out
	gcov -b -f -c dominion.c >> unittestresults.out
	
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
	rm -f *.o playdom.exe playdom unittest1 unittest1.exe unittest2 unittest2.exe  unittest3 unittest3.exe unittest4 unittest4.exe unittest5 unittest5.exe player player.exe  andomtest1 randomtest1.exe randomtest2 randomtest2.exe  randomtest3 randomtest3.exe  *.gcov *.gcda *.gcno *.so *.out testdrawcard testdrawcard.exe
