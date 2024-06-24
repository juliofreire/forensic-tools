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
	setBuffer();

	// glue
	// int* i = new int(10);
	// cout << *i << endl;
	// delete i;
}



Arqdhav::~Arqdhav()
{
	inputfile->close();
	delete[] inputfile;
	// delete[] buffer_init;
}


bool Arqdhav::dirExist(const filesystem::path& path){
	return filesystem::exists(path);
}


void Arqdhav::setLength()
{
	inputfile->seekg(0, inputfile->end);
	length = inputfile->tellg();
	inputfile->seekg(0, inputfile->beg);
}


int Arqdhav::getLength()
{
	return length;
}


void Arqdhav::setBuffer(){
	// buffer_init = new char [length];
	buffer = new Buffer();

	inputfile->read(buffer->buffer_init, buffer->length_buffer);
	// buffer_end = buffer_init + length;
	// cout << buffer_init[0] << endl;

}


// char* Arqdhav::getBuffers(){
// 	return buffer_init;
// 	// cout << buffer_end << endl;
// }

char* Arqdhav::nextString(char* buffer_atual)
{
	int length_search = buffer->buffer_end - buffer_atual;
	cout << length - length_search << endl;
	// cout << buffer_atual[0] << endl;
	while(buffer_atual < buffer->buffer_end)
	{
		// CHECK DHAVFD ------ IT'S NECESSARY LOOK THE PATTERNS OF DHAV
		cout << length_search << endl;
		cout << length - length_search << endl;
		buffer_atual = (char*) memchr (buffer_atual, 'O', length_search);
		if (buffer_atual == nullptr) break;
		bool cH = (buffer_atual + 1) < buffer->buffer_end ? *(buffer_atual + 1) == 'F' : false;
		bool cA = (buffer_atual + 2) < buffer->buffer_end ? *(buffer_atual + 2) == 'N' : false;
		bool cV = (buffer_atual + 3) < buffer->buffer_end ? *(buffer_atual + 3) == 'I' : false;
		bool cFD = (buffer_atual + 4) < buffer->buffer_end ? *(buffer_atual + 4) == '8' : false;
		bool c0 = (buffer_atual + 5) < buffer->buffer_end ? *(buffer_atual + 5) == 0   : false;
		bool match_pattern = cH && cA && cV && cFD;// && c0;

		if (match_pattern) return buffer_atual;

		buffer_atual++;

		length_search = buffer->buffer_end - buffer_atual;
	}

	return nullptr;
}

void Arqdhav::searchOffsets(ofstream& outputfile)
{
	char* buffer_run_slow = nextString(buffer->buffer_init);
	if (buffer_run_slow == nullptr){
		cout << "String nao encontrada" << endl;
		exit(0);
	}
	char* buffer_run_fast = buffer_run_slow;
	while(buffer_run_fast < buffer->buffer_end)
	{
		buffer_run_fast = nextString(buffer_run_fast+1);

		if (buffer_run_fast == nullptr) break;
		
		outputfile << buffer_run_fast << "\n";
		buffer_run_slow = buffer_run_fast;

		// cout << "mais uma volta";
	}
	cout << "Programa rodado e strings encontradas" << endl;
}
