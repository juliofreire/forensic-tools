#ifndef ARQOUT_H
#define ARQOUT_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include "Phrase.h"

using namespace std;

class Arqout
{

    private:

        Phrase* phrase = nullptr;
        ofstream output;

    public:

        
	    //================ Constr e Destr =========
        Arqout(string);
        ~Arqout();

	    //================ Utilities ==============
        bool checkName(string); // it's unecessary
        string addDateToName(string);

	    //================ Actions ================
        void WriteOn(Phrase*);
};

#endif