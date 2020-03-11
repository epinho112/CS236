//
//  main.cpp
//  lab3
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Predicate.h"
#include "Database.h"
#include "Relation.h"
#include "Parameter.h"


int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out;
    // in.open( argv[1] );
    // out.open( argv[2] );
    
    string file_name[1] = {"in30.txt"};
    for (int i = 0; i < 1; i++)
{
    in.close();
    in.open(file_name[i]);
    Scanner scanner;
    scanner.scan( in );
    
    try
    {
        vector<Token>& storedTokens = scanner.getTokenTypes();
        Parser parser;
        
        parser.parse( storedTokens );
        
        vector<Predicate>& Schemes = parser.getSchemes();
		vector<Predicate>& Facts = parser.getFacts();
        vector<Predicate>& Queries = parser.getQueries();
        
		Database database;
        database.fill( Schemes, Facts, Queries );
        Relation r;
        string value = "c";
        size_t index = 1;
        // database.printResults( out );
        
        // void Relation::rename( string s, size_t j )
        // Relation Relation::select( size_t index, string value )
        
        r.select(index, value);
        database.printResults( out );
    }
    catch( Token e )
    {
        out << "Failure!" << endl;
        string tokenType;
        
        switch( e.getTokenType() )
        {
            case 0: tokenType = "COMMA";           break;
            case 1: tokenType = "PERIOD";          break;
            case 2: tokenType = "Q_MARK";          break;
            case 3: tokenType = "LEFT_PAREN";      break;
            case 4: tokenType = "RIGHT_PAREN";     break;
            case 5: tokenType = "COLON";           break;
            case 6: tokenType = "COLON_DASH";      break;
            case 7: tokenType = "SCHEMES";         break;
            case 8: tokenType = "FACTS";           break;
            case 9: tokenType = "RULES";           break;
            case 10: tokenType = "QUERIES";        break;
            case 11: tokenType = "ID";             break;
            case 12: tokenType = "STRING";         break;
            default: tokenType = "NULL";           break;
        }
        
        out << "  (" << tokenType << ",\"" << e.getTokensValue() << "\","
        << e.getTokenLineNumber() << ")" << endl;
    }
}
    
    return 0;
}