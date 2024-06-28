#include "Buffer.h"

Buffer::Buffer() : length_buffer(10000)
{
	buffer_init = new char[length_buffer];
	buffer_end = buffer_init + length_buffer;
}


Buffer::~Buffer()
{
	// delete[] buffer_init;
}


long int Buffer::getLength()
{
	return length_buffer;
}


char* Buffer::getBufferInit()
{
	return buffer_init;
}


char* Buffer::getBufferEnd()
{
	return buffer_end;
}

void Buffer::setBuffer(ifstream& inputfile){
	// getBufferInit() = new char [length_arq];
	// buffer = new Buffer();

	inputfile.read(getBufferInit(), getLength());
	// getBufferEnd() = getBufferInit() + length_arq;
	// cout << getBufferInit()[0] << endl;

}

void Buffer::updateBuffer(int deslocate, char* buffer_atual){
	// getBufferInit() = new char [length_arq];
	// buffer = new Buffer();
	// memcpy(getBufferInit(), buffer_atual, deslocate);
	// inputfile->read(getBufferInit()+deslocate, getLength()-deslocate);
	// getBufferEnd() = getBufferInit() + length_arq;
	// cout << getBufferInit()[0] << endl;

}


// char* Buffer::getBuffers(){
// 	return getBufferInit();
// 	// cout << getBufferEnd() << endl;
// }

bool Buffer::compareString(char* buffer_atual, char* buffer_end)
{
	bool cH = (buffer_atual + 1)  < buffer_end ? *(buffer_atual + 1) == 'H' : false;
	bool cA = (buffer_atual + 2)  < buffer_end ? *(buffer_atual + 2) == 'A' : false;
	bool cV = (buffer_atual + 3)  < buffer_end ? *(buffer_atual + 3) == 'V' : false;
	bool cFD = (buffer_atual + 4) < buffer_end ? *(buffer_atual + 4) == 253	 : false;
	bool c0 = (buffer_atual + 5)  < buffer_end ? *(buffer_atual + 5) == 0   : false;
	bool match_pattern = cH && cA && cV && cFD;// && c0;
	// cout << "string4: " << hex << *(buffer_atual + 4) << dec << endl;
	return match_pattern;
}


char* Buffer::nextString(char* buffer_atual, long long int length_arq)
{
	int length_search = getBufferEnd() - buffer_atual;
	cout << length_arq - length_search << endl;
	// cout << buffer_atual[0] << endl;
	while(buffer_atual < getBufferEnd())
	{
		// CHECK DHAVFD ------ IT'S NECESSARY LOOK THE PATTERNS OF DHAV
		// sleep(1);
		cout << length_search << endl;
		// cout << length_arq - length_search << endl;
		buffer_atual = (char*) memchr (buffer_atual, 'D', length_search);
		if (buffer_atual == nullptr) break;
		bool match_pattern = compareString(buffer_atual, getBufferEnd());
		// bool cH = (buffer_atual + 1) < getBufferEnd() ? *(buffer_atual + 1) == 'H' : false;
		// bool cA = (buffer_atual + 2) < getBufferEnd() ? *(buffer_atual + 2) == 'A' : false;
		// bool cV = (buffer_atual + 3) < getBufferEnd() ? *(buffer_atual + 3) == 'V' : false;
		// bool cFD = (buffer_atual + 4) < getBufferEnd() ? *(buffer_atual + 4) == 253	 : false;
		// bool c0 = (buffer_atual + 5) < getBufferEnd() ? *(buffer_atual + 5) == 0   : false;
		// bool match_pattern = cH && cA && cV && cFD;// && c0;
		
		if (match_pattern) return buffer_atual;

		buffer_atual++;

		length_search = getBufferEnd() - buffer_atual;
	}

	return nullptr;
}

void Buffer::searchOffsets(ifstream& inputfile, ofstream& outputfile, long long int length_arq)
{
	setBuffer(inputfile);
	
	char* buffer_run_slow = nextString(getBufferInit(), length_arq);
	if (buffer_run_slow == nullptr){
		cout << "String nao encontrada" << endl;
		exit(0);
	}
	char* buffer_run_fast = buffer_run_slow;
	while(buffer_run_fast < getBufferEnd())
	{
		buffer_run_fast = nextString(buffer_run_fast+1, length_arq);

		if (buffer_run_fast == nullptr) break;
		
		outputfile << buffer_run_fast << "\n";
		buffer_run_slow = buffer_run_fast;

		// cout << "mais uma volta";
	}
	cout << "Programa rodado e strings foram encontradas" << endl;
}