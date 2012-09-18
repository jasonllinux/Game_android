
#include "MenuScene.h"
#include "AboutScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
//#include "SceneManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();

    MenuScene *layer = MenuScene::create();

    scene->addChild(layer);

    return scene;
}


bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCLabelTTF* pLabel = CCLabelTTF::create("Jasonllinux", "Marker Felt", 60);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

//    CCMenuItemLabel *menuItem = CCMenuItemLabel::itemWithLabel(pLabel,this,menu_selector(MenuScene::menuExitCallback));
//
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
//    this->addChild(pLabel, 1);
//    menuItem->setPosition(ccp(size.width / 2, size.height - 20));
//    this->addChild(menuItem, 1);

    //添加背景
    CCSprite* pSprite = CCSprite::create("logo.png");
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    this->addChild(pSprite, 0);


    //增加自己的菜单
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    //添加背景音乐
//    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("feng.mp3");
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("feng.mp3");
//
    double distance = 120; //菜单之间相隔的距离

    CCMenuItemFont::setFontSize(70);
    CCMenuItemFont::setFontName("Marker Felt");

    CCMenuItemFont *start = CCMenuItemFont::create("Start", this, menu_selector(MenuScene::menuStartCallback));
    //start->setAnchorPoint(CCPointZero);

    start->setPosition(ccp(size.width/2,size.height/2+distance));
    start->setEnabled(true);
    this->addChild(start);

    CCMenuItemFont *about = CCMenuItemFont::create("About", this, menu_selector(MenuScene::menuCloseCallback));
    //about->setAnchorPoint(CCPointZero);
    about->setPosition(ccp(size.width/2,size.height/2));
    about->setEnabled(true);
    this->addChild(about);


    CCMenuItemFont *exit = CCMenuItemFont::create("Exit", this, menu_selector(MenuScene::menuCloseCallback));
//    CCMenuItemFont *exit = CCMenuItemFont::create("Exit");
    //exit->setAnchorPoint(CCPointZero);
//    CCMenuItem* exitItem = CCMenuItem::itemWithTarget(exit, menu_selector(MenuScene::menuCloseCallback));
    exit->setPosition(ccp(size.width/2, size.height/2-distance));
    exit->setEnabled(true);
    this->addChild(exit);

//    CCMenu* pMenu2 = CCMenu::create(start, about, exit, NULL);
//    pMenu2->setPosition(CCPointZero);
//    this->addChild(pMenu2);

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MenuScene::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

//#endif

    return true;
}

void MenuScene::onEnter()
{
//    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("feng.mp3", true);
//    //播放的时候 其他选项无法响应
}


//退出时，关闭音乐
void MenuScene::onExit()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}



void MenuScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    exit(0);
#endif
}

void MenuScene::menuStartCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
//    SceneManager::loadScene(GAME_SCENE);

}

void MenuScene::menuAboutCallback(CCObject* pSender)
{
//    SceneManager::loadScene(ABOUT_SCENE);

}

void MenuScene::menuExitCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    exit(0);
#endif
}
