/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 4 - Random Test - Adventurer
 * 2/25/19
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "interface.h"
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//checks the state variables for a players's cards to determine if there has been any change
int stateChangedPlayerCards(struct gameState *origState, struct gameState *newState, int player){

	int j=-5;

	//check designated player's hand, deck, and discard piles 
	//for prior and updated states
	
	for (j = 0; j < MAX_DECK; j++){
		if (origState -> hand[player][j] != newState -> hand[player][j]){
			return 1;
		}
	}


	if (origState->handCount[player] != newState -> handCount[player]){
		return 1;
	}


	
	for (j = 0; j < MAX_DECK; j++){
		if (origState -> deck[player][j] != newState -> deck[player][j]){
			return 1;
		}
	}
	

	
	if (origState->deckCount[player] != newState -> deckCount[player]){
		return 1;
	}
	

	
	for (j = 0; j < MAX_DECK; j++){
		if (origState -> discard[player][j] != newState -> discard[player][j]){
			return 1;
		}
	}
	

	
	if (origState->discardCount[player] != newState -> discardCount[player]){
		return 1;
	}
	

	return 0;
}


//initialize test gameStruct
void initTest(struct gameState* testState, int *numPlayers, int k[]){

    //randomly choose [2, MAX_PLAYERS] players
    *numPlayers = rand() % (MAX_PLAYERS + 1 - 2) + 2;

    //9 is always used as seed for repeatability
    initializeGame(*numPlayers, k, 9, testState);
}


//function to randomly set input player's test hand
void setTestHands(struct gameState* state, int player, int advPosArr[]){
	
	int i = -5, MAX_TEST_HAND = 100;

	//randomly select number of cards in hand
	int handCount = (rand() % MAX_TEST_HAND) + 1;
	state -> handCount[player] = handCount;

	//randomly select index position of adventurer card to be 
	//played in random test
	int advPos = rand() % handCount;
	state -> hand[player][advPos] = adventurer;

	//store position of player's adventurer card
	advPosArr[player] = advPos;

	//randomly select card for each of the positions in 
	//player's hand
	for (i = 0; i < handCount; i++){
		
		if (i != advPos){
			state -> hand[player][i] = (rand() % treasure_map) + 1;
		}
	}
}


//function to randomly set input player's test deck
void setTestDeck(struct gameState* state, int player){
	
	int i = -5, MAX_TEST_DECK = 100;

	//randomly make some decks empty to test call to shuffle function
	if (rand() % 10 == 0){
		state -> deckCount[player] = 0;

		//randomly select discard count from [1,20]
		int discardCount = (rand() % 20) + 1;

		//fill discard pile with randomly chosen cards
		for (i = 0; i < discardCount; i++){
			state -> discard[player][i] = (rand() % treasure_map) + 1;
		}

		state -> discardCount[player] = discardCount;
	}
	else{

		//randomly select number of cards in deck
		int deckCount = (rand() % MAX_TEST_DECK) + 1;
		state -> deckCount[player] = deckCount;

		//randomly select card for each of the positions in 
		//player's deck
		for (i = 0; i < deckCount; i++){
			
			state -> deck[player][i] = (rand() % treasure_map) + 1;
			
		}
	}
}





//boolean function to test if player has same cards aside from added cards between two states
int sameCardsExAddPos(struct gameState* origState, struct gameState* state, int player, int handPos){
	int i = -5;

	for (i = 0; i < origState -> handCount[player]; i++){
		if (i != handPos){
			if (origState -> hand[player][i] != state -> hand[player][i]){
				return 0;
			}
		}
	}

	return 1;
}



//boolean function determines whether Adventurer is in the played cards pile
int adInPlayed(struct gameState* state){

	int i = 0;

	for(i = 0; i < state -> playedCardCount; i++){
		if (state -> playedCards[i] == adventurer){
			return 1;
		}
	}
	
	return 0;
}


//boolean function to test that the card supply is unchanged
//between two states
int sameSupply(struct gameState* origState, struct gameState* state){

	int i = -5;

	for (i = 0; i < treasure_map + 1; i++){
		if (origState -> supplyCount[i] != state -> supplyCount[i]){
			return 0;
		}
	}

	return 1;
}


//boolean function to test whether a card is a Treasure Card
int isTreasure(enum CARD cardIn){
	if (cardIn == copper || cardIn == silver || cardIn == gold){
		return 1;
	}

	return 0;
}


