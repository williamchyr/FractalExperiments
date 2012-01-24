//
//  TorusTurtle.cpp
//  LSystem3D_003
//
//  Created by Willy Chyr on 1/4/12.
//  Copyright 2012 Willy Chyr. All rights reserved.
//

#include "TorusTurtle.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h" 
#include "cinder/matrix.h"
#include <iostream.h>

using namespace ci;

TorusTurtle::TorusTurtle()
{
}

void TorusTurtle::init( Vec3f startPosition, Vec3f basisRotation, Vec3f objectRotation, float outerRadius, float innerRadius, float r, float g, float b)
{
    mWorldStartPosition = startPosition;
    mLocalBasisRotation = basisRotation;
    mLocalObjectRotation = objectRotation;
    
    mFinalOuterRadius = outerRadius;
    mOuterRadius = 0.0f; 
    mFinalInnerRadius = innerRadius;
    mInnerRadius = 0.0f;
    
    mObjectEndPosition.set(0.0f, mFinalOuterRadius, 0.0f); //because cylinder's length is along the y-axis
    
    mR = r/255.0f;
    mG = g/255.0f;
    mB = b/255.0f;
    
    mTotalRotationMatrix = getTotalLocalRotation(mLocalBasisRotation, mLocalObjectRotation);
    
    mLocalCurrentPosition.set( 0.0f, 0.0f, 0.0f );
    mWorldCurrentPosition = getWorldPosition( mWorldStartPosition, mTotalRotationMatrix, mLocalCurrentPosition );
    
    mWorldEndPosition = getWorldPosition( mWorldStartPosition, mTotalRotationMatrix, mObjectEndPosition );
    
    branchNow1 = false;
    branched1 = false;
    
    branchNow2 = false;
    branched2 = false;
    
    matrixInput = false;
}

void TorusTurtle::init( Vec3f startPosition, Matrix44<float> rotationMatrix, Vec3f objectRotation, float outerRadius, float innerRadius, float r, float g, float b)
{
    mWorldStartPosition = startPosition;
    mPreviousRotationMatrix = rotationMatrix;
    
    mLocalObjectRotation = objectRotation;
    
    mFinalOuterRadius = outerRadius;
    mOuterRadius = 0.0f;
    mFinalInnerRadius = innerRadius;
    mInnerRadius = 0.0f;
    
    mObjectEndPosition.set(0.0f, mFinalOuterRadius, 0.0f); //because cylinder's length is along the y-axis
    
    mR = r/255.0f;
    mG = g/255.0f;
    mB = b/255.0f;
    
    mTotalRotationMatrix = getTotalLocalRotation( mPreviousRotationMatrix, mLocalObjectRotation);
    
    mLocalCurrentPosition.set( 0.0f, 0.0f, 0.0f );
    mWorldCurrentPosition = getWorldPosition( mWorldStartPosition, mTotalRotationMatrix, mLocalCurrentPosition );
    
    mWorldEndPosition = getWorldPosition( mWorldStartPosition, mTotalRotationMatrix, mObjectEndPosition );
    
    branchNow1 = false;
    branched1 = false;
    
    branchNow2 = false;
    branched2 = false;
    
    matrixInput = true;
}

void TorusTurtle::update()
{
    if (mOuterRadius < mFinalOuterRadius) {
        mOuterRadius += 1.0f;
        mLocalCurrentPosition.set( 0.0f, mOuterRadius, 0.0f );
    }
    
    if (mInnerRadius < mFinalInnerRadius ) {
        mInnerRadius += 1.0f;
    }
    
    mWorldCurrentPosition = getWorldPosition( mWorldStartPosition, mTotalRotationMatrix, mLocalCurrentPosition );
    
    if (mOuterRadius > mFinalOuterRadius*(2.0f/4.0f) ) {
        
        if (branched1){
            branchNow1 = false;
        }
        
        if (!branched1){
            branchNow1 = true;
            branched1 = true;
        }
    }
    
    if (mOuterRadius >= mFinalOuterRadius ) {
        
        if (branched2){
            branchNow2 = false;
        }
        
        if (!branched2){
            branchNow2 = true;
            branched2 = true;
        }
    }
}

void TorusTurtle::draw()
{
    ci::ColorA color1( CM_RGB, mR, mG, mB );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );   
    
    gl::pushMatrices();
    gl::translate( mWorldStartPosition );
    gl::multModelView(  mTotalRotationMatrix );
    
    gl::drawTorus( mOuterRadius, mInnerRadius, 24, 40 );
    
    gl::popMatrices();
    
}

Vec3f TorusTurtle::getWorldPosition( Vec3f worldStartPosition, Matrix44<float> totalLocalRotation, Vec3f localEndPosition )
{
    Matrix44 <float> m4;
    Vec3f worldEndPosition;
    
    m4 = m4.createTranslation( worldStartPosition );
    m4 = m4*totalLocalRotation;
    
    worldEndPosition = m4.transformPoint( localEndPosition );
    
    return worldEndPosition;
}

Matrix44<float> TorusTurtle::getTotalLocalRotation( Vec3f localBasisRotation, Vec3f localObjectRotation)
{
    Matrix44 <float> m4;
    
    m4.setToIdentity();
    
    m4.rotate( Vec3f(( localBasisRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );
    m4.rotate( Vec3f(0.0f, ( localBasisRotation.y/180.0f)*M_PI, 0.0f) );    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localBasisRotation.z/180.0f)*M_PI) );
    
    m4.rotate( Vec3f(( localObjectRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );    
    m4.rotate( Vec3f(0.0f, ( localObjectRotation.y/180.0f)*M_PI, 0.0f) );    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localObjectRotation.z/180.0f)*M_PI) );
    
    return m4;
    
}

Matrix44<float> TorusTurtle::getTotalLocalRotation( Matrix44<float> previousRotation, Vec3f localObjectRotation )
{
    Matrix44 <float> m4;
    
    m4.setToIdentity();
    m4 = m4*previousRotation;
    
    m4.rotate( Vec3f(( localObjectRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );    
    m4.rotate( Vec3f(0.0f, ( localObjectRotation.y/180.0f)*M_PI, 0.0f) );    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localObjectRotation.z/180.0f)*M_PI) );
    
    return m4;
}
