#pragma once
#include <string>
#include <fstream>

void writeStringToBinFile(std::string& str, std::fstream& of);
void readStringFromBinFile(std::string& str, std::ifstream& in);
