#include "Arqout.h"
#include <cstring>

using namespace std;

Arqout::Arqout(string path_out){
    output = ofstream(path_out, fstream::app);
    output << "Channel, Sequential, Size, Date \n";
}

Arqout::~Arqout(){
    
}

void Arqout::WriteOn(Phrase* phrase){
    output << phrase->getChannel()    << ", " << \
              phrase->getSequential() << ", " << \
              phrase->getSize()       << ", " << \
              phrase->getYear()       << "-" << \
              phrase->getMonth()      << "-" << \
              phrase->getDay()        << " " << \
              phrase->getHour()       << ":" << \
              phrase->getMinute()     << ":" << \
              phrase->getSeconds()    << endl;
}