#include "../include/Matrix.h"

list<string> Group2Elements;
list<string> CurrentsInd;
list<string> CurrentsCap;

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
            cout << value;
            cout.unsetf(ios::scientific);

            if (id == 'C' || id == 'c' || id == 'L' || id == 'l')
                cout << " ; Iinicial: " << nodeC;
            cout << endl;
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

        else if (it->id == 'C' || it->id == 'C')
        { // Capacitor
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

            CurrentsCap.push_back(it->id + it->label);
        }
        else if (it->id == 'L' || it->id == 'l')
        { // Indutor
            if (it->nodeA != 0)
            {
                matrixH[it->nodeA - 1][lengthB + number - 1] += 1;
            }
            if (it->nodeB != 0)
            {
                matrixH[it->nodeB - 1][lengthB + number - 1] += -1;
            }

            matrixH[lengthB + number - 1][lengthB + number - 1] = 1;
            matrixB[lengthB + number - 1] += it->value;
            CurrentsInd.push_back(it->id + it->label);
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
            if (v == idlabel) //search till find it
                return cont;
            else
                cont++;
        }

    return 0;
}

// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void Matrix::getCofactor(vector<vector<double>> &temp, int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = matrixH[row][col];
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
int Matrix::determinant(vector<vector<double>> &A, int n)
{
    int D = 0; // Initialize result

    vector<vector<double>> temp(lengthH, vector<double>(lengthH)); // To store cofactors

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}

// Function to get adjoint of A[N][N] in adj[N][N].
void Matrix::adjoint(vector<vector<double>> &adj)
{
    // temp is used to store cofactors of A[][]
    int sign = 1;

    vector<vector<double>> temp(lengthH, vector<double>(lengthH));

    for (int i = 0; i < lengthH; i++)
    {
        for (int j = 0; j < lengthH; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(temp, i, j, lengthH);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign) * (determinant(temp, lengthH - 1));
        }
    }
}
/*
// Function to calculate and store inverse, returns false if
// matrix is singular
bool Matrix::inverse(vector<vector<double>> &inverse)
{
    // Find determinant of A[][]
    int det = determinant(matrixH, lengthH);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }

    // Find adjoint
    double adj[lengthH][lengthH];
    adjoint(adj);

    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i = 0; i < lengthH; i++)
        for (int j = 0; j < lengthH; j++)
            inverse[i][j] = adj[i][j] / float(det);

    return true;
}
*/
void Matrix::display(vector<vector<double>> matrix)
{
    for (int i = 0; i < lengthH; i++)
    {
        for (int j = 0; j < lengthH; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

vector<double> Matrix::multMatrix(vector<vector<double>> matrixA, vector<vector<double>> matrixB)
{
    vector<double> mult(lengthB);

    //matrixB = matrixH;

    // Multiplying matrix a and b and storing in array mult.
    for (int i = 0; i < lengthB; ++i)
        for (int j = 0; j < lengthB; ++j)
            for (int k = 0; k < lengthB; ++k)
            {
                mult[i] += matrixA[i][k] * matrixB[k][j];
            }

    return mult;
}

/*vector<double> Matrix::ForwardEuler(vector<double> x, double stop, double step)
{
    vector<double> matrixZ;

    for (int i = 1; i < (stop / step); i++)
    {
        //cout << i <<" "<< i*p->getTstep() <<" " << il << " " << vc << endl;
        std::list<string>::iterator it;
        std::list<Element>::iterator it2;

        double value;

        for (auto it = CurrentsCap.begin(); it != CurrentsCap.end(); ++it)
        {
            it2 = find(Group2Elements.begin(), Group2Elements.end(), it->c_str);
            int number = lookstring(it);
            matrixZ[lengthB + number - 1] = x[it2->nodeA - 1] + (step / it2->value) * x[lengthB + number - 1];
        }

        for (auto it = CurrentsInd.begin(); it != CurrentsInd.end(); ++it)
        {
            it2 = find(Group2Elements.begin(), Group2Elements.end(), it->c_str);
            int number = lookstring(it);
            matrixZ[lengthB + number - 1] = x[lengthB + number - 1] + (step / it2->value) * (x[it2->nodeA - 1] - x[it2->nodeB - 1]);
        }

        return matrixZ;
    }
}
*/