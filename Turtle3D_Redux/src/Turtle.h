//
//  Turtle.h
//  Turtle3D_Redux
//
//  Created by Willy Chyr on 12/18/11.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"

#ifndef Turtle3D_Redux_Turtle_h
#define Turtle3D_Redux_Turtle_h

using namespace ci;

class Turtle{
public:
    Turtle();
    
    void init( Vec3f position, Vec3f previousAngle, Vec3f rotateAngle, float length, float radius);
    
    void init( Vec3f position, Vec3f previousAngle, Vec3f rotateAngle, int rectFaceNumber, float length, float radius);
    
    void update();
    //void update(float rotateX, float rotateY, float rotateZ);
    void draw();
    Vec3f cartesianConvert( Vec3f angle );
    
    Vec3f mStartPosition;
    Vec3f mCurrentPosition;
    
    Vec3f mPreviousAngle;
    Vec3f mRotateAngle;
    Vec3f mAddAngle;
    Vec3f mFinalAngle;
    
    Vec3f mStartAngle;
    
    float xAngleAdjusted, zAngleAdjusted, yAngleAdjusted;
    Vec3f mCartesianDirection;
    Vec3f mFinalPosition;
    
    float mLength;
    float mFinalLength;
    
    float mRadius;
    
    bool branchNow1;
    bool branched1; 
    
    bool branchNow2;
    bool branched2;
    
    bool branchNow3;
    bool branched3;

};

#endif
