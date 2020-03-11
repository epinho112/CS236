//
//  Relation.h
//  lab03
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab03__Relation__
#define __lab03__Relation__

#include "Scheme.h"
#include "Tuple.h"
#include "Predicate.h"

#include <set>

using namespace std;

class Relation
{
public:
	Relation() {};
	~Relation() {};
    
    Relation evalParams( vector<Predicate>&, size_t, Relation );
	Relation select( size_t, string );
	Relation select( size_t, size_t );
	Relation project( vector<size_t>& );
    
    void evalParamID( Relation&,
                     Relation&,
                     size_t&,
                     size_t&,
                     int,
                     vector<string>&,
                     vector<size_t>&,
                     bool
                     );
    void printRelation( size_t, ofstream&, vector<size_t>& );
	void rename( string, size_t );
    void setName( vector<Predicate>&, size_t );
	void setNameSchema( vector<Predicate>&, size_t );
    void setTuples( vector<Predicate>&, size_t );
	void checkForDuplicate( Relation&,
                           Relation&,
                           size_t&,
                           size_t&,
                           int,
                           vector<string>&,
                           vector<size_t>&,
                           bool
                           );
    
	size_t checkForAnotherRelation( string, vector<Parameter>, size_t );
    
    string name;
    
private:
    Scheme scheme;
	
    set<Tuple> Tuples;
    
	vector<Predicate> Schemes;
	vector<Predicate> Facts;
	vector<Predicate> Queries;
};

#endif /* defined(__lab03__Relation__) */