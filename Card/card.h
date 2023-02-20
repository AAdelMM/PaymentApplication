#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned int uint16_t;
uint8_t name[25];            
int length;
char date[20];
char actr[20];
char number[50];

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t errorCases;                   


//ST_cardData_t* cardData = &getCardData;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

ST_cardData_t* cardData;

//*******note ********
//create new pointer to pass inside function

extern ST_cardData_t* userCardPointer;
#endif // !CARD_H


