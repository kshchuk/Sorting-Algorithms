#pragma once
#include <fstream>
#include <string>
#include "Message.h"


class NodeList
{
protected:
	struct Node
	{
		Message* data;
		Node* next;

		Node(Message* data);
	};

	Node* head = nullptr;
	Node* tail = nullptr;

public:

	void printAll();

	// Delete
	void clear();
	bool removeMessage(const int ID);

	// Add
	void append(Message* data);
	void addFirst(Message* data);
	bool insertAfter(Message* data, const int ID);
	bool insertBefore(Message* data, const int ID);

	// Save
	bool saveBinFile(const std::string& fileName);
	bool saveTextFile(const std::string& fileName);
	bool appendBinFile(std::fstream& file);
	bool appendTextFile(std::fstream& file);

	//	Restore
	bool readBinFile(const std::string& fileName);
	bool readTextFile(const std::string& fileName);
	bool readBinFile(std::ifstream& file);
	bool readTextFile(std::ifstream& file);

	//	Modify
	bool modifyMessage(const int type, const int ID);
	bool modifyMessage(const double  spamRating, const int ID);
	bool modifyMessage(const std::string* sender, const int ID);
	bool modifyMessage(const std::string receiver, const int ID);
	bool modifyMessageText(const std::string* text, const int ID);
	bool modifyMessage(Time* time, const int ID);
	bool modifyMessage(Message* const data, const int ID);

	//	Filter
	NodeList endTextFilter(const std::string& endText);
	NodeList typeAndUserFilter(const int type, const std::string& sender, const std::string& receiver);
	NodeList receiverAndSentTimeFilter(const std::string& receiver, Time* minSentTime);

	//	Other
	bool includesText(std::string& text);
	bool includesMaxTimeUsers(Time* maxTime, std::string& user1, std::string& user2);

};