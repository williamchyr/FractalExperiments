#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include "cinder/matrix.h"
#include "cinder/gl/Texture.h"
#include "Turtle.h"
#include "SphereTurtle.h"
#include "CuboidTurtle.h"
#include "TorusTurtle.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

//LIGHTS
GLfloat mat_diffuse[]		= { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 0.7 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

//FOG
GLfloat density = 0.0004;
GLfloat fogColor[4] = {1.0, 1.0, 1.0, 1.0};

class LSystem3D_003App : public AppBasic {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf   mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    float camAngle;
    
    bool mAutoCam;
    
    // ROTATION
    float xAngle, yAngle, zAngle;
    float mDirectional;
    
    // TEXTURE
    gl::Texture		mTexture;	
    gl::Texture     mTexture2;
    
    // INITIAL
    Turtle originalTurtle1;
    Turtle originalTurtle2;
    Turtle originalTurtle3;
    Turtle originalTurtle4;
    
    SphereTurtle originalSphereTurtle1;
    CuboidTurtle originalCuboidTurtle1;
    CuboidTurtle originalCuboidTurtle2;
    TorusTurtle originalTorusTurtle1, originalTorusTurtle2;
    
    Vec3f originalPosition;
    Vec3f originalPreviousRotation;
    Vec3f originalRotation1;
    Vec3f originalRotation2;
    Vec3f originalRotation3;
    Vec3f originalRotation4;

    float originalLength;
    float originalRadius;
    
    // ORIGINAL TURTLE
    vector<Turtle> mTurtlesA;
    vector<Turtle> mTurtlesB;
    
    // CUBOID TURTLE
    vector<CuboidTurtle> mCuboidTurtlesA;
    vector<CuboidTurtle> mCuboidTurtlesB;
    
    // TORUS TURTLE
    vector<TorusTurtle> mTorusTurtlesA;
    
    // SPHERE TURTLE
    vector<SphereTurtle> mSphereTurtlesA;
    vector<SphereTurtle> mSphereTurtlesB;

    Vec3f direction1;
    Vec3f direction2;
    Vec3f direction3;
    Vec3f direction4;
    Vec3f direction5;
    Vec3f direction6;
    Vec3f direction7, direction8, direction9;
    
    // COLORS
    float r_turtleA, g_turtleA, b_turtleA;
    float r_turtleB, g_turtleB, b_turtleB;
    float r_cuboidA, g_cuboidA, b_cuboidA;
    float r_cuboidB, g_cuboidB, b_cuboidB;
    float r_torusA, g_torusA, b_torusA;
    float r_sphereA, g_sphereA, b_sphereA;
    float r_sphereB, g_sphereB, b_sphereB;
    
    // AXIS
    bool mShowAxis;
    
    // SAVING
    bool mSaveFrame;

};

void LSystem3D_003App::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void LSystem3D_003App::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1650.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 4000.0f );
    
    camAngle = 0.0f;
    
    mAutoCam = true;
    
    // CAMERA ROTATION
    xAngle = 0.0f;
    yAngle = 0.0f;
    zAngle = 0.0f;
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=2600.0 step=50.0 keyIncr=s keyDecr=w" );
    mParams.addParam( "X Angle", &xAngle, "min=0.0 max=360.0 step=5.0 keyIncr=r keyDecr=f" );
    mParams.addParam( "Y Angle", &yAngle, "min=0.0 max=360.0 step=5.0 keyIncr=t keyDecr=g" );
    mParams.addParam( "Z Angle", &zAngle, "min=0.0 max=360.0 step=5.0 keyIncr=y keyDecr=h" );
    
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    // TEXTURE
    mTexture = gl::Texture( loadImage( loadResource("wood.jpg") ) );
    mTexture2 = gl::Texture( loadImage( loadResource("marble.jpg") ) );
    
    // LIGHTS
    mDirectional = 0.0f;
    
    // COLORS
    r_turtleA = 2.0f;
    g_turtleA = 123.0f;
    b_turtleA = 127.0f;
    
    r_turtleB = 86.0f;
    g_turtleB = 47.0f;
    b_turtleB = 79.0f;
    
    r_cuboidA = 255.0f;
    g_cuboidA = 165.0f;
    b_cuboidA = 136.0f;
    
    r_cuboidB = 214.0f;
    g_cuboidB = 41.0f;
    b_cuboidB = 87.0f;
    
    r_torusA = 72.0f;
    g_torusA = 121.0f;
    b_torusA = 184.0f;
    
    r_sphereA = 2.0f;
    g_sphereA = 123.0f;
    b_sphereA = 127.0f;
    
    r_sphereB = 191.0f;
    g_sphereB = 30.0f;
    b_sphereB = 98.0f;
    
    // INITIAL STARTING TURTLE
    originalPosition.set( 0.0f, -200.0f, 0.0f);
    originalPreviousRotation.set( 50.0f, 0.0f, 60.0f );
    originalRotation1.set( 0.0f, 0.0f, 0.0f);
    originalRotation2.set( 50.0f, 0.0f, 145.0f );
    originalRotation3.set( 0.0f, 0.0f, 180.0f );
    originalRotation4.set( 0.0f, 0.0f, 270.0f );
    originalLength = 1000.0f;
    originalRadius = 40.0f;
   
     /*
    originalTurtle1.init( originalPosition, originalPreviousRotation, originalRotation1, originalLength, originalRadius, r_turtleA, g_turtleA, b_turtleA );
    mTurtlesA.push_back( originalTurtle1 );
    
    originalTurtle2.init( originalPosition, originalPreviousRotation, originalRotation2, originalLength, originalRadius, r_turtleA, g_turtleA, b_turtleA);
    mTurtlesA.push_back( originalTurtle2 );
   */
    
    originalSphereTurtle1.init( originalPosition, originalPreviousRotation, originalRotation1, originalLength*0.3f, false, r_sphereA, g_sphereA, b_sphereA );
    mSphereTurtlesA.push_back( originalSphereTurtle1 );
   
     /*
    originalCuboidTurtle1.init( originalPosition, originalPreviousRotation, originalRotation1, Vec3f( originalLength*0.3f, originalLength*0.3f, originalLength*0.3f), false, r_cuboidA, g_cuboidA, b_cuboidA);
    mCuboidTurtlesA.push_back( originalCuboidTurtle1);
    
    originalCuboidTurtle2.init( originalPosition, originalPreviousRotation, originalRotation2, Vec3f( originalLength*0.4f, originalLength*0.7f, originalLength*0.1f), false, r_cuboidA, g_cuboidA, b_cuboidA);
    mCuboidTurtlesA.push_back( originalCuboidTurtle2);
    
    originalTorusTurtle1.init( originalPosition, originalPreviousRotation, originalRotation1, originalLength, originalRadius, r_torusA, g_torusA, b_torusA );
    mTorusTurtlesA.push_back( originalTorusTurtle1);
    
    originalTorusTurtle2.init( originalPosition, originalPreviousRotation, originalRotation2, originalLength, originalRadius, r_torusA, g_torusA, b_torusA );
    mTorusTurtlesA.push_back( originalTorusTurtle2);
    */
    direction1.set( 0.0f, 0.0f, 0.0f );
    direction2.set( 50.0f, 0.0f, 145.0f);
    direction3.set( 90.0f, 55.0f, 90.0f);
    direction4.set( 100.0f, 35.0f, 180.0f );
    direction5.set( 0.0f, 125.0f, 167.0f );
    direction6.set( 40.0f, 0.0f, 0.0f);
    direction7.set( 70.0f, 15.0f, 30.0f );
    direction8.set( 10.0f, 35.0f, 140.0f);
    direction9.set( 120.0f, 40.0f, 80.0f );
    
    // AXIS
    mShowAxis = false;
    
    // SAVING
    mSaveFrame = true;
    
    // FOG
    glEnable (GL_FOG);
    glFogi (GL_FOG_MODE, GL_EXP2);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST); 

}

