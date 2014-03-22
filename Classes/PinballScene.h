/*
 * PinballScene.h
 *
 *  Created on: 2014/02/22
 *      Author: mainitiamai
 */

#ifndef PINBALLSCENE_H_
#define PINBALLSCENE_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class GamePhysicsContactListener : public b2ContactListener
{
protected:
	cocos2d::CCObject* m_target;
	cocos2d::SEL_CallFunc m_selector;

public:
	GamePhysicsContactListener(cocos2d::CCObject* target , cocos2d::SEL_CallFunc selector );
	void BeginContact(b2Contact* contact);
};

class PinballScene : public cocos2d::CCLayer
{
protected:
	enum kTag{
		kTagBackground = 1,
	};

	enum kZOrder {
		kZOrder_Background = 1,
		kZOrder_Score,
		kZOrder_Flipper,
		kZOrder_Ball,
		kZOrder_Button,
	};

	void createBackground( int _iStageNo = 1);
	void createButton();
	void createFlipper();

	b2World* world;
	void initPhysics();

	b2Body* bgBody;

	void createBall(float _x);
	virtual void ccTouchesBegan( cocos2d::CCSet* touches , cocos2d::CCEvent* event);

	b2Body* leftFlipperBody;
	b2Body* rightFlipperBody;

	cocos2d::CCLabelTTF* score;

	GamePhysicsContactListener* gamePhysicsContactListener;
	void createScore();
	void updateScore();

	int ballCount;
	void createReset();
	void tapReset();

public:

	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PinballScene);

	void update(float dt);

	void test();

	void callbackGotoTitleScene(CCObject* pSender);

};







#endif /* PINBALLSCENE_H_ */








