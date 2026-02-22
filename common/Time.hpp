#pragma once

#ifndef TIME_HPP_
#define TIME_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

struct Time
{
    size_t year, month, day, hour, minute, second;

    void print() {
        std::cout << hour << ':' << minute << ':' << second << "   " <<
            day << '/' << month << '/' << year << '\n';
    }

    bool DateIsLaterThan(Time t) {
        if (year > t.year)
            return true;
        else if (year == t.year)
            if (month > t.month)
                return true;
            else if (month == t.month)
                if (day > t.day)
                    return true;
                else
                    return false;
        return false;
    }

    bool EqvDateWith(Time t) {
        return (year == t.year) && (month == t.month) && (day == t.day);
    }

    bool TimeIsLaterThan(Time t) {
        if (hour > t.hour)
            return true;
        else if (hour == t.hour)
            if (minute > t.minute)
                return true;
            else if (minute == t.minute)
                if (second > t.second)
                    return true;
                else
                    return false;
        return false;
    }

    bool EqvTimeWith(Time t) {
        return (hour == t.hour) && (minute == t.minute) && (second == t.second);
    }

    Time random()
    {
        std::random_device rd;
        std::mt19937 mersenne(rd());
        this->year = mersenne() % 24 + 1998;
        this->month = mersenne() % 12 + 1;
        this->day = mersenne() % 31 + 1;
        this->hour = mersenne() % 25;
        this->minute = mersenne() % 60;
        this->second = mersenne() % 60;
        return *this;
    }
};

inline bool operator==(Time d1, Time d2)
{
    return ((d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day) &&
        (d1.hour == d2.hour) && (d1.minute == d2.minute) && (d1.second == d2.second));
}

inline bool operator!=(Time d1, Time d2) { return !(d1 == d2); }

inline bool operator<(Time d1, Time d2)
{
    if (d1.year < d2.year)
        return true;
    else if (d1.year == d2.year)
        if (d1.month < d2.month)
            return true;
        else if (d1.month == d2.month)
            if (d1.day < d2.day)
                return true;
            else if (d1.day == d2.day)
                if (d1.hour < d2.hour)
                    return true;
                else if (d1.hour == d2.hour)
                    if (d1.minute < d2.minute)
                        return true;
                    else if (d1.minute == d2.minute)
                        return d1.second < d2.second;
    return false;
}

inline bool operator>(Time d1, Time d2) { return !(d1 < d2) && (d1 != d2); }
inline bool operator<=(Time d1, Time d2) { return (d1 < d2 || d1 == d2); }
inline bool operator>=(Time d1, Time d2) { return (d1 > d2 || d1 == d2); }

inline Time operator++(Time& t)
{
    if (t.minute + 1 < 60)
        t.minute++;
    else {
        t.minute = 0;
        if (t.hour + 1 < 24)
            t.hour++;
        else {
            t.hour = 0;
            if (t.day + 1 < 32)
                t.day++;
            else {
                t.day = 1;
                if (t.month + 1 < 13)
                    t.month++;
                else {
                    t.year++;
                    t.month = 1;
                }
            }
        }
    }
    return t;
}

inline Time operator--(Time& t)
{
    if (t.minute >= 1)
        t.minute--;
    else {
        t.minute = 59;
        if (t.hour >= 1)
            t.hour--;
        else {
            t.hour = 23;
            if (t.day > 1)
                t.day--;
            else {
                t.day = 31;
                if (t.month > 1)
                    t.month--;
                else {
                    t.year--;
                    t.month = 12;
                }
            }
        }
    }
    return t;
}

inline std::ostream& operator<<(std::ostream& os, const Time& dt)
{
    os << dt.hour << ':' << dt.minute << ':' << dt.second << "    " <<
        dt.day << '/' << dt.month << '/' << dt.year;
    return os;
}

inline Time getTime()
{
    Time time;
    std::string buf;
    std::cout << "Date (dd/mm/yyyy):";
    std::getline(std::cin, buf, '/');
    time.day = static_cast<size_t>(stoi(buf));
    std::getline(std::cin, buf, '/');
    time.month = static_cast<size_t>(stoi(buf));
    std::getline(std::cin, buf);
    time.year = static_cast<size_t>(stoi(buf));
    std::cout << "Time (hh:mm:ss):";
    std::getline(std::cin, buf, ':');
    time.hour = static_cast<size_t>(stoi(buf));
    std::getline(std::cin, buf, ':');
    time.minute = static_cast<size_t>(stoi(buf));
    std::getline(std::cin, buf);
    time.second = static_cast<size_t>(stoi(buf));
    return time;
}

#ifdef _WIN32
inline void EnterTimeByKeys(Time t) {
    std::string buf;
    buf = std::to_string(t.day);
    for (size_t i = 0; i < buf.size(); i++)
        keybd_event(static_cast<BYTE>(buf[i]), 0, 0, 0);
    keybd_event(VK_OEM_2, 0, 0, 0);
    buf = std::to_string(t.month);
    for (size_t i = 0; i < buf.size(); i++)
        keybd_event(static_cast<BYTE>(buf[i]), 0, 0, 0);
    keybd_event(VK_OEM_2, 0, 0, 0);
    buf = std::to_string(t.year);
    for (size_t i = 0; i < buf.size(); i++)
        keybd_event(static_cast<BYTE>(buf[i]), 0, 0, 0);
    Sleep(200); keybd_event(VK_RETURN, 0, 0, 0);
    buf = std::to_string(t.hour);
    for (size_t i = 0; i < buf.size(); i++)
        keybd_event(static_cast<BYTE>(buf[i]), 0, 0, 0);
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event(VK_OEM_1, 0, 0, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    buf = std::to_string(t.minute);
    for (size_t i = 0; i < buf.size(); i++)
        keybd_event(static_cast<BYTE>(buf[i]), 0, 0, 0);
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event(VK_OEM_1, 0, 0, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    buf = std::to_string(t.second);
    for (size_t i = 0; i < buf.size(); i++)
        keybd_event(static_cast<BYTE>(buf[i]), 0, 0, 0);
    keybd_event(VK_RETURN, 0, 0, 0);
}
#endif

#endif // !TIME_HPP_