void LSystem3D_003App::mouseDown( MouseEvent event )
{
}

void LSystem3D_003App::keyDown( KeyEvent event )
{
    if( event.getChar() == 'a' ){
		mShowAxis = ! mShowAxis;
	}
    
    if( event.getChar() == 'k' ){
		mSaveFrame = ! mSaveFrame;
	}
    
    if( event.getChar() == 'l' ){
		mAutoCam = ! mAutoCam;
	}
}

void LSystem3D_003App::update()
{
    //UPDATE CAMERA
    if (mAutoCam) {
        camAngle += M_PI/750.0f;
        mEye = Vec3f( mCameraDistance * sin(camAngle), 0.0f, mCameraDistance * cos( camAngle ) );
    } else {
        mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    }
    
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    
    //UDPATE TURTLE A
    for (int i = 0; i < mTurtlesA.size(); i++ ) {
        mTurtlesA[i].update();

        if (mTurtlesA[i].branchNow3 ){
            if ( mTurtlesA[i].mFinalLength > 10.0f)  {

                SphereTurtle newSphereTurtle;
                newSphereTurtle.init( mTurtlesA[i].mWorldEndPosition, mTurtlesA[i].mTotalRotationMatrix, direction5, mTurtlesA[i].mFinalLength*0.2f, false, r_sphereB, g_sphereB, b_sphereB );
                mSphereTurtlesB.push_back( newSphereTurtle ); 
                
                CuboidTurtle newCuboidTurtle;
                newCuboidTurtle.init( mTurtlesA[i].mWorldEndPosition, mTurtlesA[i].mTotalRotationMatrix, direction2, Vec3f(mTurtlesA[i].mFinalLength*0.4f, mTurtlesA[i].mFinalLength*0.7f, mTurtlesA[i].mFinalLength*0.1f), false, r_cuboidA, g_cuboidA, b_cuboidA );
                mCuboidTurtlesA.push_back( newCuboidTurtle ); 

            }
        }
            
    }
    
    //UDPATE TURTLE B
    for (int i = 0; i < mTurtlesB.size(); i++ ) {
        mTurtlesB[i].update();

        if (mTurtlesB[i].branchNow3 ){
            if ( mTurtlesB[i].mFinalLength > 10.0f)  {
                
                SphereTurtle newSphereTurtle;
                newSphereTurtle.init( mTurtlesB[i].mWorldEndPosition, mTurtlesB[i].mTotalRotationMatrix, direction1, mTurtlesB[i].mFinalLength*0.17f, false, r_sphereA, g_sphereA, b_sphereA );
                mSphereTurtlesA.push_back( newSphereTurtle ); 
                
               
                
            }
        }
    }
    
    //UDPATE SPHERE TURTLE A
    for (int i = 0; i < mSphereTurtlesA.size(); i++ ) {
        mSphereTurtlesA[i].update();
        
        if (mSphereTurtlesA[i].branchNow2 ){
            if ( mSphereTurtlesA[i].mFinalRadius > 10.0f)  {
                Turtle newTurtle1;
                newTurtle1.init( mSphereTurtlesA[i].mWorldStartPosition, mSphereTurtlesA[i].mTotalRotationMatrix, direction1, mSphereTurtlesA[i].mFinalRadius*2.3f, mSphereTurtlesA[i].mFinalRadius*0.15f, r_turtleA, g_turtleA, b_turtleA ); 
                mTurtlesA.push_back( newTurtle1 );
                
                Turtle newTurtle2;
                newTurtle2.init( mSphereTurtlesA[i].mWorldStartPosition, mSphereTurtlesA[i].mTotalRotationMatrix, direction2, mSphereTurtlesA[i].mFinalRadius*2.0f, mSphereTurtlesA[i].mFinalRadius*0.15f, r_turtleB, g_turtleB, b_turtleB ); 
                mTurtlesB.push_back( newTurtle2 );
                
                Turtle newTurtle3;
                newTurtle3.init( mSphereTurtlesA[i].mWorldStartPosition, mSphereTurtlesA[i].mTotalRotationMatrix, direction3, mSphereTurtlesA[i].mFinalRadius*2.0f, mSphereTurtlesA[i].mFinalRadius*0.15f, r_turtleB, g_turtleB, b_turtleB ); 
                mTurtlesB.push_back( newTurtle3 );
                
                Turtle newTurtle4;
                newTurtle4.init( mSphereTurtlesA[i].mWorldStartPosition, mSphereTurtlesA[i].mTotalRotationMatrix, direction4, mSphereTurtlesA[i].mFinalRadius*2.0f, mSphereTurtlesA[i].mFinalRadius*0.2f, r_turtleA, g_turtleA, b_turtleA ); 
                mTurtlesA.push_back( newTurtle4 );
                /*
                Turtle newTurtle5;
                newTurtle5.init( mSphereTurtlesA[i].mWorldStartPosition, mSphereTurtlesA[i].mTotalRotationMatrix, direction5, mSphereTurtlesA[i].mFinalRadius*2.0f, mSphereTurtlesA[i].mFinalRadius*0.2f, r_turtleB, g_turtleB, b_turtleB ); 
                mTurtlesB.push_back( newTurtle5 );
                
                Turtle newTurtle6;
                newTurtle6.init( mSphereTurtlesA[i].mWorldStartPosition, mSphereTurtlesA[i].mTotalRotationMatrix, direction6, mSphereTurtlesA[i].mFinalRadius*2.0f, mSphereTurtlesA[i].mFinalRadius*0.2f, r_turtleB, g_turtleB, b_turtleB ); 
                mTurtlesB.push_back( newTurtle6 );
                 */
            }      
        }
        
    }
    
    //UDPATE SPHERE TURTLE B
    for (int i = 0; i < mSphereTurtlesB.size(); i++ ) {
        mSphereTurtlesB[i].update();
        
        if (mSphereTurtlesB[i].branchNow2 ){
            if ( mSphereTurtlesB[i].mFinalRadius > 10.0f)  {
                Turtle newTurtle1;
                newTurtle1.init( mSphereTurtlesB[i].mWorldStartPosition, mSphereTurtlesB[i].mTotalRotationMatrix, direction4, mSphereTurtlesB[i].mFinalRadius*2.4f, mSphereTurtlesB[i].mFinalRadius*0.15f, r_turtleA, g_turtleA, b_turtleA ); 
                mTurtlesA.push_back( newTurtle1 );
                
            }      
        }
        
    }
    
    // UPDATE CUBOID TURTLE A
    for (int i = 0; i < mCuboidTurtlesA.size(); i++) {
        mCuboidTurtlesA[i].update();
        
        if (mCuboidTurtlesA[i].branchNow2 ){
            if ( mCuboidTurtlesA[i].mFinalSize.x > 10.0f)  {

                Turtle newTurtle2;
                newTurtle2.init( mCuboidTurtlesA[i].mWorldStartPosition, mCuboidTurtlesA[i].mTotalRotationMatrix, direction4, mCuboidTurtlesA[i].mFinalSize.x*2.0f, mCuboidTurtlesA[i].mFinalSize.x*0.1f, r_turtleA, g_turtleA, b_turtleA );
                mTurtlesA.push_back( newTurtle2 );
                
                Turtle newTurtle3;
                newTurtle3.init( mCuboidTurtlesA[i].mWorldStartPosition, mCuboidTurtlesA[i].mTotalRotationMatrix, direction5, mCuboidTurtlesA[i].mFinalSize.x*2.0f, mCuboidTurtlesA[i].mFinalSize.x*0.1f, r_turtleB, g_turtleB, b_turtleB );
                mTurtlesB.push_back( newTurtle3 ); 
                      
            }
        }
        
    }
    
    // UPDATE CUBOID TURTLE B
    for (int i = 0; i < mCuboidTurtlesB.size(); i++) {
        mCuboidTurtlesB[i].update();
        
        if (mCuboidTurtlesB[i].branchNow2 ){
            if ( mCuboidTurtlesB[i].mFinalSize.x > 10.0f)  {
                
                Turtle newTurtle1;
                newTurtle1.init( mCuboidTurtlesB[i].mWorldStartPosition, mCuboidTurtlesB[i].mTotalRotationMatrix, direction1, mCuboidTurtlesB[i].mFinalSize.x*2.0f, mCuboidTurtlesB[i].mFinalSize.x*0.1f, r_turtleB, g_turtleB, b_turtleB );
                mTurtlesB.push_back( newTurtle1 ); 
                
                Turtle newTurtle2;
                newTurtle2.init( mCuboidTurtlesB[i].mWorldStartPosition, mCuboidTurtlesB[i].mTotalRotationMatrix, direction2, mCuboidTurtlesB[i].mFinalSize.x*2.0f, mCuboidTurtlesB[i].mFinalSize.x*0.1f, r_turtleB, g_turtleB, b_turtleB );
                mTurtlesB.push_back( newTurtle2 ); 
            }
        }
        
    }
    
    //UDPATE TORUS TURTLE
    for (int i = 0; i < mTorusTurtlesA.size(); i++ ) {
        mTorusTurtlesA[i].update();
        
        if (mTorusTurtlesA[i].branchNow1 ){
            if ( mTorusTurtlesA[i].mOuterRadius > 10.0f)  {
                Turtle newTurtle1;
                newTurtle1.init( mTorusTurtlesA[i].mWorldStartPosition, mTorusTurtlesA[i].mTotalRotationMatrix, direction1, mTorusTurtlesA[i].mOuterRadius*3.0f, mTorusTurtlesA[i].mOuterRadius*0.3f, r_turtleB, g_turtleB, b_turtleB); 
                mTurtlesB.push_back( newTurtle1 );
                
                Turtle newTurtle2;
                newTurtle2.init( mTorusTurtlesA[i].mWorldStartPosition, mTorusTurtlesA[i].mTotalRotationMatrix, direction2, mTorusTurtlesA[i].mOuterRadius*3.0f, mTorusTurtlesA[i].mOuterRadius*0.3f, r_turtleB, g_turtleB, b_turtleB); 
                mTurtlesB.push_back( newTurtle2 );
                
            }
        }
        
    }
    
    cout << "Elapsed Frames: " + toString( getElapsedFrames() ) + "\n";
    
    if (getElapsedFrames() > 4000) {
        cout << "Exiting Program \n";
        exit(1);
    }
    
}

