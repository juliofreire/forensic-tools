#ifndef BUFFER_H
#define BUFFER_H

class Buffer
{
public:

	int length_buffer;
	char* buffer_init = nullptr;
	char* buffer_end = nullptr;

// public:
	Buffer();
	~Buffer();
};

#endif