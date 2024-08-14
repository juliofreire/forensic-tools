#include "Arqout.h"
#include <cstring>
#include <filesystem>
#include <time.h>

using namespace std;

Arqout::Arqout(string filename)
{
    filename = addDateToName(filename);
    output = ofstream(filename, fstream::app);
    output << "Channel, Sequential, Size, Date \n";
}

Arqout::~Arqout()
{
    output.close();
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

string Arqout::addDateToName(string filename)
{
    time_t rawtime;
    tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    string dateString = to_string(timeinfo->tm_year + 1900)+"-"+\
                        to_string(timeinfo->tm_mon)+"-"+\
                        to_string(timeinfo->tm_mday)+"-"+\
                        to_string(timeinfo->tm_hour)+":"+\
                        to_string(timeinfo->tm_min)+":"+\
                        to_string(timeinfo->tm_sec)+".csv";
    filesystem::path in_path(filename);
    string fullfilename = filename + "-" + dateString;
    return fullfilename;
}