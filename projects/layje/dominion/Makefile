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

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittest1: unittest1.c dominion.o rngs.o interface.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o interface.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o interface.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o interface.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o interface.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o interface.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o interface.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o interface.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o interface.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o interface.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o interface.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o interface.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o interface.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o interface.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o interface.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

unittests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

randomtests: randomtestcard1 randomtestcard2

unittestresults: clean all unittests 
	echo "********************************************************" > unittestresults.out
	echo "Unit Test 1: isGameOver" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	./unittest1 >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	echo "Unit Test 2: updateCoins" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	echo "Unit Test 3: getCost" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	echo "Unit Test 4: compare" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	echo "Card Test 1: Village" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	echo "Card Test 2: Smithy" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	echo "Card Test 3: Council Room" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	echo "Card Test 4: Adventurer" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	echo "COVERAGE SUMMARY" >> unittestresults.out
	echo "********************************************************" >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestresults: clean all randomtests
	echo "********************************************************" > randomtestresults.out
	echo "Random Test 1: Village" >> randomtestresults.out
	echo "********************************************************" >> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	echo "********************************************************" >> randomtestresults.out
	echo "Random Test 2: Great Hall" >> randomtestresults.out
	echo "********************************************************" >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	echo "********************************************************" >> randomtestresults.out
	echo "COVERAGE SUMMARY" >> randomtestresults.out
	echo "********************************************************" >> randomtestresults.out
	gcov -b dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out


clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe \
	unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
