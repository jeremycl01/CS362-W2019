/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 3 - Unit Test 1 - isGameOver Function
 * 2/3/19
 * -----------------------------------------------------------------------
 */

#include <string.h>
#include <time.h>
#include "dominion.h"
#include "interface.h"

int stateChanged(struct gameState *origState, struct gameState *newState){

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

	if (origState -> coins != newState -> coins){
		return 1;
	}

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

void printTestSupply(struct gameState* state){
	int i = 0, currCount = -5;

	char name[50];
	memset(name, '\0', 50 * sizeof(char));

	printf("SUPPLY:\n\n");

	for (i = 0; i < treasure_map + 1; i++){
		memset(name, '\0', 50 * sizeof(char));
		//get card name
		cardNumToName(i, name);
		currCount = state -> supplyCount[i];
		//exclude any card not in game from listing
		if (currCount != -1){
			printf("%s: %d\n", name, currCount);
		}
		
	}
}

int getEmpties(struct gameState* state){
	int i = 0, count = 0;

	for (i = 0; i < treasure_map + 1; i++){
		if (i != (int)province && state -> supplyCount[i] == 0){
			count++;
		}
	}

	return count;
}

void initTest(struct gameState *testState){
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 9, testState);
}

void checkState(struct gameState *origState, struct gameState *newState){
	printf("NO CHANGE OF STATE FROM PRIOR TEST: ");
	if (stateChanged(origState, newState)){
		printf("\n*****************FAILED****************\n\n");
	}
	else{
		printf("\nPASSED\n\n");
	}

}

void findResult(struct gameState *testState, int passVal){
	printf("\nEMPTIES: %d\n", getEmpties(testState));
	if (isGameOver(testState) == passVal){
		printf("PASSED\n\n");
	}
	else{
		printf("*****************FAILED****************\n\n");
	}
}

void provAlone(struct gameState* testState, int proVal, int passVal){
	int tmp = testState -> supplyCount[province];
	testState -> supplyCount[province] = proVal;
	
	struct gameState preTest = *testState;

	findResult(testState, passVal);

	//test that isGameOver function did not change game state
	checkState(&preTest, testState);

	testState -> supplyCount[province] = tmp;
}

void oneZ(struct gameState* testState, int z1, int passVal){

	int tmp = testState -> supplyCount[z1], 
	    pTmp = testState -> supplyCount[province];
	
	testState -> supplyCount[z1] = 0;
	struct gameState preTest = *testState; 

	findResult(testState, passVal);
	
	checkState(&preTest, testState);

	printf("SAME AS ABOVE, BUT SET PROVINCE 0, GAME ENDS: ");
	testState -> supplyCount[province] = 0;

	preTest = *testState;

	findResult(testState, 1);
	
	checkState(&preTest, testState);

	testState -> supplyCount[province] = pTmp;
	testState -> supplyCount[z1] = tmp;

}


void twoZ(struct gameState* testState, int z1, int z2, int passVal){

	int tmp1 = testState -> supplyCount[z1],
	    tmp2 = testState -> supplyCount[z2],
	    pTmp = testState -> supplyCount[province];
	testState -> supplyCount[z1] = 0;
	testState -> supplyCount[z2] = 0;
	struct gameState preTest = *testState; 

	findResult(testState, passVal);
	
	checkState(&preTest, testState);

	printf("SAME AS ABOVE, BUT SET PROVINCE 0, GAME ENDS: ");
	testState -> supplyCount[province] = 0;

	preTest = *testState;

	findResult(testState, 1);
	
	checkState(&preTest, testState);

	testState -> supplyCount[province] = pTmp;
	testState -> supplyCount[z1] = tmp1;
	testState -> supplyCount[z2] = tmp2;
}


