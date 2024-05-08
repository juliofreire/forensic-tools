/*
Program: separate_sign.cpp
ITEP-RN
Developed by Julio Freire
Supervised by Jossergio Gouveia <<<<<<< TO CHECK, PLEASE!
Last update: 03/05/2024
Version: 0.0.02

Describe:
This code find a sign of stream video file, in specific OFNI8, and get the string between
them. Through these string can search some informations about the file, like date, channel
and offset address where it's locate in partition that can be useful in a investigative case.

*/

#include <iostream> // (cout, setw, fill)
#include <fstream> // (seekg, tellg, read, good, close)
#include <cstring> // used to check matchs of values in address (memchr)
#include <iomanip> // used to convert in hex (hex)
#include <unistd.h>
#include <filesystem> // used to get filename (path, filename)


/*
Verify the call of the programa with the correct parameters, if not just terminate the program.
*/
void Usage (char* prog_name) {
	std::cerr << "Usage: " << prog_name <<": Must be use two arguments:"
	" <inputfile> <output_directory>" << std::endl;
	exit(0);
}


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

bool directory_existence(const std::filesystem::path& path){
	if (std::filesystem::exists(path)) return true;
	else return false;
}


std::string create_file_with_index(std::string path, std::string filename){
	int i = 1;
	std::string outputfilename = filename + std::to_string(i) + ".csv";
	std::string fullname = path + "/" + outputfilename;
	while(directory_existence(fullname)){
		i++;
		outputfilename = filename + std::to_string(i) + ".csv";
		fullname = path + "/" + outputfilename;
	}
	std::cout << "The outfile exists and it was saved was a index " << i << " at final" << std::endl;
	return fullname;
}


// TODO: VERIFY IF IS BETTER USE RETURN ON MAIN OR EXIT(0) IN FUNCTION
/*
This function just check the arguments of int main is a regular file and a existent directory, 
if it is not ok terminate the program.
Arguments	: string input
			  string output
*/
void check_args (std::string input, std::string output){

	if (directory_existence(input)){
		std::cout << "The file that will be read exists and the program will proceed with the"
					 " execution." << std::endl;
	} else {
		std::cout << "The file does not exist, please check the the path." << std::endl;
		exit(0);
	}

	if (directory_existence(output)){
		std::cout << "The directory to store the csv files exists" << std::endl;
	} else {
		std::cout << "The directory to store the csv files does not exist, please check it or create"
					 " before run the program." << std::endl;
		exit(0);
	}
}


/*
This main aim of this function is separate in lines of csv file the content between two sign, 
in especific OFNI8 sign. Although all the management to inputfiles and output files it's include 
therefore the user must concern with the arguments that was explict in case of error.

Arguments 	: <input_file>
			  <output_directory>
Returns		: Csv files
*/
int main (int argc, char *args[]){

	if (argc != 3){
		Usage(args[0]);
	}

	// Set variables to files from read and write
	std::string inputfile_path = args[1];
	std::string outputfile_path = args[2];

	check_args(inputfile_path, outputfile_path);

	std::filesystem::path in_path (inputfile_path);


	std::string filename = in_path.filename();
	std::cout << "Opening the file " << filename << std::endl;

	// Define a ifstream type and a binary file
	std::ifstream inputfile (inputfile_path, std::ifstream::binary);



	std::string outputfilename = filename + ".csv";


	std::string full_outputfile_path = outputfile_path+ "/" + outputfilename;



	if (!directory_existence(full_outputfile_path)){
		std::cout << "The output file does not exist." << std::endl;
	} else {
		full_outputfile_path = create_file_with_index(outputfile_path, filename);
	}

	std::ofstream outputfile (full_outputfile_path);// (outputfile_path);


	if (inputfile.good()){
		if (outputfile.good()){
		} else{
			std::cout << "Could'nt read the outfile " << filename << std::endl;
			inputfile.close();
			return 1;
		}
	} else {
		std::cout << "Could'nt read the inputfile " << filename + ".csv" << std::endl;
		return 1;
	}

	std::cout << "Reading the file " << filename << std::endl;

	// Get lenght of the inputfile
	inputfile.seekg(0, inputfile.end);
	int length = inputfile.tellg();
	inputfile.seekg(0, inputfile.beg);

	std::cout << "The whole file has " << length << " characeters" << std::endl;

	// Create a buffer to allocate the file in memory
	char *buffer1 = new char [length]; // The existence
	char *buffer2 = buffer1;
	char *buffer_end = buffer1+length-1;

	int buffer_size;

	// Allocate in memory of buffer1
	inputfile.read(buffer1, length);


	if (inputfile.good()) {
		buffer2 = next_string(buffer2, buffer_end);
		char *c = buffer2;
		while (c < buffer_end) {

			c = next_string(c+1, buffer_end);
			// This check seems redundant however without this check occurs a segmentation fault
			if (c == nullptr) break;

			// Block of code that takes the length of phrases and copies it to a file
			buffer_size = c - buffer2;
			for (int i = 0; i < buffer_size; i++){
				outputfile << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)buffer2[i];
			}
			outputfile << "\n";
			buffer2 = c;

			/*/ code for tests
			outputfile.flush();
			sleep(1);
			/*/
		}

	}

	delete[] buffer1;

	inputfile.close();
	outputfile.close();

	return 0;
}