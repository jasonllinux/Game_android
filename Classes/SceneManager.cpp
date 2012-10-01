/*
 * SceneManager.cpp
 *
 *  Created on: 2012-9-16
 *      Author: arch
 */

#include "SceneManager.h"

//include some scenes
//#include "About.h"
//#include "GameScene.h"
#include "MenuScene.h"

void SceneManager::loadScene(SceneType type) {

    switch (type) {
        case GAME_SCENE:
            CCLog("GAME SCENE");
            CCDirector::sharedDirector()->replaceScene(GameScene::scene());
            break;
        case ABOUT_SCENE:
            CCLog("About Scene");
            CCDirector::sharedDirector()->replaceScene(AboutScene::scene());
            break;
        case EXIT:
            CCLog("exit");
            break;
        case BACK_TO_HOME:
            CCLog("back to home");
            CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
            break;
        default:
            break;
    }

}
