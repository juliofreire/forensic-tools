#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <iomanip>

using namespace std;

string toHex(char* buffer){
	ostringstream oss;
	for(int i = 0; i < 4; i++){
		oss << hex << setw(2) << setfill('0') << (int)(unsigned char)buffer[i];
	}
	return oss.str();
}
string read_little_endian(string hex){
	char tmp = hex[0];
	hex[0] = hex[6];
	hex[6] = tmp;

	tmp = hex[1];
	hex[1] = hex[7];
	hex[7] = tmp;

	tmp = hex[2];
	hex[2] = hex[4];
	hex[4] = tmp;

	tmp = hex[3];
	hex[3] = hex[5];
	hex[5] = tmp;

	return hex;
}

time_t hex_to_time(string hex_date) {
    // Convert hexadecimal string to integer
    istringstream iss(hex_date);
    unsigned long long int_value;
    iss >> hex >> int_value;

    // Convert integer to time_t
    time_t time_value = int_value;

    return time_value;
}

void writeHeader(ofstream &outputfile){

    outputfile << "Channel,";
    outputfile << "Date\n";

}

void writeDates(tm date, string channel, time_t chrono, ofstream &outputfile)
{
    outputfile << channel.back()       << ",";
    outputfile << date.tm_year+1900    << "-";
    outputfile << "0" << date.tm_mon+1 << "-";
    outputfile << date.tm_mday         << " ";
    outputfile << date.tm_hour+3       << ":";
    outputfile << date.tm_min          << ":";
    outputfile << date.tm_sec          << ",";
    outputfile << chrono << "\n";

}


int main(int argc, char* argv[])
{
    if (argc != 3) return 1;

    string inputfile_path(argv[1]);
    string outputfile_path(argv[2]);

    ifstream inputfile(inputfile_path, ifstream::binary);
    ofstream outputfile(outputfile_path, fstream::app);

    filesystem::path path(inputfile_path);
    filesystem::path channel_path = path.parent_path().filename();
    string channel = channel_path;

    cout << channel.back() << endl;

    if (!inputfile.good())
        cout << "Arquivo não conseguiu ser preparado para leitura." << endl;
    else cout << "Arquivo Ok" << endl;

    inputfile.seekg(0, inputfile.end);
    int length = inputfile.tellg();
    inputfile.seekg(0, inputfile.beg);

    char* buffer = new char [length];

    inputfile.read(buffer, length);

    string date;
    time_t chrono;
    tm time;

    cout << inputfile_path << endl;

    for (int i = 0; i < length; i+=28)
    {
        date = read_little_endian(toHex(buffer+i));
        chrono = hex_to_time(date);
        time = *localtime(&chrono);

        writeDates(time, channel, chrono, outputfile);
    }

    return 0;
}