void threeZ(struct gameState* testState, int z1, int z2, int z3, int passVal){

	int tmp1 = testState -> supplyCount[z1],
	    tmp2 = testState -> supplyCount[z2],
	    tmp3 = testState -> supplyCount[z3],
	    pTmp = testState -> supplyCount[province];
	testState -> supplyCount[z1] = 0;
	testState -> supplyCount[z2] = 0;
	testState -> supplyCount[z3] = 0;
	struct gameState preTest = *testState; 

	findResult(testState, passVal);
	
	checkState(&preTest, testState);

	printf("SAME AS ABOVE, BUT SET PROVINCE 0, GAME ENDS: ");
	testState -> supplyCount[province] = 0;

	preTest = *testState;

	findResult(testState, 1);
	
	checkState(&preTest, testState);

	testState -> supplyCount[province] = pTmp;
	testState -> supplyCount[z1] = tmp1;
	testState -> supplyCount[z2] = tmp2;
	testState -> supplyCount[z3] = tmp3;
}

void fourZ(struct gameState* testState, int z1, int z2, int z3, int z4, int passVal){

	int tmp1 = testState -> supplyCount[z1],
	    tmp2 = testState -> supplyCount[z2],
	    tmp3 = testState -> supplyCount[z3],
	    tmp4 = testState -> supplyCount[z4],
	    pTmp = testState -> supplyCount[province];
	testState -> supplyCount[z1] = 0;
	testState -> supplyCount[z2] = 0;
	testState -> supplyCount[z3] = 0;
	testState -> supplyCount[z4] = 0;

	struct gameState preTest = *testState; 

	findResult(testState, passVal);
	
	checkState(&preTest, testState);

	printf("SAME AS ABOVE, BUT SET PROVINCE 0, GAME ENDS: ");
	testState -> supplyCount[province] = 0;

	preTest = *testState;

	findResult(testState, 1);
	
	checkState(&preTest, testState);

	testState -> supplyCount[province] = pTmp;
	testState -> supplyCount[z1] = tmp1;
	testState -> supplyCount[z2] = tmp2;
	testState -> supplyCount[z3] = tmp3;
	testState -> supplyCount[z4] = tmp4;
}


