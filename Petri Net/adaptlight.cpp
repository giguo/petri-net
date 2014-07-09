//
//  fitlight.cpp
//  Petri Net
//
//  Created by adore on 14-7-3.
//  Copyright (c) 2014年 adore. All rights reserved.
//
#include <vector>
#include <algorithm>
#include <cmath>
#include "light.h"
#include "token.h"
#include "graph.h"
#include <random>
adaptLight::adaptLight():lastphase(0),nextphase(2)
{}
void adaptLight::act(const std::vector<std::vector<int> >& g)
{
    for (int i = 0; i != 4; i++) {
        if (this->localphase != i) {
            red_time[i] += 1;
        }
        else {
            red_time[i] = 0;
        }
    }
    if (green_losttime != 0) {
        --green_losttime;
    }
    if (remaintime != 0) {
        --remaintime;
    }
    if (remaintime == 0) {
        std::cerr << "\033[33mphase changed from " << localphase << " to " << nextphase << "\033[0m" << std::endl;
        changephase(g);
    }
}

float perfecttime(float wait_car0, float wait_car1, float lambda0, float lambda1, float local_wait_cars0, float local_wait_cars1, float local_lambda0, float local_lambda1, int local_red_time)
{
    auto Th = light_averagetime;
    auto TL = greenlight_losttime;
    auto Gmin = greenlight_mintime;
    auto Gmax = greenlight_maxtime;
    float ENt0, ENt1;
    if (lambda0 * Th >= 1) {
        ENt0 = Gmax - 1;
    }
    else {
        ENt0 = (local_wait_cars0 * light_averagetime + greenlight_losttime) / (1 - lambda0 * Th);
    }
    if (lambda1 * Th >= 1) {
        ENt1 = Gmax - 1;
    }
    else {
        ENt1 = (local_wait_cars1 * light_averagetime + greenlight_losttime) / (1 - lambda1 * Th);
    }
    
    for (int time = (int)std::min(ENt0, ENt1) + 1; time != Gmax + 1; time++) {
        float EG00 = ((wait_car0) + lambda0 * (time + Gmin)) / Gmin;
        float EG01 = ((TL + time) * lambda0 + wait_car0) / (TL + Th * (time * lambda0 + wait_car0));
        float EG10 = ((wait_car1) + lambda1 * (time + Gmin)) / Gmin;
        float EG11 = ((TL + time) * lambda0 + wait_car1) / (TL + Th * (time * lambda1 + wait_car1));
        
        if (time <= std::max(ENt0, ENt1)) {
            float EG = std::min(EG00, EG01) + std::min(EG10, EG11);
            float EN = 1 / Th + ENt0>ENt1?local_lambda1:local_lambda0;
            if (EG > EN) {
                return time;
            }
        }
        else {
            float EG = std::min(EG00, EG01) + std::min(EG10, EG11);
            float EN = local_lambda0 + local_lambda1;
            if (EG > EN) {
                return time;
            }
        }
    }
    return Gmax;
}
void adaptLight::changephase(const std::vector<std::vector<int> >& g)
{
    //确定下一相位
    int wait_cars[4][2];                        //第i相位第j车道的车辆数
    memset(wait_cars, 0, sizeof(wait_cars));
    for (int i = 0; i != 4; i++) {
        for (int j = 0; j != 3; j++) {
            switch (i) {
                case 0:{
                    switch (j) {
                        case 0:
                            wait_cars[1][0] += g[i].at(j);
                            break;
                        case 1:
                            wait_cars[0][0] += g[i].at(j);
                            break;
                        case 2:
                            wait_cars[0][0] += g[i].at(j);
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case 1:{
                    switch (j) {
                        case 0:
                            wait_cars[3][0] += g[i].at(j);
                            break;
                        case 1:
                            wait_cars[2][0] += g[i].at(j);
                            break;
                        case 2:
                            wait_cars[2][0] += g[i].at(j);
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case 2:{
                    switch (j) {
                        case 0:
                            wait_cars[1][1] += g[i].at(j);
                            break;
                        case 1:
                            wait_cars[0][1] += g[i].at(j);
                            break;
                        case 2:
                            wait_cars[0][1] += g[i].at(j);
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case 3:{
                    switch (j) {
                        case 0:
                            wait_cars[3][1] += g[i].at(j);
                            break;
                        case 1:
                            wait_cars[2][1] += g[i].at(j);
                            break;
                        case 2:
                            wait_cars[2][1] += g[i].at(j);
                            break;
                        default:
                            break;
                    }
                    break;
                }
                    
                default:
                    break;
            }
        }
    }
    float lambda[4][2];                         //第i相位第j车道的泊松强度
    for (int i = 0; i != 4; i++) {
        for (int j = 0; j != 2; j++) {
            lambda[i][j] = (float)(wait_cars[i][j]) / float(red_time[i]);
        }
    }
    std::vector<std::pair<int, int>> vv;
    for (int i = 0; i != 4; i++) {
        if (i != localphase && i != nextphase) {
            float f = perfecttime(wait_cars[i][0],wait_cars[i][1],lambda[i][0],lambda[i][1],wait_cars[nextphase][0],wait_cars[nextphase][1],lambda[nextphase][0],lambda[nextphase][1],red_time[nextphase]);
            vv.push_back(std::pair<int, int>(f,i));
        }
    }
    if (vv.size() != 2) {
        throw 2;
    }
    else {
        lastphase = localphase;
        localphase = nextphase;
        if (vv[0].first < vv[1].first) {
            nextphase = vv[0].second;
            remaintime = std::max(vv[0].first, greenlight_mintime);
        }
        else {
            if (vv[0].first == vv[1].first)
            {
                std::random_device r;
                std::bernoulli_distribution b(0.5);
                auto x = b(r);
                nextphase = vv[x].second;
                remaintime = std::max(vv[x].first, greenlight_mintime);
                
            }
            else {
                nextphase = vv[1].second;
                remaintime = std::max(vv[1].first, greenlight_mintime);
            }
        }
        std::cerr << "green time: " << remaintime << std::endl;
        green_losttime = greenlight_losttime;
    }
    green_losttime = 2;
    return;
}

bool adaptLight::canrun(int direct, int turn) const
{
    if (green_losttime != 0) {
        return 0;
    }
    switch (localphase) {
        case 0:
            if (direct == 0 || direct == 2) {
                if (turn == 1 || turn == 2) {
                    return 1;
                }
            }
            break;
        case 1:
            if (direct == 0|| direct == 2) {
                if (turn == 0) {
                    return 1;
                }
            }
            break;
        case 2:
            if (direct == 1 || direct == 3) {
                if (turn == 1 || turn == 2) {
                    return 1;
                }
            }
            break;
        case 3:
            if (direct == 1 || direct == 3) {
                if (turn == 0) {
                    return 1;
                }
            }
            break;
        default:
            break;
    }
    return 0;
}
bool adaptLight::canrun(const token& t) const
{
    return canrun(t.getdirctions(), t.getturn());
}
