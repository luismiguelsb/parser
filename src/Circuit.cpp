#include "../include/Circuit.h"
#include "../include/Element.h"

void Circuit::readFile(ifstream &myFile, string fileName)
{
    char singleCharacter;
    char firstLine[LIM];
    list<Element> OriginalList;
    Element Piece;
    listNode nodeX;
    int Parameter;
    int numNodes;

    myElement.InitializeListNode();
    myFile.open(fileName, ios::in);

    if (myFile.is_open())
    { //Abre para leitura

        myFile.getline(firstLine, LIM); //Le a primeira linha de comentarios e ignora

        while (!myFile.eof())
        {                                //Leitura até o fim do arquivo
            myFile.get(singleCharacter); //Pega caracter por caracter

            switch (singleCharacter)
            {
            case 'V': //Tensao
            case 'v':
            case 'I': //Corrente
            case 'i':
            case 'R': //Resistor
            case 'r':
            case 'L': //Indutor
            case 'l':
            case 'D': //Diodo
            case 'd':
                Parameter = 4;
                break; //Parametro funciona pra indicar quantos campos cada componente tem
            case 'C': //Capacitor
            case 'c':
            case 'Q':  //TJB
            case 'q':
            case 'M': //MOSFET
            case 'm':
                Parameter = 5;
                break;
            case 'f':
            case 'F':
            case 'h':
            case 'H':
                Parameter = 7;
                break;
            case 'g':
            case 'G':
            case 'e':
            case 'E':
                Parameter = 6;
                break;
            case ' ':
            case '\t':
                break;
            case '\n':
                break;
            case '.':
            case '*':
                myFile.getline(firstLine, LIM);
                break;
            default:
                cout << "Formato invalido!\n";
            }

            if (singleCharacter != '.' && singleCharacter != '\n' && singleCharacter != '*')
            {                                                          //Caracterer que serao ignorados
                Piece = readLabel(myFile, singleCharacter, Parameter); //Realiza a tokenizacao

                myElement.InsertList(Piece, OriginalList);
            }
        }

        Matrix::PrintList(OriginalList);

        numNodes = myElement.PrintListNode();

        Matrix::SetGroup2(OriginalList, numNodes);

        Matrix myMatrix(Matrix::getlengthH());

        myMatrix.initMatrixB();
        myMatrix.initMatrixH(OriginalList);

        cout << endl
             << "Matrix H:" << endl;
        myMatrix.printMatrixH();

        cout << endl
             << "Matrix B:" << endl;
        myMatrix.printMatrixB();

        int l = Matrix::getlengthH();

        vector<vector<double>> inv(l, vector<double>(l)); // To store inverse of A[][]
 
        //cout << "\nThe Inverse is :\n";
        //myMatrix.inverse(inv);
        //myMatrix.display(inv);

        //vector<double> Result;
        //MNA = myMatrix.multMatrix(inv);
        //myMatrix.display(Resut);

        myFile.close();
    }
    else
        cout << "Error opening the file" << endl;
}

Element Circuit::readLabel(ifstream &myFile, char singleCharacter, int Parameter)
{
    char label[LIM];
    char *point;
    int i = 0;
    Element Piece;

    Piece.id = singleCharacter;

    myFile.getline(label, LIM);

    point = strtok(label, " \t");

    Piece.nodeA = -1;
    Piece.nodeB = -1;
    Piece.nodeC = -1;
    Piece.nodeD = -1;
    Piece.value = -1;

    while (point != NULL)
    { //Coloca o label tokenizado no campo adequado
        if (i == 0)
            Piece.label = point;
        if (i == 1)
            Piece.nodeA = myElement.Mapping(point);
        if (i == 2)
            Piece.nodeB = myElement.Mapping(point);
        if (i == 3)
        {
            if (Parameter == 4)
                Piece.value = myElement.MappingDouble(point);
            if (Parameter == 5 || Parameter == 6)
                Piece.nodeC = myElement.Mapping(point);
            if (Parameter == 7)
                Piece.controlled = point;
        }
        if (i == 4)
        {
            if (Parameter == 5)
                Piece.value = myElement.MappingDouble(point);
            if (Parameter == 6)
                Piece.nodeD = myElement.Mapping(point);
            if (Parameter == 7)
            {
                Piece.value = myElement.MappingDouble(point);
                i = i + 2;
            }
        }
        if (i == 5)
            Piece.value = myElement.MappingDouble(point);
        i++;
        point = strtok(NULL, " \t");
    }

    if (i != Parameter)
    {                    //Se o numero de parametros passado for diferente do esperado
        Piece.id = '\0'; //Coloca o id com \0 para indicar erro
        cout << "I: " << i << "Parameter: " << Parameter << endl;
    }

    return Piece;
}