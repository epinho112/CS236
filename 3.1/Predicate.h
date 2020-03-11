//
//  Predicate.h
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab2__Predicate__
#define __lab2__Predicate__

#include "Parameter.h"
#include "vector"

using namespace std;

class Predicate
{
public:
    Predicate() {};
    Predicate( string );
    ~Predicate() {};
    
    void setParameter( Parameter );
    void setInfo( string );
    
    string toString();
    
    string getPredicateInfo();
    vector<Parameter>& getParamList();
    
private:
    string info;
    vector<Parameter> paramList;
};

#endif /* defined(__lab2__Predicate__) */