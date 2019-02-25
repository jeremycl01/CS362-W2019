/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 4 - Random Test 2 - Great Hall
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
void setTestHands(struct gameState* state, int player, int ghPosArr[]){
	
	int i = -5, numGameCards = 17, MAX_TEST_HAND = 100;

	//randomly select number of cards in hand
	int handCount = (rand() % MAX_TEST_HAND) + 1;
	state -> handCount[player] = handCount;

	//randomly select index position of Great Hall card to be 
	//played in random test
	int ghPos = rand() % handCount;
	state -> hand[player][ghPos] = great_hall;

	//store position of player's Great Hall card
	ghPosArr[player] = ghPos;

	//randomly select card for each of the other positions in 
	//player's hand
	for (i = 0; i < handCount; i++){
		
		if (i != ghPos){
			state -> hand[player][i] = (rand() % treasure_map) + 1;
		}
	}
}


int ghCount(int pile[], int pileSize){

	int i = -5, vils = 0;

	for (i = 0; i < pileSize; i++){
		if (pile[i] == great_hall){
			vils++;
		}
	}

	return vils;

}


//boolean function determines whether Great Hall is in a player's hand
int ghInHand(struct gameState* state, int player){

	int i = 0;

	for(i = 0; i < state -> handCount[player]; i++){
		if (state -> hand[player][i] == great_hall){
			return 1;
		}
	}
	
	return 0;
}

//boolean function determines whether Great Hall is in the played cards pile
int ghInPlayed(struct gameState* origState, struct gameState* currState){

	if (ghCount(currState -> playedCards, currState -> playedCardCount) - 
		ghCount(origState -> playedCards, origState -> playedCardCount) == 1){
		return 1;
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

//test Great Hall. the expected effects are:
//add 1 card to hand of player using Great Hall from player's deck
//add 1 action to player using Great Hall
//remove Great Hall from hand of player using Great Hall and place in played cards pile

void runTests(struct gameState* state, int ghPosArr[]){

	int dummyInt = 1, i = -1, j=-1;


	printf("STARTING HANDS:\n\n");

	displayAllHands(state);

	printf("\nTESTS: \n\n");

	//iterate through players
	for (i = 0; i < state -> numPlayers; i++){
		
		//set current player as having current turn
		state -> whoseTurn = i;

		//increment number of actions available for each player
		//to test effect on different number of actions
		state -> numActions = i + 1;

		//save state prior to cardEffect/Great Hall call
		struct gameState origState = *state;

		printf("******TESTING PLAYER %d PLAYS GREAT HALL*******\n\n", i + 1);

		//call cardEffect with Great Hall
		cardEffect(great_hall, dummyInt, dummyInt, dummyInt, state, ghPosArr[i], &dummyInt);

		printf("*******GREAT HALL PLAYED*******\n\n");
		
		displayAllHands(state);


		//test that Great Hall has been replaced in the player's hand
		printf("GREAT HALL CARD REPLACED WITH ANOTHER CARD\n");
		if (state -> hand[i][ghPosArr[i]] == great_hall || state -> handCount[i] != origState.handCount[i]){
			printf("*****************FAILED****************\n\n");
		}
		else{
			printf("PASSED\n\n");
		}

		//test that Great Hall has been placed in the played cards pile
		printf("GREAT HALL CARD NOW IN PLAYER'S PLAYED CARDS PILE\n");
		if (!ghInPlayed(&origState, state)){
			printf("*****************FAILED****************\n\n");
		}
		else{
			printf("PASSED\n\n");
		}

		//test that new card came from current player's pile
		printf("REPLACEMENT CARD CAME FROM PLAYER'S DECK\n");
		if (!(state -> deckCount[i] < origState.deckCount[i])){
			printf("*****************FAILED****************\n\n");
			printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
				   origState.deckCount[i], origState.deckCount[i] - 1, state -> deckCount[i]);
		}
		else{
			printf("PASSED\n\n");
		}

		//test that player's cards are the same except for the card
		//that replaced Great Hall
		printf("PLAYER %d'S OTHER CARDS (ASIDE FROM GREAT HALL/ADDED CARD) UNCHANGED\n", i + 1);

				if (!sameCardsExPos(&origState, state, i, ghPosArr[i])){
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


		//test that no ascpect of other players' game state has been changed by call to Great Hall
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

		//test that 1 action have been added to curr player
		//NOTE: numActions is only stored in gameState for curr player
		//therefore, no value to check for other players
		printf("1 ACTION ADDED TO CURR PLAYER\n");
		if (state -> numActions == (origState.numActions) + 1){
			printf("PASSED\n\n");
		}
		else{
			printf("*****************FAILED****************\n\n");
			printf("ORIG ACTIONS: %d\nCURR ACTIONS: %d\n\n", origState.numActions, state -> numActions);
		}
		

		//reset test state for next player
		*state = origState;

	}
}



int main(){

	srand(time(0));

	struct gameState testState;

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           great_hall, tribute, smithy};

	int numPlayers = 0, i = -5, testNo = 0, NUM_TESTS = 50;

	printf("\nRANDOM CARD TEST 1: dominion.c - Great Hall\n");
	printf("**********************************\n\n");

	for (testNo = 0; testNo < NUM_TESTS; testNo++){

		printf("TEST %d\n", testNo + 1);
		printf("**********************************\n\n");

		initTest(&testState, &numPlayers, k);

		int ghPosArr[numPlayers];

		for (i = 0; i < numPlayers; i++){
			setTestHands(&testState, i, ghPosArr);
		}

		runTests(&testState, ghPosArr);

	}

	return 0;
}