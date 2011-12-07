#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h" 
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "Turtle.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

class Turtle3D_2App : public AppBasic {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    // TURTLES
    vector <Turtle> mTurtle;
    float startLength;
    
    Vec3f startPosition;
    Vec3f initialDirection;
    Vec3f direction1, direction2;
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    // ROTATION
    float xAngle, yAngle, zAngle;
    float xAngleAdjusted, yAngleAdjusted, zAngleAdjusted;
    
    float X, Y, Z;
    
    float mDirectional;
    
    float camAngle;
    
};

void Turtle3D_2App::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void Turtle3D_2App::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1200.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 2000.0f );
    
    // ROTATION
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
    
    camAngle = 0;
    
    // TURTLE
    startPosition.set( 0.0f, 0.0f, 0.0f );
    initialDirection.set(0.0f, 0.0f, 0.0f );
    direction1.set( 0.0f, 0.0f, 90.0f );
    direction2.set( 0.0f, 90.0f, 0.0f );
    
    startLength = 800.0f;
    
    Turtle firstTurtle;
    firstTurtle.init( startPosition, Vec3f(0.0f, 0.0f, 0.0f), initialDirection, startLength, 20.0f );
    
    mTurtle.push_back( firstTurtle );
}

void Turtle3D_2App::mouseDown( MouseEvent event )
{
}

void Turtle3D_2App::update()
{   
    camAngle += M_PI/50;
    
    //UPDATE CAMERA
    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    
    // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    
    //UPDATE TURTLE
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].update();
        
        if (mTurtle[i].mLength < 20.0f) {
            break;
        }       
        
        if (mTurtle[i].branchNow1){
            
            if ( mTurtle[i].mFinalLength > 2.f)  {
                Turtle newTurtle1;
                newTurtle1.init( mTurtle[i].mCurrentPosition, mTurtle[i].mRotateAngle, direction1, mTurtle[i].mFinalLength*0.5f, mTurtle[i].mRadius*0.5f);
            
                mTurtle.push_back( newTurtle1 );
            
                //cout << "Hello1 \n";
            }
        }
        
        if (mTurtle[i].branchNow2){
            
            if ( mTurtle[i].mFinalLength > 2.f)  {
                Turtle newTurtle2;
                newTurtle2.init( mTurtle[i].mCurrentPosition, mTurtle[i].mRotateAngle, direction2, mTurtle[i].mFinalLength*0.5f, mTurtle[i].mRadius*0.5f);
            
                mTurtle.push_back( newTurtle2 );
            
                //cout << "Hello2 \n";
            }
        }
        
        if (mTurtle[i].branchNow3){
            
            if ( mTurtle[i].mFinalLength > 2.f)  {
                Turtle newTurtle3;
                newTurtle3.init( mTurtle[i].mCurrentPosition, mTurtle[i].mRotateAngle, direction1, mTurtle[i].mFinalLength*0.5f, mTurtle[i].mRadius*0.5f);
            
                mTurtle.push_back( newTurtle3 );
            
                //cout << "Hello3 \n";
            }
        }
        
    }
}

void Turtle3D_2App::draw()
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
    
    
    // DRAW TURTLE
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].draw();
    }
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}


CINDER_APP_BASIC( Turtle3D_2App, RendererGl )