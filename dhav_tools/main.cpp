#include <iostream>
#include "Arqdhav.h"
#include "Buffer.h"
#include "Phrase.h"
#include "Arqout.h"


int main (){


	// string path = "../headers/seq000001.dd";
	string path = "../media/teste.dd";
	string outpath = "ok";

	Arqdhav arq(path);
	Arqout output(outpath);
	// cout << arq.dirExist(path) << endl;

	cout << "The program is processing the following file: " << path << endl;

	// ifstream inputfile(path, ifstream::binary);
	// ofstream outputfile(outpath);

	long long int length =  arq.getLength();
	cout << "tamanho:" << length << endl;

	Buffer buf(&arq, &output);

	// arq.read(buf.getBufferInit(), 200);

	// cout << buf.getBufferInit() << endl;

	buf.searchInWindow();
	// arq.exec(outputfile);

	// cout << "estou aqui?" << endl;

	// inputfile.close();
	return 0;
}

// List of erros:

/*
return -1 = directory doesnt exist
*/
