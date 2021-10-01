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
// #include "cusUtil.h"
// #include "cusBar.h"
// #include "cusPrint.h"

int main () {
	char usrInput = 0;
		
	std::fstream csvFile;
	
	std::cout << "Make selection:" << std::endl;
	std::cout << "[1] - Lookup Customer" << std::endl;
	std::cout << "[2] - Create Customer" << std::endl;
	std::cout << "[q] - Quit" << std::endl;
	std::cout << "Selection: " << std::endl;
	
	switch() {
		case 1:
			// Ask
			// xxx-xxx-xxxx or first last
			// Search function
			// Ask
			// [1] Bill
			// [2] Update
			// [3] Delete
			// [m] Return to menu
			// Loop until m entered
			break;
		
		case 2:
			csvFile = createCustomer();
			// cls
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