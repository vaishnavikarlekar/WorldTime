#include "LocationManager.h"
#include "TimeZoneException.h"
#include "utils.h"
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

LocationManager::LocationManager()
{
    zones.push_back(TimeZone("IST",  "New Delhi",    "IST",   5.5f,  false, "India"));
    zones.push_back(TimeZone("IST",  "Mumbai",       "IST",   5.5f,  false, "India"));
    zones.push_back(TimeZone("IST",  "Bangalore",    "IST",   5.5f,  false, "India"));
    zones.push_back(TimeZone("IST",  "Chennai",      "IST",   5.5f,  false, "India"));
    zones.push_back(TimeZone("IST",  "Kolkata",      "IST",   5.5f,  false, "India"));
    zones.push_back(TimeZone("IST",  "Colombo",      "IST",   5.5f,  false, "Sri Lanka"));
    zones.push_back(TimeZone("NPT",  "Kathmandu",    "NPT",   5.75f, false, "Nepal"));
    zones.push_back(TimeZone("BST",  "Dhaka",        "BST",   6.0f,  false, "Bangladesh"));
    zones.push_back(TimeZone("PKT",  "Karachi",      "PKT",   5.0f,  false, "Pakistan"));
    zones.push_back(TimeZone("AFT",  "Kabul",        "AFT",   4.5f,  false, "Afghanistan"));
    zones.push_back(TimeZone("IRST", "Tehran",       "IRST",  3.5f,  true,  "Iran"));
    zones.push_back(TimeZone("GST",  "Dubai",        "GST",   4.0f,  false, "UAE"));
    zones.push_back(TimeZone("AST",  "Riyadh",       "AST",   3.0f,  false, "Saudi Arabia"));
    zones.push_back(TimeZone("MSK",  "Moscow",       "MSK",   3.0f,  false, "Russia"));
    zones.push_back(TimeZone("GMT",  "London",       "GMT",   0.0f,  true,  "UK"));
    zones.push_back(TimeZone("CET",  "Paris",        "CET",   1.0f,  true,  "France"));
    zones.push_back(TimeZone("CET",  "Berlin",       "CET",   1.0f,  true,  "Germany"));
    zones.push_back(TimeZone("CET",  "Rome",         "CET",   1.0f,  true,  "Italy"));
    zones.push_back(TimeZone("CET",  "Madrid",       "CET",   1.0f,  true,  "Spain"));
    zones.push_back(TimeZone("EET",  "Athens",       "EET",   2.0f,  true,  "Greece"));
    zones.push_back(TimeZone("EET",  "Cairo",        "EET",   2.0f,  true,  "Egypt"));
    zones.push_back(TimeZone("WET",  "Casablanca",   "WET",   0.0f,  true,  "Morocco"));
    zones.push_back(TimeZone("SAST", "Johannesburg", "SAST",  2.0f,  false, "South Africa"));
    zones.push_back(TimeZone("EAT",  "Nairobi",      "EAT",   3.0f,  false, "Kenya"));
    zones.push_back(TimeZone("WAT",  "Lagos",        "WAT",   1.0f,  false, "Nigeria"));
    zones.push_back(TimeZone("EST",  "New York",     "EST",  -5.0f,  true,  "USA"));
    zones.push_back(TimeZone("CST",  "Chicago",      "CST",  -6.0f,  true,  "USA"));
    zones.push_back(TimeZone("MST",  "Denver",       "MST",  -7.0f,  true,  "USA"));
    zones.push_back(TimeZone("PST",  "Los Angeles",  "PST",  -8.0f,  true,  "USA"));
    zones.push_back(TimeZone("AKST", "Anchorage",    "AKST", -9.0f,  true,  "USA"));
    zones.push_back(TimeZone("HST",  "Honolulu",     "HST", -10.0f,  false, "USA"));
    zones.push_back(TimeZone("EST",  "Toronto",      "EST",  -5.0f,  true,  "Canada"));
    zones.push_back(TimeZone("PST",  "Vancouver",    "PST",  -8.0f,  true,  "Canada"));
    zones.push_back(TimeZone("CST",  "Mexico City",  "CST",  -6.0f,  false, "Mexico"));
    zones.push_back(TimeZone("BRT",  "Sao Paulo",    "BRT",  -3.0f,  false, "Brazil"));
    zones.push_back(TimeZone("ART",  "Buenos Aires", "ART",  -3.0f,  false, "Argentina"));
    zones.push_back(TimeZone("CLT",  "Santiago",     "CLT",  -4.0f,  true,  "Chile"));
    zones.push_back(TimeZone("PET",  "Lima",         "PET",  -5.0f,  false, "Peru"));
    zones.push_back(TimeZone("COT",  "Bogota",       "COT",  -5.0f,  false, "Colombia"));
    zones.push_back(TimeZone("CST",  "Beijing",      "CST",   8.0f,  false, "China"));
    zones.push_back(TimeZone("CST",  "Shanghai",     "CST",   8.0f,  false, "China"));
    zones.push_back(TimeZone("HKT",  "Hong Kong",    "HKT",   8.0f,  false, "Hong Kong"));
    zones.push_back(TimeZone("SGT",  "Singapore",    "SGT",   8.0f,  false, "Singapore"));
    zones.push_back(TimeZone("KST",  "Seoul",        "KST",   9.0f,  false, "South Korea"));
    zones.push_back(TimeZone("JST",  "Tokyo",        "JST",   9.0f,  false, "Japan"));
    zones.push_back(TimeZone("ICT",  "Bangkok",      "ICT",   7.0f,  false, "Thailand"));
    zones.push_back(TimeZone("WIB",  "Jakarta",      "WIB",   7.0f,  false, "Indonesia"));
    zones.push_back(TimeZone("AWST", "Perth",        "AWST",  8.0f,  false, "Australia"));
    zones.push_back(TimeZone("AEST", "Sydney",       "AEST", 10.0f,  true,  "Australia"));
    zones.push_back(TimeZone("AEST", "Melbourne",    "AEST", 10.0f,  true,  "Australia"));
    zones.push_back(TimeZone("ACST", "Adelaide",     "ACST",  9.5f,  true,  "Australia"));
    zones.push_back(TimeZone("AEST", "Brisbane",     "AEST", 10.0f,  false, "Australia"));
    zones.push_back(TimeZone("NZST", "Auckland",     "NZST", 12.0f,  true,  "New Zealand"));
    zones.push_back(TimeZone("NZST", "Wellington",   "NZST", 12.0f,  true,  "New Zealand"));
}

