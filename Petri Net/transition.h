//
//  transition.h
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#ifndef __Petri_Net__transition__
#define __Petri_Net__transition__
#include "token.h"
#include <iostream>
#include <vector>
typedef std::pair<token, int> pair;
class place;
class transition
{
private:
    place* next;
    place* next2;
    place* pre;
    int time;
    int next1turn;         //next1允许的token方向
    int nextnum;
    bool iscross;
    std::vector<pair> contain;
public:
    transition(int i, bool is = 0); //时间i，是否是红绿灯is
    void act();
    bool pop(int i = 0);
    bool push(token& t, bool canrun = 0);
    token& top();
    void update();
    void setnext(place* nex);
    void setpre(place* pre);
    void setattach(place* nex);
    void setattach2(place* nex, int color); //next1允许通行的token方向
    place* getnext() const;
    place* getpre() const;
    void setnext2(place* next, int color);
    int getnowcars(int x, int y);
    
};
#endif /* defined(__Petri_Net__transition__) */


