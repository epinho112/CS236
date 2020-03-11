//
//  Tuple.h
//  lab03
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab03__Tuple__
#define __lab03__Tuple__

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Tuple : public vector<string>
{
public:
	Tuple() {};
	~Tuple() {};
    
	void printTuple( ofstream&, vector<string>&, vector<size_t>& );
};

#endif /* defined(__lab03__Tuple__) */