#pragma once
#include <string>

std::string normalize(const std::string &s);
std::string readCity();
std::string readCityOrBack();
int         readIntOrBack();
std::string getDateStr();

extern const std::string BACK_CMD;
