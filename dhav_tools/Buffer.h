#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include "Arqdhav.h"
#include "Phrase.h"
#include "Arqout.h"

using namespace std;

class Buffer
{

private:

	int length_buffer = 100000000;
	long long int char_read = 0;
	char* buffer_init = nullptr;
	char* buffer_end = nullptr;

	string path;
	Arqdhav* arqdhav = nullptr;
	Arqout* arqout = nullptr;


public:

	//================ Constr e Destr =========
	Buffer(Arqdhav*, Arqout*);
	~Buffer();

	//================ Gettings ===============
	int getLength();
	char* getBufferInit();
	char* getBufferEnd();

	//================ Settings ===============
	void setBuffer(/*ifstream&*/);

	//================ Main Functions ========
	bool compareString(char*, char*);
	char* nextString(char*);
	void searchInWindow();
	char* rotateWindow(char*);
	

};

#endif
