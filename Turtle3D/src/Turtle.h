//
//  Turtle.h
//  Turtle3D
//
//  Created by Willy Chyr on 12/23/11.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/matrix.h"

#ifndef Turtle3D_Turtle_h
#define Turtle3D_Turtle_h

using namespace ci;
using namespace std;

class Turtle{
public:
    Turtle();
    
    void init( Vec3f startPosition, Vec3f basisRotation, Vec3f objectRotation, float length, float radius, float r, float g, float b);
    void init( Vec3f startPosition, Matrix44<float> rotationMatrix, Vec3f objectRotation, float length, float radius, float r, float g, float b);
    
    void update();
    void draw();
    
    // GET POSITION IN WORLD COORDINATES 
    Vec3f getWorldPosition( Vec3f localStartPosition, Matrix44<float> totalLocalRotation, Vec3f localEndPosition );
    
    // GET TOTAL ROTATION MATRIX 
    //using two angles
    Matrix44<float> getTotalLocalRotation( Vec3f localBasisRotation, Vec3f localObjectRotation );
    
    //using one matrix and one angle
    Matrix44<float> getTotalLocalRotation( Matrix44<float> previousRotation, Vec3f localObjectRotation);
    
    Vec3f mWorldStartPosition; //where the local basis translate to
    Vec3f mLocalBasisRotation; //How the local basis is rotated
    Vec3f mLocalObjectRotation; //how the object is rotated in relation to the local basis
    
    Vec3f mObjectEndPosition;
    Vec3f mWorldEndPosition; //This gets passed onto next object as a parameter
    
    Vec3f mLocalCurrentPosition;
    Vec3f mWorldCurrentPosition; //This may get passed onto next object as a parameter
    
    Matrix44 <float> mPreviousRotationMatrix;
    Matrix44 <float> mTotalRotationMatrix; // This gets passed onto next object as a parameter
    
    float mRadius;
    float mLength;
    float mFinalLength;
    
    bool branchNow1;
    bool branched1; 
    
    bool branchNow2;
    bool branched2;
    
    bool branchNow3;
    bool branched3;
    
    float mR, mG, mB;
    
    bool matrixInput;
};

#endif
