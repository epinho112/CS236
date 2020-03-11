//
//  Parameter.h
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab2__Parameter__
#define __lab2__Parameter__

#include "Token.h"

#include <sstream>

using namespace std;

class Parameter
{
public:
    Parameter( string, TokenType );
    ~Parameter() {};
    
    string toString();
    string getParameterInfo();
    
    TokenType getParameterType();
    
private:
    string info;
    TokenType type;
};

#endif /* defined(__lab2__Parameter__) */