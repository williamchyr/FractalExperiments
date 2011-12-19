#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h" 
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "Turtle.h"
#include "RectTurtle.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

class Turtle3D_ReduxApp : public AppBasic {
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
    float camAngle;
    
    // TURTLE
    Turtle testTurtle;
    float rotateX, rotateZ, rotateY;
    
    vector <Turtle> mTurtles;
    
    Vec3f startPosition;
    Vec3f zeroDirection;
    Vec3f initialDirection;
    
    Vec3f direction1, direction2;
    
    // RECT TURTLE
    RectTurtle mRectTurtle;
};

void Turtle3D_ReduxApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void Turtle3D_ReduxApp::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1200.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 2000.0f );
    
    // CAMERA ROTATION
    xAngle = 0.0f;
    yAngle = 0.0f;
    zAngle = 0.0f;
    
    // OBJECT ROTATION
    rotateX = 0.0f;
    rotateY = 0.0f;
    rotateZ = 0.0f;
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w" );
    mParams.addParam( "X Angle", &xAngle, "min=0.0 max=360.0 step=5.0 keyIncr=r keyDecr=f" );
    mParams.addParam( "Y Angle", &yAngle, "min=0.0 max=360.0 step=5.0 keyIncr=t keyDecr=g" );
    mParams.addParam( "Z Angle", &zAngle, "min=0.0 max=360.0 step=5.0 keyIncr=y keyDecr=h" );
    
    mParams.addParam( "Rotate X", &rotateX, "min=0.0 max=360.0 step=5.0 keyIncr=u keyDecr=j" );
    mParams.addParam( "Rotate Y", &rotateY, "min=0.0 max=360.0 step=5.0 keyIncr=i keyDecr=k" );
    mParams.addParam( "Rotate Z", &rotateZ, "min=0.0 max=360.0 step=5.0 keyIncr=o keyDecr=l" );
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    mDirectional = 1.0f;
    
    camAngle = 0;
    
    // TURTLE
    startPosition.set( 0.0f, 0.0f, 0.0f);
    zeroDirection.set( 0.0f, 0.0f, 0.0f);
    initialDirection.set( 100.0f, 0.0f, 10.0f);
    
    direction1.set( 90.0f, 0.0f, 50.0f );
    
    //testTurtle.init( Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 0.0f, 0.0f), direction1, 200.0f, 20.0f );
    
    //mTurtles.push_back(testTurtle);
    
    mRectTurtle.init( startPosition, Vec3f(100.0f, 100.0f, 100.0f), zeroDirection, initialDirection); 
 
    Turtle newTurtle1;
    newTurtle1.init( mRectTurtle.mStartPosition, mRectTurtle.mPreviousAngle,mRectTurtle.mRotateAngle, 1, 200.0f, 20.0f);
    mTurtles.push_back( newTurtle1 );
    
    Turtle newTurtle2;
    newTurtle2.init( mRectTurtle.mStartPosition, mRectTurtle.mPreviousAngle, mRectTurtle.mRotateAngle, 2, 200.0f, 20.0f);
    mTurtles.push_back( newTurtle2 );
    
    Turtle newTurtle3;
    newTurtle3.init( mRectTurtle.mStartPosition, mRectTurtle.mPreviousAngle, mRectTurtle.mRotateAngle, 3, 200.0f, 20.0f);
    mTurtles.push_back( newTurtle3 );
    
    Turtle newTurtle4;
    newTurtle4.init( mRectTurtle.mStartPosition, mRectTurtle.mPreviousAngle, mRectTurtle.mRotateAngle, 4, 200.0f, 20.0f);
    mTurtles.push_back( newTurtle4 );
    
    Turtle newTurtle5;
    newTurtle5.init( mRectTurtle.mStartPosition, mRectTurtle.mPreviousAngle, mRectTurtle.mRotateAngle, 5, 200.0f, 20.0f);
    mTurtles.push_back( newTurtle5 );
    
    Turtle newTurtle6;
    newTurtle6.init( mRectTurtle.mStartPosition, mRectTurtle.mPreviousAngle, mRectTurtle.mRotateAngle, 6, 200.0f, 20.0f);
    mTurtles.push_back( newTurtle6 );
  
}

void Turtle3D_ReduxApp::mouseDown( MouseEvent event )
{
}

void Turtle3D_ReduxApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'z' ){
		rotateZ = !rotateZ;
	}
    
    if( event.getChar() == 'x' ){
		rotateX = !rotateX;
	}
}


void Turtle3D_ReduxApp::update()
{
    cout << toString( mTurtles.size() ) + "\n";
    
    camAngle += M_PI/50;
    
    //UPDATE CAMERA
    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    
    // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    //UPDATE TURTLE
    //testTurtle.update( rotateX, rotateY, rotateZ);
    
    mRectTurtle.update();
    
    for (int i = 0; i < mTurtles.size(); i++) {
        mTurtles[i].update();
      
         cout << "Hello3 \n";
       
        if (mTurtles[i].mLength < 20.0f) {
            break;
        }    
        
        if ( mTurtles[i].mFinalLength > 2.0f)  {
            if (mTurtles[i].branchNow1 ){

            Turtle newTurtle;
            newTurtle.init( mTurtles[i].mFinalPosition, mTurtles[i].mFinalAngle, direction1, mTurtles[i].mFinalLength*0.5f, mTurtles[i].mRadius*0.7f);
            
            mTurtles.push_back( newTurtle );
            
            cout << "Hello3 \n";
            }
        }
       
    }
         
}

void Turtle3D_ReduxApp::draw()
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
    ci::ColorA colorX( CM_RGB, 1.0f, 0.0f, 0.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorX );
    gl::drawLine( Vec3f(-500.0f, 0.0f, 0.0f), Vec3f(500.0f, 0.0f, 0.0f) );
    
    ci::ColorA colorY( CM_RGB, 0.0f, 1.0f, 0.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorY );
    gl::drawLine( Vec3f(0.0f, -500.0f, 0.0f), Vec3f(0.0f, 500.0f, 0.0f) );
    
    ci::ColorA colorZ( CM_RGB, 0.0f, 0.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorZ );
    gl::drawLine( Vec3f(0.0f, 0.0f, -500.0f), Vec3f(0.0f, 0.0f, 500.0f) );
    
    // DRAW RECT TURTLE
    ci::ColorA color1( CM_RGB, 1.0f, 1.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );
    
    mRectTurtle.draw();
    
    // DRAW TURTLE
    for (int i=0; i < mTurtles.size(); i++) {
        mTurtles[i].draw();
        /*
        gl::pushMatrices();
        gl::translate( mTurtles[i].mFinalPosition );
        gl::rotate( mTurtles[i].mFinalAngle );
        //gl::drawCube( Vec3f(0.0f, 0.0f, 0.0f), Vec3f( 20.0f, 20.0f, 20.0f ) );
        gl::popMatrices();
         */
    }
    
    
    //testTurtle.draw();
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}

CINDER_APP_BASIC( Turtle3D_ReduxApp, RendererGl )
