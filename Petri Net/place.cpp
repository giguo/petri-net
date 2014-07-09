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
    contain.push_back(t);
    nowcars[t.getdirctions()][t.getturn()] += 1;
    return 1;
}
bool place::pop(int i)
{
    if (i <= contain.size() - 1){
        auto k = contain[i];
        nowcars[k.getdirctions()][k.getturn()] -= 1;
        contain.erase(contain.begin() + i);
        return 1;
    }
    return 0;
}
token& place::top()
{
    if (contain.empty()) throw 0;
    else return *contain.begin();
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
void place::addcars(int x, int y, int cars)     //x表方向 y表转向 cars表个数
{
    for (auto i = 0; i != cars; i++) {
        this->push(*(new token(x, y)));
    }
}
void place::update_delay_time()
{
    for (auto beg = contain.begin(); beg != contain.end(); beg++) {
        (*beg).add_delay_time();
    }
}
void place::act()
{
    try {
        if (this->next != nullptr) {
            for (int i = 0; i != contain.size(); i++) {
                token* t = new token(contain[i]);
                if (this->next->push(*t)) {
                    this->pop(i);
                    --i;
                }
                else {
                    delete t;
                }
            }
        }
    }
    catch (int i){}
}
int place::getnowcars(int x,int y) const
{
    return nowcars[x][y];
}
float place::get_delay_time() const
{
    float tmp = 0.0;
    for (auto beg = contain.begin(); beg != contain.end(); beg++) {
        tmp += (*beg).get_delay_time();
    }
    return tmp;
}
int place::get_arrive_cars()const
{
    int k = 0;
    for (int i = 0; i != 4; i++) {
        for (int j = 0; j != 3; j++) {
            k += (this->getnowcars(i, j));
        }
    }
    return k;
}
