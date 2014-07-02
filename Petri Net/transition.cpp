//
//  transition.cpp
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//
#include "place.h"
#include "transition.h"
#include <initializer_list>
Light transition::l;

transition::transition(std::initializer_list<float> i,bool is): next(nullptr), pre(nullptr), nextnum(0), iscross(is)
{
    for (int num = 0; num != i.size(); num++) {
        time[num] = *(i.begin() + num);
    }
}
bool transition::pop(int i)
{
    if (i <= contain.size() - 1 && contain[i].second >= time[contain[i].first.getdirctions()]){
        contain.erase(contain.begin() + i);
        return 1;
    }
    return 0;
}
bool transition::push(token& t)
{
    if (iscross == 1) {
        if (!l.canrun(t)) {
            return 0;
        }
    }
    if (this->next != nullptr) {
        if (nextnum == 1)
        {
            if (!this->next->subcapacity(t.getdirctions())) return 0;
        }
        else {
            if (t.getturn() == next1turn) {
                if (!this->next->subcapacity(t.getdirctions())) return 0;
            }
            else {
                if (!this->next2->subcapacity(t.getdirctions())) return 0;
            }
        }
    }
    if (this->pre != nullptr) {
        this->pre->addcapacity(t.getdirctions());
    }
    contain.push_back(pair(t, 1.0 / (float)frequency));
    return 1;
}
token& transition::top()
{
    if (contain.empty()) throw 0;
    else return contain[0].first;
}
void transition::update()
{
    for (auto& beg: contain){
        beg.second += 1.0 / (float)frequency;
    }
}
void transition::setnext2(place* next, int color)
{
    this->next2 = next;
    next1turn = color;
    nextnum = 2;
}
void transition::setnext(place* next)
{
    this->next = next;
    nextnum += 1;
}
void transition::setpre(place* pre)
{
    this->pre = pre;
}
void transition::setattach(place* next)
{
    this->setnext(next);
    this->next->setpre(this);
}
void transition::setattach2(place* next, int color)
{
    this->setnext2(next, color);
    this->next2->setpre(this);
}
place* transition::getnext() const
{
    return next;
}
place* transition::getpre() const
{
    return pre;
}
void transition::act()
{
    this->update();
    
    try {
        if (nextnum == 1) {
            if (this->next != nullptr) {
                for (int i = 0; i != contain.size(); i++) {
                    token* k = new token(contain[i].first);
                    if (this->pop(i)) {
                        this->next->push(*k);
                        --i;
                    }
                    else {
                        delete k;
                    }
                }
            }
        }   
        else {
            if (this->next != nullptr && this->next2 != nullptr) {
                for (int i = 0; i != contain.size(); i++) {
                    if (!contain.empty()) {
                        token* k = new token(contain[i].first);
                        if (this->pop(i)) {
                            if (k->getturn() == next1turn){
                                this->next->push(*k);
                            }
                            else {
                                this->next2->push(*k);
                            }
                            --i;
                        }
                        else {
                            delete k;
                        }
                    }
                }
            }
        }
    }
    catch (int i){}
    this->next->act();
    if (nextnum == 2) {
        this->next2->act();
    }
}
int transition::getnowcars(int x, int y) const
{
    auto k = 0;
    for (auto beg = contain.begin(); beg != contain.end(); beg++)
    {
        if (beg->first.getdirctions() == x && beg->first.getturn() == y) {
            k++;
        }
    }
    return k;
    
}
int transition::get_local_phase() const
{
    return l.localphase;
}
void transition::light_act()
{
    l.act();
}
int transition::get_local_phase_time() const
{
    return l.remaintime;
}