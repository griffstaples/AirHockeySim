//
//  Striker.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-05.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include "Striker.h"
using namespace std;



Striker::Striker(float radius, Edges edges){
    x = (edges.x_1-edges.x_0)*3/4;    //center of left side
    y = (edges.y_1-edges.y_0)/2;    //y center
    r = radius;
    vy = 0;
    vx = 0;
}

void Striker::moveStriker(int *x_point, int *y_point,Edges edges){
    x_past = x;     //store previous x for velocity calculation
    y_past = y;     //store previous y for velocity calculation
    SDL_GetMouseState(x_point, y_point);            //update striker position
    *x_point = (*x_point)*2;
    *y_point = (*y_point)*2;

    
    //ensure max speed of 30px/frame
    if (sqrt((vx)*(vx)+(vy)*(vy)) > 30 ){
        if (vx>0){
            x = x_past + 30*cos(atan((vy)/(vx)));
            y = y_past + 30*sin(atan((vy)/(vx)));
            vx = x-x_past;
            vy = y-y_past;
        }
        else{
            x = x_past - 30*cos(atan(vy/vx));
            y = y_past - 30*sin(atan(vy/vx));
            vx = x-x_past;
            vy = y-y_past;
        }
    }

    
    //set boundaries of striker
    if (x>(edges.x_1/2)-r){
        x = (edges.x_1-edges.x_0)/2-r;
        vx = x-x_past;
        vy = y-y_past;
    }
    else if (x<edges.x_0+r){
        x = edges.x_0+r;
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


void Striker::autoMove(Edges edges){
    x+=vx;
    y+=vy;
    
    if (x>(edges.x_1/2)-r){
        x = (edges.x_1-edges.x_0)/2-r;
        vx = x-x_past;
        vy = y-y_past;
    }
    else if (x<edges.x_0+r){
        x = edges.x_0+r;
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

