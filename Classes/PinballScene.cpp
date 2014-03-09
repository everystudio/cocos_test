/*
 * PinballScene.cpp
 *
 *  Created on: 2014/02/22
 *      Author: mainitiamai
 */

#include "PinballScene.h"
#include "GB2ShapeCache-x.h"
#include "AppMacros.h"

static int PTM_RATIO = 32;
static int scorePoint = 0;

//#include "SkitSceneBase.h"
//#include "BlockGameScene.h"

USING_NS_CC;
void PinballScene::test()
{
	int i = 0;
	i += 10;
	return;
}


CCScene* PinballScene::scene()
{
	CCScene *scene = CCScene::create();

	PinballScene* layer = PinballScene::create();
	scene->addChild(layer);

	return scene;
}

bool PinballScene::init()
{
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCPoint scroll_pos = ccp(0 , winSize.height * 0.2);

	this->setPosition(scroll_pos);

	ballCount = 5;

	float scale = CCDirector::sharedDirector()->getContentScaleFactor();

	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CCSize frameSize = pEGLView->getFrameSize();

	// シェイプデータの読み込み
	gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("pinball_physics.plist" , scale );
	PTM_RATIO = gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->getPtmRatio();

	// タップを有効にする
	setTouchEnabled(true);

	initPhysics();

	// 背景を追加
	createBackground(2);

	// ボタンを追加
	createButton();

	// フリッパーを追加
	createFlipper();

	// 得点の追加
	createScore();

	// リセットボタンの表示
	createReset();

	// 毎フレーム処理の開始
	scheduleUpdate();

	char temp[100];
	sprintf( temp , "scale=%f x=%d y=%d" , scale , (int)frameSize.width , (int)frameSize.height);
	//std::string test = sprints( "scale=%f" , scale );

	CCLabelTTF *text = CCLabelTTF::create(temp, "arial", 20);
	text->setPosition(CCPointMake(10, 10));
	this->addChild(text);


	return true;
}

void PinballScene::initPhysics()
{
	b2Vec2 gravity;
	gravity.Set( 0.0f , -9.8f );
	world = new b2World( gravity );

	// Do we want to let bodies sleep?
	world->SetAllowSleeping(true);

	world->SetContinuousPhysics(true);

	// 衝突判定処理を追加
	gamePhysicsContactListener = new GamePhysicsContactListener(this , callfunc_selector(PinballScene::updateScore));
	world->SetContactListener(gamePhysicsContactListener );

	return;
}


void PinballScene::createBackground( int _iStageNo )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	char stage_name[100];
	char filename[100];

	sprintf( stage_name , "sample_stage_%.2d" , _iStageNo );
	sprintf( filename , "%s.png" , stage_name);

	// 背景
	CCSprite* bg = CCSprite::create( filename );
	bg->setPosition(CCPoint(winSize.width / 2 , winSize.height / 2 ));
	//bg->setPosition(CCPoint(winSize.width / 2  , 50 ));
	this->addChild( bg , kZOrder_Background , kTagBackground);
	// 背景の物理構造
	b2BodyDef bgBodyDef;
	bgBodyDef.type = b2_staticBody;
	bgBodyDef.position.Set(bg->getPositionX() / PTM_RATIO , bg->getPositionY() / PTM_RATIO);
	bgBodyDef.userData = bg;
	bgBody = world->CreateBody(&bgBodyDef);

	gbox2d::GB2ShapeCache* sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(bgBody , stage_name );
	bg->setAnchorPoint(sc->anchorPointForShape(stage_name));

	return;
}

void PinballScene::createButton()
{
	return;
}

void PinballScene::createFlipper()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	gbox2d::GB2ShapeCache* sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();

	// 左フリッパー
	CCPoint leftFlipperPos = ccp(winSize.width * 0.2 , winSize.height * 0.2);
	CCSprite* leftFlipper = CCSprite::create("flipper_left.png");
	leftFlipper->setPosition(leftFlipperPos);
	this->addChild(leftFlipper , kZOrder_Flipper);

	// 左フリッパー
	b2BodyDef leftFlipperBodyDef;
	leftFlipperBodyDef.type = b2_dynamicBody;
	leftFlipperBodyDef.position.Set(leftFlipperPos.x / PTM_RATIO , leftFlipperPos.y / PTM_RATIO);
	leftFlipperBodyDef.userData = leftFlipper;

	leftFlipperBody = world->CreateBody(&leftFlipperBodyDef);
	sc->addFixturesToBody(leftFlipperBody , "flipper_left");
	leftFlipper->setAnchorPoint(sc->anchorPointForShape("flipper_left"));
	leftFlipperBody->SetTransform(leftFlipperBody->GetPosition() , CC_DEGREES_TO_RADIANS(0));

	// 左フリッパーのジョイント
	b2RevoluteJointDef leftJointDef;
	leftJointDef.Initialize(leftFlipperBody , bgBody , leftFlipperBody->GetPosition());
	leftJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(-45);
	leftJointDef.upperAngle=CC_DEGREES_TO_RADIANS(  0);
	leftJointDef.enableLimit=true;
	world->CreateJoint(&leftJointDef);

	// 右フリッパー
	CCPoint rightFlipperPos = ccp(winSize.width * 0.8 , winSize.height * 0.2);
	CCSprite* rightFlipper = CCSprite::create("flipper_right.png");
	rightFlipper->setPosition(rightFlipperPos);
	this->addChild(rightFlipper , kZOrder_Flipper);

	// 右フリッパー
	b2BodyDef rightFlipperBodyDef;
	rightFlipperBodyDef.type = b2_dynamicBody;
	rightFlipperBodyDef.position.Set(rightFlipperPos.x / PTM_RATIO , rightFlipperPos.y / PTM_RATIO);
	rightFlipperBodyDef.userData = rightFlipper;

	rightFlipperBody = world->CreateBody(&rightFlipperBodyDef);
	sc->addFixturesToBody(rightFlipperBody , "flipper_right");
	rightFlipper->setAnchorPoint(sc->anchorPointForShape("flipper_right"));
	rightFlipperBody->SetTransform(rightFlipperBody->GetPosition() , CC_DEGREES_TO_RADIANS(0));

	// 右フリッパーのジョイント
	b2RevoluteJointDef rightJointDef;
	rightJointDef.Initialize(rightFlipperBody , bgBody , rightFlipperBody->GetPosition());
	rightJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(  0);
	rightJointDef.upperAngle=CC_DEGREES_TO_RADIANS( 45);
	rightJointDef.enableLimit=true;
	world->CreateJoint(&rightJointDef);

	return;
}

