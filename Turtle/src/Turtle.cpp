//
//  Turtle.cpp
//  Turtle
//
//  Created by Willy Chyr on 11-12-02.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "Turtle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Turtle::Turtle()
{
}

void Turtle::init( Vec2f position, Vec2f direction, float length)
{
    mStartPosition = position;
    mCurrentPosition = mStartPosition;
    mLength = length;
    
    mDirection = direction.normalized();
    
    branchNow = false;
    branched = false;
}

void Turtle::update()
{
    mDistance = mCurrentPosition - mStartPosition;
    
    mDistanceTraveled = mDistance.length();
    
    if (mDistanceTraveled < mLength ) {
        mCurrentPosition += mDirection;
    } else {
        
        if (branched){
            branchNow = false;
        }
        
        if (!branched){
            branchNow = true;
            branched = true;
        }
    }
  
}

void Turtle::draw()
{
    gl::drawLine( mStartPosition, mCurrentPosition );
}
