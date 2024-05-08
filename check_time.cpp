#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

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

time_t hex_to_time(std::string hex_date) {
    // Convert hexadecimal string to integer
    std::istringstream iss(hex_date);
    unsigned long long int_value;
    iss >> std::hex >> int_value;

    // Convert integer to time_t
    time_t time_value = int_value;

    return time_value;
}

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

bool compare_dates(tm date_to_compare, tm date){
	// bool match = false;
	if (date_to_compare.tm_mday == date.tm_mday){
		// cout << "ok";
		if ((date_to_compare.tm_mon-1) == date.tm_mon){
			// cout << "ok";
			if ((date_to_compare.tm_year ) == date.tm_year + 1900){
				// match = true;
				if (date_to_compare.tm_wday == date.tm_wday){
					// cout << "ok";
					if (date_to_compare.tm_hour == date.tm_hour){
						// cout << "ok";
						if (date_to_compare.tm_min == date.tm_min){
							// cout << "ok";
							if (date_to_compare.tm_sec == date.tm_sec){
								// cout << "ok";
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

int main (int argc, char* args[]){

	// preparing args
	string inputfile_path = args[1];
	string date_to_compare = args[2];

	cout << date_to_compare << endl;

	tm date_to_compare_tm = convert_to_tm(date_to_compare);

	// 
	ifstream inputfile (inputfile_path);

	inputfile.seekg(0, inputfile.end);
	int length = inputfile.tellg();
	inputfile.seekg(0, inputfile.beg);

	std::cout << "The whole file has " << length << " characeters" << std::endl;

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

			// cout << date << endl;
			// cout << "BE:" << endl;
			// cout << date << endl;
			// cout << "LE:" << endl;
			// read_little_endian(date);
			// cout << read_little_endian(date) << endl;
			// cout << "readable date:" << endl;
			chrono = hex_to_time(read_little_endian(date));
			// cout << chrono << endl;
			if (chrono == 1229866575){
				// cout << date << endl;
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

			// cout << year << endl;
			// cout << year << month << day << wday << hour << minute << second << endl;

			// cout << date_to_compare_tm.tm_year << endl;
			// cout << date_to_compare_tm.tm_mon << endl;
			// cout << date_to_compare_tm.tm_mday << endl;
			// cout << date_to_compare_tm.tm_wday << endl;
			// cout << date_to_compare_tm.tm_hour << endl;
			// cout << date_to_compare_tm.tm_min << endl;
			// cout << date_to_compare_tm.tm_sec << endl;


			// cout << endl;

			// cout << j;

			if (compare_dates(date_to_compare_tm, time)){
				// cout << " okoko ";
				// cout << std::hex << i;
				cout << std::put_time(&time, "%c") << endl;
				cout << std::hex << i << endl;
				cout << "The time begins ";
				cout << std::dec << (j-2) << " bytes after the OFNI8." << endl;

			}

			// cout << std::put_time(&time, "%c") << endl;
			// cout << std::hex << i << endl;

			// cout << ctime(&chrono);
			// cout << "year: ";
			// cout << year+1900;
			// cout << "day: ";
			// cout << day;
			// cout << &buffer1 << endl;
			// cout << *buffer1;
			// sleep(1);
			i++;
			j++;
		}
	}

	delete[] buffer1;
	inputfile.close();
	return 0;
}