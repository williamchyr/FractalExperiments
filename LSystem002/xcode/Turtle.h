//
//  Turtle.h
//  Turtle
//
//  Created by Willy Chyr on 11-12-02.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"

#ifndef LSystem002_Turtle_h
#define LSystem002_Turtle_h

using namespace ci;

class Turtle{
public:
    Turtle();
    
    void init( Vec2f position, float lastAngle, float newAngle, float length);
    void update();
    void draw();
    
    bool branchNow;
    bool branched;
    
    Vec2f mStartPosition;
    Vec2f mCurrentPosition;
    Vec2f mDistance;
    
    float mAngle;
    Vec2f mDirection;
    
    float mLength;
    float mDistanceTraveled;
    
    
};

#endif