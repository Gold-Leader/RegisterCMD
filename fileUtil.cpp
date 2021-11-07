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

void getDir(std::string dirPath, std::vector<std::string> &dirFiles) {
	std::filesystem::path directory{dirPath};
	
	for(auto& directoryEntry: std::filesystem::directory_iterator{directory}) {
		// std::cout << directoryEntry.path().string() << std::endl;
		dirFiles.push_back(directoryEntry.path().string());		// Explicit conversion
	}
}

void printDir(std::vector<std::string> &dirFiles) {
	for(int idp = 0; idp < dirFiles.size(); idp++) {
		std::cout << dirFiles[idp] << std::endl;
		// dirFiles.push_back(directoryEntry.path().string());		// Explicit conversion
	}
}

std::string searchDir(std::vector<std::string> &dirArr, std::string target) {
	for(int idx = 0; idx < dirArr.size(); idx++)
		if(dirArr[idx].find(target) != std::string::npos)
			return dirArr[idx];
		
	return "";
}

std::fstream openFile(std::string targetFile) {
	std::fstream currFile;
	currFile.open(targetFile, std::fstream::in | std::fstream::out);
	
	return currFile;
}