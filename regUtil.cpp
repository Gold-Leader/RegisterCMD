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
void printCSV(std::fstream& csvFile) {
	csvFile.clear();
	// Files are zero-indexed
	csvFile.seekg(0);
	
	std::string input = "";
	
	for(int idp = 0; idp < 6; idp++) {
		std::getline(csvFile, input);
		std::cout << input << std::endl;
	}
	
	while(!csvFile.eof()) {
		std::getline(csvFile, input);
		std::cout << input << std::endl;
	}
}

void readCustomerStatic(std::fstream& csvFile, std::vector<std::pair<std::string, std::string>> &staticRef) {
	std::string delimiter = ",";
	
	csvFile.clear();
	csvFile.seekg(0);
	
	std::string input;
	std::string output[2];
	
	for(int idr = 0; idr < 6; idr++) {
		std::getline(csvFile, input);
		
		output[0] = input.substr(0, input.find(delimiter));
		input.erase(0, input.find(delimiter) + delimiter.length());
		output[1] = input.substr(0, input.find(delimiter));
		
		staticRef.push_back({output[0], output[1]});
	}	
}

void readCustomerDynamic(std::fstream& csvFile, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	std::string delimiter = ",";
	
	std::string input;
	std::string output[6];
	
	std::getline(csvFile, input);
	std::getline(csvFile, input);
	
	while(input != "") {
		for(int idr = 0; idr < 6; idr++) {
			output[idr] = input.substr(0, input.find(delimiter));
			input.erase(0, input.find(delimiter) + delimiter.length());			
		}
		
		dynamicRef.push_back(make_tuple(output[0], output[1], output[2], output[3], output[4], output[5]));
		std::getline(csvFile, input);
	}
	
	// csvFile.clear();
	// csvFile.seekg(0);
}

void readCustomerComment(std::fstream& csvFile, std::vector<std::string> &commentRef) {
	std::string delimiter = ",";
	
	std::string input;
	std::string output;
	
	std::getline(csvFile, input);
	
	while(std::getline(csvFile, input)) {		
		commentRef.push_back(output);
	}
}

void printData(std::vector<std::pair<std::string, std::string>> &staticRef) {
	for(int idp = 0; idp < staticRef.size(); idp++) {
		std::cout << staticRef[idp].first << staticRef[idp].second << std::endl;
	}
}

void printData(std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	for(int idp = 0; idp < dynamicRef.size(); idp++) {
		std::cout << std::get<0>(dynamicRef[idp]) << " | ";
		std::cout << std::get<1>(dynamicRef[idp]) << " | ";
		std::cout << std::get<2>(dynamicRef[idp]) << " | ";
		std::cout << std::get<3>(dynamicRef[idp]) << " | ";
		std::cout << std::get<4>(dynamicRef[idp]) << " | ";
		std::cout << std::get<5>(dynamicRef[idp]) << " | ";
		
		std::cout << std::endl;
	}
	
}

void printData(std::vector<std::string> &commentRef) {
	for(int idp = 0; idp < commentRef.size(); idp++) {
		std::cout << commentRef[idp] << std::endl;
	}
}


void editCustomer(std::vector<std::pair<std::string, std::string>> &staticRef, std::vector<std::tuple<std::string, int, std::string, std::string, std::string, int>> &dynamicRef) {
	
}

void billCustomer(std::vector<std::tuple<std::string, int, std::string, std::string, std::string, int>> &dynamicRef) {
	// Get amount to bill
	// Get amount date of billing
	// Ask if 
}