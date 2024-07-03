#include "Buffer.h"

Buffer::Buffer() : length_buffer(500)
{
	buffer_init = new char[length_buffer];
	buffer_end = buffer_init + length_buffer;
}


Buffer::~Buffer()
{
	// delete[] buffer_init;
}


int Buffer::getLength()
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
	int length_search = getBufferInit() - getBufferEnd();
	// cout << " olha so: " << getBufferInit() - getBufferEnd() << endl;
	char* local_init = getBufferInit();
	// char* local_end = buffer_atual + getLength();
	// int length_search = local_end-local_init;
	cout << "restam: " << length_arq - char_read << endl;
	// cout << buffer_atual[0] << endl;	
	int window_read = 0;
	while(buffer_atual < getBufferEnd())
	{
		// sleep(1);
		
		// cout << length_arq - length_search << endl;
		buffer_atual = (char*) memchr (buffer_atual, 'D', length_search);


		// int window_read_tmp = (buffer_atual - window_init) - window_read;
		// window_read = length_buffer - length_search;
		
		// char_read += window_read_tmp;
		// cout  << "ja foram lidos no total: " << char_read << endl;


		if (buffer_atual == nullptr)
		{
			// window_read_tmp = length_buffer - window_read;
			// char_read += getLength();
			break;
		} //else {cout  << "ja foram lidos na janela: " << (buffer_atual - local_init)<< endl;};

		bool match_pattern = compareString(buffer_atual, getBufferEnd());
		if (match_pattern) {cout << "ACHEI !!!!!!!!!!!!!!!!!!!!!!!!!" << endl;};
		if (match_pattern)
		{
			// window_read_tmp = length_buffer - length_search - window_read_tmp;
			// char_read += window_read_tmp;
			int searched = buffer_atual - local_init;
			int found = char_read+searched;
			cout << "ENCONTRADO AQUI: " << found << endl;
			// char_read += searched;
			return buffer_atual;
		}
		
		buffer_atual++;


		length_search = length_arq - char_read;
	}
	char_read += getLength();
	return nullptr;
}

void Buffer::searchInWindow(ifstream& inputfile, ofstream& outputfile, long long int length_arq)
{
	setBuffer(inputfile);
	
	char* buffer_run_slow = nextString(getBufferInit(), length_arq);
	// fase de teste
	int rotates = 0;
	while (buffer_run_slow == nullptr){
		buffer_run_slow = rotateWindow(inputfile, getBufferInit(), length_arq, length_buffer);
		buffer_run_slow = nextString(buffer_run_slow, length_arq);
		// cout << "String nao encontrada" << endl;
		// if(buffer_run_slow) continue;
		// exit(0);
		rotates++;
	}
	// cout << "e agora?" << endl;
	char* buffer_run_fast = buffer_run_slow;
	// cout << "e agora?" << endl;
	cout << "lidos: " << char_read << endl;

	while(buffer_run_fast < getBufferEnd() && rotates < 300)
	{
		cout << "e agora?" << endl;
		buffer_run_fast = nextString(buffer_run_fast+1, length_arq);

		if (buffer_run_fast == nullptr)
		{
			buffer_run_fast = rotateWindow(inputfile, getBufferInit(), length_arq, length_buffer);
			cout << "depois de rotacionar" << endl;
			rotates++;
			cout << "lidos: " << char_read << endl;
			// buffer_run_slow = buffer_run_fast;
			cout << "rotates: " << rotates << endl;
		} //else {
			buffer_run_slow = buffer_run_fast;
			cout << "encontrei no: " << char_read << endl;
			// buffer_run_fast = nextString(buffer_run_fast+1, length_arq);
			// buffer_run_fast = rotateWindow(inputfile, getBufferInit(), length_arq, getBufferEnd() - buffer_run_fast);
			// cout << "depois de rotacionar" << endl;
			// rotates++;
			// cout << "rotates: " << rotates << endl;
		// }

		
		// outputfile << buffer_run_fast << "\n";
		

		// cout << "mais uma volta";
	}
	cout << "Programa rodado e strings foram encontradas" << endl;
}

// void Buffer::updateBuffer(int deslocate, char* buffer_atual){
// 	// getBufferInit() = new char [length_arq];
// 	// buffer = new Buffer();
// 	// memcpy(getBufferInit(), buffer_atual, deslocate);
// 	// inputfile->read(getBufferInit()+deslocate, getLength()-deslocate);
// 	// getBufferEnd() = getBufferInit() + length_arq;
// 	// cout << getBufferInit()[0] << endl;

// }

char* Buffer::rotateWindow(ifstream& inputfile, char* buffer_atual, long long int length_arq, int deslocate)
{
	cout << "Rotacionando..." << endl;
	memcpy(buffer_atual, buffer_atual+(getLength() - deslocate), deslocate);
	cout << "Copiado..." << endl;
	inputfile.read(buffer_atual+(getLength() - deslocate), deslocate);
	return buffer_atual;
}

//void Buffer:search(){
	// 
// }