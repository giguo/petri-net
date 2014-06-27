//
//  light.h
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#ifndef __Petri_Net__light__
#define __Petri_Net__light__

#include <iostream>
#include "token.h"

class light
{
private:
    int localphase;                 //当前相位
    int remaintime;                 //剩余时间
    
public:
    void changephase();                 //切换相位
    bool canrun(int direct, int turn);  //测试该方向能否走
    bool canrun(const token& t)const;   //测试该token能否走
};
#endif /* defined(__Petri_Net__light__) */
