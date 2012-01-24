//
//  CuboidTurtle.h
//  LSystem3D_003
//
//  Created by Willy Chyr on 1/4/12.
//  Copyright 2012 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/matrix.h"

#ifndef LSystem3D_003_CuboidTurtle_h
#define LSystem3D_003_CuboidTurtle_h

using namespace ci;
using namespace std;

class CuboidTurtle{
public:
    CuboidTurtle();
    
    void init( Vec3f startPosition, Vec3f basisRotation, Vec3f objectRotation, Vec3f size, bool stroked, float r, float g, float b);
    void init( Vec3f startPosition, Matrix44<float> rotationMatrix, Vec3f objectRotation, Vec3f size, bool stroked, float r, float g, float b);
    
    void update();
    void draw();
    
    // GET POSITION IN WORLD COORDINATES 
    Vec3f getWorldPosition( Vec3f localStartPosition, Matrix44<float> totalLocalRotation, Vec3f localEndPosition );
    
    // GET TOTAL ROTATION MATRIX 
    //using two angles
    Matrix44<float> getTotalLocalRotation( Vec3f localBasisRotation, Vec3f localObjectRotation );
    
    //using one matrix and one angle
    Matrix44<float> getTotalLocalRotation( Matrix44<float> previousRotation, Vec3f localObjectRotation);
    
    Vec3f mWorldStartPosition; //where the local basis translate to. // For cylinders, this is what is passed on to them
    Vec3f mLocalBasisRotation; //How the local basis is rotated
    Vec3f mLocalObjectRotation; //how the object is rotated in relation to the local basis
    
    Vec3f mObjectEndPosition;
    Vec3f mWorldEndPosition; //gets passed on if it's another sphere or rectangle.
    
    Vec3f mLocalCurrentPosition;
    Vec3f mWorldCurrentPosition; //This may get passed onto next object as a parameter
    
    Matrix44 <float> mPreviousRotationMatrix;
    Matrix44 <float> mTotalRotationMatrix; // This gets passed onto next object as a parameter
    
    float mLength;
    float mFinalLength;
    
    Vec3f mSize;
    Vec3f mFinalSize;
    
    bool branchNow1;
    bool branched1; 
    
    bool branchNow2;
    bool branched2;
    
    bool branchNow3;
    bool branched3;
    
    float mR, mG, mB;
    
    bool mStroked;
    bool matrixInput;
};

#endif