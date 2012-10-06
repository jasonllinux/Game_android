/*
 * GameScene.cpp
 *
 *  Created on: 2012-9-17
 *      Author: arch
 */

#include "MenuScene.h"
#include "GameScene.h"

#include "SimpleAudioEngine.h"
#include "Contact/MyContactListener.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define TILE_SIZE 32
#define PT_RATIO 32

GameScene::GameScene() {
	contactListener = new MyContactListener();
	//TODO new word
	b2Vec2 gravity(0, 0);
	world = new b2World(gravity);

}

GameScene::~GameScene() {
	if (world) {
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

	//添加粒子系统
	this->addParticle();
	//---碰撞检测
	// create physic world
//	b2Vec2 gravity(0, 0);
//	world = new b2World(gravity);
	world->SetAllowSleeping(false);
	//contact listener

	this->contactListener = new MyContactListener();
	world->SetContactListener(contactListener);

//	  spawnCar();
//
	schedule(schedule_selector(GameScene::tick));
	this->schedule(schedule_selector(GameScene::gameLogic), 1.0);
	this->schedule(schedule_selector(GameScene::update), 1.f);

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
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

//注册
void GameScene::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
			this, 0, true);
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
	//获取触点坐标
	CCPoint touchLocation = touch->getLocationInView();
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

	return true;
}

//触屏结束的时候发射子弹
void GameScene::ccTouchEnded(cocos2d::CCTouch * touch,
		cocos2d::CCEvent * event) {
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	// Set up initial location of projectile
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pBullet = CCSprite::create("bullet.png",
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
	pBullet->runAction(
			CCSequence::create(CCMoveTo::create(realMoveDuration, realDest),
					CCCallFuncN::create(this,
							callfuncN_selector(GameScene::spriteMoveFinished)),
					NULL));

}

void GameScene::ccTouchMoved(cocos2d::CCTouch *touch,
		cocos2d::CCEvent * event) {
	//移动精灵
	CCPoint touchLocation = touch->getLocationInView();
	CCPoint prevLocation = touch->getPreviousLocationInView();
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

//随机添加Sprite
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
			callfuncN_selector(GameScene::spriteDone));
	target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	//TODO 添加Boxbody
	addBoxBodyForSprite(target);
	this->addChild(target, 1, 2);

}

//move finished,删除该节点
void GameScene::spriteMoveFinished(CCNode* sender) {
	CCSprite* sprite = (CCSprite *) sender;
	this->removeChild(sprite, true);
}

//Game logic,动态添加节点
void GameScene::gameLogic(float dt) {
	this->addTarget();
}

//碰撞检测
void GameScene::update(CCTime dt) {
	//散播子弹
	spawmBullets();
}

//为Sprite加上刚体
void GameScene::addBoxBodyForSprite(cocos2d::CCSprite* sprite) {
	//PTM_RATIO  ，这个数一般定义为： 32.0，在box 世界中 是以 米 为单位的，这里是将坐标兑换为box世界中的米，即除以 PTM_RATIO
	// Create physic body for cat
	b2PolygonShape polygon;
	polygon.SetAsBox((float) sprite->getContentSize().width / PT_RATIO / 2,
			(float) sprite->getContentSize().height / PT_RATIO / 2);

	b2FixtureDef spriteShapeDef;
	spriteShapeDef.shape = &polygon;
	spriteShapeDef.density = 10.f;
	spriteShapeDef.isSensor = true;   // 对象之间有碰撞检测但是又不想让它们有碰撞反应
//	spriteShapeDef.isSensor = false;

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position = b2Vec2((float) (sprite->getPosition().x / PT_RATIO),
			(float) (sprite->getPosition().y / PT_RATIO));
	bd.userData = sprite;

	b2Body* spriteBody = world->CreateBody(&bd);
	spriteBody->CreateFixture(&spriteShapeDef);

}

//散播子弹
void GameScene::spawmBullets() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* cat = CCSprite::create("bullet.png");

	float minY = cat->getContentSize().height / 2;
	float maxY = winSize.height - cat->getContentSize().height / 2;
	float y = minY + rand() % (int) (maxY - minY);

	float startX = winSize.width + cat->getContentSize().width / 2;
	float endX = -cat->getContentSize().width / 2;

	CCPoint startPos = ccp(startX, y);
	CCPoint endPos = ccp(endX, y);

	cat->setPosition(startPos);

	cat->runAction(
			CCSequence::create(CCMoveTo::create(10.f, endPos),
					CCCallFuncN::create(this,
							callfuncN_selector(GameScene::spriteDone)), NULL));
	//TODO 添加BoxBody
	addBoxBodyForSprite(cat);
	addChild(cat, 1, 1);
}



//销毁Sprite
//TODO 调用
void GameScene::spriteDone(CCNode* sender) {

//	CCLog("Sprite Done");
	// sprites被销毁的时候，我们需要销毁Box2d的body
	CCSprite* sprite = dynamic_cast<CCSprite*>(sender);
	if (sprite) {
		b2Body* spriteBody = NULL;
		for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
			if (b->GetUserData() != NULL) {
				CCSprite* curSprite = (CCSprite*) b->GetUserData();
				if (curSprite == sprite) {

//					CCLog("亲，碰撞了！！");
					spriteBody = b;
					removeChild(sprite, true);
					world->DestroyBody(spriteBody);
					break;
				}
			}

			//if (spriteBody)
			//{
			//  world->DestroyBody(spriteBody);
			//}

			// removeChild(sprite, true);
		}
	}
}

//添加粒子发射器，粒子效果
void GameScene::addParticle() {
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

}

//没周期检测碰撞 判断 销毁实体
void GameScene::tick(float dt) {
	if (world) {
		world->Step(dt, 10, 10);
	}

// 基于cocos2d的精灵位置来更新box2d的body位置
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			CCSprite* sprite = (CCSprite*) b->GetUserData();
			if (sprite) {
				b2Vec2 pt = b2Vec2((float) (sprite->getPosition().x / PT_RATIO),
						(float) (sprite->getPosition().y / PT_RATIO));
				float angle =
						(float) CC_DEGREES_TO_RADIANS(sprite->getRotation());
				b->SetTransform(pt, angle);
			}
		}
	}

	std::list<b2Body*> toDestroy_list;

	for (std::list<MyContact>::iterator it = contactListener->contact_list.begin(); it != contactListener->contact_list.end(); ++it) {
		MyContact& contact = *it;

		b2Body* bodyA = contact.fixtureA->GetBody();
		b2Body* bodyB = contact.fixtureB->GetBody();

		CCSprite* sa = (CCSprite*) bodyA->GetUserData();
		CCSprite* sb = (CCSprite*) bodyB->GetUserData();

		if (sa && sb) {
			if (sa->getTag() == 1 && sb->getTag() == 2) {
				//TODO 只执行这个,有问题
				CCLog("To Destroy sb");
				toDestroy_list.push_back(bodyB);
			} else if (sa->getTag() == 2 && sa->getTag() == 1) {
				CCLog("To Destroy sa");
				toDestroy_list.push_back(bodyA);
			}
		}
	}

	//销毁碰撞的实体
	std::list<b2Body*>::iterator it = toDestroy_list.begin();
	while (it != toDestroy_list.end()) {
		if ((*it)->GetUserData() != NULL) {
			CCSprite* sprite = (CCSprite*) ((*it)->GetUserData());
			if (sprite) {
				removeChild(sprite, true);
			}
			world->DestroyBody(*it);
		}
		++it;
	}

	toDestroy_list.clear();

}

