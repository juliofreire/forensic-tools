#include <iostream>
#include "Arqdhav.h"
#include "Buffer.h"



int main (){


	string path = "../headers/seq000001.dd";
	string outpath = "./ok.csv";

	Arqdhav arq(path);

	// cout << arq.dirExist(path) << endl;

	cout << "The program is processing the following file: " << path << endl;

	ifstream inputfile(path, ifstream::binary);
	ofstream outputfile(outpath);

	int length =  arq.getLength();

	arq.searchOffsets(outputfile);

	inputfile.close();

	return 0;
}

// List of erros:

/*
return -1 = directory doesnt exist
*/