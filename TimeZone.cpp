#include "TimeZone.h"
using namespace std;

TimeZone::TimeZone(string n, string c, string tz,
                   float offset, bool dst, string ctry)
    : name(tz), city(c), utcOffset(offset), hasDST(dst), country(ctry) {}

string TimeZone::getName()     const { return name; }
string TimeZone::getCity()     const { return city; }
string TimeZone::getCountry()  const { return country; }
float  TimeZone::getOffset()   const { return utcOffset; }
bool   TimeZone::supportsDST() const { return hasDST; }
