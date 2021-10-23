#include <iostream>

#include <ios>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <vector>
#include <tuple>
#include <utility>
#include <string>

#include <stdlib.h>
#include <conio.h>


#include "fileUtil.h"

std::vector<std::string> getDir(std::string dirPath) {
	std::vector<std::string> fileNameArr;
	
	std::filesystem::path directory{dirPath};
	

	for(auto& directoryEntry: std::filesystem::directory_iterator{directory}) {
		fileNameArr.push_back(directoryEntry.path().string());		// Explicit conversion
		std::cout << directoryEntry.path().string() << std::endl;
	}

	return fileNameArr;
}

std::string searchDir(std::vector<std::string> dirArr, std::string target) {
	
}

std::ifstream openFile(std::string target) {
	
}