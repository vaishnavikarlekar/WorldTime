#pragma once
#include "LocationManager.h"
#include "FavoriteManager.h"
#include "Time.h"
#include <string>
#include <thread>
#include <atomic>

class App
{
private:
    LocationManager locationManager;
    FavoriteManager favManager;
    bool        dst         = false;
    std::string defaultCity = "New Delhi";

    std::atomic<bool> clockRunning{false};
    std::thread       clockThread;

    void printBackHint();
    void convertMenu();
    void setDefaultMenu();

public:
    void stopLiveClock();
    void showClock();
    void run();
};
