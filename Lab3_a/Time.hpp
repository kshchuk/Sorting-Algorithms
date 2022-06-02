#pragma once

#ifndef TIME_HPP_

#define TIME_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>

#include <random>


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
        return (hour = t.hour) && (minute == t.minute) && (second == t.second);
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

bool operator == (Time d1, Time d2)
{
    return ((d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day) &&
        (d1.hour == d2.hour) && (d1.minute == d2.minute) && (d1.second == d2.second));
}

bool operator != (Time d1, Time d2)
{
    return !(d1 == d2);
}

bool operator < (Time d1, Time d2)
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
                        if (d1.second < d2.second)
                            return true;
                        else return false;
    return false;
}

bool operator > (Time d1, Time d2)
{
    return !(d1 < d2) && (d1 != d2);
}

bool operator <= (Time d1, Time d2)
{
    return (d1 < d2 || d1 == d2);
}

bool operator >= (Time d1, Time d2)
{
    return (d1 > d2 || d1 == d2);
}

// increments minute by one
Time operator++(Time& t)
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

// decrements minute by one
Time operator--(Time& t)
{
    if (t.minute - 1 >= 0)
        t.minute--;
    else {
        t.minute = 59;
        if (t.hour - 1 >= 0)
            t.hour--;
        else {
            t.hour = 23;
            if (t.day - 1 > 0)
                t.day--;
            else {
                t.day = 31;
                if (t.month - 1 > 0)
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

std::ostream& operator<<(std::ostream& os, const Time& dt)
{
    os << dt.hour << ':' << dt.minute << ':' << dt.second << "    " <<
        dt.day << '/' << dt.month << '/' << dt.year;
    return os;
}

Time getTime()
{
    Time time;

    std::string buf;;

    std::cout << "Date (dd/mm/yyyy):";
    std::getline(std::cin, buf, '/');
    time.day = stoi(buf);
    std::getline(std::cin, buf, '/');
    time.month = stoi(buf);
    std::getline(std::cin, buf);
    time.year = stoi(buf);

    std::cout << "Time (hh:mm:ss):";
    std::getline(std::cin, buf, ':');
    time.hour = stoi(buf);
    std::getline(std::cin, buf, ':');
    time.minute = stoi(buf);
    std::getline(std::cin, buf);
    time.second = stoi(buf);

    return time;
}


void EnterTimeByKeys(Time t) {
    std::string buf;
    buf = std::to_string(t.day);
    for (int i = 0; i < buf.size(); i++)
       keybd_event(buf[i], 0, 0, 0);
    keybd_event(VK_OEM_2, 0, 0, 0);
    buf = std::to_string(t.month);
    for (int i = 0; i < buf.size(); i++)
        keybd_event(buf[i], 0, 0, 0);
    keybd_event(VK_OEM_2, 0, 0, 0);
    buf = std::to_string(t.year);
    for (int i = 0; i < buf.size(); i++)
        keybd_event(buf[i], 0, 0, 0);
    Sleep(200); keybd_event(VK_RETURN, 0, 0, 0);
    buf = std::to_string(t.hour);
    for (int i = 0; i < buf.size(); i++)
        keybd_event(buf[i], 0, 0, 0);
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event(VK_OEM_1, 0, 0, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    buf = std::to_string(t.minute);
    for (int i = 0; i < buf.size(); i++)
        keybd_event(buf[i], 0, 0, 0);
    keybd_event(VK_SHIFT, 0, 0, 0);
    keybd_event(VK_OEM_1, 0, 0, 0);
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
    buf = std::to_string(t.second);
    for (int i = 0; i < buf.size(); i++)
        keybd_event(buf[i], 0, 0, 0);
    keybd_event(VK_RETURN, 0, 0, 0);

}

#endif // !TIME_HPP_