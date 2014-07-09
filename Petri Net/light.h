//
//  light.h
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#ifndef __Petri_Net__light__
#define __Petri_Net__light__
#include <vector>
#include <iostream>
class graph;
class token;

//#define Light  adaptLight                 //选择何种方式
#define Light  fixedLight                   //选择何种方式
const int frequency = 10;                   //更新频率
const int greenlight_fixedtime = 50;        //固定相位时绿灯时间
//const int yellowlight_time = 2;           //黄灯时间
const int greenlight_losttime = 2;          //绿灯损失时间
const int greenlight_mintime = 5;          //绿灯最小时间
const int greenlight_maxtime = 80;          //绿灯最长时间
const int redlight_mintime = 120;           //红灯最小时间
const int redlight_maxtime = 200;           //红灯最长时间
const int light_averagetime = 1;            //过绿灯的平均时间

class light
{
public:
    int localphase = 1;             //当前相位 1:第一相位
//    int yellowtime;               //剩余黄灯时间
    int remaintime;                 //剩余时间
    int green_losttime;             //绿灯损失时间
    
public:
    light();
    virtual void act(const std::vector<std::vector<int> >& g) = 0;                                 //更新
    virtual void changephase(const std::vector<std::vector<int> >& g) = 0;                         //切换相位
    virtual bool canrun(int direct, int turn)const = 0;                                            //测试该方向能否走
    virtual bool canrun(const token& t)const = 0;                                                  //测试该token能否走
};

class fixedLight:public light
{
public:
    void act(const std::vector<std::vector<int> >& g);
    void changephase(const std::vector<std::vector<int> >& g);
    virtual bool canrun(int direct, int turn)const;          //测试该方向能否走
    virtual bool canrun(const token& t)const;                //测试该token能否走
};
class adaptLight:public light
{
private:
    int lastphase;
    int nextphase;
    int red_time[4];
public:
    adaptLight();
    void act(const std::vector<std::vector<int> >& g);
    void changephase(const std::vector<std::vector<int> >& g);
    virtual bool canrun(int direct, int turn)const;          //测试该方向能否走
    virtual bool canrun(const token& t)const;                //测试该token能否走

};
#endif /* defined(__Petri_Net__light__) */
