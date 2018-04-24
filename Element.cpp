
#include "Element.h"

list <listNode> Table;
list <Element> OriginalList;
int i=1;
int j = 1;



void Element::IdentifyComponent(Element Piece){

    cout << Piece.id;
    cout << Piece.label.c_str();
    cout << Piece.nodeA;
    cout << Piece.nodeB;
    cout << Piece.value;
}


int Element::checkFormat(Element Piece, int Parameter) {

    if(Piece.id == '\0') {
        return 0;
    }
    return 1;
}


void Element::InsertList(Element Piece) {

    OriginalList.push_back(Piece);
}

int Element::Mapping(string node) {

    if (!node.empty()){
        std::list<listNode>::iterator it;
        int found = 0;

        listNode nodeX;

        for (it = Table.begin(); it != Table.end(); it++) {
            char idNum = it->idNum;
            std::string label = it->label;

            nodeX.idNum = idNum;
            nodeX.label = label;

            if (label == node)
                found = 1;
        }

        //Se não encontrou insere na lista
        if (!found) {
            nodeX.idNum = i;
            i = i + 1;
            nodeX.label = node;
            //cout << "id: " << nodeX.idNum << " label: " << nodeX.label.c_str() << endl;
            Table.push_back(nodeX);
        }

        return i-1;
    }

}

double Element::MappingDouble(string value) {
    int k = 0;
    while(value[k] != '\0'){
     if (isdigit(value[k]))
         k++;

     else{
         switch (value[k]) {
             case 'f': return stod(value, NULL) * 0.000000000000001;
             case 'p': return stod(value, NULL) * 0.000000000001;
             case 'n': return stod(value, NULL) * 0.000000001;
             case 'u': return stod(value, NULL) * 0.000001;
             case 'm': if(value[k+1] == '\0')
                        return stod(value, NULL) * 0.001;
                        else if ((value[k+2] == 'e') && (value[k+3] == 'g'))
                            return stod(value, NULL) * 1000000;
                        else
                            return -1;

             case 'k': return stod(value, NULL) * 1000;
             case 'g': return stod(value, NULL) * 1000000000;
             case 't': return stod(value, NULL) * 1000000000000;
         }
         k++;
     }
    }

    return stod(value, NULL);

}

void Element::InitializeListNode() {
    listNode nodeX;

    nodeX.label = "Ground";
    nodeX.idNum = 0;

    Table.push_back(nodeX);
}

void Element::PrintList( ) {
    std::list<Element>::iterator it;

    for (it = OriginalList.begin(); it != OriginalList.end(); it++) {
        // Access the object through iterator
        char id = it->id;
        string label = it->label;
        int nodeA = it->nodeA;
        int nodeB = it->nodeB;
        int nodeC = it->nodeC;
        int nodeD = it->nodeD;
        double value = it->value;

        //Print the contents
        cout << "#" << j << ": ";
        switch (id){
            case 'V':
            case 'v': cout << (char) toupper(id) << "SR[" << label.c_str() << "] ; "; break;
            case 'I':
            case 'i': cout << (char) toupper(id) << "SR[" << label.c_str() << "] ; "; break;
            case 'R':
            case 'r': cout << (char) toupper(id) << "ES[" << label.c_str() << "] ; "; break;
            case 'g':
            case 'G': cout << "VCCS[" << label.c_str() << "] ; "; break;
            case 'e':
            case 'E': cout << "VCVS[" << label.c_str() << "] ; "; break;
            case 'f':
            case 'F': cout << "CCCS[" << label.c_str() << "] ; "; break;
            case 'h':
            case 'H': cout << "CCVS[" << label.c_str() << "] ; "; break;
            default: cout << "Formato nao reconhecido!" << endl;

        }
        cout << "n+[" << nodeA << "],  n-[" << nodeB << "]; ";
        if(nodeC != -1)
            cout << "nx+[" << nodeC << "]; ";
        if(nodeD != -1)
            cout << "nx-[" << nodeD << "]; ";


        cout << "value =  ";
        cout.setf(ios::scientific);
        cout << value<< endl;
        cout.unsetf(ios::scientific);
        j++;

    }

}

void Element::PrintListNode( ) {
listNode myNodes;
std::list<listNode>::iterator it;
for (it = Table.begin(); it != Table.end(); it++) {
char idNum = it->idNum;
std::string label = it->label;

myNodes.idNum = idNum;
myNodes.label = label;

cout << "ID: " << myNodes.idNum << " Label: " << myNodes.label.c_str() << endl;
}

}
