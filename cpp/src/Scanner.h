//
// Created by Lovro on 17.3.2022..
//

#ifndef RAZPOZNAVALNIK_1_LOVRO35_SCANNER_H
#define RAZPOZNAVALNIK_1_LOVRO35_SCANNER_H

#include "Token.h"

#pragma once
class Scanner
{
private:
    std::istream* input;
    Token lastToken;
    int row;
    int column;

    // table
    const static int maxState = 13;
    const static int startState = 0;
    const static int noEdge = -1;
    int automata[maxState + 1][256];
    int finite[maxState + 1];

    void initAutomata() {
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
        for (int i = 0; i <= maxState; i++)
            for (int j = 0; j < 256; j++)
                automata[i][j] = noEdge;

        for (int i = '0'; i <= '9'; i++) {
            automata[0][i] = automata[1][i] = 1;
            automata[2][i] = automata[3][i] = 3;
            automata[4][i] = automata[5][i] = 5;
        }
        for (int i = 'a'; i <= 'z'; i++)
            automata[0][i] = automata[4][i] = 4;
        for (int i = 'A'; i <= 'Z'; i++)
            automata[0][i] = automata[4][i] = 4;

        automata[0]['.'] = automata[1]['.'] = 2;
        automata[0]['('] = 6;
        automata[0][')'] = 7;
        automata[0]['+'] = 8;
        automata[0]['-'] = 9;
        automata[0]['*'] = 10;
        automata[0]['/'] = 11;
        automata[0]['^'] = 12;
        automata[0]['\n'] = automata[0][' '] = automata[0]['\t'] = 13;
        automata[13]['\n'] = automata[13][' '] = automata[13]['\t'] = 13;

        finite[0] = tLexError;
        finite[2] = tLexError;
        finite[1] = tFloat;
        finite[3] = tFloat;
        finite[4] = tVariable;
        finite[5] = tVariable;
        finite[6] = tPlus;
        finite[7] = tMinus;
        finite[8] = tTimes;
        finite[9] = tDivide;
        finite[10] = tPow;
        finite[11] = tIparen;
        finite[12] = tRparen;
        finite[13] = tIgnore;
    }

    int peek() {
        return input->peek();
    }

    int read() {
        int temp = input->get();
        column++;
        if (temp == '\n') {
            row++;
            column = 1;
        }
        return temp;
    }

    bool eof() {
        return peek() == -1;
    }

    Token nextTokenImp() {
        int currentState = startState;
        std::string lexem = "";
        int startColumn = column;
        int startRow = row;
        while (true)
        {
            int tempState = getNextState(currentState, peek());
            if (tempState != noEdge) {
                currentState = tempState;
                lexem += (char)read();
            }
            else {

                if (isFiniteState(currentState)) {
                    Token token(lexem, startColumn, startRow, getFiniteState(currentState), eof());
                    if (token.getToken() == tIgnore)
                        return nextToken();
                    else
                        return token;
                }
                else
                    return Token("", startColumn, startRow, tLexError, eof());
                lexem = "";
            }
        }
    }

protected:
    int getNextState(int aState, int aChar) const {
        if (aChar == -1)
            return noEdge;
        return automata[aState][aChar];
    }

    bool isFiniteState(int aState) const {
        return finite[aState] != tLexError;
    }

    int getFiniteState(int aState) const {
        return finite[aState];
    }

public:
    const static int tLexError = -1;
    const static int tIgnore = 0;
    const static int tFloat = 1;
    const static int tVariable = 2;
    const static int tPlus = 3;
    const static int tMinus = 4;
    const static int tTimes = 5;
    const static int tDivide = 6;
    const static int tPow = 7;
    const static int tIparen = 8;
    const static int tRparen = 9;

    Scanner(std::istream* aInput) {
        row = 1;
        column = 1;
        initAutomata();
        input = aInput;
    }

    Token nextToken() {
        return lastToken = nextTokenImp();
    }

    Token currentToken() {
        return lastToken;
    }
};

#endif //RAZPOZNAVALNIK_1_LOVRO35_SCANNER_H
