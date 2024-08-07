#include "Arqout.h"

using namespace std;

Arqout::Arqout(Phrase* phrase){
    output = ofstream("saida.txt", fstream::app);
}

Arqout::~Arqout(){
    
}