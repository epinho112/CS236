//
//  Token.cpp
//  lab01
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Token.h"

Token::Token()
{
    tokenType = NUL;
    lineNumber = 0;
    value = "";
}

Token::Token(string Data, int Line, TokenType Type) :
value( Data ), lineNumber( Line ), tokenType( Type ) {}

string Token::getTokensValue()
{
    return value;
}

int Token::getTokenLineNumber()
{
    return lineNumber;
}

TokenType Token::getTokenType()
{
    return tokenType;
}

void Token::setTokensValue( string v )
{
    value = v;
}

void Token::setTokenLineNumber( int n )
{
    lineNumber = n;
}

void Token::setTokenType( TokenType t )
{
    tokenType = t;
}