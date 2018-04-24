#include <iostream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include "Circuit.h"
#include "Element.h"


using namespace std ;

void main(int argc, const char **argv) {

if(argc != 2){
    cout << "Missing parameter!" << endl; 
}
    else{
        ifstream myFile;

        Circuit myCircuit;
        myCircuit.readFile(myFile, argv[1]);
    }
}