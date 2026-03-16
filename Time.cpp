#include "Time.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

Time::Time() : hour(0), minute(0), second(0) {}
Time::Time(int h, int m, int s) : hour(h), minute(m), second(s) {}

void Time::setTime()
{
    cout << "  Enter Hour   (0-23) [or 'back']: ";
    hour = readIntOrBack();
    if (hour == INT_MIN) { hour = INT_MIN; return; }

    cout << "  Enter Minute (0-59) [or 'back']: ";
    minute = readIntOrBack();
    if (minute == INT_MIN) { hour = INT_MIN; return; }

    cout << "  Enter Second (0-59) [or 'back']: ";
    second = readIntOrBack();
    if (second == INT_MIN) { hour = INT_MIN; return; }
}

bool Time::isCancelled() { return hour == INT_MIN; }

void Time::setHour(int h)   { hour   = h; }
void Time::setMinute(int m) { minute = m; }
void Time::setSecond(int s) { second = s; }

int Time::getHour()   { return hour; }
int Time::getMinute() { return minute; }
int Time::getSecond() { return second; }

void Time::display()
{
    cout << setw(2) << setfill('0') << hour   << ":"
         << setw(2) << setfill('0') << minute << ":"
         << setw(2) << setfill('0') << second << endl;
}

Time convertTime(Time t, float fromOffset, float toOffset,
                 bool applyDST, bool toDST)
{
    int totalMin = t.getHour() * 60 + t.getMinute();
    int utcMin   = totalMin - (int)(fromOffset * 60);
    if (applyDST && toDST) utcMin += 60;
    int destMin  = utcMin + (int)(toOffset * 60);
    destMin = ((destMin % 1440) + 1440) % 1440;
    Time result;
    result.setHour(destMin / 60);
    result.setMinute(destMin % 60);
    result.setSecond(t.getSecond());
    return result;
}
