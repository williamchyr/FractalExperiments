#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include "cinder/Vector.h"
#include "cinder/Rand.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

class FractalStudyApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
	void keyDown( KeyEvent event );
	void update();
	void draw();
    
    void branch(float length, float angle);
    
    bool mSaveFrame;
    
    float r, g, b;
    //float angle;
    
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

void FractalStudyApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void FractalStudyApp::setup()
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

void FractalStudyApp::mouseDown( MouseEvent event )
{
}

void FractalStudyApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'k' ){
		mSaveFrame = ! mSaveFrame;
	}
}

void FractalStudyApp::update()
{
    camAngle += M_PI/50;
    
    //UPDATE CAMERA
    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    
   // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
}

void FractalStudyApp::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
    
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
    
    
    gl::pushMatrices();
    //gl::translate( getWindowWidth()/2, getWindowHeight()/2);
    branch(500.0f, 0.0f);
    gl::popMatrices();
    
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "fractal_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrame = false;
	}
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}

void FractalStudyApp::branch( float length, float angle) 
{
    length *= 0.6f;
    float length2 = length*0.78f;
    
    if (angle < 2*M_PI) {
        angle += M_PI/20;
    } else {
        angle = 0.0f;
    }
    
    
    
    float r = ( sin(angle) + 1.0f)/2.0f;
    float b = ( cos(angle) + 1.0f)/2.0f;

    
    if (length > 5.0f) {
        gl::pushMatrices();
        //gl::rotate( 30.0f);
        
        gl::rotate( Vec3f( 90.0f, -90.0f, 90.0f) );
        ci::ColorA color4( CM_RGB, 1.0f, r, b, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color4 );
        gl::drawCube( Vec3f(0.0f, 0.0f, 0.0f), Vec3f(length/2.0f, length/2.0f, length/2.0f) );
        //gl::drawSphere( Vec3f(0.0f, 0.0f, 0.0f), length/2.0f, 24 );
        gl::translate( Vec3f( 0, 2*length, length) );
        branch( length, angle);
        gl::popMatrices();
    
        
        gl::pushMatrices();
        gl::translate( Vec2f(100.0f, 200.0f) );
        gl::rotate( Vec3f( 115.0f, 90.0f, 0.0f) );
       
        ci::ColorA color3( CM_RGB, 0.4f, 0.8f, b, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color3 );
        gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f ), length/2.0f, 24 );
        //gl::drawLine( Vec2f(0, 0), Vec2f(0, length*2) );

        gl::translate( Vec2f( -length, length) );
        branch( length2, angle );
        gl::popMatrices();
        
        /*
        gl::pushMatrices();
        gl::rotate( Vec3f( 90.0f, 30.0f, -30.0f) );
        ci::ColorA color2( CM_RGB, 1.0f, 0.5f, b, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
        
       // gl::drawSphere( Vec3f( 0.0f, 0.0f, 0.0f ), length/3.0f, 24 );
        gl::drawCube( Vec3f(0.0f, 0.0f, 0.0f), Vec3f(length/5.0f, length/2.0f, length) );
        gl::translate( Vec2f( 0, length*4) );
        branch( length, angle );
        gl::popMatrices();
         */
    }
}


CINDER_APP_BASIC( FractalStudyApp, RendererGl )
