#pragma once

struct Time
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    bool isLaterThan(Time* time);
    bool isBeforeThan(Time* time);
};

Time* getTime();
