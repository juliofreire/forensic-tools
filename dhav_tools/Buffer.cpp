#include "Buffer.h"

Buffer::Buffer() : length_buffer(10000)
{
	buffer_init = new char[length_buffer];
	buffer_end = buffer_init + length_buffer;
}

Buffer::~Buffer()
{
	delete[] buffer_init;
}