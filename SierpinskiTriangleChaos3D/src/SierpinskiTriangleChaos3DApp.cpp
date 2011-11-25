#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/Rand.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;
using std::vector;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };

class SierpinskiTriangleChaos3DApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    Vec3f chaosGamePoint( Vec3f point );
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    float mDirectional;
    
    // MARKERS
    Vec3f marker1, marker2, marker3, marker4;
    
    vector<Vec3f>	mPoints;
    
    Vec3f thePoint;
    
    bool mSaveFrame;
    
};

void SierpinskiTriangleChaos3DApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1000, 800 );
	settings->setFrameRate( 60.0f );
}

void SierpinskiTriangleChaos3DApp::setup()
{
    
    // SETUP CAMERA
	mCameraDistance = 1000.0f;
	mEye			= Vec3f( 0.0f, 300.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 300.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 3000.0f );
    
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1300.0 step=20.0 keyIncr=s keyDecr=w" );
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    mDirectional = 1.0f;
    
    marker1.set( 0.0f, 0.0f, 400.0f);
    marker2.set( -346.5f, 0.0f, -200.0f);
    marker3.set( 346.5f, 0.0f, -200.0f);
    marker4.set( 0.0f, 600.0f, 0.0f);
    
    thePoint.set( Rand::randFloat(-100.0f, 100.0f), Rand::randFloat(-100.0f, 100.0f), Rand::randFloat(-100.0f, 100.0f) );
    
    mSaveFrame = true;
}

void SierpinskiTriangleChaos3DApp::mouseDown( MouseEvent event )
{
}

void SierpinskiTriangleChaos3DApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 's' ){
		mSaveFrame = ! mSaveFrame;
	}
}

void SierpinskiTriangleChaos3DApp::update()
{
    //UPDATE CAMERA    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance);
    
    // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    thePoint = chaosGamePoint( thePoint ); 

}

void SierpinskiTriangleChaos3DApp::draw()
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
    
    
    ci::ColorA color1( CM_RGB, 1.0f, 1.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );
    
    
    gl::drawSphere( marker1, 10 );
    gl::drawSphere( marker2, 10 );
    gl::drawSphere( marker3, 10 );
    gl::drawSphere( marker4, 10 );
    
    for (int i = 0; i < mPoints.size(); i++ ) {
        
        ci::ColorA color2( CM_RGB, abs(mPoints[i].x/300.0f), mPoints[i].y/600, 1.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
        
        gl::drawSphere( mPoints[i], 1.0f );
    }
    
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "Sierpinski3D/sierpinski_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
       //mSaveFrame = false;
	}
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
    
}

Vec3f SierpinskiTriangleChaos3DApp::chaosGamePoint( Vec3f point )
{
    Vec3f midPoint;
    Vec3f chosenMarker;
    
    int markerNumber;
    
    markerNumber = Rand::randInt( 1, 5 );
    
    switch (markerNumber) {
        case 1:
            chosenMarker = marker1;
            break;
        case 2:
            chosenMarker = marker2;
            break;
        case 3:
            chosenMarker = marker3;
            break;
        case 4: 
            chosenMarker = marker4;
            break;
    }
    
    midPoint.set( (point.x + chosenMarker.x)/2, (point.y + chosenMarker.y)/2, (point.z + chosenMarker.z)/2 );
    mPoints.push_back( midPoint );
    
    return midPoint;
    
    
}

CINDER_APP_BASIC( SierpinskiTriangleChaos3DApp, RendererGl )
