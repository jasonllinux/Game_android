/*
 * GameScene.h
 *
 *  Created on: 2012-9-17
 *      Author: arch
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "Box2D.h"
#include <list>

using std::list;

//-------------------------------------------------------------------------------//

class MyContact {
public:
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
};

// Contact listener
class MyContactListener: public b2ContactListener {
	// Callbacks for derived classes.

	virtual void BeginContact(b2Contact* contact) {
		if (contact) {
			MyContact mc;
			mc.fixtureA = contact->GetFixtureA();
			mc.fixtureB = contact->GetFixtureB();

			contact_list.push_back(mc);
		}
		B2_NOT_USED(contact);
	}

	virtual void EndContact(b2Contact* contact) {
		contact_list.clear();
		B2_NOT_USED(contact);
	}
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	virtual void PostSolve(const b2Contact* contact,
			const b2ContactImpulse* impulse) {
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

public:
	std::list<MyContact> contact_list;

};

//-----------------------------------------------------------------------//
class GameScene: public cocos2d::CCLayer {

public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);
	void menuBackCallback(CCObject* pSender);

	//触屏事件
	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(cocos2d::CCTouch *touch,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouche,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouche,
			cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *touch,
			cocos2d::CCEvent *event);

	void addTarget();  //添加敌方部队
	void spriteMoveFinished(CCNode* sender);
	void gameLogic(float dt);

	CREATE_FUNC(GameScene)
	;
	void update(CCTime dt);

private:
//    CCMutableArray *  _shipLasers ;

//    int _nextShipLaser ;
	void addParticle();

};

#endif /* GAMESCENE_H_ */
