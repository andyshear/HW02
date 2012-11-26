#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "Square.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//Square.cpp forked from brinkmwj's diamond.cpp, then edited to work with my HW_02App.cpp

Square::Square(int depth, Vec2i position, Vec2f initial, float radius){	
	next_ = prev_ = this;
	children_ = NULL;

	initial_ = initial;
	position_ = position;
	radius_ = radius;

	if(depth>0){
		addChild(depth-1);
		addChild(depth-1);
	}
	
}

void insertAfter(Square* new_item, Square* insert_here){	
	new_item->next_ = insert_here->next_;
	new_item->prev_ = insert_here;
	insert_here->next_->prev_ = new_item;
	insert_here->next_ = new_item;
}



void Square::update(Vec2i &mouseLoc, float parent_r){
	
	position_ = mouseLoc;

	Square* cur = children_;
	if(cur != NULL){
		do {
			cur->update(position_,radius_);
			cur = cur->next_;
		} while (cur->next_ != children_);
	}
}

void Square::addChild(int depth){
	Square* new_item = new Square(depth,position_,Vec2f(0.0,0.0),0.7*radius_);

	if(children_ != NULL){
		insertAfter(new_item, children_);
	} else {
		children_ = new_item;
	}
}

void Square::draw(){
	//draw origional
	gl::color(Color8u(255,0,0));
	gl::drawSolidRect(Rectf(position_.x-radius_,position_.y-radius_,position_.x+radius_,position_.y+radius_));
	gl::color(Color8u(0,255,0));
	gl::drawSolidRect(Rectf(position_.x-0.8*radius_,position_.y-0.8*radius_,position_.x+0.8*radius_,position_.y+0.8*radius_));
	gl::color(Color8u(0,0,255));
	gl::drawSolidRect(Rectf(position_.x-0.6*radius_,position_.y-0.6*radius_,position_.x+0.6*radius_,position_.y+0.6*radius_));
	
	//draw children
	Square* cur = children_;
	if(cur != NULL){
		do {
			cur->draw();
			cur = cur->next_;
		} while (cur->next_ != children_);
	}

}
