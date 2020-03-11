//
//  TokenType.cpp
//  lab01
//
//  Created by Erik Pinho.
//  Copyright (c) 2017 cs236. All rights reserved.
//

#include "TokenType.h"

string TokenTypetoString(int t)
{
    string type;
    
    switch (t)
    {
        case 0:  type = "COMMA";         return type;
        case 1:  type = "PERIOD";        return type;
        case 2:  type = "Q_MARK";        return type;
        case 3:  type = "LEFT_PAREN";    return type;
        case 4:  type = "RIGHT_PAREN";   return type;
        case 5:  type = "COLON";         return type;
        case 6:  type = "COLON_DASH";    return type;
        case 7:  type = "SCHEMES";       return type;
        case 8:  type = "FACTS";         return type;
        case 9:  type = "RULES";         return type;
        case 10: type = "QUERIES";       return type;
        case 11: type = "ID";            return type;
        case 12: type = "STRING";        return type;
        default: type = "NULL";          return type;
    }
}