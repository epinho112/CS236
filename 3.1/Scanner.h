//
//  Scanner.h
//  lab01
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab01__Scanner__
#define __lab01__Scanner__

#include "Token.h"
#include "Utils.h"

#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

class Scanner
{
public:
    Scanner();
    ~Scanner() {};
    
    void comment( ifstream& );
    void error( int, ofstream& );
    void errorOccurred();
    void colon( char, ifstream& );
    void iD( char, ifstream& );
    void special( string );
    void String( char, ifstream& );
    void print( ofstream& );
    void punctuation( char );
    void scan( ifstream & );
    
    bool isPunctuation( char, ifstream& );
    bool isQuoteColon( char, string, ifstream& );
    bool isSpaceCharacter( string );
    bool isToken( char );
    
    vector<Token>& getTokenTypes();
    
private:
    string value;
    string type;
    
    int lineNumber;
    int currentTokenLineNumber;
    
    vector<Token> storedTokens;
    
    bool ERROR;
};

#endif /* defined(__lab01__Scanner__) */