#pragma once
#include <exception>
#include <string>

// Base exception for all timezone app errors
class TimeZoneException : public std::exception
{
protected:
    std::string message;

public:
    TimeZoneException(const std::string &msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// Thrown when a city name is not found in the database
class CityNotFoundException : public TimeZoneException
{
public:
    CityNotFoundException(const std::string &city)
        : TimeZoneException("City not found: \"" + city + "\". Check spelling or try another city.") {}
};

// Thrown when a timezone code is not found (e.g. user types "XYZ")
class TimezoneNotFoundException : public TimeZoneException
{
public:
    TimezoneNotFoundException(const std::string &tz)
        : TimeZoneException("Timezone not found: \"" + tz + "\". Example valid codes: IST, JST, EST, GMT.") {}
};

// Thrown when a zone list index is out of range
class InvalidZoneIndexException : public TimeZoneException
{
public:
    InvalidZoneIndexException(int index, int maxIndex)
        : TimeZoneException("Invalid zone number: " + std::to_string(index) +
                            ". Please enter a number between 1 and " + std::to_string(maxIndex) + ".") {}
};

// Thrown when hour/minute/second values are out of valid range
class InvalidTimeException : public TimeZoneException
{
public:
    InvalidTimeException(const std::string &field, int value)
        : TimeZoneException("Invalid " + field + ": " + std::to_string(value) +
                            ". " + field + " must be " +
                            (field == "hour" ? "0-23." : "0-59.")) {}
};

// Thrown when default city is set to something not in the database
class InvalidDefaultCityException : public TimeZoneException
{
public:
    InvalidDefaultCityException(const std::string &city)
        : TimeZoneException("Cannot set default city to \"" + city + "\" — not found in database.") {}
};
