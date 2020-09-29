//
//  AI.h
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-16.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include "SDL2/SDL.h"
#include "Edges.h"
#include "math.h"

#ifndef AI_h
#define AI_h



using namespace std;

class AI {
private:
    Edges edges;
public:
    AI(Edges edges, const float rad);
    float x; float x_past;
    float y; float y_past;
    float vx;
    float vy;
    float yi;
    float t;
    float r;
    float delta;
    //void findIntersect(Puck puck);
    void MoveAI();
};


#endif /* AI_h */
