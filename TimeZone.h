#pragma once
#include <string>

class TimeZone
{
private:
    std::string name;
    std::string city;
    float       utcOffset;
    bool        hasDST;
    std::string country;

public:
    TimeZone(std::string n, std::string c, std::string tz,
             float offset, bool dst, std::string ctry);

    std::string getName()     const;
    std::string getCity()     const;
    std::string getCountry()  const;
    float       getOffset()   const;
    bool        supportsDST() const;
};
