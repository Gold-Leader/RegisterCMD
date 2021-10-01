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
		
	std::fstream csvOutputFile;
	
	std::cout << "Make selection:" << std::endl;
	std::cout << "[1] - Lookup Customer" << std::endl;
	std::cout << "[2] - Create Customer" << std::endl;
	std::cout << "[3] - Delete Customer" << std::endl;
	std::cout << "[q] - Quit" << std::endl;
	std::cout << "Selection: " << std::endl;
	
	switch() {
		case 1:
			
			break;
		
		case 2:
			csvOutputFile = createCustomer();			
			break;
		case 3:
		
			
			break;
		
		default:
			
		break;
	}
	
	
	csvOutputFile.close();
	
	return 0;
}