//
//  Predicate.cpp
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Predicate.h"

Predicate::Predicate( string data ) : info( data ) {}

void Predicate::setParameter( Parameter p )
{
    paramList.push_back( p );
}

void Predicate::setInfo( string s )
{
    info = s;
}

string Predicate::toString()
{
    ostringstream sb;
    sb << info << "(";
    
    return sb.str();
}

string Predicate::getPredicateInfo()
{
    return info;
}

vector<Parameter>& Predicate::getParamList()
{
    return paramList;
}