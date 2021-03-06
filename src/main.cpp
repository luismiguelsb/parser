#include <iostream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include "../include/Circuit.h"
#include "../include/Element.h"
#include "../include/Matrix.h"


using namespace std ;

int main(int argc, const char **argv) {

if(argc != 2){
    cout << "Missing parameter!" << endl; 
}
    else{
        ifstream myFile;

        Circuit myCircuit;
        myCircuit.readFile(myFile, argv[1]);
    }

    return 0;
}