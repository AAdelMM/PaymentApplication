#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#define _NO_CRT_STDIO_INLINE
#include "card.h"


//getting card holder name
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	//uint8_t name[25] = { 0 };
	//uint8_t name[25];
	printf("Please enter your name as shown in your card \nName: ");
	gets(name);
	
	
	length = strlen(name);                              //check the number of characters in input name.
	printf("\nNumber of characters is : %d\n", length);
	if (length < 20 || length > 24) {                //if the name is less than 20 or greater than 24 then its wrong number
		errorCases = WRONG_NAME;
	}
	else {
		errorCases = CARD_OK;
		printf("\n\tBefore");
		strcpy(cardData->cardHolderName,name );
		printf("\n\t%s",cardData->cardHolderName);
		
		
	}
	return errorCases;
}

//getting card expiry date 
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("Please enter card expiry date in this format MM/YY\nExpiry Date: ");
	gets(date);
	length = strlen(date);

	if (length == 5 && date[2] == '/') {    //checking data format
		
		if (date[0] == '1' || date[0] == '0') {         //first number must be 0 or 1
			
			if (date[0] == '0' && date[1] <= '9') {      //second number between 1 & 9

				if (date[3] == '2' && '3' <= date[4] <= '5') {
					
					if (date[3] == '2') {                   //third number must equal 2

						if (date[4] >= '3' && date[4] <= '5') {        //fourth number not greater than 5

							errorCases = CARD_OK;
							strcpy(cardData->cardExpirationDate,date);

						}
						else {
							errorCases = WRONG_EXP_DATE;
						}

					}
					else {
						errorCases = WRONG_EXP_DATE;
					}
				}
				else {
					errorCases = WRONG_EXP_DATE;
				} 
					
			}else if (date[0] = '1' && date[1] <= '2') {

				if (date[3] == '2') {                   //third number must equal 2

					if (date[4] >= '3' && date[4] <= '5') {        //fourth number not greater than 5

						errorCases = CARD_OK;
						strcpy(cardData->cardExpirationDate,date);
						
					}
					else {
						errorCases = WRONG_EXP_DATE;
					}
					
				}
				else {
					errorCases = WRONG_EXP_DATE;
				}
			}
			else {
				errorCases = WRONG_EXP_DATE;
			}
		}
		else {
			errorCases = WRONG_EXP_DATE;
		}
	
	}
	else {
		errorCases = WRONG_EXP_DATE;
	}

	return errorCases;
}

//getting card pan number
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	printf("Please enter IPAN as shown in your card\nIPAN: ");
	gets(&number);
	printf("number is :%s\n", number);
	length = strlen(number);
	printf("the number of characters :%d\n",length);                     
	if (length >= 19 || length < 16) {
		errorCases = WRONG_PAN;
	}
	else {
		for (int i=0;i<=length;i++){
			if ((number[i]>='a' && number[i]<='z') || (number[i]>='A' && number[i]<='Z')){    //check if the number contains alphabatic character
				errorCases = WRONG_PAN;
				break;
			}else{
				errorCases = CARD_OK;
				strcpy(cardData->primaryAccountNumber, number);
			}
	    }
		}

	return errorCases;
}

//******************************************************
//************Card Name Test Function*******************
//******************************************************

void getCardHolderNameTest(void) {

//testing if name is ok
	//uint8_t name[25] = { 0 };
	getCardHolderName(&cardData);
	printf("Tester Name : Ahmed Adel\nFunction Name : getCardHolderName\n");
	printf("Test Case1 : input correct name\nInput Data : %s\n",name);
	printf("Expected Resault : NAME IS OK \n");
	if (errorCases == 0) { strcpy(actr, "NAME IS OK"); }
	else if (errorCases == 1) { strcpy(actr, "NAME IS WRONG"); };
	printf("Actual Result :%s\n", actr);

//testing if name is null

	getCardHolderName(&cardData);
	printf("Tester Name : Ahmed Adel\nFunction Name : getCardHolderName\n");
	printf("Test Case2 : input incorrect name \nInput Data : %s\n", name);
	printf("Expected Resault : NAME IS WRONG \n");
	if (errorCases == 0) { strcpy(actr, "NAME IS OK"); }
	else if (errorCases == 1) { strcpy(actr, "NAME IS WRONG"); };
	printf("Actual Result :%s\n", actr);

//testing if name is less than 20 chars

	getCardHolderName(&cardData);
	printf("Tester Name : Ahmed Adel\nFunction Name : getCardHolderName\n");
	printf("Test Case2 : input null \nInput Data : %s\n", name);
	printf("Expected Resault : NAME IS WRONG \n");
	if (errorCases == 0) { strcpy(actr, "NAME IS OK"); }
	else if (errorCases == 1) { strcpy(actr, "NAME IS WRONG"); };
	printf("Actual Result :%s\n", actr);

}

