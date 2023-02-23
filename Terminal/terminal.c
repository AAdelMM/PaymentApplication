#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <time.h>
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    //get date from user
    printf("Please enter transaction date in this format DD/MM/YYYY: ");
    gets(T_date);
    length = strlen(T_date);
    if (length == 10){                                                    //input length must be equal 10 digits
        if (T_date[0] < '3') {                                              //check first num of MM
            if (T_date[1] <= '9') {                                         //check second num of MM
                if (T_date[2] == '/' && T_date[5] == '/') {                   //check '/' sign
                    if (T_date[6] == '2' && T_date[7] == '0') {               //first and second nums in YYYY must be 20
                        if (T_date[8] == '2' && T_date[9] > '2') {            //third num in YYYY must be 2
                            if (T_date[3] == '0' && T_date[4] <= '9') {       //month not greater than 09
                                terminalErrors = TERMINAL_OK;
                                strcpy(T_date, termData->transactionDate);
                            }
                            if (T_date[3] == '1' && T_date[4] <= '2') {       //month not greater than 12

                                terminalErrors = TERMINAL_OK;
                                strcpy(T_date, termData->transactionDate);
                            }
                            else {
                                terminalErrors = WRONG_DATE;
                                
                            }
                        }
                        else {
                            terminalErrors = WRONG_DATE;
                        }
                    }
                    else {
                        terminalErrors = WRONG_DATE;
                    }
                }
                else {
                    terminalErrors = WRONG_DATE;
                }
            }
            else {
                terminalErrors = WRONG_DATE;
            }
        }
        else {
            terminalErrors = WRONG_DATE;
        }
    }
    else{
        terminalErrors = WRONG_DATE;
    }
    return terminalErrors;  
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    terminalErrors = 0;
    uint8_t mm_trans[3] = { 0 };
    uint8_t yy_trans[3] = { 0 };
    uint8_t mm_exp[3] = { 0 };
    uint8_t yy_exp[3] = { 0 };
    uint16_t mm_trans_number = 0;
    uint16_t yy_trans_number = 0;
    uint16_t mm_exp_number = 0;
    uint16_t yy_exp_number = 0;

    mm_trans[0] = termData->transactionDate[3];
    mm_trans[1] = termData->transactionDate[4];
    mm_trans[2] = '\0';
    mm_trans_number = atoi(mm_trans);

    yy_trans[0] = termData->transactionDate[8];
    yy_trans[1] = termData->transactionDate[9];
    yy_trans[2] = '\0';
    yy_trans_number = atoi(yy_trans);

    mm_exp[0] = cardData->cardExpirationDate[0];
    mm_exp[1] = cardData->cardExpirationDate[1];
    mm_exp[2] = '\0';
    mm_exp_number = atoi(mm_exp);

    yy_exp[0] = cardData->cardExpirationDate[3];
    yy_exp[1] = cardData->cardExpirationDate[4];
    yy_exp[2] = '\0';
    yy_exp_number = atoi(yy_exp);

    if (yy_trans_number > yy_exp_number)
    {
        terminalErrors = EXPIRED_CARD;
    }
    else if (yy_trans_number < yy_exp_number)
    {
        terminalErrors = TERMINAL_OK;
    }
    else if (yy_trans_number == yy_exp_number)
    {
        if (mm_trans_number <= mm_exp_number)
        {
            terminalErrors = TERMINAL_OK;
        }
        else if (mm_trans_number > mm_exp_number)
        {
            terminalErrors = EXPIRED_CARD;
        }
    }

    return terminalErrors;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    terminalErrors = 0;
    float trans_amount = 0.0;

    printf("Enter Transaction Amount : ");
    
    scanf_s("%f", &trans_amount);

    if (trans_amount <= 0.0)
    {
        terminalErrors = INVALID_AMOUNT;
    }
    else
    {
        terminalErrors = TERMINAL_OK;
        termData->transAmount = trans_amount;
    }
    return terminalErrors;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    terminalErrors = 0; 

    if (termData->transAmount > termData->maxTransAmount)
    {
        terminalErrors = EXCEED_MAX_AMOUNT;
    }
    else
    {
        terminalErrors = TERMINAL_OK;
    }
    
    return terminalErrors;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
    terminalErrors = 0;

    if (maxAmount <= 0.0)
    {
        terminalErrors = INVALID_MAX_AMOUNT;
    }
    else
    {
        terminalErrors = TERMINAL_OK;
        termData->maxTransAmount = maxAmount;
    }
    return terminalErrors;
}


