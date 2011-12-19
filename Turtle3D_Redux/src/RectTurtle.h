//
//  RectTurtle.h
//  Turtle3D_Redux
//
//  Created by Willy Chyr on 12/18/11.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"

#ifndef Turtle3D_Redux_RectTurtle_h
#define Turtle3D_Redux_RectTurtle_h

using namespace ci;

class RectTurtle{
public:
    RectTurtle();
    
    void init( Vec3f position, Vec3f size, Vec3f previousAngle, Vec3f rotateAngle);
    void update();
    void draw();
    
    Vec3f mStartPosition;
    
    Vec3f mPreviousAngle;
    Vec3f mRotateAngle;
    Vec3f mFinalAngle;
    
    Vec3f mAddRotationZ;
    Vec3f mAddRotationX;
    
    Vec3f mCurrentPosition;
    
    Vec3f mSize;
    Vec3f mFinalSize;
    
    bool branchNow1;
    bool branched1; 
    
    bool branchNow2;
    bool branched2;
    
    bool branchNow3;
    bool branched3;
};

#endif