void LSystem3D_003App::draw()
{
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { -10.0f, 10.0f, 10.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    
    GLfloat light_position1[] = { 10.0f, -10.0f, -15.0f, mDirectional };
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light1_diffuse );
    
    glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
    
    // DRAW AXIS
    if (mShowAxis){
        ci::ColorA colorX( CM_RGB, 1.0f, 0.0f, 0.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorX );
        gl::drawLine( Vec3f(-500.0f, 0.0f, 0.0f), Vec3f(500.0f, 0.0f, 0.0f) );
        
        ci::ColorA colorY( CM_RGB, 0.0f, 1.0f, 0.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorY );
        gl::drawLine( Vec3f(0.0f, -500.0f, 0.0f), Vec3f(0.0f, 500.0f, 0.0f) );
        
        ci::ColorA colorZ( CM_RGB, 0.0f, 0.0f, 1.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorZ );
        gl::drawLine( Vec3f(0.0f, 0.0f, -500.0f), Vec3f(0.0f, 0.0f, 500.0f) );
    }
    
    // DRAW TURTLE 
    for (int i= 0; i< mTurtlesA.size(); i++) {
        mTurtlesA[i].draw();
    }
    
    for (int i= 0; i< mTurtlesB.size(); i++) {
        mTurtlesB[i].draw();
    }
   
    // ENABLE TEXTURE
    //glEnable( GL_TEXTURE_2D);
    
   // mTexture2.bind();
    
    // DRAW CUBOID TURTLE
    for (int i = 0; i < mCuboidTurtlesA.size(); i++ ) {
        mCuboidTurtlesA[i].draw();
    }
    
    for (int i = 0; i < mCuboidTurtlesB.size(); i++ ) {
        mCuboidTurtlesB[i].draw();
    }
    
    //mTexture2.unbind();
   // mTexture.bind();
    
    // DRAW SPHERE TURTLE
    for (int i = 0; i< mSphereTurtlesA.size(); i++) {
        mSphereTurtlesA[i].draw();
    }
    
    for (int i = 0; i< mSphereTurtlesB.size(); i++) {
        mSphereTurtlesB[i].draw();
    }
    //mTexture.unbind();
    
    //glDisable(GL_TEXTURE_2D);
    // DRAW TORUS TURTLE
    for (int i = 0; i< mTorusTurtlesA.size(); i++) {
        mTorusTurtlesA[i].draw();
    }
    
    // SAVING FRAME
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "LSystem3D_032/LSystem_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
   
        //mSaveFrame = false;
	}
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}


CINDER_APP_BASIC( LSystem3D_003App, RendererGl )