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
    if (scanner->currentToken().getToken() == 7 || scanner->currentToken().getToken() == 8 || scanner->currentToken().getToken() == 9) { // * / ^
        scanner->nextToken();
        notError = F(scanner, notError);
        notError = TT(scanner, notError);
    }
    return notError;
}

bool F(Scanner*& scanner, bool& notError) {
    if (scanner->currentToken().getToken() == 3) { // (
        scanner->nextToken();
        notError = E(scanner, notError);
        if (scanner->currentToken().getToken() == 4) { // )
            scanner->nextToken();
        }
        else {
            return false;
        }
    }
    else if (scanner->currentToken().getToken() == 1) { // float
        scanner->nextToken();
    }
    else if (scanner->currentToken().getToken() == 2) { // variable
        scanner->nextToken();
    }
    else {
        return false;
    }
    return notError;
}

bool EE(Scanner*& scanner, bool& notError) {
    if (scanner->currentToken().getToken() == 5 || scanner->currentToken().getToken() == 6) { // + -
        scanner->nextToken();
        notError = T(scanner, notError);
        notError = EE(scanner, notError);
    }
    return notError;
}

bool T(Scanner*& scanner, bool& notError) {
    notError = F(scanner, notError);
    notError = TT(scanner, notError);
    return notError;
}

bool E(Scanner*& scanner, bool& notError) {
    notError = T(scanner, notError);
    notError = EE(scanner, notError);
    return notError;
}