/*
 * SceneManager.h
 *
 *  Created on: 2012-9-16
 *      Author: arch
 */

#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

#include <cocos2d.h>
using namespace cocos2d;

//存放一些于游戏的常量
enum SceneType{
    ABOUT_SCENE,
    GAME_SCENE,
    BACK_TO_HOME,
    EXIT,
    SETTING,
};

class SceneManager {
public:
	 static void loadScene(SceneType type);

};

#endif /* SCENEMANAGER_H_ */
