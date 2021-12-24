#include <iostream>

#include <ios>
#include <iomanip>
#include <fstream>
#include <sstream>

#ifndef REGUTIL_H
#define REGUTIL_H


std::fstream createCustomer(std::string dirParam);

void readCustomerStatic(std::fstream&, std::vector<std::pair<std::string, std::string>>&);
void readCustomerDynamic(std::fstream&, std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>>&);
void readCustomerComment(std::fstream&, std::vector<std::string>&);

void printData(std::vector<std::pair<std::string, std::string>>&);
void printData(std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>>&);
void printData(std::vector<std::string>&);

void editCustomer(std::fstream&, std::string&,
				std::vector<std::pair<std::string, std::string>>&,
				std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>>&,
				std::vector<std::string>&);

void editStatic(std::fstream&, std::string&, std::vector<std::pair<std::string, std::string>>&);
void editDynamic(std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>>&);
void editComment(std::vector<std::string>&);

void billCustomer(std::vector<std::pair<std::string, std::string>> &,
					std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>>&);

void writeCustomer(std::fstream&, std::string&,
					std::vector<std::pair<std::string, std::string>> &,
					std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>>&,
					std::vector<std::string>&);

#endif