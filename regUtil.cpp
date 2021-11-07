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

// TODO: Add bars and pretty printing

std::fstream createCustomer(std::string dirParam) {
	std::string dir = dirParam;
	std::string fileName;
	
	std::string cusName;
	std::string cusPhone;
	std::string insName;
	std::string insPhone;
	
	std::string cusCopay;
	std::string cusAVisit;
	
	std::fstream csvOutputFile;
	
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
	
	getInputGET(cusCopay, "Copay (AMOUNT): ", "Invalid copay.", checkValidNumberGT0);
	getInputGET(cusAVisit, "Number of authorized visits (AMOUNT): ", "Invalid number of visits", checkValidNumberGT0);
	
	staticData.push_back({"Client Name", cusName});
	staticData.push_back({"Client Phone", cusPhone});
	staticData.push_back({"Insurer Name", insName});
	staticData.push_back({"Insurer Phone", insPhone});
	staticData.push_back({"Client Copay", cusCopay});
	staticData.push_back({"Client Authorized Visits", cusAVisit});
	
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
	fileName = dir + "/" + cusPhone + '_' + cusName + ".csv";
	csvOutputFile.open(fileName, std::fstream::out | std::fstream::in);
	
	for(int i = 0; i < 6; i++) {
		// Can also using [i] instead of .at(i)
		// .at(), .first, .second return pointers if type NOT a primitive
		// or string
		csvOutputFile << staticData.at(i).first;
		csvOutputFile << ',';
		csvOutputFile << staticData.at(i).second;
		csvOutputFile << '\n';
	}
	
	csvOutputFile << '\n';
	csvOutputFile << "Date,Amount Billed,Date Billed,Date of Referral,Date Requiring new Referral,Number Remaining Visits";
	csvOutputFile << '\n';
	
	return csvOutputFile;
}

// std::fstream findCustomer(std::string);
// std::fstream readCustomer();
void printCustomer(std::fstream& csvFile) {
	csvFile.clear();
	// Files are zero-indexed
	csvFile.seekg(0);
	
	std::string temp = "";
	
	for(int idp = 0; idp < 6; idp++) {
		std::getline(csvFile, temp);
		std::cout << temp << std::endl;
	}
	
	while(!csvFile.eof()) {
		std::getline(csvFile, temp);
		std::cout << temp << std::endl;
	}
}