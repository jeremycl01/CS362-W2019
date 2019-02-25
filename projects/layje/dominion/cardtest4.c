/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 3 - Card Test 4 - Adventurer
 * 2/4/19
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "interface.h"
#include <limits.h>
#include <string.h>


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
void initTest(struct gameState* testState){
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(3, k, 9, testState);
}

//set player hands for testing
//3 players are set to have same hands; position of adventurer card is only difference
void setTestHands(struct gameState* state){
	//set player 1's hand
	int player1 = 0, player2 = 1, player3 = 2, 
	    i = -5, numCards = 9;

	state -> hand[player1][0] = village;
	state -> hand[player1][1] = estate;
	state -> hand[player1][2] = copper;
	state -> hand[player1][3] = silver;
	state -> hand[player1][4] = gold;
	state -> hand[player1][5] = adventurer;
	state -> hand[player1][6] = province;
	state -> hand[player1][7] = smithy;
	state -> hand[player1][8] = council_room;

	state -> handCount[player1] = numCards;

	//player 2
	state -> hand[player2][0] = adventurer;
	state -> hand[player2][1] = estate;
	state -> hand[player2][2] = copper;
	state -> hand[player2][3] = silver;
	state -> hand[player2][4] = gold;
	state -> hand[player2][5] = village;
	state -> hand[player2][6] = province;
	state -> hand[player2][7] = smithy;
	state -> hand[player2][8] = council_room;

	//player 3
	state -> hand[player3][0] = village;
	state -> hand[player3][1] = estate;
	state -> hand[player3][2] = copper;
	state -> hand[player3][3] = silver;
	state -> hand[player3][4] = gold;
	state -> hand[player3][5] = council_room;
	state -> hand[player3][6] = province;
	state -> hand[player3][7] = smithy;
	state -> hand[player3][8] = adventurer;


	//set count for all players
	for (i = 0; i < 3; i++){
		state -> handCount[i] = numCards;
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
void commonTests(struct gameState* origState, struct gameState* state, int handPos){
	int player = 0, j = -5, addNum = 1;

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
	if (!( (isTreasure(state -> hand[player][(state -> handCount[player]) - 1])) &&
	     (isTreasure(state -> hand[player][(state -> handCount[player]) - 2] || 
	      isTreasure(state -> hand[player][handPos]))))) {
		
		cardNumToName(state -> hand[player][handPos], name3);
		cardNumToName(state -> hand[player][(state -> handCount[player]) - 2], name2);
		cardNumToName(state -> hand[player][(state -> handCount[player]) - 1], name1);

		printf("*****************FAILED****************\n\n");
		printf("ADVENTURER POS CARD: %s PENULTIMATE CARD: %s LAST CARD: %s\n\n", 
				name3, name2, name1);
	}
	else{
		printf("PASSED\n\n");
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
void commonAction(struct gameState* origState, struct gameState* state){

	int player = 0, dummyInt = 0, handPos = 5;

	printf("BEFORE CALL: \n\n");
	displayHand(state, player);
	displayDeck(state, player);
	displayDiscard(state, player);

	//call cardEffect with village
	cardEffect(adventurer, dummyInt, dummyInt, dummyInt, state, handPos, &dummyInt);

	printf("*******ADVENTURER PLAYED*******\n\n");

	displayHand(state, player);
	displayDeck(state, player);
	displayDiscard(state, player);

	commonTests(origState, state, handPos);
}



//test 2 treasure cards at bottom of deck
void test1(struct gameState* state){

	int player = 0;

	char name[50];

	memset(name, '\0', 50 * sizeof(char));

	printf("******TESTING PLAYER HAS 2 TREASURE CARDS AT LAST 2 DECK POS*******\n\n");

	//set current player as having current turn
	state -> whoseTurn = 0;

	//set deck
	state -> deck[player][0] = duchy;
	state -> deck[player][1] = province;
	state -> deck[player][2] = steward;
	state -> deck[player][3] = adventurer;
	state -> deck[player][4] = council_room;
	state -> deck[player][5] = village;
	state -> deck[player][6] = smithy;
	state -> deck[player][7] = sea_hag;
	state -> deck[player][8] = silver;
	state -> deck[player][9] = gold;

	state -> deckCount[player] = 10;

	//save state prior to cardEffect/village call
	struct gameState origState = *state;

	commonAction(&origState, state);
	
	//test number of cards from deck discarded
	printf("NO CARD ADDED TO DISCARD (TREASURE CARDS ON TOP OF DECK)\n");
	if (!(origState.discardCount[player] == state -> discardCount[player])){
		printf("*****************FAILED****************\n\n");
		printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
		   		origState.discardCount[player], origState.discardCount[player], 
		   		state -> discardCount[player]);
	}
	else{
		printf("PASSED\n\n");
	}

	//reset state
	*state = origState;

}



//test 2 treasure cards at top of deck
void test2(struct gameState* state){

	int player = 0;

	char name[50];

	memset(name, '\0', 50 * sizeof(char));

	printf("******TESTING PLAYER HAS 2 TREASURE CARDS AT FIRST 2 DECK POS*******\n\n");

	//set current player as having current turn
	state -> whoseTurn = 0;

	//set deck
	state -> deck[player][0] = silver;
	state -> deck[player][1] = gold;
	state -> deck[player][2] = steward;
	state -> deck[player][3] = adventurer;
	state -> deck[player][4] = council_room;
	state -> deck[player][5] = village;
	state -> deck[player][6] = smithy;
	state -> deck[player][7] = sea_hag;
	state -> deck[player][8] = duchy;
	state -> deck[player][9] = province;

	state -> deckCount[player] = 10;

	//save state prior to cardEffect/village call
	struct gameState origState = *state;

	commonAction(&origState, state);
	
	//test number of cards from deck discarded
	printf("ALL DECK CARDS TO DISCARD EX TREASURE (TREASURE CARDS ON BOTTOM OF DECK)\n");
	if (!(state -> discardCount[player] == 8)){
		printf("*****************FAILED****************\n\n");
		printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
		   		origState.discardCount[player], 8, 
		   		state -> discardCount[player]);
	}
	else{
		printf("PASSED\n\n");
	}

	//reset state
	*state = origState;

}



//test 2 treasure cards at 1 at top of deck, 1 at bottom
void test3(struct gameState* state){

	int player = 0;

	char name[50];

	memset(name, '\0', 50 * sizeof(char));

	printf("******TESTING PLAYER HAS 1 TREASURE CARD DECK TOP 1 AT DECK BOTTOM*******\n\n");

	//set current player as having current turn
	state -> whoseTurn = 0;

	//set deck
	state -> deck[player][0] = silver;
	state -> deck[player][1] = province;
	state -> deck[player][2] = steward;
	state -> deck[player][3] = adventurer;
	state -> deck[player][4] = council_room;
	state -> deck[player][5] = village;
	state -> deck[player][6] = smithy;
	state -> deck[player][7] = sea_hag;
	state -> deck[player][8] = duchy;
	state -> deck[player][9] = gold;

	state -> deckCount[player] = 10;

	//save state prior to cardEffect/village call
	struct gameState origState = *state;

	commonAction(&origState, state);

	//test number of cards from deck discarded
	printf("ALL DECK CARDS TO DISCARD EX TREASURE (TREASURE CARDS ON TOP/BOTTOM OF DECK)\n");
	if (!(state -> discardCount[player] == 8)){
		printf("*****************FAILED****************\n\n");
		printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
		   		origState.discardCount[player], 8, 
		   		state -> discardCount[player]);
	}
	else{
		printf("PASSED\n\n");
	}

	//reset state
	*state = origState;

}



//2 treasure cards in middle of deck, side by side
void test4(struct gameState* state){

	int player = 0;

	char name[50];

	memset(name, '\0', 50 * sizeof(char));

	printf("******TESTING PLAYER HAS 2 MID DECK SIDE BY SIDE*******\n\n");

	//set current player as having current turn
	state -> whoseTurn = 0;

	//set deck
	state -> deck[player][0] = village;
	state -> deck[player][1] = province;
	state -> deck[player][2] = steward;
	state -> deck[player][3] = adventurer;
	state -> deck[player][4] = gold;
	state -> deck[player][5] = silver;
	state -> deck[player][6] = smithy;
	state -> deck[player][7] = sea_hag;
	state -> deck[player][8] = duchy;
	state -> deck[player][9] = council_room;

	state -> deckCount[player] = 10;

	//save state prior to cardEffect/village call
	struct gameState origState = *state;

	commonAction(&origState, state);
	
	//test number of cards from deck discarded
	printf("4 DECK CARDS TO DISCARD\n");
	if (!(state -> discardCount[player] == 4)){
		printf("*****************FAILED****************\n\n");
		printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
		   		origState.discardCount[player], 4, 
		   		state -> discardCount[player]);
	}
	else{
		printf("PASSED\n\n");
	}

	//reset state
	*state = origState;

}


