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
	int length_search = getBufferEnd() - buffer_atual;
	cout << "okok" << length_search << endl;
	char* local_init = buffer_atual;
	cout << "restam: " << arqdhav->getLength() - char_read << endl;
	int window_read = 0;
	while(buffer_atual < getBufferEnd())
	{
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
			cout << "searched" << searched << endl;
			int found = char_read + searched;
			char_read += searched+1;
			cout << "ENCONTRADO AQUI: " << found << endl;
			// cout << "buffer_atual" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_atual[0] << endl;
			return buffer_atual;
		}
		
		buffer_atual++;
		// length_search = getBufferEnd() - buffer_atual;
	}
	cout << "antes" << char_read << '+' << length_search <<endl;
	char_read += length_search+1; // adicionar ou não +1??
	cout << "depois" <<char_read << endl;
	return nullptr;
}

void Buffer::searchInWindow()
{
	setBuffer();

	
	char* buffer_run_slow = nextString(getBufferInit());
	cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[0] << endl;
	cout << dec;
	// fase de teste
	int rotates = 0;
	while (buffer_run_slow == nullptr){
		buffer_run_slow = rotateWindow(length_buffer);
		buffer_run_slow = nextString(buffer_run_slow);
		rotates++;
	}


	char* buffer_run_fast = buffer_run_slow;
	cout << "lidos: " << char_read << endl;

	while(char_read < arqdhav->getLength())// && rotates < 5/*buffer_run_fast < getBufferEnd() && rotates < 10*/)
	{

		cout << "e agora?" << endl;
		buffer_run_fast = nextString(buffer_run_fast+1);
		if (buffer_run_fast != nullptr){
			// buffer_run_slow = getBufferInit();
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[0] << endl;
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[1] << endl;
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[2] << endl;
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[3] << endl;
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[4] << endl;
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[5] << endl;
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[6] << endl;
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[7] << endl;
			// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[8] << endl;

			buffer_run_slow = buffer_run_fast;
			// cout << "try" << buffer_run_fast[0] << endl;// - (buffer_run_slow - getBufferInit()) << endl;
			Phrase metadata(buffer_run_slow, buffer_run_fast - buffer_run_slow);
			cout << "hex" << hex << metadata.getAllInfo() << endl;
			cout << dec << endl;
		}		
		cout << "lidos meio: " <<char_read << endl;	
		if (buffer_run_fast == nullptr)
		{
			// cout << dec << buffer_run_slow - getBufferInit() << endl;
			int deslocate = getBufferEnd() - buffer_run_slow;// - getBufferInit();
			cout << "deslocate" << deslocate << endl;
			buffer_run_fast = rotateWindow(deslocate);//length_buffer);
			// buffer_run_fast = buffer_run_slow + (deslocate);

			rotates++;
			
			cout << "rotates: " << rotates << endl;
			buffer_run_slow = getBufferInit();
			// buffer_run_slow = buffer_run_fast-deslocate-1;
		}

		// buffer_run_slow = buffer_run_fast-deslocate;
		cout << "lidos fim: " << char_read << endl;
	}
	cout << "Programa rodado e strings foram encontradas" << endl;
}

char* Buffer::rotateWindow(int deslocate)
{
	cout << "=============== Rotating ================" << endl;
	cout << "Rotacionando " << deslocate << " bytes ..." << endl;
	memcpy(getBufferInit(), getBufferInit() + deslocate, getLength() - deslocate);
	cout << "Copiado..." << endl;
	arqdhav->read(getBufferInit()+(getLength() - deslocate), deslocate);
	// char_read -= getLength() - deslocate;
	return getBufferInit() +getLength() - deslocate;
}

//void Buffer:search(){
	// 
// }
