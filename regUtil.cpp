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

#include <filesystem>

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
	std::cout << "==========================" << std::endl;
	std::cout << "| Input customer details |" << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << "Customer name (First Last): ";
	
	std::cin.clear();
	std::cin.sync();
	std::getline(std::cin, cusName);
	
	getInputGET(cusPhone, "Customer phone (XXX-XXX-XXXX): ", "== Invalid phone number ==", checkValidPhone);
	
	std::cout << "===========================" << std::endl;
	std::cout << "| Input insurance details |" << std::endl;
	std::cout << "===========================" << std::endl;
	std::cout << "Insurer name (Name): ";
	
	std::cin.clear();
	std::cin.sync();
	std::getline(std::cin, insName);
	
	getInputGET(insPhone, "Insurer phone (XXX-XXX-XXXX): ", "== Invalid phone number ==", checkValidPhone);
	
	getInputGET(cusCopay, "Copay (AMOUNT): ", "== Invalid copay ==", checkValidNumberGT0);
	getInputGET(cusAVisit, "Number of authorized visits (AMOUNT): ", "== Invalid number of visits ==", checkValidNumberGT0);
	
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
	csvOutputFile << "Comments";
	
	// std::cout << "Done!" << std::endl;
	
	std::cin.clear();
	
	csvOutputFile.close();
	csvOutputFile.open(fileName, std::fstream::out | std::fstream::in);
	
	return csvOutputFile;
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
		std::cout << staticRef[idp].first << std::setw(31 - staticRef[idp].first.length()) << " | ";
		std::cout << staticRef[idp].second;
		
		std::cout << std::endl;
	}
}

void printData(std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	for(int idp = 0; idp < dynamicRef.size(); idp++) {
		std::cout << std::get<0>(dynamicRef[idp]) << std::setw(13 - std::get<0>(dynamicRef[idp]).length()) << " | ";
		std::cout << std::get<1>(dynamicRef[idp]) << std::setw(17 - std::get<1>(dynamicRef[idp]).length()) << " | ";
		std::cout << std::get<2>(dynamicRef[idp]) << std::setw(8 - std::get<2>(dynamicRef[idp]).length()) << " | ";
		std::cout << std::get<3>(dynamicRef[idp]) << std::setw(18 - std::get<3>(dynamicRef[idp]).length()) << " | ";
		std::cout << std::get<4>(dynamicRef[idp]);
		
		std::cout << std::endl;
	}
}

void printData(std::vector<std::string> &commentRef) {
	for(int idp = 0; idp < commentRef.size(); idp++) {
		if(idp) {
			std::cout << std::to_string(idp) + ": " << commentRef[idp] << std::endl;			
		} else {
			std::cout << commentRef[idp] << std::endl;			
		}
	}
}


void editCustomer(std::fstream &csvFile, std::string &filePath,
					std::vector<std::pair<std::string, std::string>> &staticRef,
					std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef,
					std::vector<std::string> &commentRef) {
	char userActionInput = 0;
	
	do {
		std::cout << "File Actions:" << std::endl;
		std::cout << "[1] - Edit Customer and Insurer Details" << std::endl;
		std::cout << "[2] - Edit Billing and Visitation Details" << std::endl;
		std::cout << "[3] - Edit Comments" << std::endl;
		std::cout << "[d] - Done" << std::endl;
		std::cout << "Selection: ";
		userActionInput = getche();
		std::cout << std::endl;
		
		switch(userActionInput) {
			case '1':
				system("CLS");
				editStatic(csvFile, filePath, staticRef, dynamicRef);
			break;
			case '2':
				// Edit a visitation detail
				editDynamic(staticRef, dynamicRef);
			break;
			case '3':
				system("CLS");
				editComment(commentRef);
			break;
			case 'd':
				// Quit
			break;
			default:
				// Invalid
				std::cout << "== Not an option" << std::endl;
				charBadInputReprint(6, 13);
			break;
		}
	} while(userActionInput != 'd');
}


