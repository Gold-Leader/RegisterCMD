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

#ifndef FILEUTIL_H
#define FILEUTIL_H

std::vector<std::string> getDir(std::string);

std::string searchDir(std::vector<std::string>, std::string);

std::ifstream openFile(std::string);

#endif