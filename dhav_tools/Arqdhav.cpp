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

void Arqdhav::exec(/*ifstream& inputfile = this->inputfile,*/ ofstream& outpufile/*, long long int length_arq = this->length_arq*/)
{
	buffer.searchOffsets(*inputfile, outpufile, length_arq);
}

