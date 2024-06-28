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
	// Buffer* buffer;
	Buffer buffer;
	long long int length_arq = 0;
	int offset = 0; // acumulator of offsets read in searchOffsets
	string path;
	ifstream* inputfile = nullptr;

	//================ Functions =============



public:


	//================ Constr e Destr ========
	Arqdhav(const string&);
	Arqdhav() = delete;
	~Arqdhav();

	//================ Settings ===============
	void setLength();
	
	// void setBuffers();

	//================ Validations ===========
	bool dirExist(const filesystem::path&);

	//================ Utilites ==============
	
	long long int getLength();

	//================ Main Functions ========
	// bool compareString(char*, char*);
	// char* nextString(char*);
	// void searchOffsets(ofstream&);
	void exec(/*ifstream&,*/ ofstream&/*, long long int*/);


	/*
	Ler sobre inline, const e constexpr
	inline dirExist(filesystem::path& path) { return filesystem::exists(path) };
	*/
};


#endif
