//
//  Puck.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-01.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include "Puck.h"
#include "math.h"
#include <iostream>
using namespace std;

Puck::Puck(int x_created, int y_created, float r_created, Edges edges):
edges(edges.x_0, edges.y_0, edges.x_1, edges.y_1, edges.CR)
{
    x_start = x_created;
    y_start = y_created;
    radius = r_created;
    vy = 1;
    vx = 1;
    x = x_created;
    y = y_created;
}

void Puck::move(){
    x+= vx;
    y+= vy;
}

void Puck::changeDirec(float new_x, float new_y){
    vx = new_x;
    vy = new_y;
}

//checks for wall collision next frame and adds in frictional factors
void Puck::checkWallCollision(){
    if(x-edges.x_0+vx <= radius && vx < 0){
        vx *= -1;
        vy *= 1;
        x = 2*edges.x_0-x+2*radius;
    }
    else if (edges.x_1-x-vx <= radius && vx > 0){
        vx *= -1;
        vy *= 1;
        x = 2*edges.x_1-x-2*radius;
    }
    else if (edges.y_0+y+vy <= radius && vy < 0){
        vy *= -1;
        vx *= 1;
        y = 2*edges.y_0-y+2*radius;
    }
    else if (edges.y_1-y-vy <=radius && vy > 0 ){
        vy *= -1;
        vx *= 1;
        y = 2*edges.y_1-y-2*radius;
    }
    else{
        vx *= 1;
        vy *= 1;
    }
        
    }



bool Puck::checkStrikerCollision(Striker striker){
    striker.vx = striker.x-striker.x_past;
    striker.vy = striker.y-striker.y_past;
    
    a = pow(vx-striker.vx,2)+pow(vy-striker.vy,2);
    b = 2*(striker.x*(striker.vx-vx) + x*(vx-striker.vx))+2*(striker.y*(striker.vy-vy) + y*(vy-striker.vy));
    c = pow(striker.x-x,2)+pow(striker.y-y,2)-pow(radius+striker.r,2);
    discriminant = b*b-4*a*c;
    p1 = -(-b+sqrt(b*b-4*a*c))/(2*a);
    p2 = -(-b-sqrt(b*b-4*a*c))/(2*a);
    
   
    if(p1>0 && p1 <=1){
        if(p2>0 && p2<=1){
            temp = min(p1,p2);
        }
        temp = p1;
    }
    else if(p2>0 && p2<=1){
        if((p1>0 && p1 <=1)){
            temp = min(p1,p2);
        }
        temp = p2;
    }
    else temp = 1;
    
    
   
    
    x_m = x+temp*vx-(striker.x+temp*striker.vx);
    y_m = y+temp*vy-(striker.y+temp*striker.vy);

    if(sqrt((x_m)*(x_m)+(y_m)*(y_m))<= striker.r+radius){
        
        nx = (x_m)/sqrt(x_m*x_m+y_m*y_m);
        ny = (y_m)/sqrt(x_m*x_m+y_m*y_m);
        
        vx += 2*nx + (striker.vx);
        vy += 2*ny + (striker.vy);
        
        x = (x + (1-temp)*vx +2*ny);
        y = (y + (1-temp)*vy -2*nx);
    
        return true;
    }
    else{
        return false;
    }
    
};


bool Puck::checkAICollision(AI ai){
    
    a = pow(vx-ai.vx,2)+pow(vy-ai.vy,2);
    b = 2*(ai.x*(ai.vx-vx) + x*(vx-ai.vx))+2*(ai.y*(ai.vy-vy) + y*(vy-ai.vy));
    c = pow(ai.x-x,2)+pow(ai.y-y,2)-pow(radius+ai.r,2);
    discriminant = b*b-4*a*c;
    p1 = (-b+sqrt(b*b-4*a*c))/(2*a);
    p2 = (-b-sqrt(b*b-4*a*c))/(2*a);
    
    
    if(p1>0 && p1 <=1){
        if(p2>0 && p2<=1){
            temp = min(p1,p2);
        }
        temp = p1;
    }
    else if(p2>0 && p2<=1){
        if((p1>0 && p1 <=1)){
            temp = min(p1,p2);
        }
        temp = p2;
    }
    else {
        temp = 1;
        
    }
    
    x_m = x+temp*vx-(ai.x+temp*ai.vx);
    y_m = y+temp*vy-(ai.y+temp*ai.vy);
    
    
    if(sqrt((x_m)*(x_m)+(y_m)*(y_m))<= ai.r+radius){
        
        nx = (x_m)/sqrt(x_m*x_m+y_m*y_m);
        ny = (y_m)/sqrt(x_m*x_m+y_m*y_m);
        
        vx += 2*nx + (ai.vx-vx);
        vy += 2*ny + (ai.vy-vy);
        
        x = (x + temp*vx +2*ny);
        y = (y + temp*vy -2*nx);
        
        return 1;
    }
    else{
        return 0;
    }
    
}









