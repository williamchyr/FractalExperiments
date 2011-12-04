//
//  Turtle.h
//  Turtle
//
//  Created by Willy Chyr on 11-12-02.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"

#ifndef Turtle_Turtle_h
#define Turtle_Turtle_h

using namespace ci;

class Turtle{
  public:
    Turtle();
    
    void init( Vec2f position, Vec2f direction, float length);
    void update();
    void draw();
    
    bool branchNow;
    bool branched;
    
    Vec2f mStartPosition;
    Vec2f mCurrentPosition;
    Vec2f mDistance;
    
    Vec2f mDirection;
    float mLength;
    float mDistanceTraveled;
    
    
};

#endif
