//
//  Puck.h
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-01.
//  Copyright © 2018 Clarity. All rights reserved.
//


#ifndef Puck_h
#define Puck_h
#include "Edges.h"
#include "Striker.h"
#include "AI.h"


class Puck{
private:
    int x_start;        //initial x position
    int y_start;        //initial y position
    float radius;
    Edges edges;
    float x_m;          // x difference between next striker and puck position
    float y_m;          // y difference between next striker and puck position
    float nx;           // x normalized normal vector
    float ny;           // y normalized normal vector
    float a; float b; float c; float p1; float p2; float discriminant;
    float temp;
public:
    float x;
    float y;
    float vx;
    float vy;
    Puck(int x_created, int y_created, float r_created, Edges edges);
    void move();
    void changeDirec(float new_x, float new_y);
    void drawPuck();
    void checkWallCollision();
    bool checkStrikerCollision(Striker striker);
    bool checkAICollision(AI ai);
    

    
    
    
};


#endif /* Puck_h */
