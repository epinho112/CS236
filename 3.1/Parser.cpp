//
//  Parser.cpp
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "Parser.h"

Token storedToken( "", 0, COMMA );

Parser::Parser()
{
    index = 0;
}

void Parser::advance()
{
    index++;
}

void Parser::fillsavedToken( vector<Token>& toParse )
{
    if( ( size_t )index < toParse.size() )
    {
        storedToken.setTokensValue( toParse.at( getIndex() ).getTokensValue() );
        storedToken.setTokenLineNumber( toParse.at( getIndex() ).getTokenLineNumber() );
        storedToken.setTokenType( toParse.at( getIndex() ).getTokenType() );
    }
    else
    {
        throw( storedToken );
    }
}

void Parser::match( TokenType t )
{
    if( t == storedToken.getTokenType() )
    {
        advance();
    }
    else
    {
        throw( storedToken );
    }
}

void Parser::parse( vector<Token>& toParse )
{
    fillsavedToken( toParse );
    match( SCHEMES );
    
    fillsavedToken( toParse );
    match( COLON );
    parseSchemeList( toParse );
    
    match( FACTS );
    
    fillsavedToken( toParse );
    match( COLON );
    fillsavedToken( toParse );
    parseFactList( toParse );
    
    match( RULES );
    
    fillsavedToken( toParse );
    match( COLON );
    fillsavedToken( toParse );
    parseRuleList( toParse );
    
    match( QUERIES );
    
    fillsavedToken( toParse );
    match( COLON );
    parseQueryList( toParse );
}

void Parser::parseFactList( vector<Token>& toParse )
{
    while( storedToken.getTokenType() != RULES )
    {
        match( ID );
        Predicate pred( storedToken.getTokensValue() );
        
        fillsavedToken( toParse );
        match( LEFT_PAREN );
        
        parseParamList( toParse, pred );
        
        match( RIGHT_PAREN );
        
        fillsavedToken( toParse );
        match( PERIOD );
        
        Facts.push_back( pred );
        
        fillsavedToken( toParse );
    }
}

void Parser::parseParamList( vector<Token>& toParse, Predicate& predicate )
{
    fillsavedToken( toParse );
    
    if( storedToken.getTokenType() == STRING )
    {
        match( STRING );
        Parameter param( storedToken.getTokensValue(), storedToken.getTokenType() );
        predicate.setParameter( param );
        Domain.insert( storedToken.getTokensValue() );
    }
    else
    {
        match( ID );
        Parameter param( storedToken.getTokensValue(), storedToken.getTokenType() );
        predicate.setParameter( param );
    }
    
    fillsavedToken( toParse );
    
    if( storedToken.getTokenType() == COMMA )
    {
        advance();
        parseParamList( toParse, predicate );
    }
}

void Parser::parsePredicateList( vector<Token>& toParse, Rule& rule )
{
    fillsavedToken( toParse );
    match( ID );
    Predicate pred( storedToken.getTokensValue() );
    
    fillsavedToken( toParse );
    match( LEFT_PAREN );
    
    parseParamList( toParse, pred );
    
    rule.addPredicate( pred );
    
    fillsavedToken( toParse );
    match( RIGHT_PAREN );
    
    fillsavedToken( toParse );
    
    if( storedToken.getTokenType() == COMMA )
    {
        advance();
        parsePredicateList( toParse, rule );
    }
}

void Parser::parseQueryList( vector<Token>& toParse )
{
    while( ( size_t )index < toParse.size() )
    {
        fillsavedToken( toParse );
        match( ID );
        Predicate pred( storedToken.getTokensValue() );
        
        fillsavedToken( toParse );
        match( LEFT_PAREN );
        
        parseParamList( toParse, pred ) ;
        
        match( RIGHT_PAREN );
        Queries.push_back( pred );
        
        fillsavedToken( toParse );
        match( Q_MARK );
        
        if( ( size_t )index < toParse.size() )
        {
            fillsavedToken( toParse );
        }
    }
}

void Parser::parseRuleList( vector<Token>& toParse )
{
    while( storedToken.getTokenType() != QUERIES )
    {
        match( ID );
        Predicate pred( storedToken.getTokensValue() );
        
        fillsavedToken( toParse );
        match( LEFT_PAREN );
        
        parseParamList( toParse, pred );
        
        match( RIGHT_PAREN );
        
        Rule rule( pred );
        
        fillsavedToken( toParse );
        match( COLON_DASH );
        
        parsePredicateList( toParse, rule );
        
        match( PERIOD );
        
        Rules.push_back( rule );
        
        fillsavedToken( toParse );
    }
}