//2 treasure cards in middle of deck, separated
void test5(struct gameState* state){

	int player = 0;

	char name[50];

	memset(name, '\0', 50 * sizeof(char));

	printf("******TESTING PLAYER HAS 2 TREASURE CARDS MID DECK SEPARATED*******\n\n");

	//set current player as having current turn
	state -> whoseTurn = 0;

	//set deck
	state -> deck[player][0] = village;
	state -> deck[player][1] = province;
	state -> deck[player][2] = gold;
	state -> deck[player][3] = adventurer;
	state -> deck[player][4] = steward;
	state -> deck[player][5] = sea_hag;
	state -> deck[player][6] = smithy;
	state -> deck[player][7] = silver;
	state -> deck[player][8] = duchy;
	state -> deck[player][9] = council_room;

	state -> deckCount[player] = 10;

	//save state prior to cardEffect/village call
	struct gameState origState = *state;

	commonAction(&origState, state);
	
	//test number of cards from deck discarded
	printf("6 DECK CARDS TO DISCARD\n");
	if (!(state -> discardCount[player] == 6)){
		printf("*****************FAILED****************\n\n");
		printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
		   		origState.discardCount[player], 6, 
		   		state -> discardCount[player]);
	}
	else{
		printf("PASSED\n\n");
	}

	//reset state
	*state = origState;

}

