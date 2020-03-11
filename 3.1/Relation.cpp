//
//  Relation.cpp
//  lab03
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Relation.h"

Relation Relation::evalParams( vector<Predicate>& q, size_t i, Relation source )
{
	size_t index = i;
	size_t j = 0;
    int duplicateIndex = 0;
	
    Relation twoRelations, threeRelations;
	
    vector<size_t> toPredict;
	vector<size_t> duplicateParams;
    vector<string> Predicted;
	vector<string> ids;
    
	bool toAdd;
    
	while( j < Queries.at( index ).getParamList().size() )
	{
		toAdd = true;
        
		if( Queries.at( index ).getParamList().at( j ).getParameterType() == STRING )
		{
			if( twoRelations.name == "" )
			{
				twoRelations = source.select( j,
                                             Queries.at( index ).getParamList().at( j ).getParameterInfo()
                                             );
				j++;
			}
			else
			{
				twoRelations = twoRelations.select( j,
                                                   Queries.at( index ).getParamList().at( j ).getParameterInfo()
                                                   );
				j++;
			}
		}
		else
		{
			evalParamID( source,
                        twoRelations,
                        index,
                        j,
                        duplicateIndex,
                        Predicted,
                        toPredict,
                        toAdd);
		}
	}
    
	if ( toPredict.size() > 0 )
	{
		if ( twoRelations.name == "" )
        {
			threeRelations = source.project( toPredict );
		}
		else
        {
			threeRelations = twoRelations.project( toPredict );
		}
		return threeRelations;
	}
	else
    {
		return twoRelations;
	}
}

Relation Relation::select( size_t index, string value )
{
	Relation r;
	r.name = name;
	r.scheme = scheme;
	set<Tuple>::iterator it;
    
	for( it = Tuples.begin(); it != Tuples.end(); it++ )
	{
		Tuple temp;
		temp = *it;
        
		if( temp.at( index ) == value )
		{
			r.Tuples.insert( temp );
		}
	}

	return r;
}

Relation Relation::select( size_t index1, size_t index2 )
{
	Relation r;
	r.name = name;
	r.scheme = scheme;
	set<Tuple>::iterator it;
    
	for( it = Tuples.begin(); it != Tuples.end(); it++ )
	{
		Tuple temp;
		temp = *it;
        
		if(temp.at( index1 ) == temp.at( index2 ) )
		{
			r.Tuples.insert( temp );
		}
	}
    
	return r;
}

Relation Relation::project( vector<size_t>& myIndicies )
{
	Relation r;
	r.name = name;
	r.scheme = scheme;
	set<Tuple>::iterator it;
	Tuple Predicted;
	size_t toPredict;
    
	for( it = Tuples.begin(); it != Tuples.end(); it++ )
	{
		Tuple temp;
		temp = *it;
        
		for( size_t i = 0; i < myIndicies.size(); i++ )
		{
			toPredict = myIndicies.at( i );
			Predicted.push_back( temp.at( toPredict ) );
		}
        
		r.Tuples.insert( Predicted );
		Predicted.clear();
	}
    
	return r;
}

void Relation::evalParamID( Relation& source,
                           Relation& twoRelations,
                           size_t& index,
                           size_t& j,
                           int duplicateIndex,
                           vector<string>& Predicted,
                           vector<size_t>& toPredict,
                           bool toAdd )
{
    
	source.rename( Queries.at( index ).getParamList().at( j ).getParameterInfo(), j );
    
	if ( twoRelations.name != "" )
    {
		twoRelations.rename( Queries.at( index ).getParamList().at( j ).getParameterInfo(), j );
	}
    
	duplicateIndex = checkForAnotherRelation(Queries.at( index ).getParamList().at( j ).getParameterInfo(),Queries.at( index ).getParamList(), j );
    
	if ( duplicateIndex != -1 )
    {
		checkForDuplicate( source,
                          twoRelations,
                          index,
                          j,
                          duplicateIndex,
                          Predicted,
                          toPredict,
                          toAdd );
	}
	else
    {
		for ( size_t y = 0; y < Predicted.size(); y++ )
        {
			if ( Queries.at( index ).getParamList().at( j ).getParameterInfo()
                == Predicted.at( y ) )
            {
				toAdd = false;
				break;
			}
		}
		if ( toAdd == true )
        {
			toPredict.push_back( j );
		}
		j++;
	}
}

