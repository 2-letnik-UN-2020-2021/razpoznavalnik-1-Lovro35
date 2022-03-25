//
// Created by Lovro on 17.3.2022..
//

#ifndef RAZPOZNAVALNIK_1_LOVRO35_TOKEN_H
#define RAZPOZNAVALNIK_1_LOVRO35_TOKEN_H

#include <iostream>
#include <string>

#pragma once
class Token
{
private:
    std::string lexem;
    int column;
    int row;
    int token;
    bool eof;

public:
    Token(const std::string aLexem, int aColumn, int aRow, int aToken, bool aEof) :lexem(aLexem), column(aColumn), row(aRow), token(aToken), eof(aEof) {}
    Token() : lexem("") {}

    const std::string getLexem() const {
        return lexem;
    }

    const int getRow() const {
        return row;
    }

    const int getColumn() const {
        return column;
    }

    const int getToken() const {
        return token;
    }

    const bool isEof() const {
        return eof;
    }

    friend std::ostream& operator<< (std::ostream& out, const Token& aToken) {
        out << aToken.getToken() << "('" << aToken.getLexem() << "')";
        return out;
    }

};

#endif //RAZPOZNAVALNIK_1_LOVRO35_TOKEN_H
