/*
Program: separate_sign.cpp
ITEP-RN
Developed by Julio Freire
Supervised by Jossergio Gouveia <<<<<<< TO CHECK, PLEASE!
Last update: 13/05/2024
Version: 0.0.01

Describe:
This program find dates contained in IDR tables, that is located in the final of each block of date
of a Hikvision FileSystem, marked by OFNI8 signature. This can be useful to search slices of video 

or some fragments of data.
*/

#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

/*
Verify the call of the programa with the correct parameters, if not just terminate the program.
*/
void Usage (char* prog_name) {
	std::cerr << "Usage: " << prog_name <<": Must be use two arguments:"
	" <inputfile> <date>" << std::endl;
	std::cout << "To see the correct format of date, open the source code." std::endl;
	exit(0);
}

/*
As known that computer store a int value in a sequence and the processor read it in reverse and it
way to read is called little endian, so this function just read the mirror of a number in hex of 4bytes.

Argument:	string
Return:		string
*/
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

/*
How the binary of a file is read as hexadecimal, to search a possible timestamp through the hex
was necessary to convert 4 bytes of hexas to a int value in order to later convert it for readable
date.

Arguments:	string
Return:		time_t
*/
time_t hex_to_time(std::string hex_date) {
    // Convert hexadecimal string to integer
    std::istringstream iss(hex_date);
    unsigned long long int_value;
    iss >> std::hex >> int_value;

    // Convert integer to time_t
    time_t time_value = int_value;

    return time_value;
}

/*
In the struct tm the days of week is read as numbers from 0 to 6, which 0 is Sunday and 6 is Saturday.

Arguments:	string
Return:		int
*/
int convert_days_to_num(std::string wday){
	if ( wday == "dom" || wday == "Dom"){
		return 0;
	} else if (wday == "seg" || wday == "Seg"){
		return 1;
	} else if(wday == "ter" || wday == "Ter"){
		return 2;
	} else if(wday == "qua" || wday == "Qua"){
		return 3;
	}else if(wday == "qui" || wday == "Qui"){
		return 4;
	}else if(wday == "sex" || wday == "Sex"){
		return 5;
	} else return 6;

}

/*
To read the data is necessary to open as a pointer to char, so to do a better interpretation of 
the dates, it was converted to struct tm and processed.

Arguments:	string
Return:		tm
*/
tm convert_to_tm(std::string date){
	std::istringstream iss(date);
	std::tm date_tm{};
	string wday;
	int hour;

	iss >> date_tm.tm_mday;
	iss >> date_tm.tm_mon;
	iss >> date_tm.tm_year;
	iss >> wday;
	date_tm.tm_wday = convert_days_to_num(wday);
	iss >> hour;
	date_tm.tm_hour = hour-3;
	iss >> date_tm.tm_min;
	iss >> date_tm.tm_sec;

	return date_tm;
}

/*
Function that is used to show only the date passed by argument when the program is executed.

Arguments:	tm
			tm
Return:		bool
*/
bool compare_dates(tm date_to_compare, tm date){

	if (date_to_compare.tm_mday == date.tm_mday){

		if ((date_to_compare.tm_mon-1) == date.tm_mon){

			if ((date_to_compare.tm_year ) == date.tm_year + 1900){

				if (date_to_compare.tm_wday == date.tm_wday){

					if (date_to_compare.tm_hour == date.tm_hour){

						if (date_to_compare.tm_min == date.tm_min){

							if (date_to_compare.tm_sec == date.tm_sec) return true;

						}
					}
				}
			}
		}
	}
	return false;
}

/*
The main purpose of this program is search along the file possibles dates that can be useful to 
analysis and extract some slices.

Arguments:	<IDR_FILES>
			date in the following format: "day month year weekday hour minute seconds", in example:
			"18 03 2020 qua 18 28 46"
Return:		
*/
int main (int argc, char* args[]){

	if (argc != 3){
		Usage(args[0]);
	}

	// preparing args
	string inputfile_path = args[1];
	string date_to_compare = args[2];

	std::cout << date_to_compare << std::endl;

	tm date_to_compare_tm = convert_to_tm(date_to_compare);

	// 
	ifstream inputfile (inputfile_path);

	inputfile.seekg(0, inputfile.end);
	int length = inputfile.tellg();
	inputfile.seekg(0, inputfile.beg);

	std::cout << "The whole file has " << length << " characeters" << std::endl;
	std::cout << "The hours must be -3 what you digit!!!" << std::endl;

	//
	char* buffer1 = new char [length];
	char date[9];
	time_t chrono;
	tm time;
	int year, month, day, wday, hour, minute, second;
	
	inputfile.read(buffer1, length);

	if (inputfile.good()){
		int i = 0;
		int j = 0;
		while (i < length){
			memmove (date, buffer1+i, 8);
			
			if (date[7] == '\n'){
				i+=8;
				continue;
			}


			chrono = hex_to_time(read_little_endian(date));
			// cout << chrono << endl;
			if (chrono == 1229866575){

				j = 0;
			}
			time = *localtime(&chrono);

			year = time.tm_year + 1900;
			month = time.tm_mon;
			day = time.tm_mday;
			wday = time.tm_wday;
			hour = time.tm_hour;
			minute = time.tm_min;
			second = time.tm_sec;


			if (compare_dates(date_to_compare_tm, time)){

				std::cout << std::put_time(&time, "%c") << std::endl;
				std::cout << std::hex << i << std::endl;
				std::cout << "The time begins ";
				std::cout << std::dec << (j-2) << " bytes after the OFNI8." << std::endl;

			}

			// sleep(1);
			i++;
			j++;
		}
	}

	delete[] buffer1;
	inputfile.close();
	return 0;
}