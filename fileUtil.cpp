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
#include "procInputUtil.h"

void getDir(std::string dirPath, std::vector<std::string> &dirFiles) {
	std::filesystem::path directory{dirPath};
	
	dirFiles.clear();
	
	for(auto& directoryEntry: std::filesystem::directory_iterator{directory}) {
		dirFiles.push_back(directoryEntry.path().string());
	}
}

void printDir(std::vector<std::string> &dirFiles) {
	for(int idp = 0; idp < dirFiles.size(); idp++) {
		dirFiles[idp].erase(dirFiles[idp].end() - 4, dirFiles[idp].end());
		dirFiles[idp].erase(0, 14);
		
		std::cout << std::to_string(idp) + ": " << dirFiles[idp] << std::endl;
	}
}

std::string searchDir(std::vector<std::string> &dirArr, std::string target) {
	
	for(int idx = 0; idx < dirArr.size(); idx++) {
		if(checkValidPhone(target)) {
			if(dirArr[idx].find(target) != std::string::npos) {
				return dirArr[idx];
			}
		} else {
			return "";
		}
	}
		
	return "";
}

std::fstream openFile(std::string targetFile) {
	std::fstream currFile;
	currFile.open(targetFile, std::fstream::in | std::fstream::out);
	
	return currFile;
}