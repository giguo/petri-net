//
//  light.cpp
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include "light.h"
void fixedLight::changephase()
{
    localphase = localphase % 4 + 1;
    remaintime = greenlight_fixedtime;
    green_losttime = greenlight_losttime;
}
void fixedLight::act()
{
    if (green_losttime) {
        --green_losttime;
    }
    if (remaintime) {
        --remaintime;
    }
    else {
        changephase();
    }
}
bool fixedLight::canrun(int direct, int turn) const
{
    if (!green_losttime) {
        return 0;
    }
    switch (localphase) {
        case 1:
            if (direct == 0 || direct == 2) {
                if (turn == 1 || turn == 2) {
                    return 1;
                }
            }
            break;
        case 2:
            if (direct == 0|| direct == 2) {
                if (turn == 0) {
                    return 1;
                }
            }
            break;
        case 3:
            if (direct == 1 || direct == 3) {
                if (turn == 1 || turn == 2) {
                    return 1;
                }
            }
            break;
        case 4:
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
bool fixedLight::canrun(const token& t) const
{
    return canrun(t.getdirctions(), t.getturn());
}