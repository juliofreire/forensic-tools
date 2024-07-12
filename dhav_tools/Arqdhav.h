#ifndef ARQDHAV_H
#define ARQDHAV_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
// #include "Buffer.h"

using namespace std;


class Arqdhav
{

private:

	//================ Variables =============

	// char* buffer_init = nullptr;
	// char* buffer_end = nullptr;
	// Buffer buffer;
	long long int length_arq = 0;
	string path;
	ifstream* inputfile = nullptr;

	//================ Functions =============


public:


	//================ Constr e Destr =========
	Arqdhav(const string&);
	~Arqdhav();

	//================ Settings ===============
	void setLength();
	void read(char*, int);
	
	// void setBuffers();

	//================ Validations ===========
	bool dirExist(const filesystem::path&);

	//================ Utilites ==============
	long long int getLength();
	ifstream& getFile();



	/*
	Ler sobre inline, const e constexpr
	inline dirExist(filesystem::path& path) { return filesystem::exists(path) };
	*/
};


#endif