//set of individual tests run in every case
void commonTests(struct gameState* origState, struct gameState* state, int player, int handPos){
	int j = -5, addNum = 1;

	char name1[50], name2[50], name3[50];

	memset(name1, '\0', 50 * sizeof(char));

	memset(name2, '\0', 50 * sizeof(char));

	memset(name3, '\0', 50 * sizeof(char));


	//test that Adventurer has been replaced in the player's hand
	printf("ADVENTURER CARD REPLACED WITH ANOTHER CARD\n");
	if (state -> hand[player][handPos] == adventurer){
		printf("*****************FAILED****************\n\n");
		addNum = 2;
	}
	else{
		printf("PASSED\n\n");
	}

	//test that Adventurer has been placed in the played cards pile
	printf("ADVENTURER CARD NOW IN PLAYER'S PLAYED CARDS PILE\n");
	if (!adInPlayed(state)){
		printf("*****************FAILED****************\n\n");
		addNum = 2;
	}
	else{
		printf("PASSED\n\n");
	}

	//test that 2 cards have been added to hand (net 1)
	printf("TWO CARDS ADDED TO PLAYER'S HAND\n");
	if (!(state -> handCount[player] == origState -> handCount[player] + addNum)){
		printf("*****************FAILED****************\n\n");
		printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
				   origState -> handCount[player], (origState -> handCount[player]) + addNum, 
				   state -> handCount[player]);
	}
	else{
		printf("PASSED\n\n");
	}

	//test that the added cards are Treausure cards 
	printf("LAST TWO CARDS ADDED TO HAND ARE TREASURE\n");

	if (isTreasure(state -> hand[player][(state -> handCount[player]) - 2])) {
		if (isTreasure(state -> hand[player][(state -> handCount[player]) - 1])){
			printf("PASSED\n\n");
		}
		else if (isTreasure(state -> hand[player][handPos])) {
			printf("PASSED\n\n");
		}
	}
	else if (isTreasure(state -> hand[player][(state -> handCount[player]) - 1])) {
		if (isTreasure(state -> hand[player][(state -> handCount[player]) - 2])){
			printf("PASSED\n\n");
		}
		else if (isTreasure(state -> hand[player][handPos])) {
			printf("PASSED\n\n");
		}
	}
	else{

		cardNumToName(state -> hand[player][handPos], name3);
		cardNumToName(state -> hand[player][(state -> handCount[player]) - 2], name2);
		cardNumToName(state -> hand[player][(state -> handCount[player]) - 1], name1);

		printf("*****************FAILED****************\n\n");
		printf("ADVENTURER POS CARD: %s PENULTIMATE CARD: %s LAST CARD: %s\n\n", 
				name3, name2, name1);

	}

	//test that player's original cards are the same except for the card
	//that replaced Adventuer
	printf("PLAYER'S OTHER CARDS (ASIDE FROM ADVENTURER/ADDED CARDS) UNCHANGED\n");
	if (!sameCardsExAddPos(origState, state, 0, handPos)){
		printf("*****************FAILED****************\n\n");
	}
	else{
		printf("PASSED\n\n");
	}

	//test that supply of Kingdom, Victory, and Treasure cards is unchanged
	printf("KINGDOM, VICTORY, TREASURE CARD SUPPLY UNCHANGED\n");
	if (!sameSupply(origState, state)){
		printf("*****************FAILED****************\n\n");
	}
	else{
		printf("PASSED\n\n");
	}

	//test that no ascpect of other players' game state has been changed by call to Adventurer
	for (j = 0; j < state -> numPlayers; j++){
		//don't run test for current player
		if (j != player){
			printf("PLAYER %d'S GAME STATE UNCHANGED\n", j + 1);

			if (stateChangedPlayerCards(origState, state, j)){
				printf("*****************FAILED****************\n\n");
			}
			else{
				printf("PASSED\n\n");
			}
		}
	}

}



//display player's hand
void displayHand(struct gameState* state, int player){

	int i = -5;

	char name[50];
	

	printf("HAND: ");

	for (i = 0; i < state -> handCount[player]; i++){
		memset(name, '\0', 50 * sizeof(char));

		cardNumToName(state -> hand[player][i], name);

		printf("%s", name);

		if (i < (state -> handCount[player]) - 1){
			printf(", ");
		}
	}

	printf("\n\n");

}



