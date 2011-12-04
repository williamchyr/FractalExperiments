#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Turtle.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

class TurtleApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    vector <Turtle> mTurtle;
    
    Vec2f initialDirection;
    Vec2f direction1;
    Vec2f direction2;
    
    Vec2f initialPosition;
    float initialLength;
   
};

void TurtleApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void TurtleApp::setup()
{
    initialDirection.set( 10.0f, 0.0f);
    direction1.set( 30.0f, 10.0f);
    direction2.set( 10.0f, -10.0f);
    
    Turtle firstTurtle;
    firstTurtle.init( Vec2f(100.0f, 500.0f), initialDirection, 200.0f );
    
    mTurtle.push_back( firstTurtle );
}

void TurtleApp::mouseDown( MouseEvent event )
{
}

void TurtleApp::update()
{
    
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].update();
        
        if (mTurtle[i].mLength < 20.0f) {
            break;
        }
        
        if (mTurtle[i].branchNow){
            Turtle newTurtle1;
            newTurtle1.init( mTurtle[i].mCurrentPosition, direction1, (mTurtle[i].mLength)*0.80);
            
            mTurtle.push_back( newTurtle1 );
            
            Turtle newTurtle2;
            newTurtle2.init( mTurtle[i].mCurrentPosition, direction2, (mTurtle[i].mLength)*0.80);
            
            mTurtle.push_back( newTurtle2 );
            cout << "Hello \n";
        }
    }
}

void TurtleApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    for (int i = 0; i < mTurtle.size(); i++) {
        mTurtle[i].draw();
    }
    
}


CINDER_APP_BASIC( TurtleApp, RendererGl )
