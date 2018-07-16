#ifndef ELEMENT_H
#define ELEMENT_H

using namespace std ;

#include <iostream>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <list>
#include <string>


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
    string controlled;

public:
    void InsertList(Element, list <Element> &);
    void PrintList(list <Element> &);
    int Mapping(string);
    double MappingDouble(string);
    void InsertLabel(string);
    void InitializeListNode();
    int PrintListNode();
    void PrintMatrix();
    double getvalue();

};



#endif
