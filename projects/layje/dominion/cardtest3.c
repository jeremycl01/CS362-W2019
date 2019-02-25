/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 3 - Card Test 3 - Council Room
 * 2/4/19
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "interface.h"
#include <limits.h>
#include <string.h>


//initialize test gameStruct
void initTest(struct gameState* testState){
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(3, k, 9, testState);
}

//set player hands for testing
//3 players are set to have same hands; position of council room card is only difference
void setTestHands(struct gameState* state){
	//set player 1's hand
	int player1 = 0, player2 = 1, player3 = 2;

	state -> hand[player1][0] = council_room;
	state -> hand[player1][1] = estate;
	state -> hand[player1][2] = copper;
	state -> hand[player1][3] = silver;
	state -> hand[player1][4] = gold;
	state -> hand[player1][5] = adventurer;
	state -> hand[player1][6] = province;
	state -> hand[player1][7] = smithy;
	state -> hand[player1][8] = village;

	state -> handCount[player1] = 9;

	state -> hand[player2][0] = adventurer;
	state -> hand[player2][1] = estate;
	state -> hand[player2][2] = copper;
	state -> hand[player2][3] = silver;
	state -> hand[player2][4] = gold;
	state -> hand[player2][5] = council_room;
	state -> hand[player2][6] = province;
	state -> hand[player2][7] = smithy;
	state -> hand[player2][8] = village;

	state -> handCount[player2] = 9;

	state -> hand[player3][0] = adventurer;
	state -> hand[player3][1] = estate;
	state -> hand[player3][2] = copper;
	state -> hand[player3][3] = silver;
	state -> hand[player3][4] = gold;
	state -> hand[player3][5] = village;
	state -> hand[player3][6] = province;
	state -> hand[player3][7] = smithy;
	state -> hand[player3][8] = council_room;

	state -> handCount[player3] = 9;

}


//boolean function determines whether council room is in a player's hand
int crInHand(struct gameState* state, int player){

	int i = 0;

	for(i = 0; i < state -> handCount[player]; i++){
		if (state -> hand[player][i] == council_room){
			return 1;
		}
	}
	
	return 0;
}

//boolean function determines whether council room is in the played cards pile
int crInPlayed(struct gameState* state){

	int i = 0;

	for(i = 0; i < state -> playedCardCount; i++){
		if (state -> playedCards[i] == council_room){
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

//test council room. the expected effects are:
//add 4 cards to hand of player using council room from player's deck
//add 1 card to each other player's hand from their deck
//1 additional buy for player
//remove council room from hand of player using council room and place in played cards pile

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

		//increment number of buys available for each player
		//to test effect on different number of buys
		state -> numBuys = i + 1;

		//save state prior to cardEffect/council room call
		struct gameState origState = *state;

		printf("******TESTING PLAYER %d PLAYS COUNCIL ROOM*******\n\n", i + 1);

		//call cardEffect with council room
		cardEffect(council_room, dummyInt, dummyInt, dummyInt, state, handPos[i], &dummyInt);

		printf("*******COUNCIL ROOM PLAYED*******\n\n");
		
		displayAllHands(state);


		//test that council room has been replaced in the player's hand
		printf("COUNCIL ROOM CARD REPLACED WITH ANOTHER CARD\n");
		if (state -> hand[i][handPos[i]] == council_room){
			printf("*****************FAILED****************\n\n");
		}
		else{
			printf("PASSED\n\n");
		}

		//test that council room has been placed in the played cards pile
		printf("COUNCIL ROOM CARD NOW IN PLAYER'S PLAYED CARDS PILE\n");
		if (!crInPlayed(state)){
			printf("*****************FAILED****************\n\n");
		}
		else{
			printf("PASSED\n\n");
		}

		//test that Council Room has been replaced in the player's hand 
		//with four additional cards (net +3)
		printf("COUNCIL ROOM CARD REPLACED WITH 4 OTHER CARDS\n");
		if (state -> handCount[i] != origState.handCount[i] + 3){
			printf("*****************FAILED****************\n\n");
			printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
				   origState.handCount[i], origState.handCount[i] + 3, state -> handCount[i]);
		}
		else{
			printf("PASSED\n\n");
		}


		//test that new card came from current player's pile
		printf("REPLACEMENT CARDS CAME FROM PLAYER'S DECK\n");
		if (!(state -> deckCount[i] < origState.deckCount[i])){
			printf("*****************FAILED****************\n\n");
			printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
				   origState.deckCount[i], origState.deckCount[i] - 4, state -> deckCount[i]);
		}
		else{
			printf("PASSED\n\n");
		}

		//test that player's cards are the same except for the cards
		//that replaced council room
		printf("PLAYER %d'S ORIGINAL CARDS (ASIDE FROM COUNCIL ROOM) UNCHANGED\n", i + 1);

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

		//test that other players have 1 additional card 
		for (j = 0; j < state -> numPlayers; j++){
			//don't run test for current player
			if (j != i){
				printf("PLAYER %d HAS 1 CARD ADDED\n", j + 1);

				if (!(state -> handCount[j] == origState.handCount[j] + 1)){
					printf("*****************FAILED****************\n\n");
					printf("ORIG COUNT: %d EXPECTED: %d  CURR COUNT: %d\n\n", 
				   origState.handCount[j], origState.handCount[j] + 1, state -> handCount[j]);
				}
				else{
					printf("PASSED\n\n");
				}
			}
		}

		//test that other players' cards are the same except for the original cards
		//remain in hand 

		for (j = 0; j < state -> numPlayers; j++){

			if (j != i){

				printf("PLAYER %d'S ORIGINAL CARDS UNCHANGED\n", j + 1);

				if (!sameCardsExPos(&origState, state, j, handPos[j])){
					printf("*****************FAILED****************\n\n");
				}
				else{
					printf("PASSED\n\n");
				}
			}
		}


		//test that 1 buy has been added to curr player
		//NOTE: numBuys is only stored in gameState for curr player
		//therefore, no value to check for other players
		printf("1 BUY ADDED TO CURR PLAYER\n");
		if (state -> numBuys == (origState.numBuys) + 1){
			printf("PASSED\n\n");
		}
		else{
			printf("*****************FAILED****************\n\n");
			printf("ORIG BUYS: %d\nCURR BUYS: %d\n\n", origState.numBuys, state -> numBuys);
		}

		//reset test state for next player
		*state = origState;

	}
}



int main(){

	struct gameState testState;

	initTest(&testState);

	setTestHands(&testState);

	printf("\nCARD TEST 3: dominion.c - Council Room\n");
	printf("**********************************\n\n");

	runTests(&testState);
	

	return 0;
}