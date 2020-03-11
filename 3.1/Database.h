//
//  Database.h
//  lab03
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab03__Database__
#define __lab03__Database__

#include "Relation.h"
#include "Predicate.h"

using namespace std;

class Database
{
public:
	Database() {};
	~Database() {};
    
	vector<Relation> Relations, toPrint;
    
	vector<Predicate> Schemes;
	vector<Predicate> Facts;
	vector<Predicate> Queries;
    
	void addRelation( Relation );
    
	void fill( vector<Predicate>&, vector<Predicate>&, vector<Predicate>& );
    
	void evalQueries( vector<Predicate>& );
    
	void printResults( ofstream& );
	void printParams( vector<size_t>&,
                     vector<string>&,
                     bool,
                     size_t,
                     ofstream& );
    
};

#endif /* defined(__lab03__Database__) */