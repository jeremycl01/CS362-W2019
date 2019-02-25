/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 3 - Unit Test 4 - Compare Function
 * 2/3/19
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "interface.h"
#include <limits.h>
#include <string.h>

void testReturn(int x, int y, int retVal){

	printf("X: %d, Y: %d, Return: %d\nRESULT: ", x, y, retVal);

	if ((x < y && retVal != -1) ||
	   (x > y && retVal != 1) ||
	   (x == y && retVal != 0)){
		printf("\n*****************FAILED****************\n\n");
	}
	else {
		printf("\nPASSED\n\n");
	}
	
}

void testEnum(enum CARD x, enum CARD y, int retVal){

	char nameStr1[50];
	memset(nameStr1, '\0', 50 * sizeof(char));

	char nameStr2[50];
	memset(nameStr2, '\0', 50 * sizeof(char));

	cardNumToName(x, nameStr1);

	cardNumToName(y, nameStr2);

	printf("X: %s, Y: %s, Return: %d\nRESULT: ", nameStr1, nameStr2, retVal);

	if ((x < y && retVal != -1) ||
	   (x > y && retVal != 1) ||
	   (x == y && retVal != 0)){
		printf("\n*****************FAILED****************\n\n");
	}
	else {
		printf("\nPASSED\n\n");
	}
	
}

void intTests(){
	
	printf("INTEGER TESTS\n\n");

	int NUM_INTS = 7, i = -5, j = -5;

	int ints[] = {INT_MIN, -7, -1, 0, 1, 7, INT_MAX};
	
	for (i = 0; i < NUM_INTS; i++){
		for (j = 0; j < NUM_INTS; j++){
			testReturn(ints[i], ints[j], compare(&(ints[i]), &(ints[j])));
		}
	} 
}

void enumTests(){

	enum CARD cardNames[] = {curse, estate, duchy, province, copper,
   	          silver, gold, adventurer, council_room, feast, gardens, 
   	          mine, remodel, smithy, village, baron, great_hall, minion, 
   	          steward, tribute, ambassador, cutpurse, embargo, outpost, 
   	          salvager, sea_hag, treasure_map};

   	int numCards = 27;

	printf("CARD ENUM TESTS\n\n");

	int i = -5, j = - 5;

	for (i = 0; i < numCards; i++){
		for (j = 0; j < numCards; j++){
			testEnum(cardNames[i], cardNames[j], compare(&(cardNames[i]), &(cardNames[j])));
		}
	}

}



int main(){

	printf("UNIT TEST 4: dominion.c - compare\n");
	printf("**********************************\n\n");

	intTests();

	enumTests();
	
	return 0;
}