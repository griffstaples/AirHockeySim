//
//  AI.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-16.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include "AI.h"
#include "Puck.h"


AI::AI(Edges edges, const float rad):
edges(edges.x_0,edges.y_0,edges.x_1,edges.y_1,edges.CR)
{
    x = (edges.x_1-edges.x_0)*3/4;
    y = (edges.y_1-edges.y_0)/2;
    vx = 0;
    vy = 0;
    delta = 1;
    t = 0;
    yi = 0;
    r = rad;
}
/*
void AI::findIntersect(Puck puck){
    if (puck.vx>0){
        t = (x-puck.x-r-15)/puck.vx;
        yi = puck.y+puck.vy*t;
        delta = t/2;
        vy = (yi-y)/delta;
    }
    else
        vy = 0;
    
}
*/
void AI::MoveAI(){
    x_past = x;
    y_past = y;
    x += vx;
    y += vy;
    
    if (x>(edges.x_1)-r){
        x = edges.x_1-r;
        vx = x-x_past;
        vy = y-y_past;
    }
    else if (x<edges.x_1/2+r){
        x = edges.x_1+r;
        vx = x-x_past;
        vy = y-y_past;
    }
    if (y>edges.y_1-r){
        y = edges.y_1-r;
        vx = x-x_past;
        vy = y-y_past;
    }
    else if (y<edges.y_0+r){
        y = edges.y_0+r;
        vx = x-x_past;
        vy = y-y_past;
    }
}
