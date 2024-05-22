#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <unistd.h>


using namespace std;

string binaryToHex(const char* buffer, int length){
	ostringstream oss;
	for(int i = 0; i < length; i++){
		oss << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer[i];
	}
	return oss.str();
}


int main (int argc, char* argv[]){

	string inputfile_path(argv[1]);
	string comparefile_path(argv[2]);

	ifstream inputfile(inputfile_path, ifstream::binary);
	ifstream comparefile(comparefile_path);
	// cout << inputfile.good();
	if (inputfile.good()){
		inputfile.seekg(0, inputfile.end);
		int length1 = inputfile.tellg();
		inputfile.seekg(0, inputfile.beg);

		char* buffer1 = new char [length1];
		char* buffer2 = new char [length1];
		inputfile.read(buffer1, length1);

		string bufferHex = binaryToHex(buffer1, length1);

		string date("5e68725e");
		int index;

		for (int i = 0; i < 2*length1; i++){
			string substr = bufferHex.substr(i, 8);
			if (memcmp(substr.c_str(), date.c_str(), 8) == 0){
				cout << substr;
				cout << "achou???";
				index = i;
				break;
			}
		}

		cout << bufferHex[index-22];
		cout << bufferHex[index-21];

	}

	if (comparefile.good()){
		comparefile.seekg(0, comparefile.end);
		int length2 = comparefile.tellg();
		comparefile.seekg(0, comparefile.beg);

		char* buffer2 = new char [length2];
		comparefile.read(buffer2, length2);

		string data(buffer2);
		cout << endl;
		cout << length2;
		cout << endl;
		for (int i = 0; i<length2-2; i+=9){
			string subdata = data.substr(i,8);
			cout << subdata << endl;
		}
	}

	return 0;

}