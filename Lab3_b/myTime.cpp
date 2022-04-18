#include "myTime.h"
#include <iostream>
#include <string>

Time* getTime()
{
	Time* time = new Time;

	std::string buf;;

	std::cout << "Date (dd/mm/yyyy):";
	std::getline(std::cin, buf, '/');
	time->day = stoi(buf);
	std::getline(std::cin, buf, '/');
	time->month = stoi(buf);
	std::getline(std::cin, buf);
	time->year = stoi(buf);

	std::cout << "Time (hh:mm:ss):";
	std::getline(std::cin, buf, ':');
	time->hour = stoi(buf);
	std::getline(std::cin, buf, ':');
	time->minute = stoi(buf);
	std::getline(std::cin, buf);
	time->second = stoi(buf);

	return time;
}

bool Time::isLaterThan(Time* time)
{
	if (time->year < this->year)
		return true;
	else {
		if (time->year == this->year)
		{
			if (time->month < this->month)
				return true;
			else {
				if (time->month == this->month)
				{
					if (time->day < this->day)
						return true;
					else {
						if (time->day == this->day)
						{
							if (time->hour < this->hour)
								return true;
							else {
								if (time->hour == this->hour)
								{
									if (time->minute < this->minute)
										return true;
									else {
										if (time->minute == this->minute)
										{
											if (time->second < this->second)
												return true;
											else
												return false;
										}
										else
											return false;

									}
								}
								else
									return false;
							}
						}
						else
							return false;
					}
				}
				else
					return false;
			}
		}
		else
			return false;
	}
}

bool Time::isBeforeThan(Time* time)
{
	return !isLaterThan(time);
}
