/*
 * GameSprite.cpp
 *
 *  Created on: 2012-10-9
 *      Author: arch
 */

#include "GameSprite.h"

//GameSprite::GameSprite(CCSprite* pSprite) {
//	this->sprite = pSprite;
//	this->hp = 100;
//
//}

GameSprite::GameSprite(const char* file) {
	this->sprite = CCSprite::create(file);
	//TODO 待调整
	this->streak = CCMotionStreak::create(2,2,2,ccColor4F(255,0,0,255),file);
	this->hp = 100;
}

GameSprite::~GameSprite() {
	delete sprite;
}

void GameSprite::setPosition(CCPoint& position) {
	sprite->setPosition(position);
	streak->setPosition(position);
}

bool GameSprite::isCollision() {
	//TODO如何判断
	return false;
}

CCSprite* GameSprite::getSprite() {
	return sprite;
}

void GameSprite::tick() {

}

int GameSprite::getHp() {
	return hp;
}

void GameSprite::setHp(int hp) {
	this->hp = hp;
}

