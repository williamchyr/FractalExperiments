//
//  Turtle.h
//  Turtle3D_2
//
//  Created by Willy Chyr on 11-12-06.
//  Copyright 2011 Willy Chyr. All rights reserved.
//


#include "cinder/Vector.h"
#include "cinder/Color.h"

#ifndef Turtle3D_2_Turtle_h
#define Turtle3D_2_Turtle_h

using namespace ci;

class Turtle{
public:
    Turtle();
    
    void init( Vec3f position, Vec3f rotateAngle, float length);
    void update();
    void draw();
    
    Vec3f mStartPosition;
    Vec3f mRotateAngle;
    
    Vec3f mCurrentPosition;
    
    float yAngleAdjusted, zAngleAdjusted;
    Vec3f mCartesianDirection;
    Vec3f mFinalPosition;
    
    float mLength;
    float mFinalLength;
    
    bool branchNow;
    bool branched;    
};

#endif
