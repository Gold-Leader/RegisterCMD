#include <iostream>
#include <stdlib.h>
#include <windows.h>

#include "regUtil.h"
#include "procInputUtil.h"

std::fstream  createCustomer() {
	std::string fileName;
	
	std::string cusName;
	std::string cusPhone;
	std::string insName;
	std::string insPhone;
	
	std::string tmpCopay;
	std::string tmpAVisit;
	
	float copay;
	int numAuthVisit;
	int numRemainVisit;
	
	// A " " char appears to be delimiter for << input stream
	// Use getline for strings with " " chars or potential delimiters
	std::cout << "Input customer details." << std::endl;
	std::cout << "Name (First Last): ";
	std::getline(std::cin, cusName);
	
	do {
		std::cout << "Phone (XXX-XXX-XXXX): ";
		std::getline(std::cin, cusPhone);
		
		if(!checkValidPhone(cusPhone)) {
			std::cout << "That does not appear to be a valid phone number.";
			Sleep(1000);
			system("CLS");
		}
		
	} while(!checkValidPhone(cusPhone));
	
	std::cout << "Input insurer details." << std::endl;
	std::cout << "Name (Name): ";
	std::getline(std::cin, insName);
	
	do {
		std::cout << "Phone (XXX-XXX-XXXX): ";
		std::getline(std::cin, insPhone);
		
		if(!checkValidPhone(cusPhone)) {
			std::cout << "That does not appear to be a valid phone number.";
			Sleep(1000);
			system("CLS");
		}
		
	} while(!checkValidPhone(cusPhone));
	
	do {
		std::cout << "Copay (AMOUNT): ";
		std::cin >> copay;
		std::cin.clear();
		
		if(copay < 0) {
			std::cout << "Invalid copay.";
			Sleep(1000);
			system("CLS");
		}
		
	} while(checkValidNumber(copay) || stoi(copay) < 0);
	
	do {
		std::cout << "Number of authorized visits (AMOUNT): ";
		std::cin >> numAuthVisit;
		std::cin.clear();
		
		if(numAuthVisit < 0) {
			std::cout << "Invalid number of visits.";
			Sleep(1000);
			system("CLS");
		}
		
	} while(numAuthVisit< 0);

	fileName = cusPhone + '_' + cusName;
	
	std::cout << '\n' << std::endl;
	std::cout << "Date | Amount Billed | Date Billed | Date of Referral | Date Requiring new Referral | Number Remaining Visits" << std::endl;
	std::cout << '\n' << std::endl;
	
	// Data should resemble the following once saved:
	/*
	Client Name,[string]
	Client Phone,[string]
	Insurance Name,[string]
	Insurance Phone,[string]
	Client Copay,[float]
	Number of Authorized Visits,[int]
	Number of Remaining Visits,[int]
	
	Date,Amount Billed,Date Billed,Date of Referral,Date Requiring new Referral,Number Remaining Visits
	(this \n is not a mistake)
	*/
	
	return "help";
	
}