void PinballScene::createBall( float _x )
{
	if( ballCount <= 0 ){
		return;
	}

	ballCount -= 1;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// ボールの作成
	CCPoint ballPoint = ccp(_x , winSize.height * 0.95);
	CCSprite* ball = CCSprite::create("pinball_ball.png");
	ball->setPosition(ballPoint);
	this->addChild(ball , kZOrder_Ball);

	// ボールの物理構造
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(ballPoint.x / PTM_RATIO , ballPoint.y / PTM_RATIO );
	ballBodyDef.userData = ball;
	b2Body* body = world->CreateBody(&ballBodyDef);

	gbox2d::GB2ShapeCache* sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(body , "pinball_ball" );
	ball->setAnchorPoint(sc->anchorPointForShape("pinball_ball"));

	return;
}

void PinballScene::createScore()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// 得点の表示
	score = CCLabelTTF::create("0" , "" , SCORE_FONT_SIZE );
	score->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.18));
	this->addChild(score , kZOrder_Score );
	return;
}

void PinballScene::createReset()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// スコアの表示
	CCMenuItemImage* reset = CCMenuItemImage::create("block_blue.png" , "block_red.png" , this , menu_selector(PinballScene::tapReset));
	reset->setPosition(ccp(winSize.width*0.8 , winSize.height * 0.94 ));

	CCMenu* menu = CCMenu::create(reset , NULL );
	menu->setPosition(CCPointZero);
	this->addChild(menu , kZOrder_Button);
	return;
}

void PinballScene::tapReset()
{
	CCScene* scene = PinballScene::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
	return;
}


void PinballScene::update(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 1;

	world->Step(dt , velocityIterations , positionIterations );

	float scale = CCDirector::sharedDirector()->getContentScaleFactor();


	for(b2Body* b = world->GetBodyList() ; b ; b = b->GetNext()){
		if(b->GetUserData() != NULL ){
			CCSprite* myActor = (CCSprite*)b->GetUserData();

			if( b->GetPosition().y < 0 ){
				world->DestroyBody(b);
				this->removeChild(myActor);
				ballCount += 1;
				continue;
			}

			float physics_x = b->GetPosition().x * PTM_RATIO ;// scale;
			float physics_y = b->GetPosition().y * PTM_RATIO ;// scale;

			myActor->setPosition(CCPointMake( physics_x, physics_y));
			myActor->setRotation(-1*CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

	return;
}

void PinballScene::updateScore()
{
	CCString* string = CCString::createWithFormat("%d" , scorePoint );
	score->setString(string->getCString());
	return;
}


void PinballScene::ccTouchesBegan(CCSet* touches , CCEvent* event)
{
	CCSetIterator it;
	for(it = touches->begin() ; it != touches->end() ; ++it){
		CCTouch* touch = (CCTouch*)(*it);
		if(!touch){
			break;
		}
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCDirector* pDirector = CCDirector::sharedDirector();
		CCPoint location = pDirector->convertToGL(touch->getLocationInView());

		if(location.y > winSize.height /2 ){
			// 画面上部をタップ
			createBall(location.x);
		}
		else if( location.x < winSize.width/2){
			// 画面下左側
			leftFlipperBody->ApplyTorque( 3000);
		}
		else {
			// 画面下右側
			rightFlipperBody->ApplyTorque(-3000);
		}
	}
}




GamePhysicsContactListener::GamePhysicsContactListener(cocos2d::CCObject* target , cocos2d::SEL_CallFunc selector )
{
	m_target = target;
	m_selector = selector;
	return;
}

void GamePhysicsContactListener::BeginContact(b2Contact* contact)
{
	CCObject* userDataA = (CCObject*)contact->GetFixtureA()->GetUserData();
	CCObject* userDataB = (CCObject*)contact->GetFixtureB()->GetUserData();

	CCString* stringA = dynamic_cast<CCString*>(userDataA);
	CCString* stringB = dynamic_cast<CCString*>(userDataB);

	if(stringA->intValue() > 0 || stringB->intValue() > 0 ){
		scorePoint += stringA->intValue();
		scorePoint += stringB->intValue();
		(m_target->*m_selector)();
	}

	return;
}



















