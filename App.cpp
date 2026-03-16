#include "App.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <climits>
#include <ctime>
using namespace std;

// ── helpers ──────────────────────────────────────────────────────────────────

static Time getUTC()
{
    time_t now = time(0);
    tm    *utc = gmtime(&now);
    return Time(utc->tm_hour, utc->tm_min, utc->tm_sec);
}

void App::printBackHint()
{
    cout << "  (type 'back' or '0' at any prompt to return to menu)\n\n";
}

// ── clock ─────────────────────────────────────────────────────────────────────

void App::stopLiveClock()
{
    if (clockRunning.load())
    {
        clockRunning.store(false);
        if (clockThread.joinable()) clockThread.join();
        cout << "\n";
    }
}

void App::showClock()
{
    int idx = locationManager.findCity(defaultCity);
    if (idx == -1)
    {
        cout << "  Default city \"" << defaultCity << "\" not found.\n";
        return;
    }

    stopLiveClock();

    TimeZone z = locationManager.getZone(idx + 1);
    clockRunning.store(true);

    clockThread = thread([this, z]()
    {
        while (clockRunning.load())
        {
            Time utc   = getUTC();
            Time local = convertTime(utc, 0.0f, z.getOffset(), dst, z.supportsDST());

            cout << "\r  " << z.getCity() << " (" << z.getName() << ")"
                 << " | " << getDateStr() << " | "
                 << setw(2) << setfill('0') << local.getHour()   << ":"
                 << setw(2) << setfill('0') << local.getMinute() << ":"
                 << setw(2) << setfill('0') << local.getSecond()
                 << "  [press Enter to stop]  " << flush;

            this_thread::sleep_for(chrono::seconds(1));
        }
    });

    string dummy;
    getline(cin, dummy);
    stopLiveClock();
}

// ── convert menu ──────────────────────────────────────────────────────────────

void App::convertMenu()
{
    printBackHint();
    cout << "  1  City to City (current time)\n";
    cout << "  2  Timezone to Timezone (current time)\n";
    cout << "  3  Manual Time Entry\n";
    cout << "  Choice: ";

    int op = readIntOrBack();
    if (op == INT_MIN) { cout << "  Returning to menu.\n"; return; }

    if (op == 1)
    {
        cout << "  From City: ";
        string fromCity = readCityOrBack();
        if (fromCity == BACK_CMD) { cout << "  Returning to menu.\n"; return; }

        cout << "  To City  : ";
        string toCity = readCityOrBack();
        if (toCity == BACK_CMD) { cout << "  Returning to menu.\n"; return; }

        int s = locationManager.findCity(fromCity);
        int d = locationManager.findCity(toCity);
        if (s == -1 || d == -1) { cout << "  City not found. Check spelling.\n"; return; }

        TimeZone fromZone = locationManager.getZone(s + 1);
        TimeZone toZone   = locationManager.getZone(d + 1);

        Time utc      = getUTC();
        Time fromTime = convertTime(utc, 0.0f, fromZone.getOffset(), dst, fromZone.supportsDST());
        Time result   = convertTime(fromTime, fromZone.getOffset(), toZone.getOffset(), dst, toZone.supportsDST());

        cout << "\n  " << fromZone.getCity() << " : "; fromTime.display();
        cout << "  " << toZone.getCity()   << " : "; result.display();
    }
    else if (op == 2)
    {
        cout << "  From TZ (e.g. IST, JST, EST): ";
        string fromTZ = readCityOrBack();
        if (fromTZ == BACK_CMD) { cout << "  Returning to menu.\n"; return; }

        cout << "  To TZ   (e.g. JST, EST, GMT): ";
        string toTZ = readCityOrBack();
        if (toTZ == BACK_CMD) { cout << "  Returning to menu.\n"; return; }

        int fromIdx = -1, toIdx = -1;
        for (int i = 0; i < locationManager.size(); i++)
        {
            string tzName = locationManager.getZone(i + 1).getName();
            if (fromIdx == -1 && normalize(tzName) == normalize(fromTZ)) fromIdx = i;
            if (toIdx   == -1 && normalize(tzName) == normalize(toTZ))   toIdx   = i;
        }
        if (fromIdx == -1 || toIdx == -1) { cout << "  Timezone not found.\n"; return; }

        TimeZone fromZone = locationManager.getZone(fromIdx + 1);
        TimeZone toZone   = locationManager.getZone(toIdx   + 1);

        Time utc      = getUTC();
        Time fromTime = convertTime(utc, 0.0f, fromZone.getOffset(), dst, fromZone.supportsDST());
        Time result   = convertTime(fromTime, fromZone.getOffset(), toZone.getOffset(), dst, toZone.supportsDST());

        cout << "\n  " << fromZone.getName() << " : "; fromTime.display();
        cout << "  " << toZone.getName()   << " : "; result.display();
    }
    else if (op == 3)
    {
        Time src;
        src.setTime();
        if (src.isCancelled()) { cout << "  Returning to menu.\n"; return; }

        cout << "\n  Select Source Zone (enter number):\n";
        locationManager.showZones();
        cout << "  Choice: ";
        int s = readIntOrBack();
        if (s == INT_MIN) { cout << "  Returning to menu.\n"; return; }

        cout << "\n  Select Destination Zone (enter number):\n";
        locationManager.showZones();
        cout << "  Choice: ";
        int d = readIntOrBack();
        if (d == INT_MIN) { cout << "  Returning to menu.\n"; return; }

        if (s < 1 || s > locationManager.size() ||
            d < 1 || d > locationManager.size())
        { cout << "  Invalid selection.\n"; return; }

        TimeZone fromZone = locationManager.getZone(s);
        TimeZone toZone   = locationManager.getZone(d);
        Time result = convertTime(src, fromZone.getOffset(), toZone.getOffset(), dst, toZone.supportsDST());

        cout << "\n  " << fromZone.getCity() << " : "; src.display();
        cout << "  " << toZone.getCity()   << " : "; result.display();
    }
    else
        cout << "  Invalid option.\n";
}

