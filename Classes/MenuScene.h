//
//  MenuScene.h
//  Game
//
//  Created by mac on 12-8-6.
//
//

#ifndef __Game__MenuScene__
#define __Game__MenuScene__

#include "cocos2d.h"


class MenuScene : public cocos2d::CCLayer
{
public:

    virtual bool init();

    static cocos2d::CCScene* scene();

    virtual void onExit();

    virtual void onEnter();

    // 退出回调函数
    void menuCloseCallback(CCObject* pSender);

    //游戏开始菜单回调函数
    void menuStartCallback(CCObject* pSender);

    //关于 回调函数
    void menuAboutCallback(CCObject* pSender);

    void menuExitCallback(CCObject* pSender);


    CREATE_FUNC(MenuScene);

};


#endif /* defined(__Game__MenuScene__) */
