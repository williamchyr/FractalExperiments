#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include <vector>


using namespace ci;
using namespace ci::app;
using namespace std;
using std::vector;

class SierpinskiTriangleChaosApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    Vec2f chaosGamePoint(Vec2f point);
    
    Vec2f thePoint;
    Vec2f marker1, marker2, marker3;
    
    vector<Vec2f>	mPoints;
    
    bool showMarkers;
    
    bool mSaveFrame;
};

void SierpinskiTriangleChaosApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1000, 800 );
	//settings->setFrameRate( 60.0f );
}


void SierpinskiTriangleChaosApp::setup()
{
    marker1.set(200, 700);
    marker2.set(800, 700);
    marker3.set(500, 181);
    
    thePoint.set( Rand::randFloat(0.0f, getWindowWidth()/2), Rand::randFloat(0.0f, getWindowHeight()/2 ) );
    
    showMarkers = false;
    
    mSaveFrame = false;
}

void SierpinskiTriangleChaosApp::mouseDown( MouseEvent event )
{
}

void SierpinskiTriangleChaosApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 's' ){
		mSaveFrame = ! mSaveFrame;
	}
}

void SierpinskiTriangleChaosApp::update()
{
    
    thePoint = chaosGamePoint( thePoint );    
}

void SierpinskiTriangleChaosApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    if (showMarkers) {
        gl::drawSolidCircle( marker1, 10.0f );
        gl::drawSolidCircle( marker2, 10.0f );
        gl::drawSolidCircle( marker3, 10.0f );
    }
    
    for (int i = 0; i < mPoints.size(); i++ ) {
        gl::drawSolidCircle( mPoints[i], 1.0f );
    }
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "SierpinskiTriangle/sierpinski_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrame = false;
	}
    
}

Vec2f SierpinskiTriangleChaosApp::chaosGamePoint( Vec2f point ) 
{
    Vec2f chosenMarker;
    Vec2f midPoint;
    
    int markerNumber;
    markerNumber = Rand::randInt(1, 4); //so it's choosing either 1, 2, or 3
    
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
    }
    
    midPoint.set( (point.x + chosenMarker.x)/2, (point.y + chosenMarker.y)/2 );
    mPoints.push_back( midPoint );
    
    return midPoint;
}



CINDER_APP_BASIC( SierpinskiTriangleChaosApp, RendererGl )
