//
//  Scheme.cpp
//  lab03
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Scheme.h"

void Scheme::setSchemeAttributes( vector<string>& s )
{
	Attributes = s;
}

vector<string>& Scheme::getSchemeAttributes()
{
	return Attributes;
}