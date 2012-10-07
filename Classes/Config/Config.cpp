/*
 * Config.cpp
 *
 *  Created on: 2012-9-16
 *      Author: arch
 */

#include "Config/Config.h"
#include <cocos2d.h>
using namespace cocos2d;

//TODO 返回值是？？？
Config* Config::instance = NULL;

Config* Config::sharedConfig() {
	if(instance != NULL) {
		return instance;
	}else  {
		instance = new Config();
		return instance;
	}
}

Config::Config() {
	//TODO
	//init();
}

Config::~Config() { }

void Config::release() {
	CC_SAFE_DELETE(instance);
}


void Config::init() {

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(size != NULL) {
		winSize = size;
	}

}

void Config::initFromXML() {
//	bool ret = CCUserDefault::sharedUserDefault()->getBoolForKey("exist");
//		if (ret) {
//			CCLog("用户存档已经存在，从其中读取。\n");
//			readConfig();
//		} else {
//			CCLog("初次使用，使用默认设置。");
//			saveConfig();
//		}

}


CCSize Config::getWinSize() {
	return winSize;
}


void Config::readConfig() {

}

void Config::saveConfig() {

}

void Config::showConfig() {

}


