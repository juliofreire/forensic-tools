#include "Buffer.h"
#include <unistd.h>
#include "Arqout.h"

/* Initializate the buffer calling the inputfile from Arqdhav Class
and create a file of output specified of Arqout. Moreover, set the
length of buffers, creating a reference to where starts the buffer and
where it ends.*/
Buffer::Buffer(Arqdhav* arqdhav, Arqout* arqout)
{
	buffer_init = new char[length_buffer];
	buffer_end = buffer_init + length_buffer;
	this->arqdhav = arqdhav;
	this->arqout = arqout;

}


Buffer::~Buffer()
{

}


/* A function if someone outside wants to know the length of the buffer*/
int Buffer::getLength()
{
	return length_buffer;
}

/* Returns the begin of the buffer*/
char* Buffer::getBufferInit()
{
	return buffer_init;
}

/* Return the end of the buffer*/
char* Buffer::getBufferEnd()
{
	return buffer_end;
}

/* Call this function to load on the buffer in main memory, this
allows to read more fast than in HD*/
void Buffer::setBuffer(){
	arqdhav->read(buffer_init, length_buffer);
}


int Buffer::compareString(char* buffer_atual)
{
/*
0 = ok
1 = doesnt match
2 = doesnt find in all buffer

*/
	buffer_atual = (char*) memchr (buffer_atual, 'D', buffer_end - buffer_atual);
	if (buffer_atual == nullptr)
		return 2;
	bool cH = (buffer_atual + 1)  < buffer_end ? *(buffer_atual + 1) == 'H' : false;
	bool cA = (buffer_atual + 2)  < buffer_end ? *(buffer_atual + 2) == 'A' : false;
	bool cV = (buffer_atual + 3)  < buffer_end ? *(buffer_atual + 3) == 'V' : false;
	bool cFD = (buffer_atual + 4) < buffer_end ? (int)(unsigned char)*(buffer_atual + 4) == 253	 : false;
	bool c0 = (buffer_atual + 5)  < buffer_end ? /*(int)(unsigned char)*/(buffer_atual + 5) == 0   : false;
	bool match_pattern = cH && cA && cV && cFD;// && c0;
	if (match_pattern != 0)	printf("achei algo");
	return match_pattern ? 0 : 1;
}


char* Buffer::nextString(char* buffer_atual)
{
	int length_search = buffer_end - buffer_atual;
	// cout << "okok" << length_search << endl;
	char* local_init = buffer_atual;
	// cout << "restam: " << arqdhav->getLength() - char_read << endl;
	int window_read = 0;
	while(buffer_atual < getBufferEnd())
	{
		// buffer_atual = (char*) memchr (buffer_atual, 'D', length_search);
		// cout << "entrou?" << endl;
		// if (buffer_atual == nullptr)
		// {
			// break;
		// }
		// if (buffer_end - buffer_atual < 1000) {return nullptr;}
		int pattern;
		pattern = compareString(buffer_atual);

		if (pattern == 2) break;
		// if (match_pattern) {cout << "ACHEI !!!!!!!!!!!!!!!!!!!!!!!!!" << endl;};
		// if (buffer_atual)
		// {
		if (pattern == 0)
		{
			int searched = buffer_atual - local_init;
			cout << "searched" << searched << endl;
			int found = char_read + searched;
			char_read += searched+1;
			cout << "ENCONTRADO AQUI: " << hex << found << dec << endl;
			// cout << "buffer_atual" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_atual[0] << endl;
			return buffer_atual;
		}
		// }
		
		buffer_atual++;
		length_search = getBufferEnd() - buffer_atual;
	}
	// cout << "antes" << char_read << '+' << length_search <<endl;
	char_read += length_search+1; // adicionar ou não +1??
	// cout << "depois" <<char_read << endl;
	return nullptr;
}

void Buffer::searchInWindow()
{
	setBuffer();

	
	char* buffer_run_slow = nextString(getBufferInit());
	// cout << "buffer slow0" << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer_run_slow[0] << endl;
	// cout << dec;
	// fase de teste
	int rotates = 0;
	while (buffer_run_slow == nullptr && rotates < 10){
		// cout << "continuando a busca" << endl;
		buffer_run_slow = rotateWindow(buffer_end);
		buffer_run_slow = nextString(buffer_run_slow);
		rotates++;
	}


	char* buffer_run_fast = buffer_run_slow;
	// cout << "lidos: " << char_read << endl;

	while(char_read < arqdhav->getLength() && rotates < 20)
	{

		// cout << "e agora?" << endl;
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

			// cout << "try" << buffer_run_fast[0] << endl;// - (buffer_run_slow - getBufferInit()) << endl;
			Phrase metadata(buffer_run_slow, buffer_run_fast - buffer_run_slow, char_read - 1);
			cout << "channel " 	  << hex << metadata.getChannel() << endl;
			cout << "sequential " << hex << metadata.getSequential() << endl;
			cout << "size "		  << hex << metadata.getSize() << endl;
			cout << "date " 	  << hex << metadata.getDate() << endl;
			cout << "Year " << dec << metadata.getYear() << endl;
			cout << "Month " << dec << metadata.getMonth() << endl;
			cout << "Day " << dec << metadata.getDay() << endl;
			cout << "Hour " << dec << metadata.getHour() << endl;
			cout << "Minute " << dec << metadata.getMinute() << endl;
			cout << "Seconds " << dec << metadata.getSeconds() << endl;
			cout << dec << endl;
			arqout->WriteOn(&metadata);
			buffer_run_slow = buffer_run_fast;
		}		
		// cout << "lidos meio: " << char_read << endl;	
		if (buffer_run_fast == nullptr)
		{
			// cout << dec << buffer_run_slow - getBufferInit() << endl;
			int deslocate = getBufferEnd() - buffer_run_slow;// - getBufferInit();
			int read = buffer_run_slow - buffer_init;
			// cout << "deslocate" << deslocate << endl;
			// if (deslocate == 0) deslocate = length_buffer;
			buffer_run_fast = rotateWindow(buffer_run_slow);//length_buffer);
			// buffer_run_fast = buffer_run_slow + (deslocate);

			rotates++;
			
			// cout << "rotates: " << rotates << endl;
			buffer_run_slow = getBufferInit();
			// buffer_run_slow = buffer_run_fast-deslocate-1;
		}

		// buffer_run_slow = buffer_run_fast-deslocate;
		// cout << "lidos fim: " << char_read << endl;
	}
	// cout << "Programa rodado e strings foram encontradas" << endl;
}

char* Buffer::rotateWindow(char* valid_buffer)
{
	int deslocate = buffer_end - valid_buffer;
	int read = valid_buffer - getBufferInit();
	cout << "=============== Rotating ================" << endl;
	cout << "Rotacionando " << deslocate << " bytes ..." << endl;
	cout << "Serão lidos " << read << " bytes ..." << endl;
	// char* tmp_buffer = new char[deslocate];
	// memcpy(tmp_buffer, valid_buffer, deslocate);
	memcpy(buffer_init, valid_buffer, deslocate);
	// memcpy(buffer_init, tmp_buffer, deslocate);
	cout << "Copiado..." << endl;
	if (deslocate == length_buffer){
		arqdhav->read(getBufferInit(), read);
		cout << "é igual";
	} else {
		arqdhav->read(getBufferInit()+deslocate, read);
	}
	// char_read -= deslocate;
	return getBufferInit()+deslocate;
}

