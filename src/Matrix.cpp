#include "../include/Matrix.h"

list <string> Group2Elements;

//Default constructor
Matrix::Matrix()
{
}

int Matrix::length;

//Main construcor
Matrix::Matrix(int m)
{
    allocArray();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            p[i][j] = 0;
        }
    }
}

//destructor
Matrix::~Matrix()
{
    for (int i = 0; i < Matrix::length; i++)
    {
        delete[] p[i];
    }
    delete[] p;
}

void Matrix::allocArray()
{
    p = new int *[Matrix::length];
    for (int i = 0; i < Matrix::length; i++)
    {
        p[i] = new int[Matrix::length];
    }
}

//SetVal function
void Matrix::setVal(int m, int n, int value)
{
    p[m][n] = value;
}

//printMatrix function
void Matrix::printMatrix()
{
    for (int i = 0; i < Matrix::length; i++)
    {
        for (int j = 0; j < Matrix::length; j++)
        {
            cout << p[i][j] << "\t";
        }

        cout << endl;
    }
}

void Matrix::PrintList(list<Element> OriginalList)
{

    int ok = 1;
    int i = 1;
    int j = 0;

    std::list<Element>::iterator it;

    for (it = OriginalList.begin(); it != OriginalList.end(); it++)
    {
        // Access the object through iterator
        char id = it->id;
        string label = it->label;
        int nodeA = it->nodeA;
        int nodeB = it->nodeB;
        int nodeC = it->nodeC;
        int nodeD = it->nodeD;
        double value = it->value;
        string controlled = it->controlled;

        //Print the contents
        cout << "#" << j << ": ";
        switch (id)
        {
        case 'V':
        case 'v':
            cout << (char)toupper(id) << "SR[" << label.c_str() << "] ; ";
            break;
        case 'I':
        case 'i':
            cout << (char)toupper(id) << "SR[" << label.c_str() << "] ; ";
            break;
        case 'R':
        case 'r':
            cout << (char)toupper(id) << "ES[" << label.c_str() << "] ; ";
            break;
        case 'g':
        case 'G':
            cout << "VCCS[" << label.c_str() << "] ; ";
            break;
        case 'e':
        case 'E':
            cout << "VCVS[" << label.c_str() << "] ; ";
            break;
        case 'f':
        case 'F':
            cout << "CCCS[" << label.c_str() << "] ; ";
            break;
        case 'h':
        case 'H':
            cout << "CCVS[" << label.c_str() << "] ; ";
            break;
        case 'c':
        case 'C':
            cout << "CAP[" << label.c_str() << "] ; ";
            break;
        case 'l':
        case 'L':
            cout << "IND[" << label.c_str() << "] ; ";
            break;
        case 'd':
        case 'D':
            cout << "DIO[" << label.c_str() << "] ; ";
            break;
        case 'q':
        case 'Q':
            cout << "TJB[" << label.c_str() << "] ; ";
            break;
        case 'm':
        case 'M':
            cout << "MOS[" << label.c_str() << "] ; ";
            break;
        default:
            cout << "Formato invalido:" << id << endl;
            ok = 0;
            break;
        }
        if (ok == 1)
        {
            cout << "n+[" << nodeA << "],  n-[" << nodeB << "]; ";
            if (nodeC != -1)
                cout << "nx+[" << nodeC << "]; ";
            if (nodeD != -1)
                cout << "nx-[" << nodeD << "]; ";
            if (id == 'H' || id == 'h' || id == 'f' || id == 'F')
                cout << "Elem: " << controlled << " ; ";

            cout << "value =  ";
            cout.setf(ios::scientific);
            cout << value << endl;
            cout.unsetf(ios::scientific);
        }
        j++;
        ok = 1;
    }
}

int Matrix::SetGroup2(list<Element> OriginalList)
{
    int ok = 1;
    int i = 1;
    int j = 0;
    string aux;

    std::list<Element>::iterator it;

    for (it = OriginalList.begin(); it != OriginalList.end(); it++)
    {

        switch (it->id)
        {
        case 'V':
        case 'v':
        case 'g':
        case 'G':
        case 'e':
        case 'E':
            Group2Elements.push_back(it->id + it->label);
            break;
        case 'f':
        case 'F':
        case 'h':
        case 'H':
            Group2Elements.push_back(it->id + it->label);
            Group2Elements.push_back(it->controlled);
            break;
        }
    }

    cout << "G2 members:" << endl;

    for (auto v : Group2Elements)
    {
        cout << v << endl;
        j++;
    }

    length = j;

    return j;
}

void Matrix::initMatrix(list<Element> OriginalList)
{

    std::list<Element>::iterator it;

    for (it = OriginalList.begin(); it != OriginalList.end(); it++)
    {
        // Access the object through iterator
        char id = it->id;
        string label = it->label;
        int nodeA = it->nodeA;
        int nodeB = it->nodeB;
        int nodeC = it->nodeC;
        int nodeD = it->nodeD;
        double value = it->value;
        string controlled = it->controlled;
 
        if(it->id == 'R'){
            if(find(Group2Elements.begin(), Group2Elements.end(), id+label) != Group2Elements.end())
            {
                //setVal(nodeA, nodeB, value);
            }
        }
    }
}

int Matrix::getlength()
{
    return length;
}