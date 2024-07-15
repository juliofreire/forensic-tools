#include "Buffer.h"
#include <unistd.h>

Buffer::Buffer(Arqdhav* arqdhav)
{
	buffer_init = new char[length_buffer];
	buffer_end = buffer_init + length_buffer;

	this->arqdhav = arqdhav;

}


Buffer::~Buffer()
{
	delete[] buffer_init;
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


void Buffer::setBuffer(){
	arqdhav->read(getBufferInit(), getLength());
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
	return match_pattern;
}


char* Buffer::nextString(char* buffer_atual)
{
	int length_search = getBufferEnd() - getBufferInit();
	cout << "okok" << length_search << endl;
	char* local_init = getBufferInit();
	cout << "restam: " << arqdhav->getLength() - char_read << endl;
	int window_read = 0;
	while(buffer_atual < getBufferEnd())
	{
		// sleep(1);
		buffer_atual = (char*) memchr (buffer_atual, 'D', length_search);
		cout << "entrou?" << endl;
		if (buffer_atual == nullptr)
		{
			break;
		}

		bool match_pattern = compareString(buffer_atual, getBufferEnd());
		if (match_pattern) {cout << "ACHEI !!!!!!!!!!!!!!!!!!!!!!!!!" << endl;};
		if (match_pattern)
		{
			int searched = buffer_atual - local_init;
			int found = char_read+searched;
			cout << "ENCONTRADO AQUI: " << found << endl;
			return buffer_atual;
		}
		
		buffer_atual++;
		length_search = getBufferEnd() - buffer_atual;
	}
	char_read += getLength();
	return nullptr;
}

void Buffer::searchInWindow()
{
	setBuffer();

	
	char* buffer_run_slow = nextString(getBufferInit());
	// fase de teste
	int rotates = 0;
	while (buffer_run_slow == nullptr){
		buffer_run_slow = rotateWindow(length_buffer);
		buffer_run_slow = nextString(buffer_run_slow);
		rotates++;
	}
	char* buffer_run_fast = buffer_run_slow;
	cout << "lidos: " << char_read << endl;

	while(char_read < arqdhav->getLength() && rotates < 10/*buffer_run_fast < getBufferEnd() && rotates < 10*/)
	{
		cout << "e agora?" << endl;
		buffer_run_fast = nextString(buffer_run_fast+1);

		if (buffer_run_fast == nullptr)
		{
			buffer_run_fast = rotateWindow(length_buffer);
			rotates++;
			
			cout << "rotates: " << rotates << endl;
		}

		Phrase metadata(buffer_run_slow, buffer_run_fast - buffer_run_slow);
		cout << "hex" << hex << metadata.getAllInfo() << endl;
		cout << dec << endl;
		buffer_run_slow = buffer_run_fast;
		cout << "lidos: " << char_read << endl;
	}
	cout << "Programa rodado e strings foram encontradas" << endl;
}

char* Buffer::rotateWindow(int deslocate)
{
	cout << "Rotacionando..." << endl;
	memcpy(getBufferInit(), getBufferInit()+(getLength() - deslocate), deslocate);
	cout << "Copiado..." << endl;
	arqdhav->read(getBufferInit()+(getLength() - deslocate), deslocate);
	return getBufferInit();
}

//void Buffer:search(){
	// 
// }
