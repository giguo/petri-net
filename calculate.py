#!/usr/bin/python

from sympy import *
init_printing(use_latex=false)
t = Symbol('t');
def get_time(wait_car0,wait_car1,lambda0,lambda1,local_wait_cars0,local_wait_cars1,local_lambda0,local_lambda1,local_red_time,Gmin,Th,TL):
    tm0 = (local_red_time * (local_wait_cars0 * Th) + TL) / (local_red_time - local_wait_cars0 * Th)
    tm1 = (local_red_time * (local_wait_cars1 * Th) + TL) / (local_red_time - local_wait_cars1 * Th)
    if tm0 > tm1:
        ktmp = lambda1
    else:
        ktmp = lambda0
    k = solve((wait_car0 + lambda0 * (t + Gmin)) / Gmin + (wait_car1 + lambda1 * (t + Gmin)) / Gmin - 1 / Th - ktmp , t)
    for i in k:
        tmp = min((wait_car0 + lambda0 * (i + Gmin))/Gmin, ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0))) + min((wait_car1 + lambda1 * (i + Gmin))/Gmin, ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)))
        if tmp !=  (wait_car0 + lambda0 * (i + Gmin)) / Gmin + (wait_car1 + lambda1 * (i + Gmin)) / Gmin:
            continue
        if i > max(tm0, tm1):
            continue
        if i <= min(tm0, tm1):
            return min(tm0, tm1)
        else:
            return i
    k = solve((wait_car0 + lambda0 * (t + Gmin)) / Gmin + ((TL + t) * lambda1 + wait_car1)/(TL + Th *(t * lambda1 + wait_car1)) - 1 / Th - ktmp , t)
    for i in k:
        tmp = min((wait_car0 + lambda0 * (i + Gmin))/Gmin, ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0))) + min((wait_car1 + lambda1 * (i + Gmin))/Gmin, ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)))
        if tmp != (wait_car0 + lambda0 * (i + Gmin)) / Gmin + ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)):
            continue
        if i > max(tm0, tm1):
            continue
        if i <= min(tm0, tm1):
            return min(tm0, tm1)
        else:
            return i
    k = solve(((TL + t) * lambda0 + wait_car0)/(TL + Th *(t * lambda0 + wait_car0)) + (wait_car1 + lambda1 * (t + Gmin))/Gmin - 1 / Th - ktmp, t)
    for i in k:
        tmp = min((wait_car0 + lambda0 * (i + Gmin))/Gmin, ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0))) + min((wait_car1 + lambda1 * (i + Gmin))/Gmin, ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)))
        if tmp != ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0)) + (wait_car1 + lambda1 * (i + Gmin))/Gmin:
            continue
        if i > max(tm0, tm1):
            continue
        if i <= min(tm0, tm1):
            return min(tm0, tm1)
        else:
            return i
    k = solve(((TL + t) * lambda0 + wait_car0)/(TL + Th *(t * lambda0 + wait_car0)) +  ((TL + t) * lambda1 + wait_car1)/(TL + Th *(t * lambda1 + wait_car1)), t)
    for i in k:
        tmp = min((wait_car0 + lambda0 * (i + Gmin))/Gmin, ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0))) + min((wait_car1 + lambda1 * (i + Gmin))/Gmin, ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)))
        if tmp != ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)) + ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0)):
            continue
        if i > max(tm0, tm1):
            continue
        if i <= min(tm0, tm1):
            return min(tm0, tm1)
        else:
            return i
    k = solve((wait_car0 + lambda0 * (t + Gmin)) / Gmin + (wait_car1 + lambda1 * (t + Gmin)) / Gmin - local_lambda0 - local_lambda1 , t)
    for i in k:
        tmp = min((wait_car0 + lambda0 * (i + Gmin))/Gmin, ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0))) + min((wait_car1 + lambda1 * (i + Gmin))/Gmin, ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)))
        if tmp !=  (wait_car0 + lambda0 * (i + Gmin)) / Gmin + (wait_car1 + lambda1 * (i + Gmin)) / Gmin:
            continue
        if i <= max(tm0, tm1):
            return max(tm0, tm1)
        else:
            return i
    k = solve((wait_car0 + lambda0 * (t + Gmin)) / Gmin + ((TL + t) * lambda1 + wait_car1)/(TL + Th *(t * lambda1 + wait_car1)) - local_lambda0 - local_lambda1 , t)
    for i in k:
        tmp = min((wait_car0 + lambda0 * (i + Gmin))/Gmin, ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0))) + min((wait_car1 + lambda1 * (i + Gmin))/Gmin, ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)))
        if tmp != (wait_car0 + lambda0 * (i + Gmin)) / Gmin + ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)):
            continue
        if i <= max(tm0, tm1):
            return max(tm0, tm1)
        else:
            return i
    k = solve(((TL + t) * lambda0 + wait_car0)/(TL + Th *(t * lambda0 + wait_car0)) + (wait_car1 + lambda1 * (t + Gmin))/Gmin - local_lambda0 - local_lambda1, t)
    for i in k:
        tmp = min((wait_car0 + lambda0 * (i + Gmin))/Gmin, ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0))) + min((wait_car1 + lambda1 * (i + Gmin))/Gmin, ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)))
        if tmp != ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0)) + (wait_car1 + lambda1 * (i + Gmin))/Gmin:
            continue
        if i <= max(tm0, tm1):
            return max(tm0, tm1)
        else:
            return i
    k = solve(((TL + t) * lambda0 + wait_car0)/(TL + Th *(t * lambda0 + wait_car0)) +  ((TL + t) * lambda1 + wait_car1)/(TL + Th *(t * lambda1 + wait_car1)), t)
    for i in k:
        tmp = min((wait_car0 + lambda0 * (i + Gmin))/Gmin, ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0))) + min((wait_car1 + lambda1 * (i + Gmin))/Gmin, ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)))
        if tmp != ((TL + i) * lambda1 + wait_car1)/(TL + Th *(i * lambda1 + wait_car1)) + ((TL + i) * lambda0 + wait_car0)/(TL + Th *(i * lambda0 + wait_car0)):
            continue
        if i <= max(tm0, tm1):
            return max(tm0, tm1)
        else:
            return i
