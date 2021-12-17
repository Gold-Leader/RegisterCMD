#include <iostream>

#include <ios>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <vector>
#include <tuple>
#include <utility>
#include <string>

#include <stdlib.h>
#include <conio.h>

#include "regUtil.h"
#include "fileUtil.h"
// #include "cusUtil.h"
// #include "cusBar.h"
// #include "cusPrint.h"

int main () {
	char usrOptionInput = 0;
	std::string usrPathInput = "";
	
	std::string filePath = "";
	
	std::vector<std::string> fileDir;
	std::vector<std::pair<std::string, std::string>> staticData;
	std::vector<std::tuple<std::string, std::string, std::string, std::string>> dynamicData;
	std::vector<std::string> commentData;
	
	std::fstream csvFile;
	
	getDir("customer_data", fileDir);
	
	while(usrOptionInput != 'q') {
		std::cout << "Make selection:" << std::endl;
		std::cout << "[1] - Lookup Customer" << std::endl;
		std::cout << "[2] - Create Customer" << std::endl;
		std::cout << "[q] - Exit Application" << std::endl;
		std::cout << "Selection: ";
		
		usrOptionInput = getche();
		std::cout << std::endl;
		
		int searchCounter = 0;

		switch(usrOptionInput) {
			case '1':
				
				do {
					std::cout << "Input customer phone number (XXX-XXX-XXXX): ";
					std::cin >> usrPathInput;
					// std::cout << usrPathInput << std::endl;
					
					filePath = searchDir(fileDir, usrPathInput);
					
					if(filePath == "") {
						std::cout << "File not found!" << std::endl;
						searchCounter++;
					}
				} while(filePath == "" && searchCounter < 6);
				
				if(searchCounter >= 6) {
					std::cout << "Please verify the customer exists." << std::endl;
					std::cout << "Current customers in database." << std::endl;
					
					printDir(fileDir);
					
					std::cout << "Press any key to continue." << std::endl;
					
					while(!getch()) {
						
					}

					break;
				}
				
				csvFile = openFile(filePath);

				readCustomerStatic(csvFile, staticData);
				readCustomerDynamic(csvFile, dynamicData);
				readCustomerComment(csvFile, commentData);

				printData(staticData);
				printData(dynamicData);
				printData(commentData);

				do {
					std::cout << "Actions:" << std::endl;
					std::cout << "[1] - Bill Customer" << std::endl;
					std::cout << "[2] - Edit Customer" << std::endl;
					std::cout << "[3] - Delete Customer" << std::endl;
					std::cout << "[m] - Return to Menu" << std::endl;
					std::cout << "Selection: ";
					usrOptionInput = getche();
					
					switch(usrOptionInput) {
						case '1':
							// [1] Bill
						break;
						case '2':
							// [2] Update/Edit
							editCustomer(staticData, dynamicData, commentData);
						break;
						case '3':
							// [3] Delete
						break;
						case 'm':
							// [m] Return to menu
						break;
						default:
							// Error message
							std::cout << "Invalid Input" << std::endl;
						break;
					}			
				} while(usrOptionInput != 'm');
			break;
			
			case '2':
				csvFile = createCustomer("customer_data");
				
				readCustomerStatic(csvFile, staticData);
				readCustomerDynamic(csvFile, dynamicData);
				readCustomerComment(csvFile, commentData);
				
				printData(staticData);
				printData(dynamicData);
				printData(commentData);
				
				// cls
				// Update fileDir vector
				getDir("customer_data", fileDir);

				do {
					usrOptionInput = getche();
					
					switch(usrOptionInput) {
						case '1':
							// [1] Bill
						break;
						case '2':
							// [2] Update/Edit
						break;
						case '3':
							// [3] Delete
						break;
						case 'm':
							// [m] Return to menu
						break;
						default:
							// Error message
							std::cout << "Invalid Input" << std::endl;
						break;
					}			
				} while(usrOptionInput != 'm');
			break;
			
			default:
				// Error message
				std::cout << "Invalid Input" << std::endl;
			break;
		}
	}

	std::cout << "Exiting Application" << std::endl;

	csvFile.close();
	
	return 0;
}