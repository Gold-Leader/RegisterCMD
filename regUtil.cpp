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
#include <conio.h>

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
	
	Date,Amount Billed,Date Billed,Number Remaining Visits
	(this \n is not a mistake)
	*/
	// std::cout << "Creating file" << std::endl;
	fileName = dir + "/" + cusPhone + '_' + cusName + ".csv";
	csvOutputFile.open(fileName, std::fstream::out);
	
	// std::cout << "Writing data" << std::endl;
	for(int i = 0; i < 6; i++) {
		// Can also using [i] instead of .at(i)
		// .at(), .first, .second return pointers if type NOT a primitive
		// or string
		csvOutputFile << staticData.at(i).first;
		csvOutputFile << ',';
		csvOutputFile << staticData.at(i).second;
		csvOutputFile << '\n';
	}
	
	csvOutputFile << "Remaining authorized visits";
	csvOutputFile << ",";
	csvOutputFile << staticData.at(5).second;
	csvOutputFile << '\n';
	
	csvOutputFile << '\n';
	csvOutputFile << "Date,Amount Billed,Copay,Deductible Met,Number Remaining Visits";
	csvOutputFile << '\n';
	csvOutputFile << '\n';
	csvOutputFile << "Comments:";
	
	// std::cout << "Done!" << std::endl;
	
	std::cin.clear();
	
	csvOutputFile.close();
	csvOutputFile.open(fileName, std::fstream::out | std::fstream::in);
	
	return csvOutputFile;
}

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
	
	std::getline(csvFile, input);
	
	while(input != "") {
		for(int idr = 0; idr < 2; idr++) {
			output[idr] = input.substr(0, input.find(delimiter));
			input.erase(0, input.find(delimiter) + delimiter.length());			
		}
		staticRef.push_back({output[0], output[1]});
		std::getline(csvFile, input);
	}
}

void readCustomerDynamic(std::fstream& csvFile, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	std::string delimiter = ",";
	
	std::string input;
	std::string output[4];
	
	std::getline(csvFile, input);
	
	while(input != "") {
		for(int idr = 0; idr < 4; idr++) {
			output[idr] = input.substr(0, input.find(delimiter));
			input.erase(0, input.find(delimiter) + delimiter.length());			
		}
		
		dynamicRef.push_back(make_tuple(output[0], output[1], output[2], output[3], output[4]));
		std::getline(csvFile, input);
	}
}

void readCustomerComment(std::fstream& csvFile, std::vector<std::string> &commentRef) {
	std::string input;
	std::string output;
	
	// std::getline(csvFile, input);
	
	while(!csvFile.eof()) {
		std::getline(csvFile, output);
		commentRef.push_back(output);
	}
	
	csvFile.clear();
	csvFile.seekg(0);
}

void printData(std::vector<std::pair<std::string, std::string>> &staticRef) {
	for(int idp = 0; idp < staticRef.size(); idp++) {
		std::cout << staticRef[idp].first  << " | ";
		std::cout << staticRef[idp].second;
		
		std::cout << std::endl;
	}
}

void printData(std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	for(int idp = 0; idp < dynamicRef.size(); idp++) {
		std::cout << std::get<0>(dynamicRef[idp]) << " | ";
		std::cout << std::get<1>(dynamicRef[idp]) << " | ";
		std::cout << std::get<2>(dynamicRef[idp]) << " | ";
		std::cout << std::get<3>(dynamicRef[idp]) << " | ";
		std::cout << std::get<4>(dynamicRef[idp]);
		
		std::cout << std::endl;
	}
}

void printData(std::vector<std::string> &commentRef) {
	for(int idp = 0; idp < commentRef.size(); idp++) {
		std::cout << commentRef[idp] << std::endl;
	}
}


void editCustomer(std::vector<std::pair<std::string, std::string>> &staticRef, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef, std::vector<std::string> &commentRef) {
	char userActionInput = 0;
	
	
	do {
		std::cout << "Actions:" << std::endl;
		std::cout << "[1] - Edit Customer and Insurer Details" << std::endl;
		std::cout << "[2] - Edit Billing and Visitation Details" << std::endl;
		std::cout << "[3] - Edit or Add Comment" << std::endl;
		std::cout << "[d] - Done" << std::endl;
		std::cout << "Selection: ";
		userActionInput = getche();
		
		switch(userActionInput) {
			case '1':
				// Edit static stuff/customer and insurer details
				editStatic(staticRef);
			break;
			case '2':
				// Edit a visitation detail
				// editDynamic(dynamicRef);
			break;
			case '3':
				// Add/remove a comment
				// editComment(commentRef);
			break;
			case 'd':
				// Quit
			break;
			default:
				// Invalid
			break;
		}
	} while(userActionInput != 'd');
}


