//
//  Turtle.cpp
//  Turtle3D_2
//
//  Created by Willy Chyr on 11-12-06.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "Turtle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Turtle::Turtle()
{
}

void Turtle::init( Vec3f position, Vec3f previousAngle, Vec3f rotateAngle, float length)
{
    mStartPosition = position;
    mCurrentPosition = mStartPosition;
    
    mFinalLength = length;
    mLength = 0.0f;
    
    mRotateAngle = rotateAngle + previousAngle;
    
    yAngleAdjusted = ((360.0f - mRotateAngle.y)/180.0f)*M_PI;
    zAngleAdjusted = ((360.0f - mRotateAngle.z)/180.0f)*M_PI;
    
    mCartesianDirection.x = cos( yAngleAdjusted )*sin( zAngleAdjusted );
    mCartesianDirection.y = cos( (mRotateAngle.z/180.0f)*M_PI );
    mCartesianDirection.z = sin( yAngleAdjusted )*sin( zAngleAdjusted );
    
    mFinalPosition = mStartPosition + mCartesianDirection * mFinalLength;
    
    branchNow = false;
    branched = false;
}

void Turtle::update()
{
    
    if (mLength < mFinalLength ) {
        mLength += 1.0f;
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
    gl::pushMatrices();
    gl::translate( mStartPosition );
    gl::rotate( mRotateAngle );
    gl::drawCylinder( 10.0f, 10.0f, mLength, 12, 1 );
    gl::popMatrices();
}