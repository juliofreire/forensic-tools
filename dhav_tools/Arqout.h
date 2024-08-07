#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include "Phrase.h"

using namespace std;

class Arqout{

    private:

        Phrase* phrase = nullptr;
        ofstream output;

    public:

        Arqout(Phrase*);
        ~Arqout();

};

#endif