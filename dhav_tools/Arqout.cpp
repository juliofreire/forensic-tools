#include "Arqout.h"
#include <cstring>
#include <filesystem>
#include <time.h>

using namespace std;

/* This a constructor of the class Arqout. That set a new
name to the output file, which is the chosen added by the
current date. Morever, it create a header where specify
what is each column.*/
Arqout::Arqout(string filename)
{
    filename = addDateToName(filename);
    output = ofstream(filename, fstream::app);
    output << "Channel, Sequential, Size, Real_Size, Date \n";
}

/* Just closes the file where occurs what is needed to do
it, like flush all content.*/
Arqout::~Arqout()
{
    output.close();
}

/* This is the main function of the class, it writes the 
metadata of the buffer on outputfile.*/
void Arqout::WriteOn(Phrase* phrase)
{
    output << phrase->getChannel()    << ", " << \
              phrase->getSequential() << ", " << \
              phrase->getSize()       << ", " << \
              phrase->getRealSize()   << ", " << \
      "20" << phrase->getYear()       << "-" << \
              phrase->getMonth()      << "-" << \
              phrase->getDay()        << " " << \
              phrase->getHour()       << ":" << \
              phrase->getMinute()     << ":" << \
              phrase->getSeconds()    << endl;
}

/* This function create a new name, adding the current date
at the final of the filename chosen.*/
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

/* It's unecessary*/
bool Arqout::checkName(string filename)
{
    if (filesystem::exists(filename))
        return true;
    return false;
}
