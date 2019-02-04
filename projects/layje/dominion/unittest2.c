/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 3 - Unit Test 2 - updateCoins
 * 2/3/19
 * -----------------------------------------------------------------------
 */

#include <string.h>
#include "dominion.h"
#include "interface.h"

int nonCoinStateChanged(struct gameState *origState, struct gameState *newState){

	int i = -5, j=-5;

	if (origState -> numPlayers != newState -> numPlayers){
		return 1;
	}

	for (i = 0; i < treasure_map + 1; i++){
		if (origState->supplyCount[i] != newState -> supplyCount[i]){
			return 1;
		}
	}

	for (i = 0; i < treasure_map + 1; i++){
		if (origState->embargoTokens[i] != newState -> embargoTokens[i]){
			return 1;
		}
	}

	if (origState -> outpostPlayed != newState -> outpostPlayed){
		return 1;
	}

	if (origState -> outpostTurn != newState -> outpostTurn){
		return 1;
	}

	if (origState -> whoseTurn != newState -> whoseTurn){
		return 1;
	}

	if (origState -> phase != newState -> phase){
		return 1;
	}

	if (origState -> numActions != newState -> numActions){
		return 1;
	}

	/*
	if (origState -> coins != newState -> coins){
		return 1;
	} */

	if (origState -> numBuys != newState -> numBuys){
		return 1;
	}

	

	for (i = 0; i < MAX_PLAYERS; i++){
		for (j = 0; j < MAX_DECK; j++){
			if (origState -> hand[i][j] != newState -> hand[i][j]){
				return 1;
			}
		}
	} 

	for (i = 0; i < MAX_PLAYERS + 1; i++){
		if (origState->handCount[i] != newState -> handCount[i]){
			return 1;
		}
	} 

	for (i = 0; i < MAX_PLAYERS; i++){
		for (j = 0; j < MAX_DECK; j++){
			if (origState -> deck[i][j] != newState -> deck[i][j]){
				return 1;
			}
		}
	}

	for (i = 0; i < MAX_PLAYERS + 1; i++){
		if (origState->deckCount[i] != newState -> deckCount[i]){
			return 1;
		}
	}

	for (i = 0; i < MAX_PLAYERS; i++){
		for (j = 0; j < MAX_DECK; j++){
			if (origState -> discard[i][j] != newState -> discard[i][j]){
				return 1;
			}
		}
	}

	for (i = 0; i < MAX_PLAYERS + 1; i++){
		if (origState->discardCount[i] != newState -> discardCount[i]){
			return 1;
		}
	}

	for (i = 0; i < MAX_DECK + 1; i++){
		if (origState->playedCards[i] != newState -> playedCards[i]){
			return 1;
		}
	}

	if (origState -> playedCardCount != newState -> playedCardCount){
		return 1;
	}

	return 0;
}


void initTest(struct gameState *testState){
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 9, testState);
}

void checkState(struct gameState *origState, struct gameState *newState){
	printf("NO CHANGE OF STATE FROM PRIOR TEST (COINS EXCLUDED): ");
	if (nonCoinStateChanged(origState, newState)){
		printf("\n*****************FAILED****************\n\n");
	}
	else{
		printf("\nPASSED\n\n");
	}

}

void findResult(struct gameState *testState, int pyr, int bon, int passVal){
	
	updateCoins(pyr, testState, bon);

	printf("CALC: %d\nSET: %d\n", passVal, testState -> coins);

	if (testState -> coins == passVal){
		printf("PASSED\n\n");
	}
	else{
		printf("*****************FAILED****************\n\n");
	}
}

void addCoins(struct gameState *testState, int ply, int coin, int numCoin, int *stIdx){

	int i;

	for (i = 0; i < numCoin; i++){
		testState -> hand[ply][(*stIdx)] = coin;
		testState -> handCount[ply]++;
		(*stIdx)++;
	}
}

void runTests(struct gameState *testState){

	int testNums[] = {0, 1, 3}, gd, sil, copp, bon, totHand, pyer, handCt;
	
	for (pyer = 0; pyer < 3; pyer++){
		for (gd = 0; gd < 3; gd++){
			for (sil = 0; sil < 3; sil++){
				for (copp = 0; copp < 3; copp++){
					for (bon = 0; bon < 3; bon++){

						memset(testState -> hand, 0, MAX_PLAYERS * MAX_HAND * sizeof(int));
						testState -> handCount[pyer] = 0;

						totHand = testNums[copp] + testNums[sil] * 2 + testNums[gd] * 3 + testNums[bon];
						handCt = 0;

						printf("PLAYER: %d ", pyer + 1);

						printf("COPPER: %d ", testNums[copp]);
						addCoins(testState, pyer, copper, testNums[copp], &handCt);

						printf("SILVER: %d ", testNums[sil]);
						addCoins(testState, pyer, silver, testNums[sil], &handCt);

						printf("GOLD: %d ", testNums[gd]);
						addCoins(testState, pyer, gold, testNums[gd], &handCt);

						printf("BONUS: %d ", testNums[bon]);
						printf("\n\n");

						struct gameState prevState = *testState;

						findResult(testState, pyer, testNums[bon], totHand);

						checkState(&prevState, testState);

						*testState = prevState;

					}
				}
			}
		}
	}
	 
}




int main(){

	struct gameState testState;

	initTest(&testState);

	printf("\nUNIT TEST 2: dominion.c - updateCoins\n");
	printf("**********************************\n\n");

	printf("\nTESTS: \n\n");

	runTests(&testState);
	

	return 0;
}


