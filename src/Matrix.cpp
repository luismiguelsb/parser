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
void Matrix::printMatrixH()
{
    for (int i = 0; i < Matrix::lengthH; i++)
    {
        for (int j = 0; j < Matrix::lengthH; j++)
        {
            cout << "H(" << i << "," << j << ") = " << matrixH[i][j] << endl;
        }
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
            break;
        }
    }

    cout << "G2 members:" << endl;

    for (auto v : Group2Elements)
    {
        cout << v << endl;
        countH++;

    }

    lengthH = countH + numNodes;
    lengthB = numNodes;
}

//SetVal function
void Matrix::setVal(int m, int n, double value)
{
    if (m != 0)
        matrixH[m - 1][m - 1] += 1 / value;
    if (m != 0 && n != 0)
    {
        matrixH[m - 1][n - 1] += -1 / value;
        matrixH[n - 1][m - 1] += -1 / value;
    }
    if (n != 0)
        matrixH[n - 1][n - 1] += 1 / value;
}

void Matrix::setValC(int m, int n, int o, double value)
{
    if (m != 0)
    {
        matrixH[o - 1][m - 1] += 1;
        matrixH[m - 1][o - 1] += 1;
    }
    if (n != 0)
    {
        matrixH[o - 1][n - 1] += -1;
        matrixH[n - 1][o - 1] += -1;
    }
    matrixH[o - 1][o - 1] += value;
}

void Matrix::initMatrixH(list<Element> OriginalList)
{
    int number;

    std::list<Element>::iterator it;

    for (it = OriginalList.begin(); it != OriginalList.end(); it++)
    {
        if (it->id == 'R' || it->id == 'r')
        {
            number = lookstring(it->id + it->label);
            if (number == 0) // Não encontrou no G2 entao é G1
            {
                this->setVal(it->nodeA, it->nodeB, it->value);
            }
            else // se or G2
                this->setValC(it->nodeA, it->nodeB, lengthB + number, it->value);
        }
        else if (it->id == 'I' || it->id == 'i')
        {
            number = lookstring(it->id + it->label);
            if (number == 0) // Não encontrou no G2 entao é G1
            {
                if (it->nodeA != 0)
                    matrixB[it->nodeA - 1] += -it->value;
                if (it->nodeB != 0)
                    matrixB[it->nodeB - 1] += it->value;
            }
            else // se for G2
            {
                if (it->nodeA != 0)
                    matrixH[it->nodeA - 1][lengthB + number - 1] += 1;
                if (it->nodeB != 0)
                    matrixH[it->nodeB - 1][lengthB + number - 1] += -1;
                matrixH[lengthB + number - 1][lengthB + number - 1] += 1;
                matrixB[lengthB + number - 1] += it->value;
            }
        }
        else if (it->id == 'V' || it->id == 'v')
        {
            number = lookstring(it->id + it->label);
            if (it->nodeA != 0)
            {
                matrixH[it->nodeA - 1][lengthB + number - 1] += 1;
                matrixH[lengthB + number - 1][it->nodeA - 1] += 1;
            } 
            if (it->nodeB != 0)
            {
                matrixH[it->nodeB - 1][lengthB + number - 1] += -1;
                matrixH[lengthB + number - 1][it->nodeB - 1] += -1;
            }
            matrixB[lengthB + number - 1] += it->value;
        }
        else if (it->id == 'E' || it->id == 'e') //VCVS
        {
            number = lookstring(it->id + it->label);
            if (it->nodeA != 0)
            {
                matrixH[it->nodeA - 1][lengthB + number - 1] += 1;
                matrixH[lengthB + number - 1][it->nodeA - 1] += 1;
            }
            if (it->nodeB != 0)
            {
                matrixH[it->nodeB - 1][lengthB + number - 1] += -1;
                matrixH[lengthB + number - 1][it->nodeB - 1] += -1;
            }
            if (it->nodeC != 0)
            {
                matrixH[lengthB + number - 1][it->nodeC - 1] += -it->value;
            }
            if (it->nodeD != 0)
            {
                matrixH[lengthB + number - 1][it->nodeD - 1] += it->value;
            }
        }

        else if (it->id == 'H' || it->id == 'h') //CCVS
        {
            number = lookstring(it->id + it->label);
            if (it->nodeA != 0)
            {
                matrixH[it->nodeA - 1][lengthB + number - 1] += 1;
                matrixH[lengthB + number - 1][it->nodeA - 1] += 1;
            }
            if (it->nodeB != 0)
            {
                matrixH[it->nodeB - 1][lengthB + number - 1] += -1;
                matrixH[lengthB + number - 1][it->nodeB - 1] += -1;
            }

            int number2 = lookstring(it->controlled);
            matrixH[lengthB + number - 1][lengthB + number2 - 1] += it->value;
        }

        else if (it->id == 'F' || it->id == 'f') //CCCS
        {
            number = lookstring(it->controlled);
            if (it->nodeA != 0)
            {
                matrixH[it->nodeA - 1][lengthB + number - 1] += it->value;
            }
            if (it->nodeB != 0)
            {
                matrixH[it->nodeB - 1][lengthB + number - 1] += -it->value;
            }
        }

        else if (it->id == 'G' || it->id == 'g') //VCCS
        {
            number = lookstring(it->id + it->label);
            if (it->nodeA != 0)
            {
                if (it->nodeC != 0)
                matrixH[it->nodeA - 1][it->nodeC - 1] += it->value;
                if (it->nodeD != 0)
                matrixH[it->nodeA - 1][it->nodeD - 1] += -it->value;
            }
            if (it->nodeB != 0)
            {
                if (it->nodeC != 0)
                matrixH[it->nodeB - 1][it->nodeC - 1] += -it->value;
                if (it->nodeD != 0)
                matrixH[it->nodeB - 1][it->nodeD - 1] += it->value;
            }
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
    matrixB = new double[Matrix::lengthH];
    for (int i = 0; i < lengthH; i++)
    {
        matrixB[i] = 0;
    }
}

void Matrix::printMatrixB()
{
    for (int i = 0; i < lengthH; i++)
    {
        cout << "B(" << i << ") = " << matrixB[i] << endl;
    }
}

//returns 0 if string not found, return index if found
int Matrix::lookstring(string idlabel)
{
    int cont = 1;
    std::list<string>::iterator it;

    it = Group2Elements.begin();

    if (find(Group2Elements.begin(), Group2Elements.end(), idlabel) != Group2Elements.end())
        for (auto v : Group2Elements)
        {
            if (v == idlabel) //procura ate encontrar
                return cont;
            else
                cont++;
        }

    return 0;
}

void Matrix::inverse(int A[N][N], float inverse[N][N])
{
    // Find determinant of A[][]
    int det = determinant(A, N);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
    // Find adjoint
    int adj[N][N];
    adjoint(A, adj);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            inverse[i][j] = adj[i][j]/float(det);
 
    return true;
}