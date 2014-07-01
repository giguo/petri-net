//
//  solveconfig.cpp
//  Petri Net
//
//  Created by adore on 14-6-28.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include "solveconfig.h"
#include <boost/python.hpp>
using namespace boost::python;
template <typename T>
void setarrayBylist(object& l,T * a)
{
    for (int i = 0; i != 4; i++)
    {
        a[i] = extract<T>(l[i]);
    }
}
void setvalue(object& l,bool& a)
{
    a = extract<bool>(l);
}
solveconfig::solveconfig()
{
    try {
        Py_Initialize();
        auto main = import("__main__").attr("__dict__");
        exec_file("/Users/adore/Documents/Petri Net/config.py", main);
        auto getvalue = main["getvalue"];
        auto getflux = main["getflux"];
        
        object k = getvalue("p1", "capacity");
        setarrayBylist(k, p1.capacity);
        
        k = getvalue("t2", "time");
        setarrayBylist(k, t2.time);
        k = getvalue("t2", "iscross");
        setvalue(k, t2.isSignal);
        
        k = getvalue("p3", "capacity");
        setarrayBylist(k, p3.capacity);

        k = getvalue("t4", "time");
        setarrayBylist(k, t4.time);
        k = getvalue("t4", "iscross");
        setvalue(k, t4.isSignal);
        
        k = getvalue("p5", "capacity");
        setarrayBylist(k, p5.capacity);
        
        k = getvalue("p52", "capacity");
        setarrayBylist(k, p52.capacity);
        
        k = getvalue("t6", "time");
        setarrayBylist(k, t6.time);
        k = getvalue("t6", "iscross");
        setvalue(k, t6.isSignal);
        
        k = getvalue("t62", "time");
        setarrayBylist(k, t62.time);
        k = getvalue("t62", "iscross");
        setvalue(k, t62.isSignal);
        
        k = getvalue("p7", "capacity");
        setarrayBylist(k, p7.capacity);
        
        k = getvalue("p72", "capacity");
        setarrayBylist(k, p72.capacity);
        
        k = getvalue("t8", "time");
        setarrayBylist(k, t8.time);
        k = getvalue("t8", "iscross");
        setvalue(k, t8.isSignal);
        
        k = getvalue("t82", "time");
        setarrayBylist(k, t82.time);
        k = getvalue("t82", "iscross");
        setvalue(k, t82.isSignal);
        
        k = getvalue("p9", "capacity");
        setarrayBylist(k, p9.capacity);
        
        k = getvalue("p921", "capacity");
        setarrayBylist(k, p921.capacity);
        
        k = getvalue("p922", "capacity");
        setarrayBylist(k, p922.capacity);
        
        k = getflux("left");
        setarrayBylist(k, flux[0]);
        
        k = getflux("down");
        setarrayBylist(k, flux[1]);
        
        k = getflux("right");
        setarrayBylist(k, flux[2]);
        
        k = getflux("up");
        setarrayBylist(k, flux[3]);
        
        Py_Finalize();
    }
    catch (...) {
        PyErr_Print();
    }
}