//
//  main.cpp
//  Petri Net
//
//  Created by adore on 14-6-26.
//  Copyright (c) 2014年 adore. All rights reserved.
//

#include <iostream>
#include "place.h"
#include "transition.h"
using namespace std;
int main(int argc, const char * argv[])
{
    place p1({30000,30000,30000,30000});
    transition t2(1);
    place p3({3,2,2,2});
    transition t4(1);
    place p5({3,30000,30000,30000});
    transition t6(1);
    place p7({30000,30000,30000,30000});
    place p72({30000,30000,30000,30000});
    p1.setattach(&t2);
    t2.setattach(&p3);
    p3.setattach(&t4);
    t4.setattach(&p5);
    p5.setattach(&t6);
    t6.setattach(&p7);
    t6.setattach2(&p72, 0);
    
    p1.addcars(0, 1, 50);
    p1.addcars(0, 0, 30);

    
    
    cout << p1.getnowcars(0, 0) <<':' << p1.getnowcars(0, 1) << ' '
    << t2.getnowcars(0, 0) <<':' << t2.getnowcars(0, 1) <<' '
    << p3.getnowcars(0, 0) <<':' << p3.getnowcars(0, 1) <<' '
    << t4.getnowcars(0, 0) <<':' << t4.getnowcars(0, 1) <<' '
    << p5.getnowcars(0, 0) <<':' << p5.getnowcars(0, 1) <<' '
    << t6.getnowcars(0, 0) <<':' << t6.getnowcars(0, 1) <<' '
    << p7.getnowcars(0, 0) <<':' << p7.getnowcars(0, 1) <<' '
    << p72.getnowcars(0, 0) <<':' << p72.getnowcars(0, 1) <<' ' << endl;
    
    for (int i = 0; i != 50; i++) {
        p72.act();
        p7.act();
        t6.act();
        p5.act();
        t4.act();
        p3.act();
        t2.act();
        p1.act();
        
        cout << p1.getnowcars(0, 0) <<':' << p1.getnowcars(0, 1) << ' '
        << t2.getnowcars(0, 0) <<':' << t2.getnowcars(0, 1) <<' '
        << p3.getnowcars(0, 0) <<':' << p3.getnowcars(0, 1) <<' '
        << t4.getnowcars(0, 0) <<':' << t4.getnowcars(0, 1) <<' '
        << p5.getnowcars(0, 0) <<':' << p5.getnowcars(0, 1) <<' '
        << t6.getnowcars(0, 0) <<':' << t6.getnowcars(0, 1) <<' '
        << p7.getnowcars(0, 0) <<':' << p7.getnowcars(0, 1) <<' '
        << p72.getnowcars(0, 0) <<':' << p72.getnowcars(0, 1) <<' ' << endl;
    }
}

