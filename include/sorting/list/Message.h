#pragma once
#include <string>
#include <fstream>
#include "myTime.h"

struct Message
{
    int ID;
    int type;
    double spamRating;
    std::string sender;
    std::string receiver;
    std::string text;
    Time* sendingTime;

    Message();
    Message(int ID, int type, double spamRating, std::string& sender, std::string& receiver,
        std::string& text, Time* sendingTime);

    void print();

    void writeBin(std::fstream& file);
    void readTxt(std::ifstream& file);
    void readBin(std::ifstream& file);
    void writeTxt(std::fstream& file);
};

void seeMessageTypes();
Message* getMessage();
