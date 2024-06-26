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
	// ??perguntar por que esse cara esta dando segmentation fault??
	// delete[] inputfile;
	inputfile->close();
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

void Arqdhav::updateBuffer(int deslocate, char* buffer_atual){
	// buffer_init = new char [length];
	// buffer = new Buffer();
	memcpy(buffer->buffer_init, buffer_atual, deslocate);
	inputfile->read(buffer->buffer_init+deslocate, buffer->length_buffer-deslocate);
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
		// sleep(1);
		cout << length_search << endl;
		// cout << length - length_search << endl;
		buffer_atual = (char*) memchr (buffer_atual, 'D', length_search);
		if (buffer_atual == nullptr) break;
		bool cH = (buffer_atual + 1) < buffer->buffer_end ? *(buffer_atual + 1) == 'H' : false;
		bool cA = (buffer_atual + 2) < buffer->buffer_end ? *(buffer_atual + 2) == 'A' : false;
		bool cV = (buffer_atual + 3) < buffer->buffer_end ? *(buffer_atual + 3) == 'V' : false;
		bool cFD = (buffer_atual + 4) < buffer->buffer_end ? *(buffer_atual + 4) == 253	 : false;
		bool c0 = (buffer_atual + 5) < buffer->buffer_end ? *(buffer_atual + 5) == 0   : false;
		bool match_pattern = cH && cA && cV && cFD;// && c0;
		cout << "string4: " << endl;// << hex << *(buffer_atual + 4) << hex << dec <<endl;
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
	cout << "Programa rodado e strings foram encontradas" << endl;
}
