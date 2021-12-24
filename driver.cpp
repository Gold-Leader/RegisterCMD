#include <iostream>
#include <windows.h>

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

#include <filesystem>

#include "regUtil.h"
#include "fileUtil.h"
#include "getInputUtil.h"
// #include "cusUtil.h"
// #include "cusBar.h"
// #include "cusPrint.h"

#include "customer.h"

int main () {
	system("CLS");
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwOriginalOutMode = 0;
    if (!GetConsoleMode(hOut, &dwOriginalOutMode))
    {
        return false;
    }

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
	
	SetConsoleMode(hOut, dwOutMode);
	
	char usrOptionInput = 0;
	std::string usrPathInput = "";
	
	customerObj customer;
	
	std::vector<std::string> fileDir;
	
	std::fstream csvFile;
	
	getDir("customer_data", fileDir);
	
	do {
		std::cout << "==============================" << std::endl;
		std::cout << "|  Welcome to Amy's Massage  |" << std::endl;
		std::cout << "|    Customer Management     |" << std::endl;
		std::cout << "|            ----            |" << std::endl;
		std::cout << "|       Make Selection       |" << std::endl;
		std::cout << "==============================" << std::endl;
		std::cout << "[1] - Lookup Customer" << std::endl;
		std::cout << "[2] - Create Customer" << std::endl;
		std::cout << "[q] - Exit Application" << std::endl;
		std::cout << "Selection: ";
		
		usrOptionInput = getche();
		std::cout << std::endl;
		
		int searchCounter = 0;

		switch(usrOptionInput) {
			case '1':
				system("CLS");
				do {
					std::cout << "Input customer phone number (XXX-XXX-XXXX): ";
					std::cin >> usrPathInput;
					// std::cout << usrPathInput << std::endl;
					
					customer.filePath = searchDir(fileDir, usrPathInput);
					
					if(customer.filePath == "") {
						std::cout << "== File not found ==" << std::endl;
						Sleep(1000);
						charBadInputReprint(1, 21);
						
						searchCounter++;
					}
				} while(customer.filePath == "" && searchCounter < 6);
				
				if(searchCounter >= 6) {
					system("CLS");
					
					std::cout << "=====================================" << std::endl;
					std::cout << "| Please verify the customer exists |" << std::endl;
					std::cout << "|        Customers in database      |" << std::endl;
					std::cout << "=====================================" << std::endl;
					
					printDir(fileDir);
					
					std::cout << "=============================" << std::endl;
					std::cout << "| Press any key to continue |" << std::endl;
					std::cout << "=============================" << std::endl;					
					
					while(!getch()) {
						
					}

					break;
				}
				
				csvFile = openFile(customer.filePath);

				customer.staticData.clear();
				customer.dynamicData.clear();
				customer.commentData.clear();

				readCustomerStatic(csvFile, customer.staticData);
				readCustomerDynamic(csvFile, customer.dynamicData);
				readCustomerComment(csvFile, customer.commentData);
				
				std::cout << "===========================" << std::endl;
				std::cout << "| Retrieved Customer Data |" << std::endl;
				std::cout << "===========================" << std::endl;
				
				printData(customer.staticData);
				std::cout << std::endl;
				printData(customer.dynamicData);
				std::cout << std::endl;
				printData(customer.commentData);
				std::cout << "===========================" << std::endl;

				do {
					std::cout << "File Actions:" << std::endl;
					std::cout << "[1] - Bill Customer" << std::endl;
					std::cout << "[2] - Edit Customer" << std::endl;
					std::cout << "[3] - Delete Customer" << std::endl;
					std::cout << "[m] - Return to Menu" << std::endl;
					std::cout << "Selection: ";
					
					usrOptionInput = getche();
					std::cout << std::endl;
					
					switch(usrOptionInput) {
						case '1':
							// [1] Bill
							system("CLS");
							billCustomer(customer.staticData, customer.dynamicData);
							writeCustomer(csvFile, customer.staticData, customer.dynamicData, customer.commentData);
						break;
						case '2':
							// [2] Update/Edit
							system("CLS");
							editCustomer(customer.staticData, customer.dynamicData, customer.commentData);
							writeCustomer(csvFile, customer.staticData, customer.dynamicData, customer.commentData);
						break;
						case '3':
							csvFile.close();
							try {
								std::filesystem::rename("customer_data" + customer.filePath, "old_customer_data" + customer.filePath.erase(0, 13));
							} catch(std::filesystem::filesystem_error& e) {
								std::cout << "File either deleted or does not exist" << std::endl;
								printDir(fileDir);
							}
							// [3] Delete
						break;
						case 'm':
							// [m] Return to menu
							// Update file and close
							system("CLS");
							csvFile.close();
						break;
						default:
							// Error message
							std::cout << "== Invalid Input ==" << std::endl;
							charBadInputReprint(6, 19);
							
						break;
					}			
				} while(usrOptionInput != 'm' && usrOptionInput != '3');
			break;
			
			case '2':
				system("CLS");
				std::cin.clear();
			
				csvFile = createCustomer("customer_data");
				
				customer.staticData.clear();
				customer.dynamicData.clear();
				customer.commentData.clear();
				
				readCustomerStatic(csvFile, customer.staticData);
				readCustomerDynamic(csvFile, customer.dynamicData);
				readCustomerComment(csvFile, customer.commentData);
				
				std::cout << "===========================" << std::endl;
				std::cout << "| Retrieved Customer Data |" << std::endl;
				std::cout << "===========================" << std::endl;
				
				printData(customer.staticData);
				std::cout << std::endl;
				printData(customer.dynamicData);
				std::cout << std::endl;
				printData(customer.commentData);
				std::cout << "===========================" << std::endl;
				
				// Update fileDir vector
				getDir("customer_data", fileDir);

				do {
					std::cout << "File Actions:" << std::endl;
					std::cout << "[1] - Bill Customer" << std::endl;
					std::cout << "[2] - Edit Customer" << std::endl;
					std::cout << "[3] - Delete Customer" << std::endl;
					std::cout << "[m] - Return to Menu" << std::endl;
					std::cout << "Selection: ";
					
					usrOptionInput = getche();
					std::cout << std::endl;
					
					switch(usrOptionInput) {
						case '1':
							// [1] Bill
							system("CLS");
							billCustomer(customer.staticData, customer.dynamicData);
							writeCustomer(csvFile, customer.staticData, customer.dynamicData, customer.commentData);
						break;
						case '2':
							// [2] Update/Edit
							system("CLS");
							editCustomer(customer.staticData, customer.dynamicData, customer.commentData);
							writeCustomer(csvFile, customer.staticData, customer.dynamicData, customer.commentData);
						break;
						case '3':
							// [3] Delete
						break;
						case 'm':
							// [m] Return to menu
							// Update file and close
							system("CLS");
							csvFile.close();
						break;
						default:
							// Error message
							std::cout << "== Invalid Input ==" << std::endl;
							charBadInputReprint(6, 19);
						break;
					}			
				} while(usrOptionInput != 'm');
			break;
			
			case 'q':
				// do nothing
				std::cout << "== Exitting application ==" << std::endl;
			break;
			default:
				// Error message
				std::cout << "== Invalid Input ==" << std::endl;
				charBadInputReprint(5, 19);
			break;
		}
	}while(usrOptionInput != 'q') ;

	csvFile.close();
	
	return 0;
}