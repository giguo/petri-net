//
//  main.cpp
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include <iostream>
#include "place.h"
#include "solveconfig.h"
#include "graph.h"
#include "transition.h"
using namespace std;
int main(int argc, const char * argv[])

{
    shared_ptr<solveconfig> s(new solveconfig());
    shared_ptr<graph> g(new graph(*s));
    for (int i = 1 ; i != 6200; i++) {
        g->act(i);
        g->print_graph(i);
        cout << "延迟时间:" << g->get_delay_time() << '\t' << "到达车辆数:" << g->get_arrive_cars()
            << '\t' << "平均延误:" << g->get_delay_time() / g->get_arrive_cars() << endl;
    }
}
