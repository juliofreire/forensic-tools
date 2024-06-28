#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
// #include "Arqdhav.h"

using namespace std;

class Buffer
{

private:

	long int length_buffer;
	char* buffer_init = nullptr;
	char* buffer_end = nullptr;

public:

// public:
	Buffer();
	~Buffer();

	long int getLength();
	char* getBufferInit();
	char* getBufferEnd();

	//================ Settings ===============
	void setBuffer(ifstream&);
	void updateBuffer(int, char*);


	//================ Main Functions ========
	bool compareString(char*, char*);
	char* nextString(char*, long long int);
	void searchOffsets(ifstream&, ofstream&, long long int);

};

#endif