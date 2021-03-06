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
t2({config.t2.time[0], config.t2.time[1], config.t2.time[2], config.t2.time[3]},config.t2.isSignal),
p3({config.p3.capacity[0], config.p3.capacity[1], config.p3.capacity[2], config.p3.capacity[3]}),
t4({config.t4.time[0], config.t4.time[1], config.t4.time[2], config.t4.time[3]},config.t4.isSignal),
p5({config.p5.capacity[0], config.p5.capacity[1], config.p5.capacity[2], config.p5.capacity[3]}),
p52({config.p52.capacity[0], config.p52.capacity[1], config.p52.capacity[2], config.p52.capacity[3]}),
t6({config.t6.time[0], config.t6.time[1], config.t6.time[2], config.t6.time[3]},config.t6.isSignal),
t62({config.t62.time[0], config.t62.time[1], config.t62.time[2], config.t62.time[3]},config.t62.isSignal),
p7({config.p7.capacity[0], config.p7.capacity[1], config.p7.capacity[2], config.p7.capacity[3]}),
p72({config.p72.capacity[0], config.p72.capacity[1], config.p72.capacity[2], config.p72.capacity[3]}),
t8({config.t8.time[0], config.t8.time[1], config.t8.time[2], config.t8.time[3]},config.t8.isSignal),
t82({config.t82.time[0], config.t82.time[1], config.t82.time[2], config.t82.time[3]},config.t82.isSignal),
p9({config.p9.capacity[0], config.p9.capacity[1], config.p9.capacity[2], config.p9.capacity[3]}),
p921({config.p921.capacity[0], config.p921.capacity[1], config.p921.capacity[2], config.p921.capacity[3]}),
p922({config.p922.capacity[0], config.p922.capacity[1], config.p922.capacity[2], config.p922.capacity[3]})
{
    for (int i = 0; i != 4; i++) {
        for (int j = 0; j != 4; j++) {
            flux[i][j] = config.flux[i][j];
        }
    }
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
}
void graph::add1Car(bool realrandom)
{
    if (realrandom) {
        for (int i = 0; i != 4; i++) {
            std::poisson_distribution<> b(flux[i][0] / frequency);
            int hascar = b(real_r);
            while (hascar) {
                std::uniform_real_distribution<> u(0, 1);
                float tmp = u(real_r);
                if (tmp < flux[i][1]) {
                    p1.addcars(i, 0, 1);
                }
                else {
                    if (tmp < flux[i][1] + flux[i][2]) {
                        p1.addcars(i, 1, 1);
                    }
                    else {
                        p1.addcars(i, 2, 1);
                    }
                }
                --hascar;
            }
        }
    }
    else {
        for (int i = 0; i != 4; i++) {
            std::poisson_distribution<> b(flux[i][0] / frequency);
            int hascar = b(r);
            while (hascar) {
                std::uniform_real_distribution<> u(0, 1);
                float tmp = u(r);
                if (tmp < flux[i][1]) {
                    p1.addcars(i, 0, 1);
                }
                else {
                    if (tmp < flux[i][1] + flux[i][2]) {
                        p1.addcars(i, 1, 1);
                    }
                    else {
                        p1.addcars(i, 2, 1);
                    }
                }
                --hascar;
            }
        }
    }
}
void graph::add1Car(std::vector<std::vector<float> > flux)
{
    for (int i = 0; i != 4; i++) {
        std::poisson_distribution<> b(flux[i][0] / frequency);
        int hascar = b(real_r);
        while (hascar) {
            std::uniform_real_distribution<> u(0, 1);
            float tmp = u(real_r);
            if (tmp < flux[i][1]) {
                p1.addcars(i, 0, 1);
            }
            else {
                if (tmp < flux[i][1] + flux[i][2]) {
                    p1.addcars(i, 1, 1);
                }
                else {
                    p1.addcars(i, 2, 1);
                }
            }
            --hascar;
        }
    }
}

void graph::act(int variety)
{
    t8.light_act(this->get_wait_cars());
    for (int i = 0; i != frequency; i++) {
        if (variety != 0) {
            if ((variety > 0 && variety <= 1000) || (variety > 5200 && variety <= 6200)) {
                add1Car({{0.389,0.25,0.5,0.25},{0.236,0.33,0.33,0.33},{0.389,0.25,0.5,0.25},{0.236,0.33,0.33,0.33}});
            }
            else {
                if ((variety > 1000 && variety <= 2200) || (variety > 4000 && variety <= 5200)) {
                    add1Car({{0.5,0.25,0.5,0.25},{0.278,0.33,0.33,0.33},{0.5,0.25,0.5,0.25},{0.278,0.33,0.33,0.33}});
                }
                else {
                    if (variety > 2200 && variety <= 4000) {
                        add1Car({{0.556,0.25,0.5,0.25},{0.333,0.33,0.33,0.33},{0.556,0.25,0.5,0.25},{0.333,0.33,0.33,0.33}});
                    }
                }
            }
        }
        else {
            add1Car(1);
        }
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
//        p1.update_delay_time();
//        p3.update_delay_time();
//        p5.update_delay_time();
//        p52.update_delay_time();
        p7.update_delay_time();
        p72.update_delay_time();
    }
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
void graph::print_graph(int i) const
{
    cout << "now situation:" << i << ' ' << '\t';
    print_light();
    for (int i = 0; i != 4; i++) {
        print_graph_nth(i, " \t");
    }
}
void graph::print_light() const
{
    cout << "local phase:" << t8.get_local_phase() << '\t' << "Green time remain:" << t8.get_local_phase_time() << '\t' << " Green lost time remain:" << t8.get_green_lost_time() << endl;
}
float graph::get_delay_time() const
{
    float tmp = 0.0;
    tmp += p9.get_delay_time();
    tmp += p921.get_delay_time();
    tmp += p922.get_delay_time();
    return tmp;
}
int graph::get_arrive_cars() const
{
    return p9.get_arrive_cars() + p921.get_arrive_cars() + p922.get_arrive_cars();
}
int graph::get_cross_cars() const
{
    return get_arrive_cars() + p7.get_arrive_cars() + p72.get_arrive_cars();
}
std::vector<std::vector<int> > graph::get_wait_cars() const
{
    vector<vector<int> > v({{0,0,0},{0,0,0},{0,0,0},{0,0,0}});
    for (int i = 0; i != 4; i++) {
        for (int j = 0; j != 3; j++) {
            v[i][j] += p7.getnowcars(i, j);
            v[i][j] += p72.getnowcars(i, j);
        }
    }
    return v;
}
