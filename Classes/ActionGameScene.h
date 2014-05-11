/*
 * ActionGame.h
 *
 *  Created on: 2014/02/27
 *      Author: mainitiamai
 */

#ifndef ACTIONGAME_H_
#define ACTIONGAME_H_

#include "cocos2d.h"
#include "Lib/SpriteBase.h"

#include "CollisionManager.h"

class ActionGameScene : public cocos2d::CCLayer
{
public:
	SpriteBase* m_pTotoki;
	CCPoint m_ptAccel;
	CCPoint m_ptSpeed;
	CCPoint m_ptPosition;

	CollisionManager m_cCollisionManager;

	enum kZOrder {
		kZOrder_Background = 1,
		kZOrder_Score,
		kZOrder_Flipper,
		kZorder_Object,
		kZOrder_Ball,
		kZOrder_Button,
	};

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(ActionGameScene);

	void callbackGotoTitleScene(CCObject* pSender);

	virtual void ccTouchesBegan( cocos2d::CCSet* touches , cocos2d::CCEvent* event);

	void update(float dt);

};




#endif /* ACTIONGAME_H_ */
