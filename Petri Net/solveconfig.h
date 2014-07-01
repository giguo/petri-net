//
//  solveconfig.h
//  placi Net
//
//  Created by adore on 14-6-28.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#ifndef __placi_Net__solveconfig__
#define __placi_Net__solveconfig__

#include <iostream>
class solveconfig
{
public:
    class plac
    {
    public:
        int capacity[4];
    };
    class tran
    {
    public:
        int time[4];
        bool isSignal = 0;
    };
    plac p1;
    tran t2;
    plac p3;
    tran t4;
    plac p5, p52;
    tran t6, t62;
    plac p7, p72;
    tran t8, t82;
    plac p9, p921, p922;
    float flux[4][4];   //方向 0：左 1：下 2：右 3：上
public:
    solveconfig();

};
#endif /* defined(__placei_Net__solveconfig__) */
