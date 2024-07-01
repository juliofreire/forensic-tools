#include "Buffer.h"

Buffer::Buffer() : length_buffer(1000)
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




// char* Buffer::getBuffers(){
// 	return getBufferInit();
// 	// cout << getBufferEnd() << endl;
// }

bool Buffer::compareString(char* buffer_atual, char* buffer_end)
{
	bool cH = (buffer_atual + 1)  < buffer_end ? *(buffer_atual + 1) == 'H' : false;
	bool cA = (buffer_atual + 2)  < buffer_end ? *(buffer_atual + 2) == 'A' : false;
	bool cV = (buffer_atual + 3)  < buffer_end ? *(buffer_atual + 3) == 'V' : false;
	bool cFD = (buffer_atual + 4) < buffer_end ? (int)(unsigned char)*(buffer_atual + 4) == 253	 : false;
	bool c0 = (buffer_atual + 5)  < buffer_end ? (int)(unsigned char)*(buffer_atual + 5) == 0   : false;
	bool match_pattern = cH && cA && cV;// && cFD && c0;
	// cout << "string1: " << (int)(unsigned char)*(buffer_atual+8) << dec << endl;
	return match_pattern;
}


char* Buffer::nextString(char* buffer_atual, long long int length_arq)
{
	int length_search = getBufferEnd() - buffer_atual;
	cout << "restam: " << length_arq - char_read << endl;
	// cout << buffer_atual[0] << endl;
	int window_read = 0;
	while(buffer_atual < getBufferEnd())
	{
		// sleep(1);
		
		// cout << length_arq - length_search << endl;
		buffer_atual = (char*) memchr (buffer_atual, 'D', length_search);
		int window_read_tmp = length_buffer - length_search - window_read;
		window_read = length_buffer - length_search;
		cout  << "ja foram lidos na janela: " << window_read << endl;
		char_read += window_read_tmp;
		cout  << "ja foram lidos no total: " << char_read << endl;
		if (buffer_atual == nullptr)
			{
				window_read_tmp = length_buffer - window_read;
				char_read += window_read_tmp;
				break;
			}
		// cout << "entrei?" << endl;
		bool match_pattern = compareString(buffer_atual, getBufferEnd());
		// bool cH = (buffer_atual + 1) < getBufferEnd() ? *(buffer_atual + 1) == 'H' : false;
		// bool cA = (buffer_atual + 2) < getBufferEnd() ? *(buffer_atual + 2) == 'A' : false;
		// bool cV = (buffer_atual + 3) < getBufferEnd() ? *(buffer_atual + 3) == 'V' : false;
		// bool cFD = (buffer_atual + 4) < getBufferEnd() ? *(buffer_atual + 4) == 253	 : false;
		// bool c0 = (buffer_atual + 5) < getBufferEnd() ? *(buffer_atual + 5) == 0   : false;
		// bool match_pattern = cH && cA && cV && cFD;// && c0;
		if (match_pattern) {cout << "ACHEI !!!!!!!!!!!!!!!!!!!!!!!!!" << endl;};
		if (match_pattern) return buffer_atual;

		buffer_atual++;


		length_search = getBufferEnd() - buffer_atual;
	}

	return nullptr;
}

void Buffer::searchInWindow(ifstream& inputfile, ofstream& outputfile, long long int length_arq)
{
	setBuffer(inputfile);
	
	char* buffer_run_slow = nextString(getBufferInit(), length_arq);
	// fase de teste
	int rotates = 0;
	if (buffer_run_slow == nullptr){
		rotateWindow(inputfile, getBufferInit(), length_arq, 1000);
		buffer_run_slow = nextString(getBufferInit(), length_arq);
		// cout << "String nao encontrada" << endl;
		// if(buffer_run_slow) continue;
		// exit(0);
		rotates++;
	}
	// cout << "e agora?" << endl;
	char* buffer_run_fast = buffer_run_slow;
	// cout << "e agora?" << endl;
	cout << "lidos: " << char_read << endl;

	while(buffer_run_fast < getBufferEnd() && rotates < 5)
	{
		cout << "e agora?" << endl;
		buffer_run_fast = nextString(buffer_run_fast+1, length_arq);

		if (buffer_run_fast == nullptr)
			{
				rotateWindow(inputfile, buffer_run_fast, length_arq, 0);
				cout << "depois de rotacionar" << endl;
				rotates++;
				buffer_run_fast = buffer_run_slow;
				cout << "rotates: " << rotates << endl;
			}

		
		// outputfile << buffer_run_fast << "\n";
		// buffer_run_slow = buffer_run_fast;

		// cout << "mais uma volta";
	}
	cout << "Programa rodado e strings foram encontradas" << endl;
}

void Buffer::updateBuffer(int deslocate, char* buffer_atual){
	// getBufferInit() = new char [length_arq];
	// buffer = new Buffer();
	// memcpy(getBufferInit(), buffer_atual, deslocate);
	// inputfile->read(getBufferInit()+deslocate, getLength()-deslocate);
	// getBufferEnd() = getBufferInit() + length_arq;
	// cout << getBufferInit()[0] << endl;

}

void Buffer::rotateWindow(ifstream& inputfile, char* buffer_atual, long long int length_arq, int deslocate)
{
	cout << "Rotacionando..." << endl;
	memcpy(buffer_atual, buffer_atual+(getLength() - deslocate), deslocate);
	cout << "Copiado..." << endl;
	inputfile.read(buffer_atual+(getLength() - deslocate), deslocate);
}

//void Buffer:search(){
	// 
// }