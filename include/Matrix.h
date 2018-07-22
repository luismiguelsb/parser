#ifndef MATRIX_H
#define MATRIX_H

using namespace std ;

#define N 15

#include <iostream>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <list>
#include <algorithm>
#include <string>
#include "Element.h"
#include <vector>



class Matrix{
public:
   	Matrix(); //Default constructor
	Matrix(int); //Main constructor
	void setVal(int, int, double); //Method to set the val of [i,j]th-entry
	void setValC(int, int, int, double);
	void printMatrixH(); //Method to display the matrix
	void printMatrixB(); //Method to display the matrix
	~Matrix(); //Destructor

private:
	static int lengthH;
	static int lengthB;
	double **matrixH;
	double *matrixB;
	//allocate the array
	void allocArray();

public:
    //funcoes
    static void PrintList(list <Element>);
    static void SetGroup2(list <Element>, int);
	static int getlengthH();
	static int getlengthB();
	void initMatrixH(list <Element>);
	void initMatrixB();
	int lookstring(string);
	void getCofactor(vector<vector<double>> &, int, int, int);
	int determinant(vector<vector<double>> &, int);
	void adjoint(vector<vector<double>> &);
	bool inverse(vector<vector<double>> &);
	void display(vector<vector<double>>);
	vector<double> multMatrix(vector<vector<double>>);


};



#endif
