#include "Arqdhav.h"
#include <unistd.h>


Arqdhav::Arqdhav(const string& path)
{
	this->path = path;

	if (!dirExist(path)){
		cerr << "Diretorio nao existe" << endl;
		exit(0);
	}

	inputfile = new ifstream(path, ifstream::binary);
	setLength();

	// glue
	// int* i = new int(10);
	// cout << *i << endl;
	// delete i;
}



Arqdhav::~Arqdhav()
{
	inputfile->close();
	delete inputfile;
}


bool Arqdhav::dirExist(const filesystem::path& path){
	return filesystem::exists(path);
}


void Arqdhav::setLength()
{
	inputfile->seekg(0, inputfile->end);
	length_arq = inputfile->tellg();
	inputfile->seekg(0, inputfile->beg);
}


long long int Arqdhav::getLength()
{
	return length_arq;
}

void Arqdhav::read(char* initAddress, int length)
{
	inputfile->read(initAddress, length);
}

ifstream& Arqdhav::getFile()
{
	return *inputfile;
}
