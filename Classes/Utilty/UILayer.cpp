/*
 * UILayer.cpp
 *
 *  Created on: 2012-10-7
 *      Author: arch
 */

#include "UILayer.h"

UILayer::UILayer() {
	life = 100;
}

UILayer::~UILayer() {

}


void UILayer::setLife(int temp) {
	life = temp;
}

int UILayer::getLife() {
	return life;
}


void UILayer::draw() {
	CCLayer::draw();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	glBlendColor(0.0,0.0,0.0,1.0);
//	glColorMask(0,0,0,1);
	glLineWidth(10);
	ccDrawLine(CCPointMake(5, winSize.height-10), CCPointMake(5+life, winSize.height-10));
	glBlendColor(1.0,0.0,0.0,1.0);
//	glColorMask(0,0,0,1);
	glLineWidth(5);
	ccDrawLine(CCPointMake(10, winSize.height-11), CCPointMake(10+life, winSize.height-11));
}
