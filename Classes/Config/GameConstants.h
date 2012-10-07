/*
 * GameConstants.h
 *
 *  Created on: 2012-10-7
 *      Author: arch
 */

#ifndef GAMECONSTANTS_H_
#define GAMECONSTANTS_H_


//记录游戏状态
enum GameState {
	NOT_START,
	STARTED,
	GAME_OVER,
};

//TODO Node的Tag值
enum NodeTag {
	PLANE_SELF = 1000,
	PLANE_OTHER = 2000,
};



#endif /* GAMECONSTANTS_H_ */
