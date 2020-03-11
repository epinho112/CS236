//
//  Utils.cpp
//  lab01
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Utils.h"

string Utils::intToString( int t )
{
    ostringstream str;
    str << t;
    return str.str();
}

int Utils::stringToInt( string s )
{
    int i = atoi( s.c_str() );
    return i;
}