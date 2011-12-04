#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIO.h"
#include "Turtle.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;


class LSystem003App : public AppBasic {
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

void LSystem003App::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void LSystem003App::setup()
{   
    initialPosition.set( getWindowWidth()/2, 650.0f);
    initialAngle =  -M_PI/2;
    angle1 = M_PI*(-10.0f/12.0f);
    angle2 = M_PI*(5.0f/12.0f);
    angle3 = M_PI*(10.0f/12.0f);
    angle4 = M_PI*(-5.0f/12.0f); 
    
    initialLength = 600.0f;
    
    Turtle firstTurtle;
    firstTurtle.init( initialPosition, 0.0f, initialAngle, initialLength );
    
    mTurtle.push_back( firstTurtle );
    
    mSaveFrame = false;
}

void LSystem003App::mouseDown( MouseEvent event )
{
}

void LSystem003App::keyDown( KeyEvent event )
{
    if( event.getChar() == 's' ){
		mSaveFrame = ! mSaveFrame;
	}
}

void LSystem003App::update()
{
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].update();
        
        if (mTurtle[i].branchNow1){
            
            if (mTurtle[i].mLength > 10.0f) {
                Turtle newTurtle1; 
                newTurtle1.init( mTurtle[i].mCurrentPosition, mTurtle[i].mAngle, angle1, mTurtle[i].mLength*0.30f );
                mTurtle.push_back( newTurtle1 );
            }
        }
        
        if (mTurtle[i].branchNow2){
            
            if (mTurtle[i].mLength > 10.0f) {
                Turtle newTurtle2; 
                newTurtle2.init( mTurtle[i].mCurrentPosition, mTurtle[i].mAngle, angle2, mTurtle[i].mLength*0.50f );
            
                mTurtle.push_back( newTurtle2 );
            }
        }
    
        
        if (mTurtle[i].branchNow3){
            
            if (mTurtle[i].mLength > 10.0f) {
            Turtle newTurtle3; 
            newTurtle3.init( mTurtle[i].mCurrentPosition, mTurtle[i].mAngle, angle3, mTurtle[i].mLength*0.50f );
            
            mTurtle.push_back( newTurtle3 );
            }

        }
        
        if (mTurtle[i].branchNow4){
            
            if (mTurtle[i].mLength > 10.0f) {
            Turtle newTurtle4; 
            newTurtle4.init( mTurtle[i].mCurrentPosition, mTurtle[i].mAngle, angle4, mTurtle[i].mLength*0.50f );
            
            mTurtle.push_back( newTurtle4 );
            }
        }
    }
}

void LSystem003App::draw()
{
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].draw();
    }
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "LSystem/LSystem005_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrame = false;
	}
}


CINDER_APP_BASIC( LSystem003App, RendererGl )