//******************************************************
//************Transaction Test Functions************
//******************************************************

void getTransactionDateTest(void)
{
    //test case 1 correct date
    getTransactionDate(&termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: Correct Format\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: DATE OK\n");
    if (terminalErrors == 0) { strcpy(actr, "DATE OK"); }
    else { strcpy(actr, "DATE WRONG"); }
    printf("Actual Result: %s\n", actr);

    //test case 2 null date
    getTransactionDate(&termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 2: Null\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: DATE WRONG\n");
    if (terminalErrors == 0) { strcpy(actr, "DATE OK"); }
    else { strcpy(actr, "DATE WRONG"); }
    printf("Actual Result: %s\n", actr);

    //test case 3 wrong format
    getTransactionDate(&termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 3: Wrong Format\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: DATE WRONG\n");
    if (terminalErrors == 0) { strcpy(actr, "DATE OK"); }
    else { strcpy(actr, "DATE WRONG"); }
    printf("Actual Result: %s\n", actr);
}

void isCardExpiredTest(void)
{
    //test case1 valid card
    isCardExpired(&cardData, &termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: valid card\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: TERMINAL_OK\n");
    if (terminalErrors == 0) { strcpy(actr, "TERMINAL_OK"); }
    else { strcpy(actr, "EXPIRED_CARD"); }
    printf("Actual Result: %s\n", actr);

    //test case2 expiry card
    isCardExpired(&cardData, &termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: expired card\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: EXPIRED_CARD\n");
    if (terminalErrors == 0) { strcpy(actr, "TERMINAL_OK"); }
    else { strcpy(actr, "EXPIRED_CARD"); }
    printf("Actual Result: %s\n", actr);
}

void getTransactionAmountTest(void)
{
    //test case1 valid amount
    getTransactionAmount(&termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: valid amount\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: TERMINAL_OK\n");
    if (terminalErrors == 0) { strcpy(actr, "TERMINAL_OK"); }
    else { strcpy(actr, "INVALIDID_AMOUNT"); }
    printf("Actual Result: %s\n", actr);

    //test case2 invalid amount
    getTransactionAmount(&termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: invalid amount\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: INValIDID_AMOUNT\n");
    if (terminalErrors == 0) { strcpy(actr, "TERMINAL_OK"); }
    else { strcpy(actr, "INVALIDID_AMOUNT"); }
    printf("Actual Result: %s\n", actr);
}

void isBelowMaxAmountTest(void)
{
    //test case1 acceptable amount
    isBelowMaxAmount(&termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: acceptable amount\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: TERMINAL_OK\n");
    if (terminalErrors == 0) { strcpy(actr, "TERMINAL_OK"); }
    else { strcpy(actr, "EXCEED_MAX_AMOUNT"); }
    printf("Actual Result: %s\n", actr);

    //test case2 exceed max amount
    isBelowMaxAmount(&termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: exceed amount\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: EXCEED_MAX_AMOUNT\n");
    if (terminalErrors == 0) { strcpy(actr, "TERMINAL_OK"); }
    else { strcpy(actr, "EXCEED_MAX_AMOUNT"); }
    printf("Actual Result: %s\n", actr);
}

void setMaxAmountTest(void)
{
    //test case1 valid amount
    setMaxAmount(&termData,termData->maxTransAmount);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: valid amount\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: TERMINAL_OK\n");
    if (terminalErrors == 0) { strcpy(actr, "TERMINAL_OK"); }
    else { strcpy(actr, "INVALID_MAX_AMOUNT"); }
    printf("Actual Result: %s\n", actr);

    //test case2 invalid max amount
    setMaxAmount(&termData, termData->maxTransAmount);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 1: invalid amount\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: INVALID_MAX_AMOUNT\n");
    if (terminalErrors == 0) { strcpy(actr, "TERMINAL_OK"); }
    else { strcpy(actr, "INVALID_MAX_AMOUNT"); }
    printf("Actual Result: %s\n", actr);
}