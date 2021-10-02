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

#include <boost/filesystem.hpp>

#include "fileUtil.h"

std::vector<std::string> getDir(std::string dirPath) {
	std::vector<std::string> fileNameArr;
	
	if(boost::filesystem::exists(dirPath)) {
		boost::filesystem::directory_iterator dirItr(dirPath);
		boost::filesystem::directory_iterator dirEnd;
		
		
		// Go look at directory_iterator type (is it just a pointer?)
		while(dirItr != dirEnd) {
			fileNameArr.push_back(dirItr->path().filename().string());
			dirItr++;
		}
	}
	
	return fileNameArr;
}

std::string searchDir(std::vector<std::string> dirArr, std::string target) {
	
}

std::ifstream openFile(std::string target) {
	
}