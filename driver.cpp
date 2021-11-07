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
	char usrInput = 0;
	
	std::string filePath;
	
	std::vector<std::string> fileDir;
	std::vector<std::pair<std::string, std::string>> staticData;
	std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string, std::string>> dynamicData;
	// fileDir.clear();
	
	std::fstream csvFile;
	
	getDir("customer_data", fileDir);
	printDir(fileDir);
	
	std::cout << "Make selection:" << std::endl;
	std::cout << "[1] - Lookup Customer" << std::endl;
	std::cout << "[2] - Create Customer" << std::endl;
	std::cout << "[q] - Quit" << std::endl;
	std::cout << "Selection: " << std::endl;
	
	std::string temp2 = "";
	usrInput = 1;
	
	switch(usrInput) {
		case 1:
			// Ask
			// xxx-xxx-xxxx or first last
			// Search function,
			filePath = searchDir(fileDir, "MODTEST_Angel_9717196804");
			
			csvFile = openFile(filePath);
			
			printCSV(csvFile);
			
			readCustomerStatic(csvFile, staticData);
			readCustomerDynamic(csvFile, dynamicData);
			
				// Ask for input if failed
				// Keep track of attempts
				// Quit to menu if too many attempts
				
			// On success read file contents
			
			// Ask
			// [1] Bill
			// [2] Update
			// [3] Delete
			// [m] Return to menu
			// Loop until m entered
			break;
		
		case 2:
			csvFile = createCustomer("customer_data");
			// cls
			// Update fileDir vector
			getDir("customer_data", fileDir);
			// Print customer out
			// Ask
			// [1] Bill
			// [2] Update
			// [m] Return to menu
			// Loop until m entered
			break;
		
		default:
			// Error message
		break;
	}
		
	csvFile.close();
	
	return 0;
}