void LocationManager::showZones()
{
    printf("\n  %-4s %-18s %-7s %-9s %s\n", "#", "City", "TZ", "Offset", "Country");
    printf("  %s\n", string(53, '-').c_str());
    for (int i = 0; i < (int)zones.size(); i++)
    {
        float off = zones[i].getOffset();
        string offStr = string("UTC") + (off >= 0 ? "+" : "-");
        float frac = off - (int)off;
        if (frac < 0) frac = -frac;
        offStr += to_string(abs((int)off));
        if (frac > 0.6f)      offStr += ":45";
        else if (frac > 0.1f) offStr += ":30";
        printf("  %-4d %-18s %-7s %-9s %s\n",
               i + 1,
               zones[i].getCity().c_str(),
               zones[i].getName().c_str(),
               offStr.c_str(),
               zones[i].getCountry().c_str());
    }
    printf("\n  Type a number to select, or 'back' to return.\n");
}

// Throws InvalidZoneIndexException if index is out of range
TimeZone LocationManager::getZone(int i)
{
    if (i < 1 || i > (int)zones.size())
        throw InvalidZoneIndexException(i, (int)zones.size());
    return zones[i - 1];
}

// Throws CityNotFoundException if city is not found
int LocationManager::findCity(string city)
{
    string key = normalize(city);
    for (int i = 0; i < (int)zones.size(); i++)
        if (normalize(zones[i].getCity()) == key)
            return i;
    return -1;
}

int LocationManager::size() { return (int)zones.size(); }
