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

	int length_buffer;
	long long int char_read = 0;
	char* buffer_init = nullptr;
	char* buffer_end = nullptr;


public:

// public:
	Buffer();
	~Buffer();

	int getLength();
	char* getBufferInit();
	char* getBufferEnd();

	//================ Settings ===============
	void setBuffer(ifstream&);
	// void updateBuffer(int, char*);


	//================ Main Functions ========
	bool compareString(char*, char*);
	char* nextString(char*, long long int);
	void searchInWindow(ifstream&, ofstream&, long long int);
	char* rotateWindow(ifstream&, char*, long long int, int);

};

#endif