void editStatic(std::fstream &csvFile, std::string &filePath,
				std::vector<std::pair<std::string, std::string>> &staticRef,
				std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	char usrEditInput = 0;
	std::string usrEditValueInput = "";
	std::string oldFileName = "";
	std::string newFileName = "";
	
	std::cin.clear();
	
	std::cout << "====================================" << std::endl;
	std::cout << "| Current Customer/Insurer Details |" << std::endl;
	std::cout << "====================================" << std::endl;
	printData(staticRef);
	
	std::cout << "===============================" << std::endl;
	std::cout << "| What would you like to edit |" << std::endl;
	std::cout << "===============================" << std::endl;
	do {
		std::cout << "Options:" << std::endl;;
		for(int idp = 0; idp < staticRef.size(); idp++) {
			std::cout << "[" << idp + 1 << "]: " << staticRef[idp].first << std::endl;
		}
		std::cout << "[c]: Cancel" << std::endl;
		std::cout << "Selection: ";
		usrEditInput = getche();
		
		std::cout << std::endl;

		std::cin.clear();
		std::cin.sync();

		switch(usrEditInput) {
			case '1':
				std::cout << "Current Client Name: " << staticRef[0].second << std::endl;
				std::cout << "New value: ";
				
				oldFileName = staticRef[1].second + "_" + staticRef[0].second + ".csv";
				
				std::getline(std::cin, usrEditValueInput);
				staticRef[0].second = usrEditValueInput;
				
				newFileName = staticRef[1].second + "_" + usrEditValueInput + ".csv";
				filePath = "customer_data/" + newFileName;
				
				csvFile.close();
				std::filesystem::rename("customer_data/" + oldFileName, "customer_data/" + newFileName);
				csvFile.open("customer_data/" + newFileName, std::fstream::out | std::fstream::in);
				
				usrEditInput = 'c';
			break;
			case '2':
				std::cout << "Current Client Phone: " << staticRef[1].second << std::endl;
				std::cout << "New value: ";
				
				oldFileName = staticRef[1].second + "_" + staticRef[0].second + ".csv";
				
				getInputGET(usrEditValueInput, "New phone (XXX-XXX-XXXX): ", "== Invalid phone number ==", checkValidPhone);
				staticRef[1].second = usrEditValueInput;
				
				newFileName = usrEditValueInput + "_" + staticRef[0].second + ".csv";
				filePath = "customer_data/" + newFileName;
				
				csvFile.close();
				std::filesystem::rename("customer_data/" + oldFileName, "customer_data/" + newFileName);
				csvFile.open("customer_data/" + newFileName, std::fstream::out | std::fstream::in);
				
				usrEditInput = 'c';
			break;
			case '3':
				std::cout << "Current Insurer Name:" << staticRef[2].second << std::endl;
				std::cout << "New value: ";
				
				std::getline(std::cin, usrEditValueInput);
				staticRef[2].second = usrEditValueInput;
				
				usrEditInput = 'c';
			break;
			case '4':
				std::cout << "Current Insurer Phone: " << staticRef[3].second << std::endl;
				std::cout << "New value: ";
				
				getInputGET(usrEditValueInput, "New phone (XXX-XXX-XXXX): ", "== Invalid phone number ==", checkValidPhone);
				staticRef[3].second = usrEditValueInput;
				
				usrEditInput = 'c';
			break;
			case '5':
				std::cout << "Current Client Copay: " << staticRef[4].second << std::endl;
				std::cout << "New value: ";
				
				getInputGET(usrEditValueInput, "New Copay (AMOUNT): ", "== Invalid copay ==", checkValidNumberGT0);
				staticRef[4].second = usrEditValueInput;
				
				usrEditInput = 'c';
			break;
			case '6':
				std::cout << "Current Authorized Visits: " << staticRef[5].second << std::endl;
				std::cout << "New value: ";

				getInputGET(usrEditValueInput, "New authorized visits (AMOUNT): ", "== Invalid number of visits ==", checkValidNumberGT0);
				staticRef[5].second = usrEditValueInput;
				
				for(short ids = 1; ids < dynamicRef.size(); ids++) {
					std::get<4>(dynamicRef[ids]) = std::to_string(stoi(usrEditValueInput) - ids);
				}
				
				staticRef[6].second = std::get<4>(dynamicRef[dynamicRef.size() - 1]);
				
				usrEditInput = 'c';
			break;
			case '7':
				std::cout << "Current Remaining Vists: " << staticRef[6].second << std::endl;
				std::cout << "New value: ";
				
				getInputGET(usrEditValueInput, "New remaining visits (AMOUNT): ", "== Invalid number of visits ==", checkValidNumberGT0);
				staticRef[6].second = usrEditValueInput;
				
				usrEditInput = 'c';
			break;
			case 'c':
			break;
			default:
				std::cout << "== Not an option ==" << std::endl;
				charBadInputReprint(10, 19);
			break;
		}
		
	} while(usrEditInput != 'c');


	std::cout << "================================" << std::endl;
	std::cout << "| New Customer/Insurer Details |" << std::endl;
	std::cout << "================================" << std::endl;
	printData(staticRef);
	std::cout << "================================" << std::endl;
	
	return;
}

