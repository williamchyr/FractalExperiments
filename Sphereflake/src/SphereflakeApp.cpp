#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include "cinder/Vector.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };

class SphereflakeApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    void branch( Vec3f position, float radius, float r1, float g1, float b1 );
    
    bool mSaveFrame;
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    float mDirectional;
    
    
    // STARTING POSITIONS
    Vec3f mStartPosition;
    float mStartRadius;
    
    // COLORS
    float r, g, b;
    
};

void SphereflakeApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void SphereflakeApp::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1800.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 2000.0f );
    
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=2000.0 step=50.0 keyIncr=s keyDecr=w" );
    
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    mDirectional = 1.0f;
    
    mSaveFrame = false;
    
    //
    mStartPosition.set( 0.0f, 0.0f, 0.0f );
    mStartRadius = 500.0f;
    
    // COLORS
    r = 0.8f;
    g = 1.0f;
    b = 0.3f;
}

void SphereflakeApp::mouseDown( MouseEvent event )
{
}

void SphereflakeApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'k' ){
		mSaveFrame = ! mSaveFrame;
	}
}

void SphereflakeApp::update()
{

    //UPDATE CAMERA    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance);
    
    // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
}

void SphereflakeApp::draw()
{
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_LIGHT2 );
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { -700.0f, 800.0f, 875.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    
    GLfloat light_position1[] = { 1000.0f, 0.0f, -400.0f, mDirectional };
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light1_diffuse );
    
    GLfloat light_position2[] = { 0.0f, 1050.0f, 0.0f, mDirectional };
    glLightfv( GL_LIGHT2, GL_POSITION, light_position2 );
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light1_diffuse );
    
    
    ci::ColorA color1( CM_RGB, r, g, b, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );
    
    
    gl::drawSphere( mStartPosition, mStartRadius, 24 );
    
    branch( mStartPosition, mStartRadius, r, g, b );
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "sphereflake/sphereflake_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrame = false;
	}
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}

void SphereflakeApp::branch( Vec3f position, float radius, float r1, float g1, float b1 )
{   
    if (radius > 5) {
    float newRadius;
    newRadius = radius/4;
    
    float zOffset;
    zOffset = -10.0f;
        
    float r2 = r1;
        
    if (r2 < 1.0) {
        r2 = r2 + 0.2f;
    } else {
        r2 = 0.4f;
    }
        
    float g2 = g1;
        
    if (g2 < 1.0) {
        g2 = g2 + 0.20f;
    } else {
        g2 = 0.1f;
    }
        
    float b2 = b1;
    
    if (b2 < 1.0) {
        b2 = b2 + 0.15f;
    } else {
        b2 = 0.4f;
    }
        
        

        
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 0.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
    ci::ColorA color2( CM_RGB, r2, g2, b2, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24); 
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b2 );
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 60.0f, zOffset) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24);
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b2 );
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 120.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24);
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b2 );
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 180.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24);   
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b1 );
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 240.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24);    
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b2 );
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 300.0f, zOffset ) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24); 
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b2 );
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 30.0f, 50.0f) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24);   
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b2 );
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 150.0f, 50.0f) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24);  
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b2 );
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 270.0f, 50.0f) );
    gl::translate( Vec3f( radius + newRadius, 0.0f, 0.0f ) );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, 24);   
        gl::rotate( Vec3f( 0.0f, 0.0f, -90.0f) );
        branch( Vec3f( 0.0f, 0.0f, 0.0f), newRadius, r2, g2, b2 );
    gl::popMatrices();
    
    }

}

CINDER_APP_BASIC( SphereflakeApp, RendererGl )
