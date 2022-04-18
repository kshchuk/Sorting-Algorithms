#include "Message.h"
#include "stringbin.h"
#include "myTime.h"
#include <vector>
#include <string>
#include <iostream>


std::vector<std::string> messageType = 
{
	"NEWS",
	"QUESTION",
	"REPLY",
	"INVITE",
	"COMMENT",
};

Message::Message()
{
	this->ID = ID;
	this->type = type;
	this->spamRating = spamRating;
	this->sendingTime = new Time;
	this->sender = sender;
	this->receiver = receiver;
	this->text = text;
}

Message::Message(int ID, int type, double spamRating, std::string& sender, 
	std::string& receiver, std::string& text, Time* sendingTime)
{
	this->ID = ID;
	this->type = type;
	this->spamRating = spamRating;
	this->sender = sender;
	this->receiver = receiver;
	this->text = text;
	this->sendingTime = sendingTime;
}

void Message::print()
{
	std::cout << "   "<< this->ID	<< "     "		 << messageType.at(this->type) << "         "	   <<
		this->spamRating			<< "           " << this->sendingTime->day	   << '/'			   <<
		this->sendingTime->month	<< '/'			 << this->sendingTime->year	   << ' '			   <<
		this->sendingTime->hour		<< ':'			 << this->sendingTime->minute  << ':'			   <<
		this->sendingTime->second	<< "        "	 << this->sender			   << "              " <<
		this->receiver << std::endl << std::endl	 << this->text				   << std::endl        <<
		std::endl;

}


// Write

void Message::writeBin(std::fstream& file)
{
	file.write((char*)&(this->ID), sizeof(int));
	file.write((char*)&(this->type), sizeof(int));
	file.write((char*)&(this->spamRating), sizeof(double));
	file.write((char*)(this->sendingTime), sizeof(Time));

	writeStringToBinFile(this->sender, file);
	writeStringToBinFile(this->receiver, file);
	writeStringToBinFile(this->text, file);
}

void Message::writeTxt(std::fstream& file)
{
	file << std::endl << this->ID			   << std::endl << this->type		  		 << std::endl << this->spamRating		 <<
		std::endl << this->sender			   << std::endl << this->receiver			 << std::endl << this->sendingTime->year <<
		std::endl << this->sendingTime->month  << std::endl	<< this->sendingTime->day	 << std::endl << this->sendingTime->hour <<
		std::endl << this->sendingTime->minute << std::endl	<< this->sendingTime->second << std::endl << this->text				 <<
		std::endl;
}


// Restore

void Message::readBin(std::ifstream& file)
{
	file.read((char*)&(this->ID), sizeof(int));
	file.read((char*)&(this->type), sizeof(int));
	file.read((char*)&(this->spamRating), sizeof(double));
	file.read((char*)(this->sendingTime), sizeof(Time));

	readStringFromBinFile(this->sender, file);
	readStringFromBinFile(this->receiver, file);
	readStringFromBinFile(this->text, file);
}

void Message::readTxt(std::ifstream& file)
{
	file >> this->ID			  >> this->type				   >> this->spamRating		  >>
		this->sender			  >> this->receiver			   >> this->sendingTime->year >>
		this->sendingTime->month  >> this->sendingTime->day    >> this->sendingTime->hour >>
		this->sendingTime->minute >> this->sendingTime->second;

	file.ignore();

	std::string textBuf;
	std::getline(file, textBuf);

	while (textBuf != "")
	{
		this->text += textBuf + '\n';

		if (!file.eof())
		{
			std::getline(file, textBuf);
		}
		else
			break;
	}
}


// Other

void seeMessageTypes()
{
	std::cout << "Message types:" << std::endl;

	for (int i = 0; i < messageType.size(); i++)
		std::cout << "	" << i << "   ---   " << messageType.at(i) << std::endl;

	std::cout << std::endl;

}

 Message* getMessage()
{
	Message* mes = new Message;

	seeMessageTypes();

	std::cout << "   Entering message" << std::endl;

	std::cout << "ID:	";
	std::cin >> mes->ID;
	std::cout << "Type (number): ";
	std::cin >> mes->type;
	std::cout << "SpamRating: ";
	std::cin >> mes->spamRating;
	std::cout << "Sender: ";
	std::cin >> mes->sender;
	std::cout << "Receiver: ";
	std::cin >> mes->receiver;

	mes->sendingTime = getTime();

	std::cout << "Text of message:";
	std::getline(std::cin, mes->text);
	std::cout << std::endl;
	return mes;
}

