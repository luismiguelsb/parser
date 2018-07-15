#ifndef MATRIX_H
#define MATRIX_H

using namespace std ;

#include <iostream>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <list>
#include <algorithm>
#include <string>
#include "Element.h"



class Matrix{
public:
   	Matrix(); //Default constructor
	Matrix(int); //Main constructor
	void setVal(int, int, int); //Method to set the val of [i,j]th-entry
	void printMatrix(); //Method to display the matrix
	~Matrix(); //Destructor

private:
	static int length;
	int **p;

	//allocate the array
	void allocArray();

public:
    //funcoes
    static void PrintList(list <Element>);
    static int SetGroup2(list <Element>);
	static int getlength();
	static void initMatrix(list <Element>);
};



#endif
