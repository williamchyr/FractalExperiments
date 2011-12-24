#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h" 
#include "cinder/matrix.h"
#include "Turtle.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

class Turtle3DApp : public AppBasic {
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
    
    // ROTATION
    float xAngle, yAngle, zAngle;
    float mDirectional;
    
    // TURTLE
    Turtle firstTurtle;
    
    Vec3f originalPosition;
    Vec3f originalRotation;
    float originalLength;
    float orginalRadius;
    
    vector<Turtle> mTurtles;
    
    Vec3f direction1;
    Vec3f direction2;
    Vec3f direction3;
    
    // AXIS
    bool mShowAxis;
};

void Turtle3DApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void Turtle3DApp::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1200.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 3000.0f );
    
    // CAMERA ROTATION
    xAngle = 0.0f;
    yAngle = 0.0f;
    zAngle = 0.0f;
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w" );
    mParams.addParam( "X Angle", &xAngle, "min=0.0 max=360.0 step=5.0 keyIncr=r keyDecr=f" );
    mParams.addParam( "Y Angle", &yAngle, "min=0.0 max=360.0 step=5.0 keyIncr=t keyDecr=g" );
    mParams.addParam( "Z Angle", &zAngle, "min=0.0 max=360.0 step=5.0 keyIncr=y keyDecr=h" );
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    mDirectional = 1.0f;
    
    // AXIS
    mShowAxis = false;
    
    // TURTLE
    originalPosition.set( 0.0f, -200.0f, 0.0f);
    originalRotation.set( 0.0f, 0.0f, 0.0f);
    originalLength = 300.0f;
    orginalRadius = 20.0f;
    
    firstTurtle.init( originalPosition, Vec3f(0.0f, 0.0f, 0.0f), originalRotation, originalLength, orginalRadius, 1.0f, 1.0f, 1.0f );
    
    mTurtles.push_back( firstTurtle );
    
    direction1.set( 0.0f, 0.0f, 25.0f );
    direction2.set( 0.0f, 120.0f, 45.0f);
    direction3.set( 0.0f, 240.0f, 80.0f);
    
}

void Turtle3DApp::mouseDown( MouseEvent event )
{
}

void Turtle3DApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'a' ){
		mShowAxis = ! mShowAxis;
	}
}

void Turtle3DApp::update()
{
    //UPDATE CAMERA
    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    
    // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    
    //UDPATE TURTLE
    for (int i = 0; i < mTurtles.size(); i++ ) {
        mTurtles[i].update();

        if (mTurtles[i].branchNow2 ){
            if ( mTurtles[i].mFinalLength > 10.0f)  {
                Turtle newTurtle;
                newTurtle.init( mTurtles[i].mWorldEndPosition, mTurtles[i].mTotalRotationMatrix, direction1, mTurtles[i].mFinalLength*0.6f, mTurtles[i].mRadius*0.7f, 1.0f, 1.0f, 1.0f);
                mTurtles.push_back( newTurtle );
                     
                Turtle newTurtle2;
                newTurtle2.init( mTurtles[i].mWorldEndPosition, mTurtles[i].mTotalRotationMatrix, direction2, mTurtles[i].mFinalLength*0.65f, mTurtles[i].mRadius*0.7f, 1.0f, 1.0f, 1.0f);
                mTurtles.push_back( newTurtle2 );
                
                Turtle newTurtle3;
                newTurtle3.init( mTurtles[i].mWorldEndPosition, mTurtles[i].mTotalRotationMatrix, direction3, mTurtles[i].mFinalLength*0.5f, mTurtles[i].mRadius*0.7f, 1.0f, 1.0f, 1.0f);
                mTurtles.push_back( newTurtle3 );
            }
        }

    }
}

void Turtle3DApp::draw()
{
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { -200.0f, 400.0f, 275.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    
    GLfloat light_position1[] = { -500.0f, -300.0f, -400.0f, mDirectional };
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
    for (int i= 0; i< mTurtles.size(); i++) {
        mTurtles[i].draw();
    }
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}


CINDER_APP_BASIC( Turtle3DApp, RendererGl )
