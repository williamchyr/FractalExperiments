#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class KochCurveApp : public AppBasic {
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

void KochCurveApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void KochCurveApp::setup()
{
    mStartPoint.set(100.0f, getWindowHeight()/2 );
    mStartLength = 1000.0f;

}

void KochCurveApp::mouseDown( MouseEvent event )
{
}

void KochCurveApp::update()
{
}

void KochCurveApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    // start the Koch Curve
    glColor3f(1.0f, 1.0f, 1.0f);
    protrude( mStartPoint, mStartLength );
}

void KochCurveApp::protrude( Vec2f firstPoint, float length ) {
    
    if (length > 10 ) {
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

CINDER_APP_BASIC( KochCurveApp, RendererGl )
