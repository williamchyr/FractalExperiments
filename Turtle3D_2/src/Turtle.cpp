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

void Turtle::init( Vec3f position, Vec3f previousAngle, Vec3f rotateAngle, float length, float radius)
{
    mStartPosition = position;
    mCurrentPosition = mStartPosition;
    
    mFinalLength = length;
    mLength = 0.0f;
    
    mRadius = radius;
    
    mRotateAngle = rotateAngle + previousAngle;
    
    yAngleAdjusted = ((360.0f - mRotateAngle.y)/180.0f)*M_PI;
    zAngleAdjusted = ((360.0f - mRotateAngle.z)/180.0f)*M_PI;
    
    mCartesianDirection.x = cos( yAngleAdjusted )*sin( zAngleAdjusted );
    mCartesianDirection.y = cos( (mRotateAngle.z/180.0f)*M_PI );
    mCartesianDirection.z = sin( yAngleAdjusted )*sin( zAngleAdjusted );
    
    mFinalPosition = mStartPosition + mCartesianDirection * mFinalLength;
    
    branchNow1 = false;
    branched1 = false;
    
    branchNow2 = false;
    branched2 = false;
    
    branchNow3 = false;
    branched3 = false;
}

void Turtle::update()
{
    
    if (mLength < mFinalLength ) {
        mLength += 1.0f;
        mCurrentPosition += mCartesianDirection;
    }
    
    if (mLength > mFinalLength*(1.0f/4.0f) ) {
        
        if (branched1){
            branchNow1 = false;
        }
        
        if (!branched1){
            branchNow1 = true;
            branched1 = true;
        }
    }
    
    if (mLength > mFinalLength*(2.0f/4.0f) ) {
        
        if (branched2){
            branchNow2 = false;
        }
        
        if (!branched2){
            branchNow2 = true;
            branched2 = true;
        }
    }
    
    if (mLength > mFinalLength*(3.0f/4.0f) ) {
        
        if (branched3){
            branchNow3 = false;
        }
        
        if (!branched3){
            branchNow3 = true;
            branched3 = true;
        }
    }
    
}

void Turtle::draw()
{   
    gl::pushMatrices();
    gl::translate( mStartPosition );
    gl::rotate( mRotateAngle );
    gl::drawCylinder( mRadius, mRadius, mLength, 12, 1 );
    gl::popMatrices();
}