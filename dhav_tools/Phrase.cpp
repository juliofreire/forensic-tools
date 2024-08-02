#include "Phrase.h"
#include <iostream>
#include <sstream>
#include <iomanip>


Phrase::Phrase(const char* init, int real_size)
{
	this->real_size = real_size;
	setAllInfo(init);

}

void Phrase::setAllInfo(const char* buffer)
{
	/*
	channel = 6~7
	sequential = 8~11
	tamanhho = 12~15
	date = 16~19
	*/

	memcpy(&channel, buffer, 14);// channel = buffer[6];//+buffer[7];
	memcpy(&sequential, buffer+8, 4);//sequential = (unsigned char)buffer[0];// + (unsigned char)buffer[1];//+buffer[9]+buffer[10]+buffer[11];
	memcpy(&size, buffer+12, 4);//size = buffer[12]+buffer[13]+buffer[14]+buffer[15];
	memcpy(&date, buffer+16, 4);//data = buffer[12]+buffer[13]+buffer[14]+buffer[15];
}

unsigned short int Phrase::getChannel(){
	return channel;
}

unsigned int Phrase::getSequential(){
	return sequential;
}

unsigned int Phrase::getSize(){
	return size;
}

unsigned int Phrase::getDate(){
	return date;
}