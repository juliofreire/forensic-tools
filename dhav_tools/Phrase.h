#ifndef PHRASE_H
#define PHRASE_H

// #include "Buffer.h"
#include <iostream>
#include <fstream>
#include <cstring>
// #include "Data.h"

using namespace std;

class Phrase
{

private:

	// char* phrase = nullptr;
	unsigned short int channel;
	// Data& date; //nova classe para tratar o tipo de data dhav 
	unsigned int sequential;
	unsigned int size;
	unsigned int date;
	long long int offset;
	int real_size;

public:
	Phrase () = delete;
	Phrase (const char*, int);
	void setAllInfo(const char*);
	unsigned short int getChannel();
	unsigned int getSequential();
	unsigned int getSize();
	unsigned int getDate();
};

#endif