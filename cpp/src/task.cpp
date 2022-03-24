//
// Created by Lovro on 17.3.2022..
//

// PrePJ_Naloga06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Scanner.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool E(Scanner*&, bool&);
bool T(Scanner*&, bool&);
bool EE(Scanner*&, bool&);
bool F(Scanner*&, bool&);
bool TT(Scanner*&, bool&);

int main(int args, char* argv[])
{
    ifstream* file = new ifstream();
    file->open(argv[1]);
    //file->open("FileAccept.txt");
    //file->open("FileReject.txt");
    //file->open("FileReject2.txt");

    Scanner* scanner = new Scanner(file);

    bool notError = true;
    scanner->nextToken();
    E(scanner, notError);

    if (scanner->currentToken().getToken() == -1 && notError)
        cout << "accept" << endl;
    else
        cout << "reject" << endl;

    return 0;
}

// -1 lexical error
// 1 float
// 2 variable
// 3 lparen
// 4 rparen
// 5 plus
// 6 minus
// 7 times
// 8 divide
// 9 power

bool TT(Scanner*& scanner, bool& notError) {
    cout << "CALLED TT " << scanner->currentToken().getToken() << endl;
    if (scanner->currentToken().getToken() == 7 || scanner->currentToken().getToken() == 8 || scanner->currentToken().getToken() == 9) { // * / ^
        cout << "\t '* / ^' " << endl;
        scanner->nextToken();
        notError = F(scanner, notError);
        notError = TT(scanner, notError);
    }
    return notError;
}

bool F(Scanner*& scanner, bool& notError) {
    cout << "CALLED F  " << scanner->currentToken().getToken() << endl;
    if (scanner->currentToken().getToken() == 3) { // (
        cout << "\t '(' " << endl;
        scanner->nextToken();
        notError = E(scanner, notError);
        if (scanner->currentToken().getToken() == 4) { // )
            cout << "\t ')' " << endl;
            scanner->nextToken();
        }
        else {
            cout << "Exit1" << endl;
            return false;
        }
    }
    else if (scanner->currentToken().getToken() == 1) { // float
        cout << "\t '0 .. 9' " << endl;
        scanner->nextToken();
    }
    else if (scanner->currentToken().getToken() == 2) { // variable
        cout << "\t 'a .. z' " << endl;
        scanner->nextToken();
    }
    else {
        cout << "Exit2" << endl;
        return false;
    }
    return notError;
}

bool EE(Scanner*& scanner, bool& notError) {
    cout << "CALLED EE " << scanner->currentToken().getToken() << endl;
    if (scanner->currentToken().getToken() == 5 || scanner->currentToken().getToken() == 6) { // + -
        cout << "\t '+ -' " << endl;
        scanner->nextToken();
        notError = T(scanner, notError);
        notError = EE(scanner, notError);
    }
    return notError;
}

bool T(Scanner*& scanner, bool& notError) {
    cout << "CALLED T  " << scanner->currentToken().getToken() << endl;
    notError = F(scanner, notError);
    notError = TT(scanner, notError);
    return notError;
}

bool E(Scanner*& scanner, bool& notError) {
    cout << "CALLED E  " << scanner->currentToken().getToken() << endl;
    notError = T(scanner, notError);
    notError = EE(scanner, notError);
    return notError;
}