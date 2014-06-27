//
//  place.cpp
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include "place.h"
#include <initializer_list>
place::place(std::initializer_list<int> s):next(nullptr), pre(nullptr)
{
    memset(capacity, 0, sizeof(capacity));
    memset(nowcars, 0, sizeof(nowcars));
    for (int i = 0; i != 4; i++) {
        capacity[i] = *(s.begin() + i);
    }
}
bool place::push(token& t)
{
    contain.push(t);
    nowcars[t.getdirctions()][t.getturn()] += 1;
    return 1;
}
bool place::pop()
{
    if (contain.empty()) return 0;
    auto k = contain.front();
    nowcars[k.getdirctions()][k.getturn()] -= 1;
    
    contain.pop();
    return 1;
}
token& place::top()
{
    if (contain.empty()) throw 0;
    else return contain.front();
}
void place::setnext(transition* nex)
{
    next = nex;
}
void place::setattach(transition* nex)
{
    this->setnext(nex);
    this->next->setpre(this);
}
void place::setpre(transition* pre)
{
    this->pre = pre;
}
transition* place::getnext() const  
{
    return this->next;    
}
transition* place::getpre() const
{
    return this->pre;
}
void place::addcapacity(int num)
{
    this->capacity[num] = this->capacity[num] + 1;
}
bool place::subcapacity(int num)
{
    if (this->capacity[num] == 0) return 0;
    this->capacity[num] = this->capacity[num] - 1;
    return 1;
}
void place::addcars(int x, int y, int cars)
{
    for (auto i = 0; i != cars; i++) {
        this->push(*(new token(x, y)));
    }
}
void place::act()
{
    try {
        if (this->next != nullptr) {
            while (this->next->push(this->top()))
            {
                this->pop();
            }
        }
    }
    catch (int i){}
}
int place::getnowcars(int x,int y) const
{
    return nowcars[x][y];
}