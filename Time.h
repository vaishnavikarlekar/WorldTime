#pragma once

class Time
{
private:
    int hour, minute, second;

public:
    Time();
    Time(int h, int m, int s);

    void setTime();
    bool isCancelled();

    void setHour(int h);
    void setMinute(int m);
    void setSecond(int s);

    int getHour();
    int getMinute();
    int getSecond();

    void display();
};

// Free function: converts a Time from one UTC offset to another
Time convertTime(Time t, float fromOffset, float toOffset,
                 bool applyDST, bool toDST);