// ── set default menu ──────────────────────────────────────────────────────────

void App::setDefaultMenu()
{
    printBackHint();
    cout << "  Current default: " << defaultCity << "\n\n";
    cout << "  1  Type a city name\n";
    cout << "  2  Pick from full list\n";
    cout << "  Choice: ";

    int op = readIntOrBack();
    if (op == INT_MIN) { cout << "  Returning to menu.\n"; return; }

    if (op == 1)
    {
        cout << "  Enter city name: ";
        string city = readCityOrBack();
        if (city == BACK_CMD) { cout << "  Returning to menu.\n"; return; }

        if (locationManager.findCity(city) == -1)
            cout << "  \"" << city << "\" not found in database.\n";
        else
        {
            defaultCity = city;
            cout << "  Default city set to " << defaultCity << ".\n";
        }
    }
    else if (op == 2)
    {
        locationManager.showZones();
        cout << "  Choice: ";
        int idx = readIntOrBack();
        if (idx == INT_MIN) { cout << "  Returning to menu.\n"; return; }

        if (idx < 1 || idx > locationManager.size())
            cout << "  Invalid selection.\n";
        else
        {
            defaultCity = locationManager.getZone(idx).getCity();
            cout << "  Default city set to " << defaultCity << ".\n";
        }
    }
    else
        cout << "  Invalid option.\n";
}

// ── main loop ─────────────────────────────────────────────────────────────────

void App::run()
{
    showClock();

    int c;
    while (true)
    {
        stopLiveClock();
        cout << "\n========== Menu ==========\n";
        cout << "  1  View Clock\n";
        cout << "  2  Convert Time\n";
        cout << "  3  Search City\n";
        cout << "  4  Add Favorite\n";
        cout << "  5  Show Favorites\n";
        cout << "  6  Toggle DST (currently " << (dst ? "ON" : "OFF") << ")\n";
        cout << "  7  Business Hours Check\n";
        cout << "  8  Set Default City (current: " << defaultCity << ")\n";
        cout << "  9  Exit\n";
        cout << "==========================\n";
        cout << "  Choice: ";

        if (cin.peek() == '\n') cin.ignore();
        string line;
        getline(cin, line);
        size_t st = line.find_first_not_of(" \t");
        line = (st == string::npos) ? "" : line.substr(st);

        if (line.empty()) continue;
        if (normalize(line) == "back") { cout << "  Already at main menu.\n"; continue; }

        try { c = stoi(line); } catch (...) { cout << "  Enter a number 1-9.\n"; continue; }

        if      (c == 1) showClock();
        else if (c == 2) convertMenu();
        else if (c == 3)
        {
            printBackHint();
            cout << "  Enter city name: ";
            string city = readCityOrBack();
            if (city == BACK_CMD) { cout << "  Returning to menu.\n"; continue; }

            int idx = locationManager.findCity(city);
            if (idx == -1)
                cout << "  \"" << city << "\" not found.\n";
            else
            {
                TimeZone z = locationManager.getZone(idx + 1);
                cout << "  Found: " << z.getCity() << " | " << z.getName()
                     << " | UTC" << (z.getOffset() >= 0 ? "+" : "")
                     << z.getOffset() << " | " << z.getCountry() << "\n";
            }
        }
        else if (c == 4)
        {
            printBackHint();
            cout << "  City name: ";
            string city = readCityOrBack();
            if (city == BACK_CMD) { cout << "  Returning to menu.\n"; continue; }
            favManager.add(city);
        }
        else if (c == 5) favManager.show();
        else if (c == 6)
        {
            dst = !dst;
            cout << "  DST " << (dst ? "Enabled" : "Disabled") << ".\n";
        }
        else if (c == 7)
        {
            printBackHint();
            cout << "  Enter city name: ";
            string city = readCityOrBack();
            if (city == BACK_CMD) { cout << "  Returning to menu.\n"; continue; }

            int idx = locationManager.findCity(city);
            if (idx == -1) { cout << "  City not found.\n"; continue; }

            TimeZone z     = locationManager.getZone(idx + 1);
            Time     utc   = getUTC();
            Time     local = convertTime(utc, 0.0f, z.getOffset(), dst, z.supportsDST());

            cout << "  " << z.getCity() << " current time: "; local.display();
            int h = local.getHour();
            cout << (h >= 9 && h < 18 ? "  Within business hours (9am-6pm).\n"
                                       : "  Outside business hours.\n");
        }
        else if (c == 8) setDefaultMenu();
        else if (c == 9) { stopLiveClock(); cout << "  Goodbye!\n"; break; }
        else cout << "  Invalid option. Enter 1-9.\n";
    }
}
