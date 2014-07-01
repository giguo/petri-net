//
//  token.cpp
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include "token.h"
token::token(int d, int t):directions(d),turn(t){}
token::token(const token& t):directions(t.directions),turn(t.turn){}
int token::getdirctions() const
{
    return directions;
}
int token::getturn() const
{
    return turn;
}
void token::setdirections(int d)
{
    this->directions = d;
}
void token::setturn(int t)
{
    this->turn = t;
}