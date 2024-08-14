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

        Arqout(string);
        ~Arqout();
        void WriteOn(Phrase*);
        bool checkName(string);
        string addDateToName(string);
};

#endif