//deck empty, separated
void test6(struct gameState* state){

	int player = 0;

	char name[50];

	memset(name, '\0', 50 * sizeof(char));

	printf("******TESTING PLAYER HAS EMPTY DECK*******\n\n");

	//set current player as having current turn
	state -> whoseTurn = 0;

	state -> deckCount[player] = 0;
	
	//set deck
	state -> discard[player][0] = village;
	state -> discard[player][1] = province;
	state -> discard[player][2] = gold;
	state -> discard[player][3] = adventurer;
	state -> discard[player][4] = steward;
	state -> discard[player][5] = sea_hag;
	state -> discard[player][6] = smithy;
	state -> discard[player][7] = silver;
	state -> discard[player][8] = duchy;
	state -> discard[player][9] = council_room;

	state -> discardCount[player] = 10;

	//save state prior to cardEffect/village call
	struct gameState origState = *state;

	commonAction(&origState, state);
	
	//reset state
	*state = origState;

}

int main(){

	struct gameState testState;

	initTest(&testState);

	setTestHands(&testState);

	printf("\nCARD TEST 4: dominion.c - Adventurer\n");
	printf("**********************************\n\n");

	//2 treasure cards at bottom of deck
	test1(&testState);

	//2 treasure cards at top of deck
	test2(&testState);

	//1 treasure cards at top of deck, 1 at bottom
	test3(&testState);

	//2 treasure cards in middle of deck, side by side
	test4(&testState);

	//2 treasure cards in middle of deck, separated
	test5(&testState);

	//deck empty
	test6(&testState);
	

	return 0;
}