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

	//num of fires  敌机数量
	//屏幕尺寸
	//bool值 是否产生粒子
	//

private :

};

#endif /* CONFIG_H_ */
