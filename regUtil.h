#include <iostream>

#ifndef REGUTIL_H
#define REGUTIL_H

// void findCustomer();

std::fstream createCustomer();

void readCustomer(std::ifstream);

void writeCustomer(std::ofstream, std::vector<std::pair<std::string, std::string>>);
void writeCustomer(std::ofstream, std::vector<std::pair<std::string, std::string>>, std::vector<std::tuple<std::string, int, std::string, std::string, std::string, int>>);

// void editCustomer();
// void billCustomer();
// void deleteCustomer();

void printCSV(std::ofstream);
void printCSV(std::vector<std::pair<std::string, std::string>>);
void printCSV(std::vector<std::pair<std::string, std::string>>, std::vector<std::tuple<std::string, int, std::string, std::string, std::string, int>>);

#endif