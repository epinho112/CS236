//
//  Rule.h
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab2__Rule__
#define __lab2__Rule__

#include "Predicate.h"
#include "vector"

class Rule
{
public:
    Rule( Predicate );
    ~Rule() {};
    
    void addPredicate( Predicate );
    
    Predicate getPred();
    vector<Predicate>& getpredList();
    
private:
    Predicate Pred;
    vector<Predicate> predList;
};

#endif /* defined(__lab2__Rule__) */