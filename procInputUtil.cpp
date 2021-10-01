#include <iostream>
#include <ctype.h>
#include <string.h>

#include "procInputUtil.h"

bool checkValidPhone(std::string phone) {
	bool dashIdx[2] = {false};
	short numDigit;
	
	short j = 0;
	
	for(int i = 0; i < phone.length(); i++) {
		if(phone[i] == '-') {
			dashIdx[j] = true;
			j++;
		}
		
		if(isdigit(phone[i])) {
			numDigit++;
		}
	}
	
	return ((dashIdx[0] && dashIdx[1] && true) && numDigit == 10);
}

bool checkValidDate(std::string date) {
	bool slashIdx[2] = {false};
	short numDigit;
	
	short j = 0;
	
	for(int i = 0; i < date.length(); i++) {
		if(date[i] == '/') {
			slashIdx[j] = true;
			j++;
		}
		
		if(isdigit(date[i])) {
			numDigit++;
		}
	}
	
	return ((slashIdx[0] && slashIdx[1] && true) && numDigit == 10);
}

bool checkValidNumber(std::string currency) {
	short numDigit;
	
	for(int i = 0; i < currency.length(); i++) {
		if(isdigit(currency[i])) {
			numDigit++;
		}
	}	
	
	return numDigit;
}