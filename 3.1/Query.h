//
//  Query.h
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab2__Query__
#define __lab2__Query__

#include "Predicate.h"

class Query
{
public:
    Query( Predicate );
    ~Query() {};
    
private:
    Predicate Pred;
};

#endif /* defined(__lab2__Query__) */