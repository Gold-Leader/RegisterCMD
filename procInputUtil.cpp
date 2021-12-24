#include <iostream>
#include <ctype.h>
#include <string>

#include "procInputUtil.h"

// TODO: Add bars and pretty printing

bool checkValidPhone(std::string phone) {
	bool dashIdx[2] = {false};
	// Initialize to 0 dummy
	short numDigit = 0;
	
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
	
	// std::cout << dashIdx[0] << dashIdx[1] << numDigit;
	
	return ((dashIdx[0] && dashIdx[1] && true) && numDigit == 10);
}

bool checkValidDate(std::string date) {
	bool slashIdx[2] = {false};
	short numDigit = 0;
	
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
	
	return ((slashIdx[0] && slashIdx[1] && true) && numDigit == (date.length() - 2));
}

bool checkValidNumber(std::string number) {
	short numDigit = 0;
	
	for(int i = 0; i < number.length(); i++) {
		if(isdigit(number[i])) {
			numDigit++;
		}
	}
	
	return numDigit;
}

bool checkValidNumberGT0(std::string number) {
	return !(number[0] == '-');
}


bool checkValidNumberLT0(std::string number) {
	short numDigit;
	float tmpValue;
	
	for(int i = 0; i < number.length(); i++) {
		if(isdigit(number[i])) {
			numDigit++;
		}
	}
	
	if(numDigit == number.length()) {
		tmpValue = std::stof(number);
	}
	
	return numDigit && (tmpValue <= 0);
}

bool checkValidNumberEQ0(std::string number) {
	short numDigit;
	float tmpValue;
	
	for(int i = 0; i < number.length(); i++) {
		if(isdigit(number[i])) {
			numDigit++;
		}
	}
	
	if(numDigit == number.length()) {
		tmpValue = std::stof(number);
	}
	
	return numDigit && (tmpValue == 0);
}