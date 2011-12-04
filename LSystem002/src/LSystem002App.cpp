#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include "Turtle.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;


class LSystem002App : public AppBasic {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    vector <Turtle> mTurtle;
    
    float initialAngle;
    float angle1, angle2, angle3, angle4;
    
    Vec2f initialPosition;
    float initialLength;
    
    bool mSaveFrame;
    
};

void LSystem002App::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void LSystem002App::setup()
{   
    initialPosition.set( getWindowWidth()/2, 700.0f);
    initialAngle =  -M_PI/2;
    angle1 = -M_PI/2;
    angle2 = M_PI/5;
    angle3 = -M_PI/6;
    //angle4 = -M_PI/11; 
    
    initialLength = 240.0f;
    
    Turtle firstTurtle;
    firstTurtle.init( initialPosition, 0.0f, initialAngle, initialLength );
    
    mTurtle.push_back( firstTurtle );
    
    mSaveFrame = false;
}

void LSystem002App::mouseDown( MouseEvent event )
{
}

void LSystem002App::keyDown( KeyEvent event )
{
    if( event.getChar() == 's' ){
		mSaveFrame = ! mSaveFrame;
	}
}

void LSystem002App::update()
{
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].update();
        
        if (mTurtle[i].mLength < 0.1f) break;
        
        if (mTurtle[i].branchNow){
            Turtle newTurtle1; 
            newTurtle1.init( mTurtle[i].mCurrentPosition, mTurtle[i].mAngle, angle1, mTurtle[i].mLength*0.75f );
            
            mTurtle.push_back( newTurtle1 );
            
            Turtle newTurtle2;
            newTurtle2.init( mTurtle[i].mCurrentPosition, mTurtle[i].mAngle, angle2, mTurtle[i].mLength*0.62f  );
            
            mTurtle.push_back( newTurtle2 );
            
            Turtle newTurtle3;
            newTurtle3.init( mTurtle[i].mCurrentPosition, mTurtle[i].mAngle, angle3, mTurtle[i].mLength*0.70f  );
            
            mTurtle.push_back( newTurtle3 );
            /*
            Turtle newTurtle4;
            newTurtle4.init( mTurtle[i].mCurrentPosition, mTurtle[i].mAngle, angle4, mTurtle[i].mLength*0.70f  );
            
            mTurtle.push_back( newTurtle4 );
            */
            cout << "Hello \n";
        }
    }
}

void LSystem002App::draw()
{
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].draw();
    }
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "LSystem001/LSystem3_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrame = false;
	}
}


CINDER_APP_BASIC( LSystem002App, RendererGl )