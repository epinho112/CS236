//
//  Scheme.h
//  lab03
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab03__Scheme__
#define __lab03__Scheme__

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Scheme
{
public:
	Scheme() {};
	~Scheme() {};
    
    void setSchemeAttributes( vector<string>& );
    
	vector<string>& getSchemeAttributes();
    vector<string> Attributes;
};

#endif /* defined(__lab03__Scheme__) */
