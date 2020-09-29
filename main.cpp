
//  main.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-09-30.
//  Copyright © 2018 Clarity. All rights reserved.
//
//
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "Screen.h"
#include "Puck.h"
#include "Edges.h"
#include "Striker.h"
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

const int SCREEN_WIDTH = 825;
const int SCREEN_HEIGHT  = 369;
const int corner_rad = 40;
const float puck_rad = 15;
const float striker_rad = 24;
const int length_data = 10;
string savepath = "/Users/MyComputer/Desktop/";


int main() {
    
    //initialize data stream to csv file
    ofstream myfile;
    myfile.open (savepath+"Data.csv");
    myfile << "pVX"<<","<<"pVY"<<","<<"pX"<<","<<"pY"<<","<<"AIX"<<","<<"AIY"<<","<<"AIVY"<<","<<"success"<<endl;
    
    //create simulation objects
    Screen screen(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    Edges edges(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, corner_rad);
    Puck puck(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, puck_rad, edges);
    Striker striker(striker_rad, edges);
    AI ai(edges, striker_rad);
    
    //initialize screen
    if(screen.init() == false) {
        cout << "Error initialising SDL." << endl;
        return 1;
    }
    
    SDL_Renderer *renderer = screen.getRenderer();      //get variable renderer to use locally
    
    SDL_Event event;        //create SDL event
    puck.changeDirec(0,0);      //set direction
    
    
    
    
    float data[10000][8];
    
    float gamma;
    float beta;
    int bounces;
    int yfinal;
    int posOrNeg;
    
    int net_L = 100;
    int net_R = 200;
    int straight_thresh = 50;
    int distance_from_corner = 20;
    float theta;
    float phi;

    
    
    bool success;
    int quit = 0; int time; int count = 0;   //declare loop variables
    while (count<length_data){
        
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                quit = 1;
        }
        
        // generate quasi-random starting positions for algo evaluation
        puck.vx =  ((float) rand()/RAND_MAX)*18+2;
        puck.vy = (((float) rand()/RAND_MAX)*2-1)*20;
        puck.x = ((float) rand()/RAND_MAX)*(SCREEN_WIDTH-2*puck_rad)/2+puck_rad;
        puck.y = ((float) rand()/RAND_MAX)*(SCREEN_HEIGHT-2*puck_rad)+puck_rad;
        ai.x = (SCREEN_WIDTH)*3/4;
        ai.y = ((float) rand()/RAND_MAX)*(SCREEN_HEIGHT-2*striker_rad)+striker_rad;
        ai.vx = 0;
        ai.vy = 0;


        // save puck data
        data[count][0] = puck.vx;
        data[count][1] = puck.vy;
        data[count][2] = puck.x;
        data[count][3] = puck.y;

        //calculate useful values
        gamma = abs((ai.x-puck.x)/puck.vx);
        posOrNeg = abs(puck.vy)/(-puck.vy); //if posOrNeg is pos then vy is up if vy is posOrNeg is neg then vy is down
        beta = (gamma*puck.vy); //the -posOrNeg*striker_rad/2 is an arbitrary correction factor
        
        if(puck.y+beta<0){
            bounces = (int) (abs(beta)-puck.y)/SCREEN_HEIGHT+1;
        }else if(puck.y+beta>SCREEN_HEIGHT){
            bounces = (int) (abs(beta)-(SCREEN_HEIGHT-puck.y))/SCREEN_HEIGHT+1;
        }else{
            bounces = 0;
        }

        //predict y position where puck and striker will intersect
        yfinal = abs((pow(-1,remainder(bounces+1,2))-posOrNeg)/2)*SCREEN_HEIGHT-posOrNeg*pow(-1,remainder(bounces,2))*(abs(beta)-posOrNeg*puck.y+((posOrNeg-1)/2)*SCREEN_HEIGHT-(bounces-1)*SCREEN_HEIGHT);
            ai.vy = (yfinal-ai.y)/gamma;
        
        //impose speed restrictions (based on reality) on striker
        if (abs(ai.vy)>20){
            ai.vy = -posOrNeg*20;
        }
        
        //save initial x,y and chosen vy
        data[count][4] = ai.x;
        data[count][5] = ai.y;
        data[count][6] = ai.vy;
        
        
        
        
        /*
        data[count][0] = puck.vx;
        data[count][1] = puck.vy;
        data[count][2] = puck.x;
        data[count][3] = puck.y;

        data[count][4] = ai.y;
        data[count][5] = ai.vy;
        */
        /*
        if(sqrt(pow(ai.y-net_L,2)+pow(ai.x,2)) < sqrt(pow(net_R-ai.y,2)+pow(ai.x,2))){
            //shoot towards right
            if((net_R-ai.y) > straight_thresh){
                //shoot straight and to the right of the striker
                theta = atan((puck.y-net_R)/(puck.x));
                puck.vy = 10*sin(theta);
                puck.vx = -10*cos(theta);
            }else{
                //bounce off right wall
                theta = atan((puck.y-net_R)/(puck.x));
                phi = atan((2*SCREEN_HEIGHT-(net_R-puck.y))/puck.x)-theta;
                puck.vy = 10*sin(phi);
                puck.vx = 10*cos(phi);
            }
        }else{
            //shoot towards left
            if((ai.y-net_L) > straight_thresh){
                //shoot straight and to the left of the striker
                theta = atan((net_L-puck.y)/(puck.x));
                puck.vy = 10*sin(theta);
                puck.vx = -10*cos(theta);
            }else{
                //bounce off left wall
                theta = atan((net_L-puck.y)/(puck.x));
                phi = atan((2*SCREEN_HEIGHT-(puck.y-net_L))/puck.x)-theta;
                puck.vy = 10*sin(phi);
                puck.vx = -10*cos(phi);
            }
        }
         */
        /*
        while(puck.vx > 0){
            
            time = SDL_GetTicks();
            
            
            puck.checkWallCollision(edges);
            success = puck.checkStrikerCollision(striker);
            
            if(puck.vx > 0.1){
                break;
            }
            puck.move();
            
            
             edges.Draw(renderer);
             filledCircleColor(renderer, puck.x, puck.y, puck_rad, 0xFF0000FF);
             filledCircleColor(renderer, ai.x, ai.y, ai.r, 0xFFFFFFFF);
             SDL_RenderDrawLine(renderer, 0, 100, 5, 100);
             SDL_RenderDrawLine(renderer, 0, 200, 5, 200);
             screen.refresh();       //update screen
            
        }
    
            /*time = SDL_GetTicks()-time;
             if (time<20){
             SDL_Delay(time);
             }
             }
        
        
        
        */
        
        //check for collisions then move
        data[count][7] = 0;
        
        while(ai.x > puck.x){

            time = SDL_GetTicks();
            puck.checkWallCollision();
            success = puck.checkAICollision(ai);
            
            if(success == true ){
                data[count][7] = 1;
                break;
            }
            else if(puck.vx <= 0.1){
                //catch rare case check collision misses success
                data[count][7] = 0.5;
                break;
            }
            
            // move puck and ai
            puck.move();
            ai.MoveAI();
            
            // animate
            edges.Draw(renderer);
            filledCircleColor(renderer, puck.x, puck.y, puck_rad, 0xFF0000FF);
            filledCircleColor(renderer, ai.x, ai.y, ai.r, 0xFFFFFFFF);
            screen.refresh();       //update screen
             
        }
        
        
    
        
//        if (data[count][6] == 0){
//            cout<<10000000<<endl;
//            cout<<data[count][0] <<endl; //puck.vx
//            cout<<data[count][1]<<endl;     //puck.vy
//            cout<<data[count][2] <<endl;    //puck.x
//            cout<<data[count][3] <<endl;    //puck.y
//            cout<<data[count][4] <<endl;    //ai.y
//            cout<<data[count][5] << endl;   //ai.vy
//
//
//            puck.vx = data[count][0]; //puck.vx
//            puck.vy = data[count][1];     //puck.vy
//            puck.x = data[count][2];    //puck.x
//            puck.y = data[count][3];    //puck.y
//            ai.y = data[count][4];    //ai.y
//            ai.vy = data[count][5];   //ai.vy
//        }
        /*
        
            while(ai.x > puck.x){
                
                
                puck.checkWallCollision(edges);
                success = puck.checkAICollision(ai);
                puck.move();
                ai.MoveAI(edges);
                edges.Draw(renderer);
                filledCircleColor(renderer, puck.x, puck.y, puck_rad, 0xFF0000FF);
                filledCircleColor(renderer, ai.x, ai.y, ai.r, 0xFFFFFFFF);
                screen.refresh();
            }
*/
        

        myfile << data[count][0]<<","<<data[count][1]<<","<<data[count][2]<<","<<data[count][3]<<","<<data[count][4]<<","<<data[count][5]<<","<<data[count][6]<<","<<data[count][7]<<endl;
        
        count ++;
        
    }
    
   
    cout<<"Done"<<endl;
    
    //close window and file
    screen.close();
    myfile.close();
    return 0;
    
    
}



