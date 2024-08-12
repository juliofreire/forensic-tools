#include "Arqout.h"
#include <cstring>
#include <filesystem>

using namespace std;

Arqout::Arqout(string filename)
{
    output = ofstream(filename, fstream::app);
    output << "Channel, Sequential, Size, Date \n";
}

Arqout::~Arqout()
{
    
}

void Arqout::WriteOn(Phrase* phrase)
{
    output << phrase->getChannel()    << ", " << \
              phrase->getSequential() << ", " << \
              phrase->getSize()       << ", " << \
      "20" << phrase->getYear()       << "-" << \
              phrase->getMonth()      << "-" << \
              phrase->getDay()        << " " << \
              phrase->getHour()       << ":" << \
              phrase->getMinute()     << ":" << \
              phrase->getSeconds()    << endl;
}

bool Arqout::checkName(string filename)
{
    if (filesystem::exists(filename))
        return true;
    return false;
}

string Arqout::addIndexToName(string filename)
{
    int i = 1;
    filesystem::path in_path(filename);
    string newFilename = in_path.filename();
    newFilename = newFilename + "_" + to_string(i) + ".csv";
    while (checkName(newFilename))
    {
        i++;
        newFilename = newFilename + "_" + to_string(i) + ".csv";
    }
    return newFilename;
}