void editDynamic(std::vector<std::pair<std::string, std::string>> &staticRef,
				std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	std::cin.clear();
	
	std::string usrEditDate;
	
	short index = 0;
	char usrEditInput = 0;
	std::string usrEditValueInput = "";
	
	do {
		std::cout << "===========================" << std::endl;
		std::cout << "| Current Customer Visits |" << std::endl;
		std::cout << "===========================" << std::endl;
		printData(dynamicRef);
		std::cout << "===========================" << std::endl;
		
		std::cout << "Options:" << std::endl;
		std::cout << "[1] Edit" << std::endl;
		std::cout << "[c] Cancel" << std::endl;
		std::cout << "Selection: ";
		usrEditInput = getche();
		std::cout << std::endl;
		
		if(dynamicRef.size() <= 1) {
			usrEditInput = 'c';
			std::cout << "== No visits on record ==" << std::endl;
		}
		
		switch(usrEditInput) {
			case '1':
				
				getInputGET(usrEditValueInput, "Date to edit (MM/DD/YYYY): ", "== Invalid Date ==", checkValidDate);
				
				for(short ids = 0; ids < dynamicRef.size(); ids++) {
					if(std::get<0>(dynamicRef[ids]) == usrEditValueInput) {
						index = ids;
					}
				}
				
				if(index) {
					do {
						std::cout << "Options:" << std::endl;
						std::cout << "[1] Date" << std::endl;
						std::cout << "[2] Amount Billed" << std::endl;
						std::cout << "[3] Copay" << std::endl;
						std::cout << "[4] Deductible Met" << std::endl;
						std::cout << "[5] Number Remaning Visits" << std::endl;
						std::cout << "[c] Cancel" << std::endl;
						std::cout << "Selection: ";
						usrEditInput = getche();
						std::cout << std::endl;
						
						switch(usrEditInput) {
							case '1':
								std::cout << "Current date: " << std::get<0>(dynamicRef[index]) << std::endl;
								std::cout << "New date (MM/DD/YYYY): ";
								
								getInputGET(usrEditValueInput, "New date: ", "== Invalid date ==", checkValidDate);
								std::get<0>(dynamicRef[index]) = usrEditValueInput;
								
								usrEditInput = 'c';
							break;
							case '2':
								std::cout << "Current bill: " << std::get<1>(dynamicRef[index]) << std::endl;
								std::cout << "New value: ";
								
								getInputGET(usrEditValueInput, "New bill: ", "== Invalid amount ==", checkValidNumberGT0);
								std::get<1>(dynamicRef[index]) = usrEditValueInput;
								
								usrEditInput = 'c';
							break;
							case '3':
								std::cout << "Current copay: " << std::get<2>(dynamicRef[index]) << std::endl;
								std::cout << "New value: ";
								
								getInputGET(usrEditValueInput, "New copay: ", "== Invalid amount ==", checkValidNumberGT0);
								std::get<2>(dynamicRef[index]) = usrEditValueInput;
																
								usrEditInput = 'c';
							break;
							case '4':
								std::cout << "Current deductible fullfillment: " << std::get<3>(dynamicRef[index]) << std::endl;
								std::cout << "New state (YES/NO): ";
								
								std::cin >> usrEditValueInput;
								std::get<3>(dynamicRef[index]) = usrEditValueInput;
								
								usrEditInput = 'c';
							break;
							case '5':
								std::cout << "Current remaining visits: " << std::get<4>(dynamicRef[index]) << std::endl;
								std::cout << "New value: ";
								
								getInputGET(usrEditValueInput, "New visits: ", "== Invalid amount ==", checkValidNumberGT0);
								std::get<4>(dynamicRef[index]) = usrEditValueInput;
								
								staticRef[6].second = usrEditValueInput;
								
								// TODO Update staticlly set auth visits and other visits
								for(short ids = index; ids < dynamicRef.size(); ids++) {
									std::get<4>(dynamicRef[ids]) = std::to_string(stoi(usrEditValueInput) - 1 - (ids - index));
								}
								
								usrEditInput = 'c';
							break;
							default:
								std::cout << "== Not an option ==" << std::endl;
								charBadInputReprint(8, 19);
							break;
						}
					} while(usrEditInput != 'c');
					
					std::cout << "===========================" << std::endl;
					std::cout << "| Updated Customer Visits |" << std::endl;
					std::cout << "===========================" << std::endl;
					printData(dynamicRef);
					std::cout << "===========================" << std::endl;
					
				} else {
					std::cout << "== Date not on record == " << std::endl;
				}
				
			break;
			case 'c':
			break;
			default:
				std::cout << "== Not an option ==" << std::endl;
				charBadInputReprint(9 + dynamicRef.size(), 19);
			break;
		}
	} while(usrEditInput != 'c');
}