//display player's deck
void displayDeck(struct gameState* state, int player){

	int i = -5;

	char name[50];
	

	printf("DECK: ");

	for (i = 0; i < state -> deckCount[player]; i++){
		memset(name, '\0', 50 * sizeof(char));

		cardNumToName(state -> deck[player][i], name);

		printf("%s", name);

		if (i < (state -> deckCount[player]) - 1){
			printf(", ");
		}
	}

	printf("\n\n");

}



//display player's discard pile
void displayDiscard(struct gameState* state, int player){

	int i = -5;

	char name[50];
	

	printf("DISCARD: ");

	for (i = 0; i < state -> discardCount[player]; i++){
		memset(name, '\0', 50 * sizeof(char));

		cardNumToName(state -> discard[player][i], name);

		printf("%s", name);

		if (i < (state -> discardCount[player]) - 1){
			printf(", ");
		}
	}

	printf("\n\n");

}



//display, function call, and test activity common to all tests
void commonAction(struct gameState* origState, struct gameState* state, int player, int advPos){

	int dummyInt = 0;

	printf("BEFORE CALL: \n\n");
	displayHand(state, player);
	displayDeck(state, player);
	displayDiscard(state, player);

	//call cardEffect with adventurer
	cardEffect(adventurer, dummyInt, dummyInt, dummyInt, state, advPos, &dummyInt);

	printf("*******ADVENTURER PLAYED*******\n\n");

	displayHand(state, player);
	displayDeck(state, player);
	displayDiscard(state, player);

	//run validation tests
	commonTests(origState, state, player, advPos);
}



//function to get position of treasure cards that should be found
//by Adventurer, i.e. first two treasure cards starting from
//bottom of player's deck.  Also, returns number of cards that
//will be discarded from deck
int setTreasPos(struct gameState* state, int player, int* t1Pos, int* t2Pos){

	int i = (state -> deckCount[player]) - 1, discCt = 0; 

	//if deck is not empty
	if (state -> deckCount[player] > 0){

		//find first treasure card
		while (i >= 0 && (*t1Pos) < 0){

			if (isTreasure(state -> deck[player][i--])){
				*t1Pos = i;
			}
			//count each card until first treasure card found
			else{
				discCt++;
			}
		}

		//find second treasure card
		while (i >= 0 && (*t2Pos) < 0){

			if (isTreasure(state -> deck[player][i--])){
				*t2Pos = i;
			}
			//count each card until second treasure card found
			else{
				discCt++;
			}
		}
	}

	return discCt;
}


void runTests(struct gameState* state, int player, int advPos){


	char name[50];

	int t1Pos = -5, t2Pos = -5;

	memset(name, '\0', 50 * sizeof(char));

	//set current player as having current turn
	state -> whoseTurn = player;

	int numToDiscard = setTreasPos(state, player, &t1Pos, &t2Pos);

	//save state prior to cardEffect/village call
	struct gameState origState = *state;

	//run tests
	commonAction(&origState, state, player, advPos);

	//run test for number of cards discarded
	if (t1Pos >= 0 && t2Pos >= 0){

		//test number of cards from deck discarded
		printf("%d DECK CARDS TO DISCARD\n", numToDiscard);
		if (!(state -> discardCount[player] == numToDiscard)){
			printf("*****************FAILED****************\n\n");
			printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
			   		origState.discardCount[player], 6, 
			   		state -> discardCount[player]);
		}
		else{
			printf("PASSED\n\n");
		}
	}
}




int main(){

	struct gameState testState;

	int numPlayers = -5, i = -5, testNo = 0;

	int NUM_TESTS = 50;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf("\nRANDOM TEST: dominion.c - Adventurer\n");
	printf("**********************************\n\n");

    for (testNo = 0; testNo < NUM_TESTS; testNo++){

    	printf("TEST %d\n", testNo + 1);
		printf("**********************************\n\n");

		initTest(&testState, &numPlayers, k);

		int advPosArr[numPlayers];

		for (i = 0; i < numPlayers; i++){
			setTestHands(&testState, i, advPosArr);
			setTestDeck(&testState, i);
		}

		for (i = 0; i < numPlayers; i++){
			printf("PLAYER %d\n", i + 1);
			printf("**********************************\n\n");
			runTests(&testState, i, advPosArr[i]);
		}
    }

	return 0;
}