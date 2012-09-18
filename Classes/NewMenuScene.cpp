#include "NewMenuScene.h"
#include "SimpleAudioEngine.h"
#include "SceneManager.h"
#include "AboutScene.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* NewMenuScene::scene()
{
    CCScene *scene = CCScene::create();

    NewMenuScene *layer = NewMenuScene::create();

    scene->addChild(layer);

    return scene;
}


bool NewMenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize size = CCDirector::sharedDirector()->getWinSize();


    CCMenuItemFont::setFontSize(70);

    int delta = 200;


    //进入游戏
    CCMenuItemFont *start = CCMenuItemFont::create("Start", this, menu_selector(NewMenuScene::menuGameCallback));
    start->setPosition(size.width/2, size.height/2 +delta);

    //退出游戏
    CCMenuItemFont *exit = CCMenuItemFont::create("Exit", this, menu_selector(NewMenuScene::menuCloseCallback));
    exit->setPosition(size.width/2, size.height/2 - 2*delta);

    //关于
    CCMenuItemFont *about = CCMenuItemFont::create("About", this, menu_selector(NewMenuScene::menuAboutCallback));
    about->setPosition(size.width/2, size.height/2 );

    //设置
     CCMenuItemFont *set = CCMenuItemFont::create("Setting", this, menu_selector(NewMenuScene::menuCloseCallback));
     set->setPosition(size.width/2, size.height/2 -delta);

    //总菜单
    CCMenu* menu = CCMenu::create(start, exit, about, set, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu, 1);


    //添加背景
    CCSprite* pSprite = CCSprite::create("logo.png");
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);

    return true;
}

void NewMenuScene::menuCloseCallback(CCObject* pSender)
{
//	CCLog("close*************************");
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    exit(0);
#endif
}


void NewMenuScene::menuAboutCallback(CCObject* pSender)
{
	CCLog("Go to about scene");
	CCDirector::sharedDirector()->replaceScene(AboutScene::scene());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	SceneManager::loadScene();

#endif
}

void NewMenuScene::menuGameCallback(CCObject* pSender)
{
CCDirector::sharedDirector()->replaceScene(GameScene::scene());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#endif
}
