#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class KochSnowflakeApp : public AppBasic {
  public:
	void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void protrude( Vec2f firstPoint, float length );
    
    Vec2f mStartPoint;
    float mStartLength;
};

void KochSnowflakeApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void KochSnowflakeApp::setup()
{
    mStartPoint.set(100.0f, 220.0f );
    mStartLength = 650.0f;
}

void KochSnowflakeApp::mouseDown( MouseEvent event )
{
}

void KochSnowflakeApp::update()
{
}

void KochSnowflakeApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    // start the Koch Island
    glColor3f(1.0f, 1.0f, 1.0f);
    
    gl::pushMatrices();
    gl::translate( mStartPoint);
    protrude( Vec2f(0.0f, 0.0f), mStartLength );
    
    gl::translate( mStartLength, 0.0f );
    gl::rotate( Vec3f( 0.0f, 0.0f, 120.0f ) );
    protrude( Vec2f(0.0f, 0.0f), mStartLength );
    
    gl::translate( mStartLength, 0.0f);
    gl::rotate( Vec3f( 0.0f, 0.0f, 120.0f ) );
    protrude( Vec2f(0.0f, 0.0f), mStartLength );
    
    gl::popMatrices();
}

void KochSnowflakeApp::protrude( Vec2f firstPoint, float length ) {
    
    if (length > 2 ) {
        //LEFT SEGMENT
        gl::pushMatrices();
        gl::translate( firstPoint );
        gl::drawLine( Vec2f(0.0f, 0.0f), Vec2f( length/3, 0.0f ) );
        protrude( Vec2f(0.0f, 0.0f), length/3 );
        gl::popMatrices();
        
        //MIDDLE SEGMENT
        gl::pushMatrices();
        gl::translate( firstPoint.x + length/3, firstPoint.y );
        
        //DRAW A BLACK LINE TO COVER UP WHITE LINE FROM PREVIOUS ITERATION
        glColor3f(0.0f, 0.0f, 0.0f);
        gl::drawLine( Vec2f(0.0f, 0.0f), Vec2f( length/3, 0.0f ) );
        
        
        //gl::drawSolidCircle( Vec2f(0.0f, 0.0f), 10.0f );
        
        gl::pushMatrices();
        
        glColor3f(1.0f, 1.0f, 1.0f);
        gl::rotate( Vec3f( 0.0f, 0.0f, -60.0f) );
        gl::drawLine( Vec2f(0.0f, 0.0f), Vec2f( length/3, 0.0f) );
        protrude( Vec2f(0.0f, 0.0f), length/3 );
        gl::translate( length/3, 0.0f );  
        gl::rotate( Vec3f( 0.0f, 0.0f, 120.0f) );
        gl::drawLine( Vec2f(0.0f, 0.0f), Vec2f( length/3, 0.0f ) );
        protrude( Vec2f(0.0f, 0.0f), length/3 );
        
        gl::popMatrices();
        
        gl::popMatrices();
        
        //RIGHT SEGMENT
        gl::pushMatrices();
        gl::translate( firstPoint.x + 2*(length/3), firstPoint.y );
        gl::drawLine( Vec2f(0.0f, 0.0f), Vec2f( length/3, 0.0f ) );
        protrude( Vec2f(0.0f, 0.0f), length/3 );
        gl::popMatrices();
    }
    
}


CINDER_APP_BASIC( KochSnowflakeApp, RendererGl )