/*
 void Puck::checkStrikerCollision(Striker striker){
 x_m = x-striker.x;
 y_m = y-striker.y;
 if(sqrt(x_m*x_m+y_m*y_m)<= striker.r+radius){
 
 vx += 2*(x_m)/sqrt(x_m*x_m+y_m*y_m)+(striker.x-striker.x_past);
 vy += 2*(y_m)/sqrt(x_m*x_m+y_m*y_m)+(striker.y-striker.y_past);
 }
 }
 */

//checks for puck-striker collision next frame
/*
 void Puck::checkStrikerCollision(Striker striker){
 x_m = x+vx-(striker.x+striker.vx);
 y_m = y+vy-(striker.y+striker.vy);
 
 if(sqrt((x_m)*(x_m)+(y_m)*(y_m))<= striker.r+radius){
 nx = (x_m)/sqrt(x_m*x_m+y_m*y_m);
 ny = (y_m)/sqrt(x_m*x_m+y_m*y_m);
 vx += 2*nx+(striker.vx);
 vy += 2*ny+(striker.vy);
 
 x = (x + vx +2*ny);
 y = (y + vy -2*nx);
 }
 }
 
 /*
 void Puck::checkStrikerCollision(Striker striker){
 
 x_m = x+vx-2*striker.x+striker.x_past;
 y_m = y+vy-2*striker.y+striker.y_past;
 
 if((-radius+x-striker.x-striker.r)*(+radius+striker.r+x+vx-striker.x-striker.vx)<0 || (y-striker.y)*(y+vy-striker.y-striker.vy) <0){
 a = pow(vx-striker.vx,2)+pow(vy-striker.vy,2);
 b = 2*(striker.x*(striker.vx-vx) + x*(vx-striker.vx))+2*(striker.y*(striker.vy-vy) + y*(vy-striker.vy));
 c = pow(striker.x-x,2)+pow(striker.y-y,2)-pow(radius+striker.r,2);
 discriminant = b*b-4*a*c;
 
 if (discriminant >=0){
 
 p1 = -b+sqrt(b*b-4*a*c)/(2*a);
 p2 = -b-sqrt(b*b-4*a*c)/(2*a);
 
 cout << p1 << endl;
 cout << p2 << endl;
 
 if ((p2>=0 && p2<=1) || (p1>=0 && p1 <=1)){
 
 
 x_m = x+p2*vx-(striker.x+p2*striker.vx);
 y_m = y+p2*vy-(striker.y+p2*striker.vy);
 
 nx = (x_m)/sqrt(x_m*x_m+y_m*y_m);
 ny = (y_m)/sqrt(x_m*x_m+y_m*y_m);
 vx += 2*nx+(striker.vx);
 vy += 2*ny+(striker.vy);
 
 x = (x + vx +2*ny);
 y = (y + vy -2*nx);
 }
 
 }
 }
 
 
 else if (sqrt((x_m)*(x_m)+(y_m)*(y_m)) <= striker.r+radius){
 nx = (x_m)/sqrt(x_m*x_m+y_m*y_m);
 ny = (y_m)/sqrt(x_m*x_m+y_m*y_m);
 vx += 2*nx+(striker.x-striker.x_past);
 vy += 2*ny+(striker.y-striker.y_past);
 
 x = (x + vx +2*ny);
 y = (y + vy -2*nx);
 }
 
 }
 */
