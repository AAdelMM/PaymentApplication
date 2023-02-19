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
                                printf("okkkk");
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
    //compare card expiry date with the transaction date 
    //copy card date and transaction date in to new variables
    strcpy(termData->transactionDate, T_date);
    strcpy(cardData->cardExpirationDate, date);
   // printf("first date %s  second date %s",date, T_date);
    //yT_date = strcat(T_date[8] + T_date[9]);
    
   // mT_date = T_date[3] + T_date[4];
    printf(">>>> %s >>>>> %s", yT_date, mT_date);
    //get current date


/* 
    SYSTEMTIME t; // Declare SYSTEMTIME struct

    GetLocalTime(&t); // Fill out the struct so that it can be used

    // Use GetSystemTime(&t) to get UTC time 

    printf("Year: %d, Month: %d, Day: %d, Hour: %d, Minute:%d, Second: %d, Millisecond: %d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds); // Return year, month, day, hour, minute, second and millisecond in that order */

    //compare to dates

    return terminalErrors;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    return terminalErrors;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    return terminalErrors;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
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