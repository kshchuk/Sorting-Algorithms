#include "NodeList.h"
#include "Message.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


NodeList::Node::Node(Message* data)
	{
		this->data = data;
		this->next = nullptr;
	}

void NodeList::printAll()
{
	if (head == nullptr)
	{
		std::cout << "List is empty" << std::endl;
	}
	else
	{
		std::cout << "_______________________________________________________________________________________________________________________" <<
			std::endl << "  ID       TYPE       SPAM RATING             TIME               SENDER            RECEIVER " << std::endl << std::endl;

		Node* i = head;

		while(i != nullptr)
		{
			i->data->print();
			i = i -> next;
		}

		std::cout << "_______________________________________________________________________________________________________________________" << std::endl;
	}
}



// Add message

void NodeList::addFirst(Message* data)
{
	Node* node = new Node(data);

	if (head == nullptr)
	{
		head = node; tail = node;
	}
	else
	{
		node->next = head;
		head = node;
	}

	std::cout << "Data successfully added" << std::endl;
}

void NodeList::append(Message* data)
	{
		Node* node = new Node(data);

		if (head == nullptr)
		{
			head = node; tail = node;
		}
		else
		{
			tail->next = node;
			tail = node;
		}

	}

bool NodeList::insertAfter(Message* data, int ID)
{
	Node* node = new Node(data);
	bool isAdded = false;
	Node* i = head;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			node->next = i->next;
			i->next = node;

			if (i == tail)
				tail = node;;

			isAdded = true;
			break;
		}
		i = i->next;
	}
	
	return isAdded;

}

bool NodeList::insertBefore(Message* data, int ID)
{
	Node* node = new Node(data);
	bool isAdded = false;
	Node* i = head, * prev = nullptr;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			if (i == head)
			{
				node->next = head;
				head = node;

				isAdded = true;
				break;
			}
			else
			{
				node->next = i;
				prev->next = node;

				isAdded = true;
				break;
			}
		}
		prev = i;
		i = i->next;
	}

	return isAdded;
}



// Delete

void NodeList::clear()
{
	Node* i = head;

	Node* t = i;

	while (i != nullptr)
	{
		t = i->next;
		delete i;
		i = t;
	}

	head = nullptr;
	tail = nullptr;

}

bool NodeList::removeMessage(int ID)
{
	Node* i = head, * prev = nullptr;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			if (i == head)
			{
				head = head->next;

				delete i;
				return true;
				break;
			}
			else
				if (i == tail)
				{
					tail = prev;
					prev->next = nullptr;

					delete i;
					return true;
				}
				else
				{
					prev->next = i->next;

					delete i;
					return true;

					break;
				}
		}
		prev = i;
		i = i->next;
	}

	return false;

}



//	Save

bool NodeList::saveBinFile(const std::string& fileName)
{
	std::fstream file(fileName, std::ios::binary | std::ios::out);

	file.clear();

	int numberOfMessages = 0;

	if (file.is_open())
	{
		file.write((char*)&numberOfMessages, sizeof(int));				//reserve memory for message quintity

		Node* i = head;

		while (i != nullptr)
		{
			i->data->writeBin(file);

			i = i->next;
			numberOfMessages++;
		}
		file.seekp(SEEK_SET);
		file.write((char*)&numberOfMessages, sizeof(int));
		file.close();

		return true;
	}
	else
		return false;
}

bool NodeList::saveTextFile(const std::string& fileName)
{
	std::fstream file(fileName, std::ios::out);

	file.clear();

	if (file.is_open())
	{
		Node* i = head;
		while(i!=nullptr)
		{
			i->data->writeTxt(file);
			i = i->next;
		}
		file.close();
		return true;
	}
	else
		return false;
}

bool NodeList::appendBinFile(std::fstream& file)
{
	int numberOfMessages = 0;

	fpos_t numPos = file.tellp();

	if (file.good())
	{
		file.write((char*)&numberOfMessages, sizeof(int));				//reserve memory for message quintity

		Node* i = head;

		while (i != nullptr)
		{
			i->data->writeBin(file);

			i = i->next;
			numberOfMessages++;
		}

		fpos_t endPos = file.tellp();

		file.seekp(numPos);

		file.write((char*)&numberOfMessages, sizeof(int));

		file.seekp(endPos);

		return true;
	}
	else
		return false;
}

bool NodeList::appendTextFile(std::fstream& file)
{
	if (file.good())
	{
		// TODO

		fpos_t numPos = file.tellp();
		file << "            ";

		int numberOfMessages = 0;

		Node* i = head;
		
		while(i != nullptr)
		{
			i->data->writeTxt(file);
			i = i->next;

			numberOfMessages++;
		}

		fpos_t endPos = file.tellp();

		file.seekp(numPos);

		file << numberOfMessages;

		file.seekp(endPos);

		return true;
	}
	else
		return false;

}




//	Restore

bool NodeList::readBinFile(const std::string& fileName)
{
	std::ifstream file(fileName, std::ios::binary);

	if (file.is_open())
	{
		this->clear();

		int numberOfMessages;
		file.read((char*)&numberOfMessages, sizeof(int));

		for (int i = 0; i < numberOfMessages; i++)
		{
			Message* mes = new Message;

			mes->readBin(file);

			this->append(mes);
		}
		file.close();

		return true;
	}
	else
		return false;
}

