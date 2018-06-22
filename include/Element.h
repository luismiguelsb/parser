#ifndef ELEMENT_H
#define ELEMENT_H

using namespace std ;

#include <iostream>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <list>
#include <string>
#include "Matrix.h"


typedef struct {
    int idNum;
    string label;
}listNode;


class Element{
public:
    char id;
    string label;
    int nodeA;
    int nodeB;
    int nodeC;
    int nodeD;
    double value;

public:
    void InsertList(Element);
    void PrintList();
    int Mapping(string);
    double MappingDouble(string);
    void InsertLabel(string);
    void InitializeListNode();
    void PrintListNode();
    void PrintMatrix();
    void MatrixHandler();

};



#endif
