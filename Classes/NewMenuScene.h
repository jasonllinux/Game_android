/*
 * NewMenuScene.h
 *
 *  Created on: 2012-9-15
 *      Author: arch
 */

#ifndef NEWMENUSCENE_H_
#define NEWMENUSCENE_H_

#include "cocos2d.h"

using namespace cocos2d;

class NewMenuScene : public cocos2d::CCLayer
{
public:
    virtual bool init();

    static cocos2d::CCScene* scene();

    void menuCloseCallback(CCObject* pSender);
    void menuAboutCallback(CCObject* pSender);
    void menuGameCallback(CCObject* pSender);

    CREATE_FUNC(NewMenuScene);

};

#endif /* NEWMENUSCENE_H_ */
