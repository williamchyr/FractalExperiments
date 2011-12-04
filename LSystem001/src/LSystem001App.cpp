#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include "Turtle.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;


class LSystem001App : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    vector <Turtle> mTurtle;
    
    Vec2f initialDirection;
    Vec2f direction1;
    Vec2f direction2;
    
    Vec2f initialPosition;
    float initialLength;
    
    bool mSaveFrame;

};

void LSystem001App::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void LSystem001App::setup()
{   
    initialPosition.set( getWindowWidth()/2, 700.0f);
    initialDirection.set( 0.0f, -10.0f);
    direction1.set( -30.0f, -10.0f);
    direction2.set( 10.0f, -10.0f);
    
    initialLength = 200.0f;
    
    Turtle firstTurtle;
    firstTurtle.init( initialPosition, initialDirection, initialLength );
    
    mTurtle.push_back( firstTurtle );
    
    mSaveFrame = false;
}

void LSystem001App::mouseDown( MouseEvent event )
{
}

void LSystem001App::keyDown( KeyEvent event )
{
    if( event.getChar() == 's' ){
		mSaveFrame = ! mSaveFrame;
	}
}

void LSystem001App::update()
{
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].update();
        
        if (mTurtle[i].mLength < 40.0f) break;

        if (mTurtle[i].branchNow){
            Turtle newTurtle1; 
            newTurtle1.init( mTurtle[i].mCurrentPosition, direction1, mTurtle[i].mLength*0.80f );
            
            mTurtle.push_back( newTurtle1 );
            
            Turtle newTurtle2;
            newTurtle2.init( mTurtle[i].mCurrentPosition, direction2, mTurtle[i].mLength*0.80f  );
            
            mTurtle.push_back( newTurtle2 );
            cout << "Hello \n";
        }
    }
}

void LSystem001App::draw()
{
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].draw();
    }
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "LSystem001/LSystem_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrame = false;
	}
}


CINDER_APP_BASIC( LSystem001App, RendererGl )
