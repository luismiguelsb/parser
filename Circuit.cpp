#include "Circuit.h"
#include "Element.h"


void Circuit::readFile(ifstream &myFile, string fileName) {
char singleCharacter;
char firstLine[LIM];
Element Piece;
listNode nodeX;
int Parameter;


myElement.InitializeListNode();

myFile.open(fileName, ios::in); //Abre para leitura

myFile.getline(firstLine,LIM); //Le a primeira linha de comentarios e ignora

while (!myFile.eof()) { //Leitura até o fim do arquivo
myFile.get(singleCharacter); //Pega caracter por caracter

switch(singleCharacter){
case 'V': //Tensao
case 'v':
case 'I': //Corrente
case 'i':
case 'R': //Resistor
case 'r':
case 'C': //Capacitor
case 'c':
case 'L': //Indutor
case 'l':
case 'D': //Diodo
case 'd': Parameter = 4; break; //Parametro funciona pra indicar quantos campos cada componente tem
case 'Q': //TJB
case 'q':
case 'M': //MOSFET
case 'm': Parameter = 5; break;
case ' ':
case '\t': break;
case '\n': break;
case '.': break;
default: cout << "Formato invalido!\n";
}


if(singleCharacter != '.' && singleCharacter != '\n') { //Caracterer que serao ignorados
Piece = readLabel(myFile, singleCharacter, Parameter); //Realiza a tokenizacao

//cout << Piece.id << Piece.nodeA.c_str() << Piece.nodeB.c_str() << Piece.value.c_str();


if(!(myElement.checkFormat(Piece, Parameter))) //Checa o formato
cout << "Formato invalido!\n";
else {
//myElement.IdentifyComponent(Piece);

myElement.InsertList(Piece);

}
}
}

myElement.PrintList();

myFile.close();

}



Element Circuit::readLabel(ifstream &myFile, char singleCharacter, int Parameter) {
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


while(point != NULL){ //Coloca o label tokenizado no campo adequado
if(i == 0)
Piece.label = point;
if(i == 1)
Piece.nodeA = myElement.Mapping(point);
if(i == 2)
Piece.nodeB = myElement.Mapping(point);
if(i == 3)
Piece.value = myElement.MappingDouble(point);
if(i == 4)
Piece.nodeC = myElement.Mapping(point);
if(i == 5)
Piece.nodeD = myElement.Mapping(point);
if(i == 6)
Piece.value = myElement.MappingDouble(point);
i++;
point = strtok (NULL, " \t");
}

if (i != Parameter) { //Se o numero de parametros passado for diferente do esperado
Piece.id = '\0'; //Coloca o id com \0 para indicar erro
}

return Piece;

}