#include "../include/Matrix.h"

list<string> Group2Elements;

//Default constructor
Matrix::Matrix()
{
}

int Matrix::lengthH;
int Matrix::lengthB;

//Main construcor
Matrix::Matrix(int m)
{
    allocArray();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrixH[i][j] = 0;
        }
    }
}

//destructor
Matrix::~Matrix()
{
    for (int i = 0; i < Matrix::lengthH; i++)
    {
        delete[] matrixH[i];
    }
    delete[] matrixH;
    delete[] matrixB;
}

void Matrix::allocArray()
{
    matrixH = new double *[Matrix::lengthH];
    for (int i = 0; i < Matrix::lengthH; i++)
    {
        matrixH[i] = new double[Matrix::lengthH];
    }
}

//printMatrix function
void Matrix::printMatrix()
{
    for (int i = 0; i < Matrix::lengthH; i++)
    {
        for (int j = 0; j < Matrix::lengthH; j++)
        {
            cout << matrixH[i][j] << "\t";
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

void Matrix::SetGroup2(list<Element> OriginalList, int numNodes)
{
    int countH = 0;

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
            countH++;
            break;
        }
    }

    cout << "G2 members:" << endl;

    for (auto v : Group2Elements)
    {
        cout << v << endl;
    }

    lengthH = countH + numNodes;
    lengthB = numNodes;
}

//SetVal function
void Matrix::setVal(int m, int n, double value)
{
    if (m != 0)
        matrixH[m-1][m-1] += 1/value;
    if (m != 0 && n != 0)
    {
        matrixH[m-1][n-1] += -1/value;
        matrixH[n-1][m-1] += -1/value;
    }
    if (n != 0)
        matrixH[n-1][n-1] += 1/value;
}

void Matrix::setValC(int m, int n, int o, double value)
{
    if (m != 0)
    {
        matrixH[o-1][m-1] += 1;
        matrixH[m-1][o-1] += 1;
    }
    if (n != 0)
    {
        matrixH[o-1][n-1] += -1;
        matrixH[n-1][o-1] += -1;
    }
    matrixH[o-1][o-1] += value;
}

void Matrix::initMatrixH(list<Element> OriginalList)
{
    int number;

    std::list<Element>::iterator it;

    for (it = OriginalList.begin(); it != OriginalList.end(); it++)
    {
        if (it->id == 'R')
        {
            number = lookstring(it->id + it->label);
            if (number == 0) // Não encontrou no G2 entao é G1
            {
                this->setVal(it->nodeA, it->nodeB, it->value);
            }
            else // se or G2
                this->setValC(it->nodeA, it->nodeB, lengthB + number, it->value);
        }
    }
}

int Matrix::getlengthH()
{
    return lengthH;
}

int Matrix::getlengthB()
{
    return lengthB;
}

void Matrix::initMatrixB()
{
    matrixB = new double *[Matrix::lengthH];
    for (int i = 0; i < lengthH; i++)
    {
        matrixB[i] = 0;
    }

    cout << "Matrix B:" << endl;
    for (int i = 0; i < lengthH; i++)
    {
        cout << matrixB[i] << endl;
    }
}

//returns 0 if string not found, return index if found
int Matrix::lookstring(string idlabel)
{
    int cont = 0;
    std::list<string>::iterator it;

    it = Group2Elements.begin();

    if (find(Group2Elements.begin(), Group2Elements.end(), idlabel) != Group2Elements.end())
        for (auto v : Group2Elements)
        {
            if (v.front() == ('R') || v.front() == ('r') && v == idlabel) //procura ate encontrar
                break;
            else
                cont++;
        }

    return cont;
}