//******************************************************
//************Card Date Test Function*******************
//******************************************************

void getCardExpiryDateTest(void)    
{
	getCardExpiryDate(&cardData);

	//test if enterd valid date

	printf("\nTester Name : Ahmed Adel\nFunction Name : getCardExpiryDateTest\n");
	printf("Test Case 1: Correct Date\n");
	printf("Input Data: %s\n", date);
	printf("Expected Data: DATE IS OK!!\n");
	if (errorCases == 0) { strcpy(actr, "DATE IS OK"); }
	else if (errorCases == 2) { strcpy(actr, "DATE IS WRONG"); };
	printf("Actual Result :%s\n", actr);

	//test if not enter '/' sign

	getCardExpiryDate(&cardData);

	printf("\nTester Name : Ahmed Adel\nFunction Name : getCardExpiryDateTest\n");
	printf("Test Case 2: wrong '/' sign\n");
	printf("Input Data: %s\n", date);
	printf("Expected Data: DATE IS WRONG!!\n");
	if (errorCases == 0) { strcpy(actr, "DATE IS OK"); }
	else if (errorCases == 2) { strcpy(actr, "DATE IS WRONG"); };
	printf("Actual Result :%s\n", actr);

	//test invalid date

	getCardExpiryDate(&cardData);

	printf("\nTester Name : Ahmed Adel\nFunction Name : getCardExpiryDateTest\n");
	printf("Test Case 3: invalid date\n");
	printf("Input Data: %s\n", date);
	printf("Expected Data: DATE IS WRONG!!\n");
	if (errorCases == 0) { strcpy(actr, "DATE IS OK"); }
	else if (errorCases == 2) { strcpy(actr, "DATE IS WRONG"); };
	printf("Actual Result :%s\n", actr);

}

//*****************************************************
//************Card PAN Test Function*******************
//***************************************************** 

void getCardPANTest(void)
{
	//test valid number 
	getCardPAN(&cardData);

	printf("\nTester Name : Ahmed Adel\nFunction Name : getCardPANTest\n");
	printf("Test Case 1: Valid Number\n");
	printf("Input Data: %s\n", number);
	printf("Expected Data: NUMBER IS OK!!\n");
	if (errorCases == 0) { strcpy(actr, "NUMBER IS OK"); }
	else if (errorCases == 3) { strcpy(actr, "NUMBER IS WRONG"); };
	printf("Actual Result :%s\n", actr);

	//test invalid number 
	getCardPAN(&cardData);

	printf("\nTester Name : Ahmed Adel\nFunction Name : getCardPANTest\n");
	printf("Test Case 2: inValid Number\n");
	printf("Input Data: %s\n", number);
	printf("Expected Data: NUMBER IS WRONG!!\n");
	if (errorCases == 0) { strcpy(actr, "NUMBER IS OK"); }
	else if (errorCases == 3) { strcpy(actr, "NUMBER IS WRONG"); };
	printf("Actual Result :%s\n", actr);

	//test null number 
	getCardPAN(&cardData);

	printf("\nTester Name : Ahmed Adel\nFunction Name : getCardPANTest\n");
	printf("Test Case 3: NULL Number\n");
	printf("Input Data: %s\n", number);
	printf("Expected Data: NUMBER IS WRONG!!\n");
	if (errorCases == 0) { strcpy(actr, "NUMBER IS OK"); }
	else if (errorCases == 3) { strcpy(actr, "NUMBER IS WRONG"); };
	printf("Actual Result :%s\n", actr);

}



