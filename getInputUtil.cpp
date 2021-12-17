#include <iostream>

#include <ios>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <functional>

#include <vector>
#include <tuple>
#include <utility>
#include <string>

#include <windows.h>
#include <stdlib.h>

#include "getInputUtil.h"

// TODO: Add bars and pretty printing

void getInputGET(std::string& target, std::string CpromptMSG, std::string CerrorMSG, std::function<bool(std::string)>Fcheck) {
	bool isValid = false;
	
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	do {
		std::cout << CpromptMSG;
		std::getline(std::cin, target);
		
		isValid = !Fcheck(target);
		
		if(isValid) {
			std::cout << CerrorMSG <<std::endl;
			Sleep(1000);
			// system("CLS");
		}
		
	} while(isValid);
}

void getInputCIN(std::string& target, std::string CpromptMSG, std::string CerrorMSG, std::function<bool(std::string)>Fcheck) {
	
}

void getInputCHAR(char& target, std::string CpromptMSG, std::string CerrorMSG, std::function<bool(std::string)>Fcheck) {
	
}