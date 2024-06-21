#include "Arqdhav.h"
#include <unistd.h>


Arqdhav::Arqdhav()
{
	buffer_init = nullptr;
	length = 0;
}


Arqdhav::~Arqdhav()
{
	delete[] buffer_init;
}


bool Arqdhav::dirExist(const filesystem::path& path){
	return filesystem::exists(path);
}


void Arqdhav::setLength(ifstream& inputfile)
{
	inputfile.seekg(0, inputfile.end);
	length = inputfile.tellg();
	inputfile.seekg(0, inputfile.beg);
}


int Arqdhav::getLength()
{
	return length;
}


void Arqdhav::setBuffers(ifstream& inputfile){
	buffer_init = new char [length];
	inputfile.read(buffer_init, length);
	buffer_end = buffer_init + length;
	cout << buffer_init[0] << endl;

}


char* Arqdhav::getBuffers(){
	return buffer_init;
	// cout << buffer_end << endl;
}

char* Arqdhav::nextString(char* buffer_atual)
{
	int length_search = buffer_end - buffer_atual;
	cout << length_search << endl;
	cout << buffer_atual[0] << endl;
	while(buffer_atual < buffer_end)
	{
		// CHECK DHAVFD ------ IT'S NECESSARY LOOK THE PATTERNS OF DHAV
		cout << length_search << endl;
		buffer_atual = (char*) memchr (buffer_atual, 'O', length_search);
		if (buffer_atual == nullptr) break;
		bool cH = (buffer_atual + 1) < buffer_end ? *(buffer_atual + 1) == 'F': false;
		bool cA = (buffer_atual + 2) < buffer_end ? *(buffer_atual + 2) == 'N': false;
		bool cV = (buffer_atual + 3) < buffer_end ? *(buffer_atual + 3) == 'I': false;
		bool cF = (buffer_atual + 4) < buffer_end ? *(buffer_atual + 4) == '8': false;
		bool cD = (buffer_atual + 5) < buffer_end ? *(buffer_atual + 5) == 'D': false;
		bool match_pattern = cH && cA && cV; //&& cF// && cD;

		if (match_pattern) return buffer_atual;

		buffer_atual++;

		length_search = buffer_end - buffer_atual;
	}

	return nullptr;
}

string Arqdhav::searchOffsets(ofstream& outputfile)
{
	char* buffer_run_slow = nextString(buffer_init);
	char* buffer_run_fast = buffer_run_slow;
	cout << endl;
	while(buffer_run_fast < buffer_end)
	{
		buffer_run_fast = nextString(buffer_run_fast+1);

		if (buffer_run_fast == nullptr) break;
		
		outputfile << buffer_run_fast << "\n";
		buffer_run_slow = buffer_run_fast;

		// cout << "mais uma volta";
	}
	return "ok";
}
