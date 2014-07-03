//
//  token.h
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#ifndef __Petri_Net__token__
#define __Petri_Net__token__

#include <iostream>
#include "light.h"
class token
{
private:
    int directions;       //方向 0：左 1：下 2：右 3：上
    int turn;             //转向 0：左转 1：直行 2：右转
    float delay_time;
public:
    token(int d, int t);
    token(const token& t);
    int getdirctions() const;
    int getturn() const;
    float get_delay_time() const;
    void setdirections(int d);
    void setturn(int t);
    void add_delay_time();
    
};
#endif /* defined(__Petri_Net__token__) */
