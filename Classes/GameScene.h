/*
 * GameScene.h
 *
 *  Created on: 2012-9-17
 *      Author: arch
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer {

public:
    virtual bool init();

    static cocos2d::CCScene* scene();

    void menuCloseCallback(CCObject* pSender);
    void menuBackCallback(CCObject* pSender);


    //触屏事件
    virtual void registerWithTouchDispatcher();

    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouche, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouche, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);

    void addTarget();  //添加敌方部队
    void spriteMoveFinished(CCNode* sender);
    void gameLogic(float dt);


    CREATE_FUNC(GameScene);

private :
//    CCMutableArray *  _shipLasers ;

//    int _nextShipLaser ;
    void addParticle();


};

#endif /* GAMESCENE_H_ */
