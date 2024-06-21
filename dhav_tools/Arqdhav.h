#ifndef ARQDHAV_H
#define ARQDHAV_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

using namespace std;


class Arqdhav
{

private:
	char* buffer_init;
	char* buffer_end;
	int length;

public:

	//================ Constr e Destr ========
	Arqdhav();
	~Arqdhav();

	//================ Validations ===========
	bool dirExist(const filesystem::path&);

	//================ Preliminar ============
	void setLength(ifstream&);
	int getLength();

	//================ Setting ===============
	void setBuffers(ifstream&);
	char* getBuffers();

	//================ Main Functions ========
	char* nextString(char*);
	string searchOffsets(ofstream&);


	/*
	Ler sobre inline, const e constexpr
	inline dirExist(filesystem::path& path) { return filesystem::exists(path) };
	*/
};



#endif
