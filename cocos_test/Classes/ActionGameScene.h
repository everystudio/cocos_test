/*
 * ActionGame.h
 *
 *  Created on: 2014/02/27
 *      Author: mainitiamai
 */

#ifndef ACTIONGAME_H_
#define ACTIONGAME_H_

#include "cocos2d.h"

class ActionGameScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(ActionGameScene);
};




#endif /* ACTIONGAME_H_ */