void editComment(std::vector<std::string> &commentRef) {
	std::cin.clear();
	char usrEditInput = 0;
	std::string usrEditValueInput = "";
	
	do {
		std::cout << "Options:" << std::endl;
		std::cout << "[1] Edit Comment" << std::endl;
		std::cout << "[2] Add Comment" << std::endl;
		std::cout << "[3] Delete Comment" << std::endl;
		std::cout << "[c] Cancel" << std::endl;
		std::cout << "Selection: ";
		usrEditInput = getche();
		
		std::cout << std::endl;
		
		switch(usrEditInput) {
			case '1':
				
				if(commentRef.size() > 1) {
					do {
						std::cout << "====================" << std::endl;
						std::cout << "| Current Comments |" << std::endl;
						std::cout << "====================" << std::endl;
						printData(commentRef);
						std::cout << "====================" << std::endl;
						std::cout << "Edit which comment: ";
						usrEditInput = getche();
						std::cout << std::endl;
						
						if(usrEditInput - '0' < 0 || usrEditInput - '0' >= commentRef.size()) {
							std::cout << "== Not an option ==" << std::endl;
							charBadInputReprint(commentRef.size() + 5, 19);
						}
					} while(usrEditInput - '0' < 0 || usrEditInput - '0' >= commentRef.size());
			
					std::cout << std::endl;			
					std::cout << "New Comment: " << std::endl;
					
					std::cin.clear();
					std::cin.sync();
					std::getline(std::cin, usrEditValueInput);
					
					commentRef[usrEditInput - '0'] = usrEditValueInput;
				} else {
					std::cout << "====================" << std::endl;
					std::cout << "| Current Comments |" << std::endl;
					std::cout << "====================" << std::endl;
					std::cout << "== No comments ==" << std::endl;
				}
				
				usrEditInput = 'c';
			break;
			case '2':
				std::cout << "New Comment:" << std::endl;
		
				std::cin.clear();
				std::cin.sync();
				std::getline(std::cin, usrEditValueInput);
		
				commentRef.push_back(usrEditValueInput);
				
				usrEditInput = 'c';
			break;
			case '3':
				
				if(commentRef.size() > 1) {
					do {
						std::cout << "====================" << std::endl;
						std::cout << "| Current Comments |" << std::endl;
						std::cout << "====================" << std::endl;
						printData(commentRef);
						std::cout << "====================" << std::endl;
						std::cout << "Delete which comment: ";
						usrEditInput = getche();
						std::cout << std::endl;
						
						if(usrEditInput - '0' < 0 || usrEditInput - '0' >= commentRef.size()) {
							std::cout << "== Not an option ==" << std::endl;
							charBadInputReprint(commentRef.size() + 5, 19);
						}
					} while(usrEditInput - '0' < 0 || usrEditInput - '0' >= commentRef.size());
			
					commentRef.erase(commentRef.begin() + (usrEditInput - '0'));
				} else {
					std::cout << "== No comments ==" << std::endl;
				}
				
				usrEditInput = 'c';
			break;
			case 'c':
			break;
			default:
				std::cout << "== Not an option ==" << std::endl;
				charBadInputReprint(6, 19);
			break;
		}
	} while(usrEditInput != 'c');
}


