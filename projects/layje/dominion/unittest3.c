/* -----------------------------------------------------------------------
 * Jeremy Lay
 * CS 362-400-W19
 * Assignment 3 - Unit Test 3 - getCost
 * 2/3/19
 * -----------------------------------------------------------------------
 */

#include <string.h>
#include "dominion.h"
#include "interface.h"


void findResult(enum CARD cardName, int cardVal){
	
	char nameStr[50];
	memset(nameStr, '\0', 50 * sizeof(char));

	cardNumToName(cardName, nameStr);

	int retVal = getCost(cardName);

	printf("%s:\n", nameStr);
	printf("VALUE: %d  FUNCTION RETURN: %d\n", cardVal, retVal);
	
	if (retVal == cardVal){
		printf("PASSED\n\n");
	}
	else{
		printf("*****************FAILED****************\n\n");
	}
}



void findResultNC(int valIn, int cardVal){
	
	int retVal = getCost(valIn);

	printf("VALUE: %d  FUNCTION RETURN: %d\n", valIn, retVal);
	
	if (retVal == cardVal){
		printf("PASSED\n\n");
	}
	else{
		printf("*****************FAILED****************\n\n");
	}
}



void runTests(){

	printf("\nCARDS: \n\n");

	//pass all cards in enum

	findResult(curse, CURSE_COST);

	findResult(estate, ESTATE_COST);

	findResult(duchy, DUCHY_COST);

	findResult(province, PROVINCE_COST);

	findResult(copper, COPPER_COST);

	findResult(silver, SILVER_COST);

	findResult(gold, GOLD_COST);

	findResult(adventurer, ADVENTURER_COST);

	findResult(council_room, COUNCIL_ROOM_COST);

	findResult(feast, FEAST_COST);

	findResult(gardens, GARDEN_COST);

	findResult(mine, MINE_COST);

	findResult(remodel, REMODEL_COST);

	findResult(smithy, SMITHY_COST);

	findResult(village, VILLAGE_COST);

	findResult(baron, BARON_COST);

	findResult(great_hall, GREAT_HALL_COST);

	findResult(minion, MINION_COST);

	findResult(steward, STEWARD_COST);

	findResult(tribute, TRIBUTE_COST);

	findResult(ambassador, AMBASSADOR_COST);

	findResult(cutpurse, CUTPURSE_COST);

	findResult(embargo, EMBARGO_COST);

	findResult(outpost, OUTPOST_COST);

	findResult(salvager, SALVAGER_COST);

	findResult(sea_hag, SEA_HAG_COST);

	findResult(treasure_map, TREASURE_MAP_COST);

	printf("\nNON-CARD VALUES: \n\n");

	//pass negative values

	findResultNC(-1, -1);

	findResultNC(-15, -1);

	//pass positive values

	findResultNC(77, -1);

	findResultNC(100, -1);


}



int main(){
	printf("\nUNIT TEST 3: dominion.c - getCost\n");
	printf("**********************************\n\n");

	runTests();
	

	return 0;
}