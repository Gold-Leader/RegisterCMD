#include <iostream>
#include <functional>
#include <string>

#ifndef GETINPUTUTIL_H
#define GETINPUTUTIL_H

void getInputGET(std::string&, std::string, std::string, std::function<bool(std::string)>);
void getInputCIN(std::string&, std::string, std::string, std::function<bool(std::string)>);

void getInputCHAR(char&, std::string, std::string, std::function<bool(std::string)>);

#endif