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
	int channel;
	// Data& date; //nova classe para tratar o tipo de data dhav 
	int data;
	int sequential;
	int size;
	long long int offset;
	int real_size;

public:
	Phrase () = delete;
	Phrase (const char*, int);
	void setAllInfo(const char*);
	int getAllInfo();
};

#endif