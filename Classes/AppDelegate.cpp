#include <cocos2d.h>
#include <SimpleAudioEngine.h>
#include "AppDelegate.h"
#include "Test/HelloWorldScene.h"
#include "Scene/SceneManager.h"
#include  "Scene/MenuScene.h"


using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() { }

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);


    CCScene *pScene = MenuScene::scene();

    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

}
