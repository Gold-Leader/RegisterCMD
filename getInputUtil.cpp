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
	
	do {
		std::cout << CpromptMSG;
		
		std::cin.clear();
		std::cin.sync();
		std::getline(std::cin, target);
		
		isValid = !Fcheck(target);
		
		if(isValid) {
			std::cout << CerrorMSG <<std::endl;
			Sleep(1000);
			// system("CLS");
		}
		
	} while(isValid);

	std::cin.clear();
}

void getInputCIN(std::string& target, std::string CpromptMSG, std::string CerrorMSG, std::function<bool(std::string)>Fcheck) {
	
}

void getInputCHAR(char& target, std::string CpromptMSG, std::string CerrorMSG, std::function<bool(std::string)>Fcheck) {
	
}

void charBadInputReprint(short numRow, short numCol) {
	Sleep(500);
	std::cout << "\x1b[1A";
	std::cout << "\x1b[" + std::to_string(numCol) + "D";
	
	for(short idp = 0; idp < numCol; idp++) {
		std::cout << " ";
	}
	
	std::cout << "\x1b[" + std::to_string(numCol) + "D";
	std::cout << "\x1b[" + std::to_string(numRow) + "A";
}