//
//  RectTurtle.cpp
//  Turtle3D_Redux
//
//  Created by Willy Chyr on 12/18/11.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "RectTurtle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h" 
#include <iostream.h>

using namespace ci;

RectTurtle::RectTurtle()
{
}

void RectTurtle::init( Vec3f position, Vec3f size, Vec3f previousAngle, Vec3f rotateAngle)
{
    mStartPosition = position;
    mCurrentPosition = mStartPosition;
    
    mFinalSize = size;
    mSize.set( 0.0f, 0.0f, 0.0f);
    
    mAddRotationZ.set( 0.0f, 0.0f, 90.0f);
    mAddRotationX.set( 90.0f, 0.0f, 0.0f);
    
    mPreviousAngle = previousAngle;
    mRotateAngle = rotateAngle;
    mFinalAngle = mPreviousAngle + mRotateAngle;
    
    branchNow1 = false;
    branched1 = false;
    
    branchNow2 = false;
    branched2 = false;
    
    branchNow3 = false;
    branched3 = false;
}

void RectTurtle::update()
{
    
    if (mSize.x < mFinalSize.x ) {
        mSize.x += 1.0f;
    }
    
    if (mSize.y < mFinalSize.y ) {
        mSize.y += 1.0f;
    }
    
    if (mSize.z < mFinalSize.z ) {
        mSize.z += 1.0f;
    }
    
    if (mSize.x >= mFinalSize.x ) {
        
        if (branched1){
            branchNow1 = false;
        }
        
        if (!branched1){
            branchNow1 = true;
            branched1 = true;
        }
    }
    
}

void RectTurtle::draw()
{   
    ci::ColorA color1( CM_RGB, 1.0f, 1.0f, 0.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );

    gl::pushMatrices();
    gl::translate( mStartPosition );
    gl::rotate( mFinalAngle );
    gl::drawCube( Vec3f(0.0f, 0.0f, 0.0f), mSize ); 
    gl::drawLine( Vec3f(-500.0f, 0.0f, 0.0f), Vec3f(500.0f, 0.0f, 0.0f) );
    gl::drawLine( Vec3f(0.0f, -500.0f, 0.0f), Vec3f(0.0f, 500.0f, 0.0f) );
    gl::drawLine( Vec3f(0.0f, 0.0f, -500.0f), Vec3f(0.0f, 0.0f, 500.0f) );
    gl::popMatrices();
}