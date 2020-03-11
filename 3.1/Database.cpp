//
//  Database.cpp
//  lab03
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

////////////////////////////EvalParams()
#include "Database.h"

void Database::addRelation( Relation r )
{
	Relations.push_back( r );
	// cout << "Relation Size .... "<<Relations.size() << endl;
}

void Database::fill( vector<Predicate>& s,
                    vector<Predicate>& f,
                    vector<Predicate>& q )
{
	Schemes = s;
	Facts = f;
    Queries = q;
	size_t i = 0;
	size_t j = 0;
    
	while( i < Schemes.size() )
	{
		Relation r;
		r.setNameSchema( s, i );
        
		for( j = 0; j < Facts.size(); j++ )
		{
			// cout << "R.name ... " << r.name << endl;
			// cout << "Facts: ... " << Facts.at( j ).getPredicateInfo() << endl;
			if( r.name == Facts.at( j ).getPredicateInfo() )
			{
				r.setTuples( f, j );
			}
		}
        
		addRelation( r );
		i++;
	}
	evalQueries( Queries );
}

void Database::evalQueries( vector<Predicate>& q )
{
	size_t i = 0;
	Relation temp, relToAdd;
	
	cout << "Query size .. " << Queries.size() << endl;
	while( i < Queries.size() )
	{
		Relation r;
		r.setName( q, i );
        
		for( size_t j = 0; j < Relations.size(); j++ )
		{
			if( r.name == Relations.at( j ).name )
			{	
				temp = Relations.at( j );
			}
		}
        
		relToAdd = r.evalParams( q, i, temp );
		toPrint.push_back( relToAdd );
		i++;
	}
}

void Database::printResults( ofstream& out )
{
	vector<size_t> varIndex;
	vector<string> varInPrintQueue;
	bool toAdd = false;

	for( size_t i = 0; i < Queries.size(); i++ )
	{
		//It will print the id and first (
			//example: "bob("
		cout << Queries.at( i ).toString();
        
		printParams( varIndex,
                    varInPrintQueue,
                    toAdd,
                    i,
                    out );
        
		cout << ")? ";
        
		toPrint.at( i ).printRelation( i, out, varIndex );
		varIndex.clear();
		varInPrintQueue.clear();
	}
}

void Database::printParams( vector<size_t>& varIndex,
                           vector<string>& varInPrintQueue,
                           bool toAdd,
                           size_t i,
                           ofstream& out )
{
    
	for( size_t j = 0; j < Queries.at( i ).getParamList().size(); j++ )
	{
		cout << Queries.at( i ).getParamList().at( j ).toString();
        
		if( j < (Queries.at( i ).getParamList().size() - 1 ) )
		{
			cout << ",";
		}
        
		if( Queries.at( i ).getParamList().at( j ).getParameterType() == ID )
		{
			toAdd = true;
            
			if( varIndex.size() < 1 )
			{
				varIndex.push_back( j );
				varInPrintQueue.push_back( Queries.at( i ).getParamList().at( j ).getParameterInfo() );
			}
			else
			{
				for( size_t y = 0; y < varInPrintQueue.size(); y++ )
				{
					if( Queries.at( i ).getParamList().at( j ).getParameterInfo()
                       == varInPrintQueue.at( y ) )
					{
						toAdd = false;
						break;
					}
				}
				if( toAdd == true )
				{
					varIndex.push_back( j );
					varInPrintQueue.push_back( Queries.at( i ).getParamList().at( j ).getParameterInfo() );
				}
			}
		}
	}
}