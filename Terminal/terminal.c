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
    EN_terminalError_t expired_card_error_type = 0;
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
        expired_card_error_type = EXPIRED_CARD;
    }
    else if (yy_trans_number < yy_exp_number)
    {
        expired_card_error_type = TERMINAL_OK;
    }
    else if (yy_trans_number == yy_exp_number)
    {
        if (mm_trans_number <= mm_exp_number)
        {
            expired_card_error_type = TERMINAL_OK;
        }
        else if (mm_trans_number > mm_exp_number)
        {
            expired_card_error_type = EXPIRED_CARD;
        }
    }

    return terminalErrors;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t trans_amount_error_type = 0; // OK or INVALID_AMOUNT
    float trans_amount = 0.0;

    printf("Enter Transaction Amount : ");
    //printf("\n");
    scanf_s("%f", &trans_amount);

    if (trans_amount <= 0.0)
    {
        trans_amount_error_type = INVALID_AMOUNT;
    }
    else
    {
        trans_amount_error_type = TERMINAL_OK;
        termData->transAmount = trans_amount;
    }
    return terminalErrors;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t below_max_amout_error_type = 0; // OK or EXCEED_MAX_AMOUNT

    if (termData->transAmount > termData->maxTransAmount)
    {
        below_max_amout_error_type = EXCEED_MAX_AMOUNT;
    }
    else
    {
        below_max_amout_error_type = TERMINAL_OK;
    }
    return below_max_amout_error_type;
    return terminalErrors;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
    EN_terminalError_t max_amount_error_type = 0;

    if (maxAmount <= 0.0)
    {
        max_amount_error_type = INVALID_MAX_AMOUNT;
    }
    else
    {
        max_amount_error_type = TERMINAL_OK;
        termData->maxTransAmount = maxAmount;
    }
    return terminalErrors;
}


//******************************************************
//************Transaction date Test Function************
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
    getTransactionDate(termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 2: Null\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: DATE WRONG\n");
    if (terminalErrors == 0) { strcpy(actr, "DATE OK"); }
    else { strcpy(actr, "DATE WRONG"); }
    printf("Actual Result: %s\n", actr);

    //test case 3 wrong format
    getTransactionDate(termData);
    printf("Tester Name: Ahmed Adel\n");
    printf("Test Case 3: Wrong Format\n");
    printf("Input Data: %s\n", date);
    printf("Expected Result: DATE WRONG\n");
    if (terminalErrors == 0) { strcpy(actr, "DATE OK"); }
    else { strcpy(actr, "DATE WRONG"); }
    printf("Actual Result: %s\n", actr);
}