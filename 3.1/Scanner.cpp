//
//  Scanner.cpp
//  lab01
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Scanner.h"

Scanner::Scanner()
{
    value = "";
    type = "";
    
    lineNumber = 1;
    currentTokenLineNumber = 0;
    
    ERROR = false;
}

void Scanner::comment( ifstream& file_in )
{
    char tokenRead = file_in.get();
    bool boolean = true;
    
    while ( boolean )
    {
        if ( tokenRead == '\n' || tokenRead == - 1 )
        {
            if ( tokenRead == '\n' )
            {
                lineNumber++;
            }
            boolean = false;
        }
        else
        {
            tokenRead = file_in.get();
        }
    }
}

void Scanner::error( int lineError, ofstream& file_out )
{
    if ( ERROR )
    {
        cout << "Input Error on line " << lineError << endl;
        storedTokens.clear();
    }
}

void Scanner::errorOccurred()
{
    ERROR = true;
    
    if ( currentTokenLineNumber == 0 )
    {
        currentTokenLineNumber = lineNumber;
    }
}

void Scanner::colon( char value, ifstream& in )
{
    string data;
    data += value;
    char tokenRead = in.peek();
    Token newToken;
    
    switch ( tokenRead )
    {
        case '-':
            tokenRead = in.get();
            data += tokenRead;
            newToken = Token( data, lineNumber, COLON_DASH );
            break;
            
        default:
            newToken = Token( data, lineNumber, COLON );
            break;
    }
    
    storedTokens.push_back( newToken );
}

void Scanner::iD( char value, ifstream& in )
{
    string data;
    data += value;
    bool boolean = true;
    
    while ( boolean )
    {
        value = in.get();
        
        if ( isalnum( value ) )
        {
            data += value;
        }
        else if ( isspace(value) )
        {
            special( data );
            data.clear();
            
            if ( value == '\n' )
            {
                lineNumber++;
            }
            
            boolean = false;
        }
        else if ( isToken( value ) )
        {
            special( data );
            data.clear();
            
            punctuation( value );
        }
        else if ( isQuoteColon( value, data, in ) )
        {
            data.clear();
        }
        else if ( value == -1 )
        {
            special( data );
            data.clear();
            boolean = false;
        }
        else
        {
            special( data );
            errorOccurred();
            boolean = false;
        }
    }
}

void Scanner::print( ofstream& file_out )
{
    string t = "";
    
    for ( size_t i = 0; i < storedTokens.size(); i++ )
    {
        t = TokenTypetoString( storedTokens.at(i).getTokenType() );
        
        cout << "(" << t << + ",\"" << storedTokens.at( i ).getTokensValue() << + "\","
        << storedTokens.at( i ).getTokenLineNumber() << + ")" << endl;
    }
    
    if ( !ERROR )
    {
        cout << "Total Tokens = " << storedTokens.size() << endl;
    }
    else
    {
        error( currentTokenLineNumber, file_out );
        storedTokens.clear();
    }
}

void Scanner::punctuation( char value )
{
    Token newToken;
    string info = "";
    info += value;
    
    switch ( value )
    {
        case ',':
            newToken = Token( info, lineNumber, COMMA );
            break;
            
        case '.':
            newToken = Token( info, lineNumber, PERIOD );
            break;
            
        case '?':
            newToken = Token( info, lineNumber, Q_MARK );
            break;
            
        case '(':
            newToken = Token( info, lineNumber, LEFT_PAREN );
            break;
            
        case ')':
            newToken = Token( info, lineNumber, RIGHT_PAREN );
            break;
            
        default:
            break;
    }
    
    storedTokens.push_back( newToken );
}

void Scanner::scan( ifstream& file_in )
{
    while ( !file_in.eof() )
    {
        char tokenRead = file_in.get();
        value += tokenRead;
        
        if ( value == "\n" )
        {
            lineNumber++;
            value.clear();
        }
        else if ( isPunctuation( tokenRead, file_in ) )
        {
            value.clear();
        }
        else if ( isalpha( tokenRead ) )
        {
            iD( tokenRead, file_in );
            value.clear();
        }
        else if ( isspace( tokenRead ) )
        {
            value.clear();
        }
        else if ( tokenRead == -1 )
        {
            value.clear();
            break;
        }
        else
        {
            errorOccurred();
            value.clear();
        }
    }
}

void Scanner::special( string data )
{
    if ( !ERROR )
    {
        if ( data == "Schemes" )
        {
            Token newToken( data, lineNumber, SCHEMES );
            storedTokens.push_back( newToken );
        }
        else if ( data == "Facts" )
        {
            Token newToken( data, lineNumber, FACTS );
            storedTokens.push_back( newToken );
        }
        else if ( data == "Rules" )
        {
            Token newToken( data, lineNumber, RULES );
            storedTokens.push_back( newToken );
        }
        else if ( data == "Queries" )
        {
            Token newToken( data, lineNumber, QUERIES );
            storedTokens.push_back( newToken );
        }
        else if ( isSpaceCharacter( data ) )
        {
        }
        else
        {
            Token newToken( data, lineNumber, ID );
            storedTokens.push_back( newToken );
        }
        
        data.clear();
    }
}

void Scanner::String( char value, ifstream& in )
{
    string data = "";
    data += value;
    char tokenRead;
    bool boolean = true;
    
    if ( data == "\'" )
    {
        data.clear();
    }
    
    while ( boolean )
    {
        tokenRead = in.get();
        
        switch ( tokenRead )
        {
            case '\'':
            {
                Token newToken( data, lineNumber, STRING );
                storedTokens.push_back( newToken );
                boolean = false;
                break;
            }
            case '\n':
            {
                errorOccurred();
                boolean = false;
                break;
            }
            case -1:
            {
                errorOccurred();
                boolean = false;
                break;
            }
            default:
                data += tokenRead;
        }
    }
}

bool Scanner::isPunctuation( char value, ifstream& file )
{
    string data;
    data += value;
    
    if ( isToken( value ) )
    {
        punctuation( value );
        data.clear();
        return true;
    }
    
    switch ( value )
    {
        case ':':
            colon( value, file );
            data.clear();
            return true;
            
        case '\'':
            String( value, file );
            data.clear();
            return true;
            
        case '#':
            comment( file );
            data.clear();
            return true;
            
        default:
            return false;
    }
}

bool Scanner::isQuoteColon( char value, string data, ifstream& in )
{
    switch ( value )
    {
        case '\'':
            special( data );
            data.clear();
            
            String( value, in );
            return true;
            
        case ':':
            special( data );
            data.clear();
            
            colon( value, in );
            return true;
            
        default:
            return false;
    }
}

bool Scanner::isSpaceCharacter( string data )
{
    if ( data == "\n" || data == "\t" || data == "" || data == " " )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Scanner::isToken( char data )
{
    switch ( data )
    {
        case ',':
            return true;
            
        case '.':
            return true;
            
        case '?':
            return true;
            
        case '(':
            return true;
            
        case ')':
            return true;
            
        default:
            return false;
    }
}

vector<Token>& Scanner::getTokenTypes()
{
    return storedTokens;
}