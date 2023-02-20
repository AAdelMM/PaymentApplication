#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "server.h"

/* Global array */
ST_accountsDB_t accountsDB[255] =
{
	{ 2000.0, RUNNING, "8569432456781456" },
	{ 3000.0, BLOCKED, "4566266456589725" },
	{ 4500.0, RUNNING, "5233004009887225" },
	{ 6700.0, BLOCKED, "3215588799965545" },
	{ 10000.0, RUNNING, "9666333335545487" },
	{ 12000.0, BLOCKED, "8456652245658793" },
	{ 9000.0, RUNNING, "6263565997807508" },
	{ 8000.0, BLOCKED, "3358065963483406" },
	{ 11000.0, RUNNING, "4068975151313987" },
	{ 10000.0, BLOCKED, "2652623873444840" }
};


ST_accountsDB_t* accountsDBptr = accountsDB; // to search for a valid account
ST_accountsDB_t* valid_account_ptr = 0; // to store the address of the valid account

ST_transaction_t transactionsDB[255] = { 0 };
ST_transaction_t* transactionsDBpointer = transactionsDB;
ST_transaction_t* transaction_reference = 0; // the pointer used to access transactionsDB array

EN_transState_t transaction_state = 0;
uint32_t transactionsDB_index = 0; // index to be added on transactionDBptr to access transactionsDB array

/* Server-side Functions */
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t trans_error_type = 0;
	EN_serverError_t account_validity = 0;
	EN_serverError_t account_state = 0;
	EN_serverError_t amount_availability = 0;
	EN_serverError_t transaction_saved = 0;
	ST_transaction_t* save_transaction_ptr = transData;

	account_validity = isValidAccount(userCardPointer, accountsDBptr);
	account_state = isBlockedAccount(valid_account_ptr);
	amount_availability = isAmountAvailable(terminalPointer, valid_account_ptr); 

	if (account_validity == ACCOUNT_NOT_FOUND)
	{
		trans_error_type = FRAUD_CARD;
		transaction_state = FRAUD_CARD;
	}
	else if (account_state == BLOCKED_ACCOUNT)
	{
		trans_error_type = DECLINED_STOLEN_CARD;
		transaction_state = DECLINED_STOLEN_CARD;
	}
	else if (amount_availability == LOW_BALANCE)
	{
		trans_error_type = DECLINED_INSUFFECIENT_FUND;
		transaction_state = DECLINED_INSUFFECIENT_FUND;
	}
	else
	{
		trans_error_type = APPROVED;
		transaction_state = APPROVED;
		valid_account_ptr->balance = valid_account_ptr->balance - terminalPointer->transAmount;
	}

	transaction_saved = saveTransaction(save_transaction_ptr);
	if (transaction_saved != SERVER_OK)
	{
		trans_error_type = INTERNAL_SERVER_ERROR;
		transaction_state = INTERNAL_SERVER_ERROR;
	}

	return trans_error_type;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t server_error_type = 0;
	uint32_t PAN_cmp = 0;
	valid_account_ptr = 0;

	for (uint16_t i = 0; i < 10; i++)
	{
		PAN_cmp = 0;
		PAN_cmp = strcmp(cardData->primaryAccountNumber, accountRefrence->primaryAccountNumber);

		if (PAN_cmp == 0)
		{
			server_error_type = SERVER_OK;
			valid_account_ptr = accountRefrence;
			break;
		}
		accountRefrence++;
	}

	if (valid_account_ptr == 0)
	{
		server_error_type = ACCOUNT_NOT_FOUND;
	}


	return  server_error_type;

}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t server_error_type = 0;
	if (accountRefrence != 0)
	{
		if (accountRefrence->state == RUNNING)
		{
			server_error_type = SERVER_OK;
		}
		else if (accountRefrence->state == BLOCKED)
		{
			server_error_type = BLOCKED_ACCOUNT;
		}
	}


	return  server_error_type;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	EN_serverError_t server_error_type = 0;
	if (accountRefrence != 0)
	{
		if (termData->transAmount > accountRefrence->balance)
		{
			server_error_type = LOW_BALANCE;
		}
		else
		{
			server_error_type = SERVER_OK;
		}
	}

	return  server_error_type;

}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	EN_serverError_t server_error_type = SERVER_OK;

	transData = transData + transactionsDB_index;
	transaction_reference = transData;

	strcpy(transData->cardHolderData.cardHolderName, userCardPointer->cardHolderName);
	strcpy(transData->cardHolderData.cardExpirationDate, userCardPointer->cardExpirationDate);
	strcpy(transData->cardHolderData.primaryAccountNumber, userCardPointer->primaryAccountNumber);

	strcpy(transData->terminalData.transactionDate, terminalPointer->transactionDate);
	transData->terminalData.transAmount = terminalPointer->transAmount;
	transData->terminalData.maxTransAmount = terminalPointer->maxTransAmount;

	transData->transState = transaction_state;

	transData->transactionSequenceNumber = 1 + transactionsDB_index;

	listSavedTransactions();

	transactionsDB_index++;

	return server_error_type;
}

void listSavedTransactions(void)
{
	printf("#########################");
	printf("\n");
	printf("Transaction Sequence Number: %ld", transaction_reference->transactionSequenceNumber);
	printf("\n");
	printf("Transaction Date: %s", transaction_reference->terminalData.transactionDate);
	printf("\n");
	printf("Transaction Amount: %f", transaction_reference->terminalData.transAmount);
	printf("\n");
	switch (transaction_reference->transState)
	{
	case APPROVED:
		printf("Transaction State: Approved");
		break;

	case DECLINED_INSUFFECIENT_FUND:
		printf("Transaction State: Declined -> Insufficient fund");
		break;

	case DECLINED_STOLEN_CARD:
		printf("Transaction State: Declined -> Blocked Account");
		break;

	case FRAUD_CARD:
		printf("Transaction State: Declined -> Fraud Card");
		break;

	case INTERNAL_SERVER_ERROR:
		printf("Transaction State: Declined -> Internal Server Error");
		break;
	}
	printf("\n");
	printf("Terminal Max Amount: %f", transaction_reference->terminalData.maxTransAmount);
	printf("\n");
	printf("Cardholder Name: %s", transaction_reference->cardHolderData.cardHolderName);
	printf("\n");
	printf("PAN: %s", transaction_reference->cardHolderData.primaryAccountNumber);
	printf("\n");
	printf("Card Expiration Date: %s", transaction_reference->cardHolderData.cardExpirationDate);
	printf("\n");
	printf("#########################");
	printf("\n");
}
