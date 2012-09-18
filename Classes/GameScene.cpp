/*
 * GameScene.cpp
 *
 *  Created on: 2012-9-17
 *      Author: arch
 */

#include "NewMenuScene.h"
#include "GameScene.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameScene::scene() {
	CCScene *scene = CCScene::create();

	GameScene *layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init() {
	if (!CCLayer::init()) {
		return false;
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//TODO 添加背景
	CCSprite* pSprite = CCSprite::create("back_game.png");
	pSprite->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(pSprite, 0);

	//TODO 添加精灵
	CCSprite* plane = CCSprite::create("plane.png");
	plane->setPosition(ccp(60,60));
	this->addChild(plane, 2, 1000);

	//TODO 添加动作

	//添加返回按钮
	CCMenuItemFont *backMenu = CCMenuItemFont::create("Back", this,
			menu_selector(GameScene::menuBackCallback));
	//exit->setAnchorPoint(CCPointZero);
	backMenu->setPosition(ccp(size.width/2,size.height/2));

	CCMenu* pMenu = CCMenu::create(backMenu, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//添加敌方部队
	//schedule_selector
	this->schedule(schedule_selector(GameScene::gameLogic), 1.0);

	//重要，设置允许触屏
	this->setTouchEnabled(true);

	return true;
}

//退出所有程序
void GameScene::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameScene::menuBackCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(NewMenuScene::scene());
}

//注册
void GameScene::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
			this, 0, true);
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
	//获取触点坐标
	CCPoint touchLocation = touch->locationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	CCLog("touch began*********************");

	return true;
}

void GameScene::ccTouchEnded(cocos2d::CCTouch * touch,
		cocos2d::CCEvent * event) {

}

void GameScene::ccTouchMoved(cocos2d::CCTouch *touch,
		cocos2d::CCEvent * event) {
	//移动精灵
	CCPoint touchLocation = touch->locationInView();
	CCPoint prevLocation = touch->previousLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	prevLocation = CCDirector::sharedDirector()->convertToGL(prevLocation);

	//sprite -> setPosition
	CCNode* pNode = getChildByTag(1000);
	if (pNode != NULL) {
		pNode->setPosition(touchLocation);
	}

}

void GameScene::ccTouchCancelled(cocos2d::CCTouch* touch,
		cocos2d::CCEvent* event) {

}

void GameScene::addTarget() {
	CCSprite *target = CCSprite::create("plane.jpg");

	//TODO y轴变x轴

	//Determin where to spawm the target along the Y axis;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = target->getContentSize().height / 2;
	int maxY = winSize.height - target->getContentSize().height / 2;

	int minX = target->getContentSize().width /2 ;
	int maxX = winSize.width - target->getContentSize().width/2;

	int rangeX = maxX - minX;

	int rangeY = maxY - minY;
	int actualY = (rand() % rangeY) + minY;

	int actualX = (rand() % rangeX) + minX;
	//create the target slightly off-screen along the right edge and along a random position along the y axis as calculated
//	target->setPosition(
//			ccp(winSize.width + (target->getContentSize().width/2), actualY));
	target->setPosition(ccp(
			actualX, winSize.height + (target->getContentSize().height/2)));

	this->addChild(target);

	//determine speed
	int minDuration = (int) 2.0;
	int maxDuratoin = (int) 4.0;
	int rangeDuration = maxDuratoin - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	//create the actions
//	CCFiniteTimeAction* actionMove = CCMoveTo::create((float) actualDuration,
//			ccp(0-target->getContentSize().width/2, actualY));
	CCFiniteTimeAction* actionMove = CCMoveTo::create((float) actualDuration,
			ccp(actualX, 0-target->getContentSize().height/2));

	//callFuncN selector
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this,
			callfuncN_selector(GameScene::spriteMoveFinished));
	target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

}

//move finished,删除该节点
void GameScene::spriteMoveFinished(CCNode* sender) {
	CCSprite* sprite = (CCSprite *) sender;
	this->removeChild(sprite, true);
}

//Game logic,动态添加节点
void GameScene::gameLogic(float dt) {
//    CCLog("add a move sprite...");
	this->addTarget();
}
