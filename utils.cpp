#include "utils.h"
#include <iostream>
#include <cctype>
#include <climits>
#include <ctime>
#include <cstdio>
using namespace std;

const string BACK_CMD = "__BACK__";

string normalize(const string &s)
{
    string out;
    for (char c : s)
        if (c != ' ' && c != '-' && c != '_')
            out += tolower(c);
    return out;
}

string readCity()
{
    string s;
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, s);
    size_t start = s.find_first_not_of(" \t");
    size_t end   = s.find_last_not_of(" \t");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

string readCityOrBack()
{
    string s = readCity();
    if (normalize(s) == "back" || s == "0") return BACK_CMD;
    return s;
}

int readIntOrBack()
{
    string s;
    while (cin.peek() == '\n') cin.ignore();
    getline(cin, s);
    size_t start = s.find_first_not_of(" \t");
    size_t end   = s.find_last_not_of(" \t");
    s = (start == string::npos) ? "" : s.substr(start, end - start + 1);
    if (normalize(s) == "back") return INT_MIN;
    try { return stoi(s); } catch (...) { return INT_MIN; }
}

string getDateStr()
{
    time_t now = time(0);
    tm    *utc = gmtime(&now);
    char buf[32];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d",
             1900 + utc->tm_year, 1 + utc->tm_mon, utc->tm_mday);
    return string(buf);
}
