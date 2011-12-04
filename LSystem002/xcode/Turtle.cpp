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

void Turtle::init( Vec2f position, float lastAngle, float newAngle, float length)
{
    mStartPosition = position;
    mCurrentPosition = mStartPosition;
    mLength = length;   
    
    mAngle = lastAngle + newAngle;
    mDirection.set( cos(mAngle), sin(mAngle) );
    
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
    glColor3f(1.0f - mStartPosition.y/800.0f, 1.0f, mStartPosition.y/800.0f );
    gl::drawLine( mStartPosition, mCurrentPosition );

}