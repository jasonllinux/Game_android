/*
 * UILayer.h
 *
 *  Created on: 2012-10-7
 *      Author: arch
 */

#ifndef UILAYER_H_
#define UILAYER_H_

#include <cocos2d.h>

using namespace cocos2d;

class UILayer: public CCLayer {

private:
	int life;

public:

	UILayer();
	~UILayer();

	int getLife();
	void setLife(int temp);

	virtual void draw();

};

#endif /* UILAYER_H_ */
