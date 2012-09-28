/*
 * Config.h
 *
 *  Created on: 2012-9-16
 *      Author: arch
 */

#ifndef CONFIG_H_
#define CONFIG_H_

class Config {
public:
	Config();
	virtual ~Config();

	//单例模式
	Config sharedConfig();

	//TODO setXX
	//TODO getXX

	//num of fires  敌机数量
	//屏幕尺寸
	//bool值 是否产生粒子
	//

private :
	CCSize winSize;
	//tag 常量
	const static int TAG_PLANE_SELF = 11;
	const static int TAG_PLANE_OTHER = 12;
	const static int TAG_BULLET = 13;

	boolean init;
	void init();

};

#endif /* CONFIG_H_ */
