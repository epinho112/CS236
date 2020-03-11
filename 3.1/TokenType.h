//
//  TokenType.h
//  lab01
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab01__TokenType__
#define __lab01__TokenType__

#include <string>

using namespace std;

enum TokenType
{
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    NUL
};

string TokenTypetoString( int t );

#endif /* defined(__lab01__TokenType__) */