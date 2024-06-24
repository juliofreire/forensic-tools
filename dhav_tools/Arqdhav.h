#ifndef ARQDHAV_H
#define ARQDHAV_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include "Buffer.h"

using namespace std;


class Arqdhav
{

private:

	//================ Variables =============

	// char* buffer_init = nullptr;
	// char* buffer_end = nullptr;
	Buffer* buffer;
	int length = 0;
	int offset = 0; // acumulator of offsets read in searchOffsets
	string path;
	ifstream* inputfile = nullptr;

	//================ Functions =============

	//================ Setting ===============
	void setLength();
	void setBuffer();
	// void setBuffers();

public:


	//================ Constr e Destr ========
	Arqdhav(const string&);
	Arqdhav() = delete;
	~Arqdhav();

	//================ Validations ===========
	bool dirExist(const filesystem::path&);

	//================ Utilites ==============
	
	int getLength();
	// char* getBuffers();

	//================ Main Functions ========
	char* nextString(char*);
	void searchOffsets(ofstream&);


	/*
	Ler sobre inline, const e constexpr
	inline dirExist(filesystem::path& path) { return filesystem::exists(path) };
	*/
};


#endif
