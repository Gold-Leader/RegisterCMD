#include <iostream>

#include <ios>
#include <iomanip>
#include <fstream>
#include <sstream>

#ifndef REGUTIL_H
#define REGUTIL_H


std::fstream createCustomer(std::string dirParam);

std::vector<std::pair<std::string, std::string>> readCustomerStatic();
std::vector<std::pair<std::string, std::string>> readCustomerDynamic();

void printCustomer(std::fstream&);

// void editCustomer();
// void billCustomer();
// void deleteCustomer();

// void writeCustomer(std::fstream, std::vector<std::pair<std::string, std::string>>);
// void writeCustomer(std::fstream, std::vector<std::pair<std::string, std::string>>, std::vector<std::tuple<std::string, int, std::string, std::string, std::string, int>>);



// void printCSV(std::fstream);
// void printCSV(std::vector<std::pair<std::string, std::string>>);
// void printCSV(std::vector<std::pair<std::string, std::string>>, std::vector<std::tuple<std::string, int, std::string, std::string, std::string, int>>);

#endif