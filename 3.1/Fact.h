//
//  Fact.h
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab2__Fact__
#define __lab2__Fact__

#include "Predicate.h"
#include "Parser.h"

class Fact
{
public:
    Fact( Predicate );
    ~Fact() {};
    
private:
    Predicate Pred;
};

#endif /* defined(__lab2__Fact__) */