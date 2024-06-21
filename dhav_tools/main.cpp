#include <iostream>
#include "Arqdhav.h"



int main (){

	Arqdhav arq;

	string path = "../headers/seq000001.dd";
	string outpath = "./ok.csv";

	// cout << arq.dirExist(path) << endl;

	if (!arq.dirExist(path)){
		cerr << "Directory doesn't exist" << endl;
		return -1;
	}

	cout << "The program is processing the following file: " << path << endl;

	ifstream inputfile(path, ifstream::binary);
	ofstream outputfile(outpath);

	arq.setLength(inputfile);
	int length =  arq.getLength();

	arq.setBuffers(inputfile);
	// char* buffer = arq.getBuffers();

	// cout << buffer[0] << endl;

	arq.searchOffsets(outputfile);
	
	cout<< length << endl;



	inputfile.close();

	return 0;
}

// List of erros:

/*
return -1 = directory doesnt exist
*/