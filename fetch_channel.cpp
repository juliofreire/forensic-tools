#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <unistd.h>
#include <vector>


using namespace std;

string binaryToHex(const char* buffer, int length){
	ostringstream oss;
	for(int i = 0; i < length; i++){
		oss << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer[i];
	}
	return oss.str();
}

string rangeInSeconds(const string date, int sizeRange){
	string substrdate = date.substr(0,2);
	string subsubstrdate = date.substr(2,2);

	ostringstream oss;
	int twoinit = stol(substrdate, 0, 16);
	int fourinit = stol(subsubstrdate, 0, 16);

	int all_number = (fourinit << 8) + twoinit;
	int new_number = all_number + sizeRange;
	oss << hex << setw(4) << setfill('0') << new_number << endl;

	substrdate = oss.str()[0];
	substrdate += oss.str()[1];

	subsubstrdate = oss.str()[2];
	subsubstrdate += oss.str()[3];

	subsubstrdate.append(substrdate.substr(0,2));
	subsubstrdate.append(date.substr(4,8));

	// cout << subsubstrdate << endl;

	return subsubstrdate;
}

string takeDates(const string& data, int length){
	string subdata;
	for (int i = 0; i<length-2; i+=9){
		subdata = data.substr(i,8);
		cout << subdata << endl;
	}
	return subdata;
}

vector<string> searchChannels(const string& date, const string& bufferHex, int length, int sizeRange){
	vector<string> vect{date, "NULL"};
	int index;
	bool found = false;
	int j = (sizeRange/2)*(-1);
	while(j <= sizeRange/2){
		string date_tmp = rangeInSeconds(date, j);
		for (int i = 0; i < 2*length; i++){
		string substr = bufferHex.substr(i, 8);
			if (memcmp(substr.c_str(), date_tmp.c_str(), 8) == 0){
				// cout << substr << endl;
				found = true;
				cout << "Find for date:" << date_tmp << endl;
				index = i;
				string channel;
				channel = bufferHex[index-22];
				channel += bufferHex[index-21];
				cout << "The channel is:";
				cout << channel << endl;
				// cout << bufferHex[index-22];
				// cout << bufferHex[index-21] << endl;
				vect[0] = date_tmp;
				vect[1] = channel;
				return vect;
				// break;
			}
		}
	if(found) break;
	j++;	
	}
	return vect;
}


int main (int argc, char* argv[]){

	string inputfile_path(argv[1]);
	string comparefile_path(argv[2]);

	ifstream inputfile(inputfile_path, ifstream::binary);
	ifstream comparefile(comparefile_path);
	ofstream outputfile("dates_ch.csv", fstream::app);
	
	if (inputfile.good()){
		if (comparefile.good()){
		} else{
			cout << "Could'nt read the comparefile" << endl;
			return 1;
		}
	} else {
		cout << "Could'nt read the inputfile" << endl;
		return 1;
	}

	inputfile.seekg(0, inputfile.end);
	int length1 = inputfile.tellg();
	inputfile.seekg(0, inputfile.beg);

	char* buffer1 = new char [length1];
	// char* buffer2 = new char [length1];
	inputfile.read(buffer1, length1);

	string bufferHex = binaryToHex(buffer1, length1);

	int sizeRange = 8;

	// int index;
	// searchChannels(date, bufferHex, length1, 8);

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
		vector<string> data_ch = {searchChannels(subdata, bufferHex, length1, 58)};
		outputfile << data_ch[0];
		outputfile << ", ";
		outputfile << data_ch[1];
		outputfile << "\n";

		cout << data_ch[0] << endl;
		cout << data_ch[1] << endl;
		// cout << subdata << endl;
	}
	

	return 0;

}