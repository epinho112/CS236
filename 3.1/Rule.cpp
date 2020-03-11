//
//  Rule.cpp
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Rule.h"

Rule::Rule(Predicate p) : Pred( p ) {}

void Rule::addPredicate( Predicate p )
{
    predList.push_back( p );
}

Predicate Rule::getPred()
{
    return Pred;
}

vector<Predicate>& Rule::getpredList()
{
    return predList;
}