void Parser::parseSchemeList( vector<Token>& toParse )
{
    while( storedToken.getTokenType() != FACTS )
    {
        fillsavedToken( toParse );
        match( ID );
        Predicate pred( storedToken.getTokensValue() );
        
        fillsavedToken( toParse );
        match( LEFT_PAREN );
        
        parseParamList( toParse, pred );
        
        match( RIGHT_PAREN );
        Schemes.push_back( pred );
        
        fillsavedToken( toParse );
    }
}

void Parser::print( ofstream& out )
{
    cout << "Success!" << endl;
    
    printSchemes( out );
    printFacts( out );
    printRules( out );
    printQueries( out );
    printDomain( out );
}

void Parser::printDomain( ofstream& out )
{
    cout << "Domain(" << Domain.size() << "):" << endl;
    
    for ( it = Domain.begin(); it != Domain.end(); it++ )
    {
        cout << "  \'" << *it << "\'" << endl;
    }
}

void Parser::printFacts( ofstream& out )
{
    cout << "Facts(" << Facts.size() << "):" << endl;
    
    for( size_t i = 0; i < Facts.size(); i++ )
    {
        cout << Facts.at( i ).toString();
        
        for( size_t j = 0; j < Facts.at( i ).getParamList().size(); j++ )
        {
            cout << Facts.at( i ).getParamList().at( j ).toString();
            
            if( j < ( Facts.at( i ).getParamList().size() - 1 ) )
            {
                cout << ",";
            }
        }
        cout << ")" << endl;
    }
}

void Parser::printQueries( ofstream& out )
{
    cout << "Queries(" << Queries.size() << "):" << endl;
    
    for( size_t i = 0; i < Queries.size(); i++ )
    {
        cout << Queries.at( i ).toString();
        
        for( size_t j = 0; j < Queries.at( i ).getParamList().size(); j++ )
        {
            cout << Queries.at( i ).getParamList().at( j ).toString();
            
            if( j < ( Queries.at( i ).getParamList().size() - 1 ) )
            {
                cout << ",";
            }
        }
        cout << ")" << endl;
    }
}

void Parser::printRules( ofstream& out )
{
    cout << "Rules(" << Rules.size() << "):" << endl;
    
    for( size_t i = 0; i < Rules.size(); i++ )
    {
        cout << "  " << Rules.at( i ).getPred().getPredicateInfo() << "(";
        
        for( size_t j = 0; j < Rules.at( i ).getPred().getParamList().size(); j++ )
        {
            cout << Rules.at( i ).getPred().getParamList().at( j ).toString();
            
            if( j < ( Rules.at( i ).getPred().getParamList().size() - 1 ) )
            {
                cout << ",";
            }
        }
        cout << ") :- ";
        
        for( size_t k = 0; k < Rules.at( i ).getpredList().size(); k++ )
        {
            cout << Rules.at( i ).getpredList().at( k ).getPredicateInfo() << "(";
            
            for( size_t z = 0; z < Rules.at( i ).getpredList().at( k ).getParamList().size(); z++ )
            {
                cout << Rules.at( i ).getpredList().at( k ).getParamList().at( z ).toString();
                
                if( z < ( Rules.at( i ).getpredList().at( k ).getParamList().size() - 1 ) )
                {
                    cout << ",";
                }
            }
            if( k < ( Rules.at( i ).getpredList().size() - 1 ) )
            {
                cout << "),";
            }
            else
            {
                cout << ")" << endl;
            }
        }
    }
}

void Parser::printSchemes( ofstream& out )
{
    cout << "Schemes(" << Schemes.size() << "):" << endl;
    
    for( size_t i = 0; i < Schemes.size(); i++ )
    {
        cout << Schemes.at( i ).toString();
        
        for( size_t j = 0; j < Schemes.at( i ).getParamList().size(); j++ )
        {
            cout << Schemes.at( i ).getParamList().at( j ).toString();
            
            if( j < ( Schemes.at( i ).getParamList().size() - 1 ) )
            {
                cout << ",";
            }
        }
        cout << ")" << endl;
    }
}

vector<Predicate>& Parser::getSchemes()
{
    return Schemes;
}

vector<Predicate>& Parser::getFacts()
{
    return Facts;
}

vector<Predicate>& Parser::getQueries()
{
    return Queries;
}

vector<Rule>& Parser::getRules()
{
    return Rules;
}

set<string>& Parser::getDomain()
{
    return Domain;
}

int Parser::getIndex()
{
    return index;
}