bool NodeList::readTextFile(const std::string& fileName)
{
	std::ifstream file(fileName, std::ios::in);

	if (file.is_open())
	{
		this->clear();

		while (!file.eof() && file.good())
		{
			Message* mes = new Message();

			mes->readTxt(file);

			this->append(mes);
			
			file.ignore();
		}
		file.close();

		return true;
	}
	else
		return false;
}

bool NodeList::readBinFile(std::ifstream& file)
{

	if (file.is_open())
	{
		this->clear();

		int numberOfMessages;
		file.read((char*)&numberOfMessages, sizeof(int));

		for (int i = 0; i < numberOfMessages; i++)
		{
			Message* mes = new Message;

			mes->readBin(file);

			this->append(mes);
		}

		return true;
	}
	else
		return false;
}

bool NodeList::readTextFile(std::ifstream& file)
{
	if (file.is_open())
	{
		//TODO

		this->clear();

		int numberOfMessages;
		file >> numberOfMessages;

		for (int i = 0; i < numberOfMessages; i++)
		{
			Message* mes = new Message();

			mes->readTxt(file);

			this->append(mes);

			//file.ignore();
		}

		return true;
	}
	else
		return false;
}




//	Modify

bool NodeList::modifyMessage(const int type, const int ID)
{
	Node* i = head;
	bool isModified = false;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			i->data->type = type;

			isModified = true;
			break;
		}
		i = i->next;
	}

	return isModified;
}

bool NodeList::modifyMessage(const double spamRating, const int ID)
{
	Node* i = head;
	bool isModified = false;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			i->data->spamRating = spamRating;

			isModified = true;
			break;
		}
		i = i->next;
	}

	return isModified;
}

bool NodeList::modifyMessage(const std::string * sender, int ID)
{
	Node* i = head;
	bool isModified = false;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			i->data->sender = *sender;

			isModified = true;
			break;
		}
		i = i->next;
	}

	return isModified;
}

bool NodeList::modifyMessage(const std::string receiver, int ID)
{
	Node* i = head;
	bool isModified = false;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			i->data->receiver = receiver;

			isModified = true;
			break;
		}
		i = i->next;
	}

	return isModified;
}

bool NodeList::modifyMessageText(const std::string* text, int ID)
{
	Node* i = head;
	bool isModified = false;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			i->data->text = *text;

			isModified = true;
			break;
		}
		i = i->next;
	}

	return isModified;
}

bool NodeList::modifyMessage(Time* time, const int ID)
{
	Node* i = head;
	bool isModified = false;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			i->data->sendingTime = time;

			isModified = true;
			break;
		}
		i = i->next;
	}

	return isModified;
}

bool NodeList::modifyMessage(Message* data, int ID)
{
	Node* i = head;
	bool isModified = false;

	while (i != nullptr)
	{
		if (i->data->ID == ID)
		{
			i->data = data;

			isModified = true;
			break;
		}
		i = i->next;
	}

	return isModified;

}




//	Filters

NodeList NodeList::endTextFilter(const std::string& endText)
{
	NodeList filteredList;
	Node* i = head, * lastNode = head;

	while (i != nullptr)
	{
		int substringPos = i->data->text.rfind(endText);

		if (substringPos + endText.length() == i->data->text.length())
		{
			filteredList.append(i->data);
			lastNode = i;
		}
		i = i->next;
	}

	filteredList.tail = lastNode;

	return filteredList;
}

NodeList NodeList::typeAndUserFilter(const int type, const std::string& sender, const std::string& receiver)
{
	NodeList filteredList;
	Node* i = head, * lastNode = head;;

	while (i != nullptr)
	{
		if (i->data->type == type && i->data->sender == sender && i->data->receiver == receiver)
		{
			filteredList.append(i->data);
			lastNode = i;
		}
		i = i->next;
	}

	filteredList.tail = lastNode;

	return filteredList;
}

NodeList NodeList::receiverAndSentTimeFilter(const std::string& receiver, Time* minSentTime)
{
	NodeList filteredList;
	Node* i = head, * lastNode = head;;

	while (i != nullptr)
	{
		bool isRightTime = i->data->sendingTime->isLaterThan(minSentTime);

		if (i->data->receiver == receiver && isRightTime)
		{
			filteredList.append(i->data);
			lastNode = i;
		}
		i = i->next;

	}
	filteredList.tail = lastNode;

	return filteredList;
}




// Other

bool NodeList::includesText(std::string& substr)
{
	Node* i = head;

	while (i != nullptr)
	{
		if (i->data->text.find(substr) != -1)
		{
			return true;
		}
		i = i->next;
	}

	return false;
}

bool NodeList::includesMaxTimeUsers(Time* maxTime, std::string& user1, std::string& user2)
{
	Node* i = head;

	while (i != nullptr)
	{
		if (i->data->sendingTime->isBeforeThan(maxTime) && 
		   (i->data->sender == user1 && i->data->receiver == user2 ||
			i->data->sender == user2 && i->data->receiver == user1))
		{
			return true;
		}
	}
	return false;
}


