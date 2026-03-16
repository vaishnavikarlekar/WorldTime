#pragma once
#include "TimeZone.h"
#include <vector>
#include <string>

class LocationManager
{
private:
    std::vector<TimeZone> zones;

public:
    LocationManager();

    void     showZones();
    TimeZone getZone(int i);   // 1-based index
    int      findCity(std::string city);
    int      size();
};
