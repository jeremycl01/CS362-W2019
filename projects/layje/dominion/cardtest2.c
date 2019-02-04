/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 3 - Card Test 2 - Smithy
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
//3 players are set to have same hands; position of smithy card is only difference
void setTestHands(struct gameState* state){
	//set player 1's hand
	int player1 = 0, player2 = 1, player3 = 2;

	state -> hand[player1][0] = smithy;
	state -> hand[player1][1] = estate;
	state -> hand[player1][2] = copper;
	state -> hand[player1][3] = silver;
	state -> hand[player1][4] = gold;
	state -> hand[player1][5] = adventurer;
	state -> hand[player1][6] = province;
	state -> hand[player1][7] = village;
	state -> hand[player1][8] = council_room;

	state -> handCount[player1] = 9;

	state -> hand[player2][0] = adventurer;
	state -> hand[player2][1] = estate;
	state -> hand[player2][2] = copper;
	state -> hand[player2][3] = silver;
	state -> hand[player2][4] = gold;
	state -> hand[player2][5] = smithy;
	state -> hand[player2][6] = province;
	state -> hand[player2][7] = village;
	state -> hand[player2][8] = council_room;

	state -> handCount[player2] = 9;

	state -> hand[player3][0] = adventurer;
	state -> hand[player3][1] = estate;
	state -> hand[player3][2] = copper;
	state -> hand[player3][3] = silver;
	state -> hand[player3][4] = gold;
	state -> hand[player3][5] = council_room;
	state -> hand[player3][6] = province;
	state -> hand[player3][7] = village;
	state -> hand[player3][8] = smithy;

	state -> handCount[player3] = 9;

}


//boolean function determines whether smithy is in a player's hand
int smithyInHand(struct gameState* state, int player){

	int i = 0;

	for(i = 0; i < state -> handCount[player]; i++){
		if (state -> hand[player][i] == smithy){
			return 1;
		}
	}
	
	return 0;
}

//boolean function determines whether smithy is in the played cards pile
int smithyInPlayed(struct gameState* state){

	int i = 0;

	for(i = 0; i < state -> playedCardCount; i++){
		if (state -> playedCards[i] == smithy){
			return 1;
		}
	}
	
	return 0;
}


//display a selected player's hand
void displayHand(struct gameState* state, int player){

	int i = -5;

	char name[50];
	

	printf("PLAYER %d's HAND:\n", player + 1);

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

//display hands for all players in a gameState struct
void displayAllHands(struct gameState* state){

	int i = -5;

	for (i = 0; i < state -> numPlayers; i++){
		displayHand(state, i);
	}

}

//boolean function to test if player has same cards between two states
int sameCards(struct gameState* origState, struct gameState* state, int player){
	int i = -5;

	if (origState -> handCount[player] != state -> handCount[player]){
		return 0;
	}

	for (i = 0; i < state -> handCount[player]; i++){
		if (origState -> hand[player][i] != state -> hand[player][i]){
			return 0;
		}
	}

	return 1;
}

//boolean function to test if player has same cards between two states
int sameCardsExPos(struct gameState* origState, struct gameState* state, int player, int handPos){
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

//test smithy. the expected effects are:
//add 3 cards to hand of player using smithy from player's deck
//remove smithy from hand of player using smithy and place in played cards pile

void runTests(struct gameState* state){

	int dummyInt = 1, i = -1, j=-1;

	int handPos[] = {0, 5, 8}; 


	printf("STARTING HANDS:\n\n");

	displayAllHands(state);

	printf("\nTESTS: \n\n");

	//iterate through players
	for (i = 0; i < state -> numPlayers; i++){
		
		//set current player as having current turn
		state -> whoseTurn = i;

		//save state prior to cardEffect/smithy call
		struct gameState origState = *state;

		printf("******TESTING PLAYER %d PLAYS SMITHY*******\n\n", i + 1);

		//call cardEffect with smithy 
		cardEffect(smithy, dummyInt, dummyInt, dummyInt, state, handPos[i], &dummyInt);

		printf("*******SMITHY PLAYED*******\n\n");
		
		displayAllHands(state);

		//test that Smithy card is no longer in hand
		printf("SMITHY CARD NO LONGER IN CURR PLAYER'S HAND\n");
		if (smithyInHand(state, i)){
			printf("*****************FAILED****************\n\n");
		}
		else{
			printf("PASSED\n\n");
		}

		//test that Smithy has been replaced in the player's hand 
		//with three additional cards (net +2)
		printf("SMITHY CARD REPLACED WITH 3 OTHER CARDS\n");
		if (state -> handCount[i] != origState.handCount[i] + 2){
			printf("*****************FAILED****************\n\n");
			printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
				   origState.handCount[i], origState.handCount[i] + 2, state -> handCount[i]);
		}
		else{
			printf("PASSED\n\n");
		}


		//test that new card(s) came from current player's pile
		printf("REPLACEMENT CARDS CAME FROM PLAYER'S DECK\n");
		if (!(state -> deckCount[i] < origState.deckCount[i])){
			printf("*****************FAILED****************\n\n");
			printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
				   origState.deckCount[i], origState.deckCount[i] - 3, state -> deckCount[i]);
		}
		else{
			printf("PASSED\n\n");
		}


		//test that Smithy has been placed in the played cards pile
		printf("SMITHY CARD NOW IN PLAYER'S PLAYED CARDS PILE\n");
		if (!smithyInPlayed(state)){
			printf("*****************FAILED****************\n\n");
		}
		else{
			printf("PASSED\n\n");
		}

		
		//test that player's cards are the same except for the card
		//that replaced Smithy
		printf("PLAYER %d'S OTHER CARDS (ASIDE FROM SMITHY/ADDED CARDS) UNCHANGED\n", i + 1);

				if (!sameCardsExPos(&origState, state, i, handPos[i])){
					printf("*****************FAILED****************\n\n");
				}
				else{
					printf("PASSED\n\n");
				}

		//test that supply of Kingdom, Victory, and Treasure cards is unchanged
		printf("KINGDOM, VICTORY, TREASURE CARD SUPPLY UNCHANGED\n");
		if (!sameSupply(&origState, state)){
			printf("*****************FAILED****************\n\n");
		}
		else{
			printf("PASSED\n\n");
		}


		//test that no ascpect of other players' game state has been changed by call to cardEffect
		for (j = 0; j < state -> numPlayers; j++){
			//don't run test for current player
			if (j != i){
				printf("PLAYER %d'S GAME STATE UNCHANGED\n", j + 1);

				if (stateChangedPlayerCards(&origState, state, j)){
					printf("*****************FAILED****************\n\n");
				}
				else{
					printf("PASSED\n\n");
				}
			}
		}

		//reset test state for next player
		*state = origState;

	}
}



int main(){

	struct gameState testState;

	initTest(&testState);

	setTestHands(&testState);

	printf("\nCARD TEST 2: dominion.c - Smithy\n");
	printf("**********************************\n\n");

	runTests(&testState);
	

	return 0;
}