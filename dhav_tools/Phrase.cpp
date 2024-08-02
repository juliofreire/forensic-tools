#include "Phrase.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>


Phrase::Phrase(const char* init, int real_size)
{
	this->real_size = real_size;
	setAllInfo(init);

}

int Phrase::transformDate(unsigned int date, int bitLoc, int bitSize){
	int mask = pow(2, bitSize)-1;
	int tmp = date >> (32 - (bitLoc + bitSize)); 
	return tmp & mask;
}

void Phrase::setAllInfo(const char* buffer)
{
	/*
	channel = 6~7
	sequential = 8~11
	tamanhho = 12~15
	date = 16~19
	*/

	memcpy(&channel, buffer+6, 2);
	memcpy(&sequential, buffer+8, 4);
	memcpy(&size, buffer+12, 4);
	memcpy(&date, buffer+16, 4);
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

unsigned int Phrase::getYear(){
	return transformDate(date, 0, 6);
}
unsigned int Phrase::getMonth(){
	return transformDate(date, 6, 4);
}
unsigned int Phrase::getDay(){
	return transformDate(date, 10, 5);
}
unsigned int Phrase::getHour(){
	return transformDate(date, 15, 5);
}
unsigned int Phrase::getMinute(){
	return transformDate(date, 20, 6);
}
unsigned int Phrase::getSeconds(){
	return transformDate(date, 26, 6);
}