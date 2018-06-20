#ifndef CIRCUIT_H
#define CIRCUIT_H

using namespace std ;


#include <iostream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include "Element.h"
#include <fstream>
#include <string>
#include <list>

const int LIM = 255;


class Circuit{
    Element myElement;
public:
    void readFile(ifstream&, string);
    Element readLabel(ifstream&, char, int);
};

#endif
