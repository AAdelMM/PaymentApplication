#include <stdio.h>
#include "app.h"


void appStart(void)
{
	//getCardHolderName(&cardData);
	//getCardHolderNameTest();         //for testing name function.
	// 
	getCardExpiryDate(&cardData);
	//getCardExpiryDateTest();           //for testing date function.
	// 
	//getCardPAN(&cardData);
	//getCardPANTest();                  //for testing IPAN function. 
	// 
	getTransactionDate(&termData);
	//getTransactionDateTest();            //for testing transaction entry date.
	// 
	isCardExpired(&cardData, &termData);
	printf("%d", terminalErrors);
	
}
