#include "Phrase.h"

Phrase::Phrase(const char* init, int real_size)
{
	this->real_size = real_size;
	setAllInfo(init);

}

void Phrase::setAllInfo(const char* buffer)
{
	channel = buffer[6];//+buffer[7];
	sequential = buffer[8];//+buffer[9]+buffer[10]+buffer[11];
	size = buffer[12]+buffer[13]+buffer[14]+buffer[15];
	data = buffer[12]+buffer[13]+buffer[14]+buffer[15];
}

int Phrase::getAllInfo(){
	return sequential;
}
