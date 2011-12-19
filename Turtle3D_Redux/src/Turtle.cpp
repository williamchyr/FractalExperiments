//
//  Turtle.cpp
//  Turtle3D_Redux
//
//  Created by Willy Chyr on 12/18/11.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "Turtle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h" 
#include <iostream.h>

using namespace ci;

Turtle::Turtle()
{
}

void Turtle::init( Vec3f position, Vec3f previousAngle, Vec3f rotateAngle, float length, float radius)
{
    mStartPosition = position;
    
    mPreviousAngle = previousAngle;
    mRotateAngle = rotateAngle;
    mFinalAngle = mPreviousAngle + mRotateAngle;
    
    mLength = 0.0f;
    mFinalLength = length;
    
    mRadius = radius;
    
    mCartesianDirection = cartesianConvert( mFinalAngle);
    mFinalPosition = mStartPosition + mCartesianDirection * mFinalLength;
    
    branchNow1 = false;
    branched1 = false;
}

void Turtle::init( Vec3f position, Vec3f previousAngle, Vec3f rotateAngle, int rectFaceNumber, float length, float radius)
{
    cout << "I AM HERE \n";
    mStartPosition = position;
    mCurrentPosition = mStartPosition;
    
    mLength = 0.0f;
    mFinalLength = length;
    
    mPreviousAngle = previousAngle;
    mRotateAngle = rotateAngle;
    mFinalAngle = mPreviousAngle + mRotateAngle;
    
    switch( rectFaceNumber ) {
        case 1: //top
            mFinalAngle += Vec3f(0.0f, 0.0f, 0.0f);
            break;
            
        case 2: //left
            mFinalAngle += Vec3f(0.0f, 0.0f, 90.0f);
            break;
            
        case 3: //bottom
            mFinalAngle += Vec3f(0.0f, 0.0f, 180.0f);
            break;
            
        case 4: //right
            mFinalAngle += Vec3f(0.0f, 0.0f, 270.0f);
            break;
            
        case 5: //front
            mFinalAngle += Vec3f(90.0f, 0.0f, -mRotateAngle.z);
            break;
            
        case 6: //back
            mFinalAngle += Vec3f(270.0f, 0.0f, -mRotateAngle.z);
            break;
    }
    
    mCartesianDirection = cartesianConvert( mFinalAngle );
    mFinalPosition = mStartPosition + mCartesianDirection*mFinalLength;

    mRadius = radius;
    
    branchNow1 = false;
    branched1 = false;
}

void Turtle::update( float rotateX, float rotateY, float rotateZ)
{
    mAddAngle.set( rotateX, rotateY, rotateZ);
    mFinalAngle = mPreviousAngle + mRotateAngle + mAddAngle;
    
    mCartesianDirection = cartesianConvert( mFinalAngle);
    mFinalPosition = mStartPosition + mCartesianDirection * mFinalLength;
     
    if (mLength < mFinalLength) {
        mLength += 1.0f;
        mCurrentPosition += mCartesianDirection;
    }
    
    if (mLength > mFinalLength*(3.0f/4.0f) ) {
        
        if (branched1){
            branchNow1 = false;
        }
        
        if (!branched1){
            branchNow1 = true;
            branched1 = true;
        }
    }
}

void Turtle::update()
{   
    if (mLength < mFinalLength) {
        mLength += 1.0f;
        mCurrentPosition += mCartesianDirection;
    }
    
    if (mLength > mFinalLength*(3.0f/4.0f) ) {
        
        if (branched1){
            branchNow1 = false;
        }
        
        if (!branched1){
            branchNow1 = true;
            branched1 = true;
        }
    }
}

void Turtle::draw()
{
    gl::pushMatrices();
    gl::translate( mStartPosition );
    gl::rotate( mFinalAngle);
    gl::drawCylinder( mRadius, mRadius, mLength, 12, 1 );
    gl::popMatrices();
}

Vec3f Turtle::cartesianConvert( Vec3f angle )
{
    //Converts angle from spherical to cartesian coordinate 
    
    float xAngleAdjust, zAngleAdjust;
    Vec3f cartesianDirection;
    
    xAngleAdjust = ((angle.x)/180.0f)*M_PI;
    zAngleAdjust = ((angle.z)/180.0f)*M_PI;
    
    cartesianDirection.x = sin(2*M_PI- zAngleAdjust);
    cartesianDirection.y = cos(2*M_PI - xAngleAdjust)*cos( zAngleAdjust);
    cartesianDirection.z = sin(xAngleAdjust)*cos(zAngleAdjust);

    return cartesianDirection;
}