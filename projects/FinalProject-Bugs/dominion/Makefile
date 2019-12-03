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


unittestresults: unittest1 
	./unittest1 >>unittestresults.out
	gcov -b -f -c  dominion.c >> unittestresults.out
	-gcovr -r . --html  --html-details -o report.html 

clean:
	rm -f *.o playdom.exe playdom player player.exe unittest1 unittest1.exe  *.gcov *.gcda *.gcno *.so *.out *.html testDrawCard testDrawCard.exe
