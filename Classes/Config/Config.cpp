/*
 * Config.cpp
 *
 *  Created on: 2012-9-16
 *      Author: arch
 */

#include "Config/Config.h"

Config::Config() {

}

Config::~Config() {

}

//获得全局对象指针
Config* Config::sharedConfig() {
	if(!init) {
		//若没有 初始化
		init();
		return this;
	}else  {
		//若已经初始化
		return this;
	}

}


void Config::init() {

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(size != NULL) {
		winSize = size;
	}

}


Config::getWinSize() {
	return winSize;
}

