//
//  Tuple.cpp
//  lab03
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Tuple.h"

void Tuple::printTuple( ofstream& out,
                       vector<string>& Attributes,
                       vector<size_t>& Index )
{
	if( Index.size() > 0 )
	{
		if( Index.size() < 2 )
		{
			for( size_t i = 0; i < size(); i++ )
			{
				cout << "  " << Attributes.at( Index.at(i) )
                << "='" << at( i ) << "'" << endl;
			}
		}
		else
		{
			for( size_t i = 0; i < size(); i++ )
			{
				if( i < size() - 1 )
				{
                    switch ( i )
                    {
                        case 0:
                            cout << "  " << Attributes.at( Index.at( i ) )
                            << "='" << at( i ) << "', ";
                            break;
                        
                        default:
                            cout << Attributes.at( Index.at( i ) )
                            << "='" << at( i ) << "', ";
                            break;
                    }
				}
				else
				{
                    switch ( i )
                    {
                        case 0:
                            cout << Attributes.at( Index.at( i ) )
                            << "='" << at( i ) << "'";
                            break;
                            
                        default:
                            cout << Attributes.at( Index.at( i ) )
                            << "='" << at( i ) << "'" << endl;
                            break;
                    }
				}
			}
		}
	}
}