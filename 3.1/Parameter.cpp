//
//  Parameter.cpp
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Parameter.h"

Parameter::Parameter( string data, TokenType t ) : info( data ), type( t ) {}

string Parameter::toString()
{
    ostringstream sb;
    
    if( type == STRING )
    {
        sb << "\'" << info << "\'";
    }
    else
    {
        sb << info;
    }
    
    return sb.str();
}

string Parameter::getParameterInfo()
{
    return info;
}

TokenType Parameter::getParameterType()
{
    return type;
}