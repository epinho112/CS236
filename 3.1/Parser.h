//
//  Parser.h
//  lab2
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#ifndef __lab2__Parser__
#define __lab2__Parser__

#include "Token.h"
#include "Predicate.h"
#include "Rule.h"
#include "Fact.h"
#include "Query.h"
#include "Scanner.h"

#include <set>

class Parser
{
public:
    Parser();
    ~Parser() {};
    
    void advance();
    void fillsavedToken( vector<Token> & );
    void match( TokenType );
    void parse( vector<Token> & );
    void parseFactList( vector<Token> & );
    void parseParamList( vector<Token> &, Predicate & );
    void parsePredicateList( vector<Token> &, Rule & );
    void parseQueryList( vector<Token> & );
    void parseRuleList( vector<Token> & );
    void parseSchemeList( vector<Token> & );
    void print( ofstream & );
    void printDomain( ofstream & );
    void printFacts( ofstream & );
    void printQueries( ofstream & );
    void printRules( ofstream & );
    void printSchemes( ofstream & );
    
    vector<Predicate>& getSchemes();
    vector<Predicate>& getFacts();
    vector<Predicate>& getQueries();
    vector<Rule>& getRules();
    
    set<string>& getDomain();
    
    int getIndex();
    
private:
    vector<Predicate> Schemes;
    vector<Predicate> Facts;
    vector<Rule> Rules;
    vector<Predicate> Queries;
    
    set<string> Domain;
    set<string>::iterator it;
    
    int index;
};


#endif /* defined(__lab2__Parser__) */