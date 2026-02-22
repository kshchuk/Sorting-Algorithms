#include "stringbin.h"

void writeStringToBinFile(std::string& str, std::fstream& of)
{
    size_t strLen = str.length() + 1;
    of.write((char*)&strLen, sizeof(size_t));
    of.write(str.data(), strLen);
}

void readStringFromBinFile(std::string& str, std::ifstream& in)
{
    size_t strLen;
    in.read((char*)&strLen, sizeof(size_t));

    char* buf = new char[strLen];
    in.read(buf, strLen);
    str = std::string(buf);

    delete[] buf;
}