void billCustomer(std::vector<std::pair<std::string, std::string>> &staticRef,
					std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef) {
	std::string billDate;
	std::string billAmount;
	std::string billCopay;
	std::string billDeductibleMet;
	std::string billRemainVisit;
	
	char usrEditInput = ' ';
	char billDeductibleInput = ' ';
	
	std::cout << "=============================" << std::endl;
	std::cout << "|      Billing Customer     |" << std::endl;
	std::cout << "=============================" << std::endl;
	
	if(checkValidNumberLT0(staticRef[6].second) || checkValidNumberEQ0(staticRef[6].second)) {
		std::cout << "=============================" << std::endl;
		std::cout << "|          Warning          |" << std::endl;
		std::cout << "| No more visits authorized |" << std::endl;
		std::cout << "=============================" << std::endl;
	}
	
	std::cout << "=============================" << std::endl;
	std::cout << "|      Previous Visits      |" << std::endl;
	std::cout << "=============================" << std::endl;
	printData(dynamicRef);
	std::cout << "=============================" << std::endl;;
	
	do {
		std::cout << "Options:" << std::endl;
		std::cout << "[1] Continue" << std::endl;
		std::cout << "[c] Cancel" << std::endl;
		std::cout << "Selection: ";
		usrEditInput = getche();
		std::cout << std::endl;
		
		std::cin.clear();
		
		switch(usrEditInput) {
			case '1':
				getInputGET(billDate, "Date of service (MM/DD/YYYY): ", "== Invalid Date ==", checkValidDate);
				getInputGET(billAmount, "Service bill: ", "== Invalid Amount ==", checkValidNumberGT0);
				
				
				do {
					std::cout << "Copay changed?" << std::endl;
					std::cout << "[1] Yes" << std::endl;
					std::cout << "[2] No" << std::endl;
					std::cout << "Selection: ";
					usrEditInput = getche();
					std::cout << std::endl;
					
					if(usrEditInput != '1' && usrEditInput != '2') {
						std::cout << "== Not an option ==" << std::endl;
						charBadInputReprint(4, 19);
					}
					
				} while(usrEditInput != '1' && usrEditInput != '2');
				
				if(usrEditInput == '1') {
					getInputGET(billCopay, "New copay: ", "== Invalid Amount ==", checkValidNumberGT0);					
					staticRef.at(4).second = billCopay;
				} else {
					billCopay = staticRef.at(4).second;
				}
				
					
				do {
					std::cout << "Was the deductible met?" << std::endl;
					std::cout << "[1] Yes" << std::endl;
					std::cout << "[2] No" << std::endl;
					std::cout << "Selection: ";
					billDeductibleInput = getche();
					std::cout << std::endl;
					
					if(billDeductibleInput != '1' && billDeductibleInput != '2') {
						std::cout << "== Not an option ==" << std::endl;
						charBadInputReprint(4, 19);
					}
					
				} while(billDeductibleInput != '1' && billDeductibleInput != '2');
				
				if(billDeductibleInput == '1') {
					billDeductibleMet = "YES";
				} else {
					billDeductibleMet = "NO";
				}
				
				billRemainVisit = std::to_string(std::stoi(staticRef.at(6).second) - 1);
				staticRef.at(6).second = billRemainVisit;
				
				dynamicRef.push_back(make_tuple(billDate, billAmount, billCopay, billDeductibleMet, billRemainVisit));
				
				std::cin.clear();
				
				usrEditInput = 'c';
			break;
			case 'c':
			break;
			default:
				std::cout << "== Not an option ==" << std::endl;
				charBadInputReprint(4, 19);
			break;
		}
		
	} while(usrEditInput != 'c');
}

void writeCustomer(std::fstream &csvFile, std::string &filePath,
					std::vector<std::pair<std::string, std::string>> &staticRef,
					std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> &dynamicRef,
					std::vector<std::string> &commentRef) {
	csvFile.close();
	
	csvFile.open(filePath, std::fstream::out | std::fstream::trunc);
	
	csvFile.clear();
	csvFile.seekg(0);
	
	for(int i = 0; i < 7; i++) {
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
		
		if(idp < commentRef.size() - 1) {
			csvFile << '\n';
		}
	}
}