void editStatic(std::vector<std::pair<std::string, std::string>> &staticRef) {
	// Print data
	// Ask which one to edit
	// Call check functions as needed
	// Edit the value
	// Return
	std::cin.clear();
	
	char usrEditInput = 0;
	std::string usrEditValueInput = "";
	
	std::cout << "Current Customer/Insurer Details" << std::endl;
	printData(staticRef);
	
	std::cout << "What would you like to edit:" << std::endl;
	for(int idp = 0; idp < staticRef.size(); idp++) {
		std::cout << idp << ": " << staticRef[idp].first << std::endl;
	}
	do {
		std::cout << "Option: ";
		usrEditInput = getche();
		
		// usrEditInput is a character but can be converted to an integer equivalent via 'char' - '0'
		// Boundaries are between 0 and size of staticRef
		if(usrEditInput - '0' < 0 || usrEditInput - '0' >= staticRef.size()) {
			std::cout << "Not an option!" << std::endl;
		}
		
	} while(usrEditInput - '0' < 0 || usrEditInput - '0' >= staticRef.size());
	
	std::cout << "Current value: " << staticRef[usrEditInput - '0'].first << staticRef[usrEditInput - '0'].second << std::endl;
	std::cout << "New value: ";
	std::getline(std::cin, usrEditValueInput);
	
	staticRef[usrEditInput - '0'].second = usrEditValueInput;
	printData(staticRef);
	
	return;
}

void editDynamic(std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	std::cin.clear();
	
	std::string usrEditDate;
	
	char usrEditInput = 0;
	std::string usrEditValueInput = "";
	
	std::cout << "Current Customer Visits" << std::endl;
	printData(dynamicRef);
	
	std::cout << "Which entry at which date would you like to edit:" << std::endl;
	
	
	// Print data
	// Ask to edit OR add
	// Call check functions as needed
	// Edit or add comment
	// Return
}

void editComment(std::vector<std::string> &commentRef) {
	// Print data
	// Ask to edit OR add
	// Edit or add comment
	// Return
	
	std::cin.clear();
}


void billCustomer(std::vector<std::pair<std::string, std::string>> &staticRef,
					std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	std::string billDate;
	std::string billAmount;
	std::string billCopay;
	std::string billDeductibleMet;
	std::string billRemainVisit;
	
	char billDeductibleInput = ' ';
	
	std::cin.clear();
	
	getInputGET(billDate, "Date of service: ", "Invalid Date!", checkValidDate);
	getInputGET(billAmount, "How much to bill: ", "Invalid Amount!", checkValidNumberGT0);
	getInputGET(billCopay, "Copay: ", "Invalid Amount!", checkValidNumberGT0);
	
	if(billCopay != staticRef.at(4).second)
		staticRef.at(4).second = billCopay;
	
	std::cout << "Was the deductible met?" << std::endl;
		
	do {
		billDeductibleInput = getche();
		std::cout << std::endl;
		
		if(billDeductibleInput != 'y' && billDeductibleInput != 'n') {
			std::cout << "Invalid" << std::endl;
		}
		
	} while(billDeductibleInput != 'y' && billDeductibleInput != 'n');
	
	if(billDeductibleInput == 'y')
		billDeductibleMet = "YES";
	if(billDeductibleInput == 'n')
		billDeductibleMet = "NO";
	
	billRemainVisit = std::to_string(std::stoi(staticRef.at(6).second) - 1);
	staticRef.at(6).second = billRemainVisit;
	
	dynamicRef.push_back(make_tuple(billDate, billAmount, billCopay, billDeductibleMet, billRemainVisit));
	
	std::cin.clear();
}

void writeCustomer(std::fstream &csvFile,
					std::vector<std::pair<std::string, std::string>> &staticRef,
					std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef,
					std::vector<std::string> &commentRef) {
	csvFile.clear();
	csvFile.seekg(0);
	
	for(int i = 0; i < 7; i++) {
		// Can also using [i] instead of .at(i)
		// .at(), .first, .second return pointers if type NOT a primitive
		// or string
		csvFile << staticRef.at(i).first;
		csvFile << ',';
		csvFile << staticRef.at(i).second;
		csvFile << '\n';
	}
	
	csvFile << '\n';
	
	for(int idp = 0; idp < dynamicRef.size(); idp++) {
		csvFile << std::get<0>(dynamicRef[idp]) << ",";
		csvFile << std::get<1>(dynamicRef[idp]) << ",";
		csvFile << std::get<2>(dynamicRef[idp]) << ",";
		csvFile << std::get<3>(dynamicRef[idp]) << ",";
		csvFile << std::get<4>(dynamicRef[idp]);
		
		csvFile << '\n';
	}
	
	csvFile << '\n';
	
	for(int idp = 0; idp < commentRef.size(); idp++) {
		csvFile << commentRef[idp];
		
		csvFile << '\n';
	}
}