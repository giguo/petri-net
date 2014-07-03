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

class token;
#define Light fixedLight
const int frequency = 10;                   //更新频率
const bool isfixed = 0;                     //是否选择固定相位
const int greenlight_fixedtime = 30;        //固定相位时绿灯时间
//const int yellowlight_time = 2;           //黄灯时间
const int greenlight_losttime = 2;          //绿灯损失时间
const int greenlight_mintime = 30;          //绿灯最小时间
const int greenlight_maxtime = 80;          //绿灯最长时间
const int redlight_mintime = 120;           //红灯最小时间
const int redlight_maxtime = 200;           //红灯最长时间

class light
{
public:
    int localphase = 1;             //当前相位 1:第一相位
//    int yellowtime;               //剩余黄灯时间
    int remaintime;                 //剩余时间
    int green_losttime;             //绿灯损失时间
    
public:
    light();
    virtual void act() = 0;                                 //更新
    virtual void changephase() = 0;                         //切换相位
    virtual bool canrun(int direct, int turn)const = 0;          //测试该方向能否走
    virtual bool canrun(const token& t)const = 0;                //测试该token能否走
};

class fixedLight:public light
{
public:
    fixedLight();
    void act();
    void changephase();
    bool canrun(int direct, int turn) const;
    bool canrun(const token& t)const;
};
//class adaptLight:public light
//{
//public:
//    void act();
//    void changephase();
//    bool canrun(int direct, int turn) const;
//    bool canrun(const token& t)const;
//};
#endif /* defined(__Petri_Net__light__) */
