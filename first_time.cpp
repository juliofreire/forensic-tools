#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

/*
This function finds the address of the first occurrence of the string 'OFNI8' within the memory block 
starting from the address pointed by first argument. It searches until the end of the memory block 
indicated by the address pointed pass as the second argument.

Arguments	: *char
			  *char
Return Type	: *char
*/
char* next_string(char* buffer_actual, char* buffer_end) {
	int length_search = buffer_end - buffer_actual;
	while (buffer_actual < buffer_end) {
		buffer_actual = (char*) memchr (buffer_actual, 'O', length_search);
		if (buffer_actual == nullptr) break;
		bool cf = (buffer_actual + 1) < buffer_end ? *(buffer_actual + 1) == 'F': false;
		bool cn = (buffer_actual + 2) < buffer_end ? *(buffer_actual + 2) == 'N': false;
		bool ci = (buffer_actual + 3) < buffer_end ? *(buffer_actual + 3) == 'I': false;
		bool c8 = (buffer_actual + 4) < buffer_end ? *(buffer_actual + 4) == '8': false;
		bool match_ofni8 = cf && cn && ci && c8;
		if (match_ofni8) break;
		buffer_actual++;
		length_search = buffer_end - buffer_actual;
	}
		return buffer_actual;

}


int main(int argc, char* argv[]){

	string inputfile_path(argv[1]);
	string outputfile_path(argv[2]);

	cout << outputfile_path+"/dates.csv" << endl;

	ifstream inputfile(inputfile_path, ifstream::binary);
	ofstream outputfile(outputfile_path+"/dates.csv", fstream::app);

	if(inputfile.good()){
		inputfile.seekg(0, inputfile.end);
		int length = inputfile.tellg();
		inputfile.seekg(0, inputfile.beg);

		char* buffer = new char [length];
		char* buffer1 = buffer;
		char* buffer_end = buffer+length-1;

		inputfile.read(buffer, length);

		cout << inputfile.good() << endl;

		int buffer_size;
	
		buffer1 = next_string(buffer1, buffer_end);

		char *c = buffer1;
		while(c != nullptr){
			buffer1 = c;
			c = next_string(c+1, buffer_end);
		}
		
		buffer_size = buffer1-c;
		cout << buffer_size << endl;

		for (int i = 24; i < 28; i++){
			outputfile << std::hex << std::setw(2) << setfill('0') << (int)(unsigned char)buffer1[i];
		}
		outputfile << "\n";

		delete[] buffer;
	}	

}