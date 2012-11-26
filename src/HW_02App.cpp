/*Author: Andy Shear
This file uses a linked list data structure to display multiple squares within one another, as children.
It uses both keyboard and mouse functionalities.  This is the main class, it calls Square.cpp to create the objects in the list.
*/



#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "Resources.h"
#include "Square.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW_02App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void keyDown( KeyEvent event );
	void update();
	void draw();

	Vec2i mMouseLoc;
	Vec2f mMouseVel;
	bool mIsPressed;
	bool mDrawImage;

private:
	Square* mSquare_;
	Font* f;
	static const int width = 800;
	static const int height = 600;
	static const int size = 1024;
	static const Vec2f kUnitX;
	static const Vec2f kUnitY;

	int frame_number_;
};

const Vec2f HW_02App::kUnitX = Vec2f(0.7071f,-0.7071f);
const Vec2f HW_02App::kUnitY = Vec2f(0.7071f,0.7071f);


void HW_02App::setup()
{
	mMouseLoc = Vec2i( 0, 0 );
	mMouseVel = Vec2f::zero();
	mIsPressed = false;
	mDrawImage = false;
	f = new Font("Times New Roman", 20);


	Vec2f trans = (width/2.0f)*kUnitX + (height/2.0f)*kUnitY;
	mSquare_ = new Square(3, mMouseLoc, trans, height/4.0f);
	
	frame_number_ = 0;
	
}

void HW_02App::mouseDown( MouseEvent event )
{
	mIsPressed = true;
}

void HW_02App::mouseUp( MouseEvent event )
{
	mIsPressed = false;
}

void HW_02App::mouseMove( MouseEvent event )
{
	mMouseVel = ( event.getPos() - mMouseLoc );
	mMouseLoc = event.getPos();
}

void HW_02App::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}

void HW_02App::keyDown( KeyEvent event )
{
	if( event.getChar() == '?' ){
		mDrawImage = ! mDrawImage;
	}
}

void HW_02App::update()
{
	Square* cur = mSquare_;
	Vec2f center = kUnitX*width/2.0 + kUnitY*height/2.0;

	if(mIsPressed){
		cur->update(mMouseLoc, width/4.0);
	}

	if(cur != NULL && mIsPressed){
		do {
			cur->update(mMouseLoc, width/4.0);
			cur = cur->next_;
		} while (cur != mSquare_);
	}

	frame_number_++;
}

void HW_02App::draw()
{
	gl::clear( Color( 0, 0, 0 ), true );
	
	if((frame_number_ <=1) || mDrawImage){
		mDrawImage = true;
		gl::clear( Color( 0, 0, 0 ), true );
		gl::drawString("Welcome to The Royal Society for Putting Things on Top of Other Things", Vec2f (20,200), Color(0.0f,1.0f,0.0f), *f);				
		gl::drawString("Press '?' to continue...", Vec2f (20,230), Color(0.0f,1.0f,0.0f), *f);			
	
	}
	else{
		Square* cur = mSquare_;		
		if(cur != NULL){
			do {
				cur->draw();
				cur = cur->next_;
			} while (cur != mSquare_);
		}
	}
}

CINDER_APP_BASIC( HW_02App, RendererGl )
