/*
 * CrushGameScene.h
 *
 *  Created on: 2014/03/10
 *      Author: mainitiamai
 */

#ifndef CRUSHGAMESCENE_H_
#define CRUSHGAMESCENE_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

// 衝突時の処理
class CrushGameContactListener : public b2ContactListener
{
protected:
	cocos2d::CCObject* m_target;
	cocos2d::SEL_CallFunc m_selector;

public:
	CrushGameContactListener(cocos2d::CCObject* target , cocos2d::SEL_CallFunc selector );
	void BeginContact(b2Contact* contact);
};

class CrushGameScene : public cocos2d::CCLayer
{
protected:
	enum kTag{
		kTagBackground = 1,
	};

	enum kZOrder {
		kZOrder_Background = 1,
		kZOrder_Score,
		kZOrder_Flipper,
		kZorder_Object,
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

	CrushGameContactListener* crushGameContactListener;
	void createScore();
	void updateScore();

	int ballCount;
	void createReset();
	void tapReset();


	void create_back();			// 背景表示関係
	void create_ball(float _fX , float _fY);			// ボールの表示
	b2Body* m_pB2bodyBall;

	void create_object( int _iType , float _fX , float _fY , bool _bAnchor = true);
	void create_objects();

public:

	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(CrushGameScene);

	void update(float dt);

	void test();
	void callbackGotoTitleScene(CCObject* pSender);

};








#endif /* CRUSHGAMESCENE_H_ */
