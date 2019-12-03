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


unittest6: dominion.o unittest6.c
	gcc -o unittest6 -g  unittest6.c   dominion.o rngs.o $(CFLAGS)

unittest7: dominion.o unittest7.c
	gcc -o unittest7 -g  unittest7.c   dominion.o rngs.o $(CFLAGS)


unittestresults: unittest1 
	./unittest1 >>unittestresults.out
	./unittest2 >>unittestresults.out
	./unittest3 >>unittestresults.out
	./unittest4 >>unittestresults.out
	./unittest6 >>unittestresults.out
	./unittest7 >>unittestresults.out
	gcov -b -f -c  dominion.c >> unittestresults.out
	-gcovr -r . --html  --html-details -o report.html 

clean:
	rm -f *.o playdom.exe playdom player player.exe unittest1 unittest1.exe unittest2 unittest2.exe  unittest3 unittest3.exe unittest4 unittest4.exe unittest5 unittest5.exe unittest6 unittest6.exe unittest7 unittest7.exe  *.gcov *.gcda *.gcno *.so *.out *.html testDrawCard testDrawCard.exe
