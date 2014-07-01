//
//  graph.cpp
//  Petri Net
//
//  Created by adore on 14-6-28.
//  Copyright (c) 2014年 adore. All rights reserved.
//
#include <random>
#include "graph.h"
#include <boost/python.hpp>
using namespace boost::python;

graph::graph(solveconfig config):
p1({config.p1.capacity[0], config.p1.capacity[1], config.p1.capacity[2], config.p1.capacity[3]}),
t2({config.t2.time[0], config.t2.time[1], config.t2.time[2], config.t2.time[3]}),
p3({config.p3.capacity[0], config.p3.capacity[1], config.p3.capacity[2], config.p3.capacity[3]}),
t4({config.t4.time[0], config.t4.time[1], config.t4.time[2], config.t4.time[3]}),
p5({config.p5.capacity[0], config.p5.capacity[1], config.p5.capacity[2], config.p5.capacity[3]}),
p52({config.p52.capacity[0], config.p52.capacity[1], config.p52.capacity[2], config.p52.capacity[3]}),
t6({config.t6.time[0], config.t6.time[1], config.t6.time[2], config.t6.time[3]}),
t62({config.t62.time[0], config.t62.time[1], config.t62.time[2], config.t62.time[3]}),
p7({config.p7.capacity[0], config.p7.capacity[1], config.p7.capacity[2], config.p7.capacity[3]}),
p72({config.p72.capacity[0], config.p72.capacity[1], config.p72.capacity[2], config.p72.capacity[3]}),
t8({config.t8.time[0], config.t8.time[1], config.t8.time[2], config.t8.time[3]}),
t82({config.t82.time[0], config.t82.time[1], config.t82.time[2], config.t82.time[3]}),
p9({config.p9.capacity[0], config.p9.capacity[1], config.p9.capacity[2], config.p9.capacity[3]}),
p921({config.p921.capacity[0], config.p921.capacity[1], config.p921.capacity[2], config.p921.capacity[3]}),
p922({config.p922.capacity[0], config.p922.capacity[1], config.p922.capacity[2], config.p922.capacity[3]})
{
    p1.setattach(&t2);
    t2.setattach(&p3);
    p3.setattach(&t4);
    t4.setattach(&p5);
    t4.setattach2(&p52, 0);
    p5.setattach(&t6);
    p52.setattach(&t62);
    t6.setattach(&p7);
    t62.setattach(&p72);
    p7.setattach(&t8);
    p72.setattach(&t82);
    t8.setattach(&p9);
    t82.setattach(&p921);
    t82.setattach2(&p922, 1);
    for (int i = 0; i != 4; i++) {
        for (int j = 0; j != 4; j++) {
            flux[i][j] = config.flux[i][j];
        }
    }
}
void graph::add1Car(bool realrandom)
{
    if (realrandom) {
        for (int i = 0; i != 4; i++) {
            std::bernoulli_distribution b(flux[i][0]);
            int hascar = b(real_r);
            if (hascar) {
                std::bernoulli_distribution b1(flux[i][1]);
                if (b1(real_r)) {
                    p1.addcars(i, 0, 1);
                }
                else {
                    std::bernoulli_distribution b2(flux[i][2]);
                    if (b2(real_r)) {
                        p1.addcars(i, 1, 1);
                    }
                    else {
                        p1.addcars(i, 2, 1);
                    }
                }
            }
        }
    }
    else {
        for (int i = 0; i != 4; i++) {
            std::bernoulli_distribution b(flux[i][0]);
            int hascar = b(r);
            if (hascar) {
                std::bernoulli_distribution b1(flux[i][1]);
                if (b1(r)) {
                    p1.addcars(i, 0, 1);
                }
                else {
                    std::bernoulli_distribution b2(flux[i][2]);
                    if (b2(r)) {
                        p1.addcars(i, 1, 1);
                    }
                    else {
                        p1.addcars(i, 2, 1);
                    }
                }
            }
        }
    }
}
void graph::act()
{
    add1Car();
    t8.act();
    t82.act();
    p7.act();
    p72.act();
    t6.act();
    t62.act();
    p5.act();
    p52.act();
    t4.act();
    p3.act();
    t2.act();
    p1.act();
}
using namespace std;
void graph::print_graph_nth(int i, const char* a) const
{
    cout << "p1:";
    for (int j = 0; j != 2; j++) {
        cout << p1.getnowcars(i, j) << ',';
    }
    cout << p1.getnowcars(i, 2) << a;
    
    cout << "t2:";
    for (int j = 0; j != 2; j++) {
        cout << t2.getnowcars(i, j) << ',';
    }
    cout << t2.getnowcars(i, 2) << a;
    
    cout << "p3:";
    for (int j = 0; j != 2; j++) {
        cout << p3.getnowcars(i, j) << ',';
    }
    cout << p3.getnowcars(i, 2) << a;
    
    cout << "t4:";
    for (int j = 0; j != 2; j++) {
        cout << t4.getnowcars(i, j) << ',';
    }
    cout << t4.getnowcars(i, 2) << a;
    
    cout << "p5:";
    for (int j = 0; j != 2; j++) {
        cout << p5.getnowcars(i, j) << ',';
    }
    cout << p5.getnowcars(i, 2) << a;
    
    cout << "p52:";
    for (int j = 0; j != 2; j++) {
        cout << p52.getnowcars(i, j) << ',';
    }
    cout << p52.getnowcars(i, 2) << a;
    
    cout << "t6:";
    for (int j = 0; j != 2; j++) {
        cout << t6.getnowcars(i, j) << ',';
    }
    cout << t6.getnowcars(i, 2) << a;
    
    cout << "t62:";
    for (int j = 0; j != 2; j++) {
        cout << t62.getnowcars(i, j) << ',';
    }
    cout << t62.getnowcars(i, 2) << a;
    
    cout << "p7:";
    for (int j = 0; j != 2; j++) {
        cout << p7.getnowcars(i, j) << ',';
    }
    cout << p7.getnowcars(i, 2) << a;
    
    cout << "p72:";
    for (int j = 0; j != 2; j++) {
        cout << p72.getnowcars(i, j) << ',';
    }
    cout << p72.getnowcars(i, 2) << a;
    
    cout << "t8:";
    for (int j = 0; j != 2; j++) {
        cout << t8.getnowcars(i, j) << ',';
    }
    cout << t8.getnowcars(i, 2) << a;
    
    cout << "t82:";
    for (int j = 0; j != 2; j++) {
        cout << t82.getnowcars(i, j) << ',';
    }
    cout << t82.getnowcars(i, 2) << a;
    
    cout << "p9:";
    for (int j = 0; j != 2; j++) {
        cout << p9.getnowcars(i, j) << ',';
    }
    cout << p9.getnowcars(i, 2) << a;
    
    cout << "p921:";
    for (int j = 0; j != 2; j++) {
        cout << p921.getnowcars(i, j) << ',';
    }
    cout << p921.getnowcars(i, 2) << a ;

    cout << "p922:";
    for (int j = 0; j != 2; j++) {
        cout << p922.getnowcars(i, j) << ',';
    }
    cout << p922.getnowcars(i, 2);
    
    cout << endl;
}
void graph::print_graph() const
{
    cout << "now condition:" << endl;
    for (int i = 0; i != 4; i++) {
        print_graph_nth(i, " \t");
    }
}







