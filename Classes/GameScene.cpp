/*
 * GameScene.cpp
 *
 *  Created on: 2012-9-17
 *      Author: arch
 */

//#include <Box2D/Box2D.h>

#include "NewMenuScene.h"
#include "GameScene.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	if(world != NULL) {
		delete world;
	}
}


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
	//每帧调用
	this->schedule(schedule_selector(GameScene::gameLogic), 1.0);
	this->schedule(schedule_selector(GameScene::update));

	//重要，设置允许触屏
	this->setTouchEnabled(true);

	//TODO 粒子系统
//	//初始化粒子
//	CCParticleSystemQuad * m_emitter = new CCParticleSystemQuad();
//	m_emitter->initWithTotalParticles(50);
//	//设置半径
//	m_emitter->setRadialAccel(-120);
//	m_emitter->setRadialAccelVar(0);
//	m_emitter->setPosition(size.width/2, size.height/2);
////	pSprite->addChild(m_emitter,10);

	CCParticleSystem* m_emitter;
	m_emitter = new CCParticleSystemQuad();
	m_emitter->initWithTotalParticles(50);
	this->addChild(m_emitter, 10);
	m_emitter->setTexture(
			CCTextureCache::sharedTextureCache()->addImage("fire1.png"));
	m_emitter->setDuration(-1);

	// gravity
	m_emitter->setGravity(CCPointZero);

	// angle
	m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);

	// speed of particles
	m_emitter->setSpeed(160);
	m_emitter->setSpeedVar(20);

	// radial
	m_emitter->setRadialAccel(-120);
	m_emitter->setRadialAccelVar(0);

	// tagential
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);

	// emitter position
	m_emitter->setPosition(CCPointMake(160,240));
	m_emitter->setPosVar(CCPointZero);

	// life of particles
	m_emitter->setLife(4);
	m_emitter->setLifeVar(1);

	// spin of particles
	m_emitter->setStartSpin(0);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(0);

	// color of particles
	ccColor4F startColor = { 0.5f, 0.5f, 0.5f, 1.0f };
	m_emitter->setStartColor(startColor);

	ccColor4F startColorVar = { 0.5f, 0.5f, 0.5f, 1.0f };
	m_emitter->setStartColorVar(startColorVar);

	ccColor4F endColor = { 0.1f, 0.1f, 0.1f, 0.2f };
	m_emitter->setEndColor(endColor);

	ccColor4F endColorVar = { 0.1f, 0.1f, 0.1f, 0.2f };
	m_emitter->setEndColorVar(endColorVar);

	// size, in pixels
	m_emitter->setStartSize(80.0f);
	m_emitter->setStartSizeVar(40.0f);
	m_emitter->setEndSize(kParticleStartSizeEqualToEndSize);

	// emits per second
	m_emitter->setEmissionRate(
			m_emitter->getTotalParticles() / m_emitter->getLife());

	// additive
	m_emitter->setBlendAdditive(true);

	//---------------------------------------------------------

	//-------------------------------------碰撞检测
	// create physic world
	b2Vec2 gravity(0,0);
	world = new b2World(gravity);
	world->SetAllowSleeping(false);
	//contact listener
	this->contactListener = new MyContactListener();
	world->SetContactListener(contactListener);

//	  spawnCar();
//
//	  schedule(schedule_selector(HelloWorld::tick));
//	  schedule(schedule_selector(HelloWorld::secondUpdate), 1.f);

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
//	CCLog("touch began*********************");

	return true;
}

//触屏结束的时候发射子弹
void GameScene::ccTouchEnded(cocos2d::CCTouch * touch, cocos2d::CCEvent * event) {
	CCPoint location = touch->locationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);


	// Set up initial location of projectile
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pBullet = CCSprite::spriteWithFile("bullet.png",
			CCRectMake(0, 0, 20 ,20));
	pBullet->setPosition(ccp(20, winSize.height/2));

	// Determinie offset of location to projectile
	int offX = location.x - pBullet->getPosition().x;
	int offY = location.y - pBullet->getPosition().y;

	if (offX <= 0)
		return;

	this->addChild(pBullet);

	// Determine where we wish to shoot the pBullet to
	int realX = winSize.width + (pBullet->getContentSize().width / 2);
	float ratio = (float) offY / (float) offX;
	int realY = (realX * ratio) + pBullet->getPosition().y;
	CCPoint realDest = ccp(realX, realY);

	// Determine the length of how far we're shooting
	int offRealX = realX - pBullet->getPosition().x;
	int offRealY = realY - pBullet->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY * offRealY));
	float velocity = 480 / 1; // 480pixels/1sec
	float realMoveDuration = length / velocity;

	// Move pBullet to actual endpoint
	pBullet->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(realMoveDuration, realDest),
										   CCCallFuncN::actionWithTarget(this,
										   callfuncN_selector(GameScene::spriteMoveFinished)),
										   	   NULL));

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

	//TODO 随机选择敌机
	int n = 1;
	CCSprite *target = CCSprite::create("fire1.png");

	//Determin where to spawm the target along the Y axis;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//	int minY = target->getContentSize().height / 2;
//	int maxY = winSize.height - target->getContentSize().height / 2;
	int minX = target->getContentSize().width / 2;
	int maxX = winSize.width - target->getContentSize().width / 2;

	int rangeX = maxX - minX;
//	int rangeY = maxY - minY;
//	int actualY = (rand() % rangeY) + minY;

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

//TODO 每帧自动调用
//碰撞检测
void GameScene::update(CCTime dt)
{

//	CCLog("Game Scene update........");
//	CCArray<CCSprite* > *projectilesToDelete = new CCArray<CCSprite*>;
//	CCMutableArray<CCSprite*> *projectilesToDelete =  new CCMutableArray<CCSprite*>;

	//记录碰撞后需要移除的Sprite
	CCArray* projectilesToDelete =new CCArray();
//	CCArray::


//	CCArray<CCSprite*>::CCArrayIterator it, jt;  //迭代器

}
