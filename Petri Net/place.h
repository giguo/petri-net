//
//  place.h
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#ifndef __Petri_Net__place__
#define __Petri_Net__place__

#include <iostream>
#include <queue>
#include "token.h"
#include <initializer_list>
#include "transition.h"
class place
{
private:
    int capacity[4];        //当前库所的剩余容量
    int nowcars[4][3];      //当前库所的车辆数
    std::queue<token> contain;
    transition* next;
    transition* pre;
public:
    place(std::initializer_list<int> s);
    bool push(token& t);
    token& top();
    bool pop();
    void act();
    void setnext(transition* nex);
    void setpre(transition* pre);
    void setattach(transition* nex);
    transition* getnext() const;
    transition* getpre() const;
    void setcolor(int cl);
    void addcapacity(int num);
    bool subcapacity(int num);
    void addcars(int x, int y, int cars);
    int getnowcars(int x,int y) const;
};

#endif /* defined(__Petri_Net__place__) */