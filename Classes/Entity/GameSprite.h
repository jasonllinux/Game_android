/*
 * GameSprite.h
 *
 *  Created on: 2012-10-9
 *      Author: arch
 */

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_

#include <cocos2d.h>
using namespace cocos2d;

class GameSprite {
public:
//	GameSprite(CCSprite* pSprite);
	GameSprite(const char* file); //通过pic文件构造
	virtual ~GameSprite();

	void setPosition(const CCPoint& position);
	CCSprite* getSprite();

	int getHp();         //状态 hp
	void setHp(int hp);

	bool isCollision(); //判断是否碰撞
	void tick();	//每周期更新

private:
	CCSprite* sprite;	//精灵类
	CCMotionStreak* streak; //添加阴影效果
	int hp;

};

#endif /* GAMESPRITE_H_ */
