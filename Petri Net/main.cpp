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
    for (int i = 1 ; i != 800; i++) {
        g->act();
        g->print_graph(i);
        cout << "延迟时间" << g->get_delay_time() << endl;
    }
}