void runTests(struct gameState *testState){

	int mid1 = smithy, mid2 = village, mid3 = mine, mid4 = adventurer, maxVal = treasure_map;

	//test change of province card supply to value above 0 
	//but below start without changing other supply cards
	printf("SET PROVINCE CARDS TO 5, GAME CONTINUES: ");
	
	provAlone(testState, 5, 0);

	printf("SET PROVINCE CARDS TO 1, GAME CONTINUES: ");
	
	provAlone(testState, 1, 0);

	//test provide supply at 0, all other active supply cards 
	//above 0
	printf("SET PROVINCE CARDS TO 0, GAME ENDS: ");
	
	provAlone(testState, 0, 1);

	//test negative supply for province card
	printf("SET PROVINCE CARDS TO NEG VAL, GAME ENDS: ");
	
	provAlone(testState, -1, 1);

	//test setting supply of 1 active supply card to 0; reset value to 
	//original after test

	printf("SET IDX 0 SUPPLY CARD TO 0, OTHERS UNCHANGED, GAME CONTINUES: ");
	
	oneZ(testState, 0, 0);

	printf("SET MAX IDX SUPPLY CARD TO 0, OTHERS UNCHANGED, GAME CONTINUES: ");
	
	oneZ(testState, maxVal, 0);

	printf("SET A MIDDLE SUPPLY CARD TO 0, OTHERS UNCHANGED, GAME CONTINUES: ");
	
	oneZ(testState, mid1, 0);

	//test 2 suppy cards at 0

	//first 2 cards
	printf("SET IDX 0, 1 SUPPLY CARD TO 0, OTHERS UNCHANGED, GAME CONTINUES: ");
	
	twoZ(testState, 0, 1, 0);

	//first and a middle card
	printf("SET IDX 0, MID SUPPLY CARD TO 0, OTHERS UNCHANGED, GAME CONTINUES: ");
	
	twoZ(testState, 0, mid1, 0);

	//first and last cards
	printf("SET IDX 0, MAX IDX SUPPLY CARD TO 0, OTHERS UNCHANGED, GAME CONTINUES: ");
	
	twoZ(testState, 0, maxVal, 0);

	//mid and last cards
	printf("SET MID1, MAX IDX SUPPLY CARD TO 0, OTHERS UNCHANGED, GAME CONTINUES: ");
	
	twoZ(testState, mid1, maxVal, 0);

	//last 2 cards
	printf("SET MAX-1, MAX IDX SUPPLY CARD TO 0, OTHERS UNCHANGED, GAME CONTINUES: ");
	
	twoZ(testState, maxVal - 1, maxVal, 0);

	//test 3 supply cards 0, game should end in all cases

	//first 3 cards
	printf("SET IDX 0, 1, 2 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	threeZ(testState, 0, 1, 2, 1);

	//first 2 + middle cards
	printf("SET IDX 0, 1, MID1 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");

	threeZ(testState, 0, 1, mid1, 1);

	//first card + 2 middle cards
	printf("SET IDX 0, MID1, MID2 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	threeZ(testState, 0, mid3, mid1, 1);

	//first card + middle cards + last card
	printf("SET IDX 0, MID1, MAX SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	threeZ(testState, 0, mid1, maxVal, 1);

	//first card + last cards
	printf("SET IDX 0, MAX-1, MAX SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	threeZ(testState, 0, maxVal - 1, maxVal, 1);

	//3 middle cards 
	printf("SET MID1, MID2, MID3 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	threeZ(testState, mid1, mid2, mid3, 1);

	//last + 2 middle cards 
	printf("SET MID1, MID2, MAX SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	threeZ(testState, mid1, mid2, maxVal, 1);

	//last 2 + 1 middle card
	printf("SET MID1, LAST 2 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	threeZ(testState, mid1, maxVal - 1, maxVal, 1);

	//last 3
	printf("SET LAST 3 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	threeZ(testState, maxVal - 2, maxVal - 1, maxVal, 1);


	//test 4 supply cards 0, game should end in all cases

	//first 4 cards
	printf("SET IDX 0, 1, 2, 3 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	fourZ(testState, 0, 1, 2, 3, 1);

	//first 3 + middle card
	printf("SET IDX 0, 1, 2, MID1 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");

	fourZ(testState, 0, 1, 2, mid1, 1);

	//first 2 cards + 2 middle cards
	printf("SET IDX 0, 1, MID1, MID2 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");

	fourZ(testState, 0, 1, mid1, mid2, 1);

	//first card + 3 middle cards
	printf("SET IDX 0, MID1, MID2, MID3 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");

	fourZ(testState, 0, mid1, mid2, mid3, 1);

	//first card + middle cards + last card
	printf("SET IDX 0, MID1, MID2, MAX SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	fourZ(testState, 0, mid1, mid2, maxVal, 1);

	//first card + middle card + last cards
	printf("SET IDX 0, MID1, MAX-1, MAX SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	fourZ(testState, 0, mid1, maxVal - 1, maxVal, 1);

	//first card + last cards
	printf("SET IDX 0, MID1, MAX-2, MAX SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	fourZ(testState, 0, maxVal - 2, maxVal - 1, maxVal, 1);

	//all middle cards 
	printf("SET MID1, MID2, MID3, MID4 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	fourZ(testState, mid1, mid2, mid3, mid4, 1);

	//3 middle cards + last card
	printf("SET MID1, MID2, MID3, MAX SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	fourZ(testState, mid1, mid2, mid3, maxVal, 1);

	//2 middle cards + last 2 cards
	printf("SET MID1, MID2, LAST 2 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	fourZ(testState, mid1, mid2, maxVal - 1, maxVal, 1);

	//1 middle card + last 3 cards
	printf("SET MID1, LAST 3 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	fourZ(testState, mid1, maxVal - 2, maxVal - 1 , maxVal, 1);

	//last 4 cards
	printf("SET LAST 4 SUPPLY CARDS TO 0, OTHERS UNCHANGED, GAME ENDS: ");
	
	fourZ(testState, maxVal - 3, maxVal - 2, maxVal - 1 , maxVal, 1);
}

int main(){

	struct gameState testState;

	initTest(&testState);

	printf("\nUNIT TEST 1: dominion.c - isGameOver\n");
	printf("**********************************\n\n");

	printf("INITIAL ");
	printTestSupply(&testState);

	printf("\nTESTS: \n\n");

	runTests(&testState);
	

	return 0;
}















