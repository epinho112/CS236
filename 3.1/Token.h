//
//  Token.h
//  lab01
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab01__Token__
#define __lab01__Token__

#include "TokenType.h"
#include <iostream>

using namespace std;

class Token
{
public:
    Token();
    ~Token() {};
    
    Token( string, int, TokenType );
    
    string getTokensValue();
    int getTokenLineNumber();
    TokenType getTokenType();
    
    void setTokensValue( string );
    void setTokenLineNumber( int );
    void setTokenType( TokenType );
    
private:
    string value;
    int lineNumber;
    TokenType tokenType;
};

#endif /* defined(__lab01__Token__) */