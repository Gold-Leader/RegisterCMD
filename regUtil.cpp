#include <iostream>

#include <ios>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <vector>
#include <tuple>
#include <utility>
#include <string>

#include <windows.h>
#include <stdlib.h>

#include "regUtil.h"
#include "procInputUtil.h"
#include "getInputUtil.h"

std::ofstream createCustomer() {
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
	
	std::ofstream file;
	
	std::vector<std::pair<std::string, std::string>> staticData;
	
	// A " " char appears to be delimiter for << input stream
	// Use getline for strings with " " chars or potential delimiters
	std::cout << "Input customer details." << std::endl;
	std::cout << "Customer name (First Last): ";
	std::getline(std::cin, cusName);
	
	getInputGET(cusPhone, "Customer phone (XXX-XXX-XXXX): ", "That does not appear to be a valid phone number.", checkValidPhone);
	
	std::cout << "Input insurer details." << std::endl;
	std::cout << "Insurer name (Name): ";
	std::getline(std::cin, insName);
	
	getInputGET(insPhone, "Insurer phone (XXX-XXX-XXXX): ", "That does not appear to be a valid phone number.", checkValidPhone);
	
	getInputGET(tmpCopay, "Copay (AMOUNT): ", "Invalid copay.", checkValidNumberGT0);
	getInputGET(tmpAVisit, "Number of authorized visits (AMOUNT): ", "Invalid number of visits", checkValidNumberGT0);

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
	fileName = cusPhone + '_' + cusName;
	
	return file;
	
}