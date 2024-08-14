#include "Arqdhav.h"
#include <unistd.h>


/* This is the constructor class that manages the inputfile.
It aims check the existence of the input, and create a ifstream
object which will be read and load on buffer*/
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


/* This destructor just closes and dealocate the memory*/
Arqdhav::~Arqdhav()
{
	inputfile->close();
	delete inputfile;
}

/* Auxiliar method that return a bool if a directory exists*/
bool Arqdhav::dirExist(const filesystem::path& path){
	return filesystem::exists(path);
}

/* Write in lenght_arq the size of inputfile*/
void Arqdhav::setLength()
{
	inputfile->seekg(0, inputfile->end);
	length_arq = inputfile->tellg();
	inputfile->seekg(0, inputfile->beg);
}

/* Return the value of length the inputfile*/
long long int Arqdhav::getLength()
{
	return length_arq;
}

/* This functions is deprecated, once this assignment is the
role of the buffer*/
void Arqdhav::read(char* initAddress, int length)
{
	inputfile->read(initAddress, length);
}

/* Just returns the fstream object which is ready to be read
in the main memory*/
ifstream& Arqdhav::getFile()
{
	return *inputfile;
}