void Relation::printRelation( size_t i, ofstream& out, vector<size_t>& varIndex )
{
	set<Tuple>::iterator it;
	vector<string> myAttributes = scheme.getSchemeAttributes();
    
	if( Tuples.size() < 1 )
	{
		cout << "No" << endl;
	}
	else
	{
		cout << "Yes(" << Tuples.size() << ")" << endl;
	}
    
	for( it = Tuples.begin(); it != Tuples.end(); it++ )
	{
		Tuple temp;
		temp = *it;
		temp.printTuple( out, myAttributes, varIndex );
	}
}

void Relation::rename( string s, size_t j )
{
	scheme.Attributes.at( j ) = s;
}

void Relation::setName( vector<Predicate>& q, size_t i )
{
	Queries = q;
	size_t index = i;
    
	name = Queries.at( index ).getPredicateInfo();
	// cout << Queries.at( index ).getPredicateInfo() << endl;
}

void Relation::setNameSchema( vector<Predicate>& s, size_t i )
{
	Schemes = s;
	size_t index = i;
	size_t j = 0;
	vector<string> schema;
    
	name = Schemes.at( index ).getPredicateInfo();
    
	while( j < Schemes.at( index ).getParamList().size() )
	{
		
		// cout << Schemes.at( index ).getParamList().at( j ).getParameterInfo()  << endl;
		scheme.Attributes.push_back( Schemes.at( index ).getParamList().at( j ).getParameterInfo() );
		j++;
	}

	// for (size_t w = 0; w < scheme.Attributes.size(); w++)
	// {
	// 	cout << "SCHEME.ATTRIBUTES: ... " << scheme.Attributes[w] << endl;
	// }
}

void Relation::setTuples( vector<Predicate>& facts, size_t i )
{
	Facts = facts;
	size_t index = i;
	size_t j = 0;
	Tuple t;
    
	while( j < Facts.at( index ).getParamList().size() )
	{
		t.push_back( Facts.at( index ).getParamList().at( j ).getParameterInfo() );
		
		j++;
	}
	Tuples.insert( t );
	
}

void Relation::checkForDuplicate( Relation& source,
                                 Relation& twoRelations,
                                 size_t& index,
                                 size_t& j,
                                 int duplicateIndex,
                                 vector<string>& Predicted,
                                 vector<size_t>& toPredict,
                                 bool toAdd )
{
    
	if ( twoRelations.name == "" )
    {
		twoRelations = source.select( j, duplicateIndex );
	}
    else
    {
		twoRelations = twoRelations.select( j, duplicateIndex );
	}
    
	for ( size_t y = 0; y < Predicted.size(); y++ )
    {
		if ( Queries.at( index ).getParamList().at( j ).getParameterInfo()
            == Predicted.at( y ) )
        {
			toAdd = false;
			break;
		}
	}
	if ( toAdd == true )
    {
		toPredict.push_back( j );
		Predicted.push_back( Queries.at( index ).getParamList().at( j ).getParameterInfo() );
	}
	j++;
}

size_t Relation::checkForAnotherRelation( string id, vector<Parameter> p, size_t j )
{
	int duplicateIndex = -1;
    
	if( j + 1 < p.size() )
	{
		for( size_t i = j + 1; i < p.size(); i++ )
		{
			if( duplicateIndex == -1 )
			{
				if( p.at( i ).getParameterInfo() == id )
				{
					duplicateIndex = i;
					break;
				}
			}
		}
	}
	else
	{
		duplicateIndex = -1;
	}
    
	return duplicateIndex;
}