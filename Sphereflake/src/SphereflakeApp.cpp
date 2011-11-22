#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include "cinder/Vector.h"

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };

class SphereflakeApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void branch( Vec3f position, float radius );
    
    bool mSaveFrame;
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    float mDirectional;
    
    float camAngle;
};

void SphereflakeApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void SphereflakeApp::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1200.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 2000.0f );
    
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w" );
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    mDirectional = 1.0f;
    
    camAngle = 0;
    
    mSaveFrame = false;
}

void SphereflakeApp::mouseDown( MouseEvent event )
{
}

void SphereflakeApp::update()
{
    camAngle += M_PI/50;
    
    //UPDATE CAMERA
    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    
    // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
}

void SphereflakeApp::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { -200.0f, 400.0f, 275.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f ), 100.0f, 24 );
    
    branch( Vec3f( 0.0f, 0.0f, 0.0f), 100.0f );
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}

void SphereflakeApp::branch( Vec3f position, float radius )
{   
    float newRadius;
    newRadius = radius/5;
    
    float zOffset;
    zOffset = -10.0f;
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 0.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);    
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 60.0f, zOffset) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);    
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 120.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);    
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 180.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);    
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 240.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);    
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 300.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);  
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 30.0f, 50.0f) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);    
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 150.0f, 50.0f) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);    
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 270.0f, 50.0f) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), 20.0f, 24);    
    gl::popMatrices();
    
    

}

CINDER_APP_BASIC( SphereflakeApp, RendererGl )
