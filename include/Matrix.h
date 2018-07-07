#ifndef MATRIX_H
#define MATRIX_H

using namespace std ;

#include <iostream>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <list>
#include <string>
#include "Element.h"



class Matrix{
public:
   //atributos

public:
    //funcoes
    void PrintMatrix(list <Element>);
    void SetGroup2(list <Element>);
};



#endif
