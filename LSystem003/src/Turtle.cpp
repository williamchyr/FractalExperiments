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
    
    branchNow1 = false;
    branched1 = false;
    
    branchNow2 = false;
    branched2 = false;
    
    branchNow3 = false;
    branched3 = false;
    
    branchNow4 = false;
    branched4 = false;
}

void Turtle::update()
{
    mDistance = mCurrentPosition - mStartPosition;
    
    mDistanceTraveled = mDistance.length();
    
    if (mDistanceTraveled < mLength ) {
        mCurrentPosition += mDirection;
    } 
    
    // When the branches emerge
    
    if (mDistanceTraveled > mLength*(5.0/6.0f) ) {
        
        if (branched1){
            branchNow1 = false;
        }
        
        if (!branched1){
            branchNow1 = true;
            branched1 = true;
        }
    }
    
    if (mDistanceTraveled > mLength*(1.0/6.0) ) {
        
        if (branched2){
            branchNow2 = false;
        }
        
        if (!branched2){
            branchNow2 = true;
            branched2 = true;
        }
    }
    
    if (mDistanceTraveled >= mLength*(2.0/6.0) ) {
        
        if (branched3){
            branchNow3 = false;
        }
        
        if (!branched3){
            branchNow3 = true;
            branched3 = true;
        }
    }
    
    if (mDistanceTraveled >= mLength*(3.0/6.0)) {
        
        if (branched4){
            branchNow4 = false;
        }
        
        if (!branched4){
            branchNow4 = true;
            branched4 = true;
        }
    }

}

void Turtle::draw()
{
    glColor3f(1.0f - mStartPosition.y/800.0f, mStartPosition.y/800.0f, 1.0f );
    gl::drawLine( mStartPosition, mCurrentPosition );
    
}