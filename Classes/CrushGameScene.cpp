
#include "CrushGameScene.h"
#include "GB2ShapeCache-x.h"
#include "AppMacros.h"

#include "TitleScene.h"

static int PTM_RATIO = 32;

USING_NS_CC;



CCScene* CrushGameScene::scene()
{
	CCScene *scene = CCScene::create();

	CrushGameScene* layer = CrushGameScene::create();
	scene->addChild(layer);

	return scene;
}


bool CrushGameScene::init()
{
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float scale = CCDirector::sharedDirector()->getContentScaleFactor();

	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	CCSize frameSize = pEGLView->getFrameSize();

	// シェイプデータの読み込み
	gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("crush_game/crush_stage_00.plist" , scale );
	PTM_RATIO = gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->getPtmRatio();

	// タップを有効にする
	setTouchEnabled(true);

	// 物理環境設定
	initPhysics();

	// 背景表示
	create_back();

	m_pB2bodyBall = NULL;		// とりあえず初期化
	float ball_x = winSize.width * 0.2f;
	float ball_y = winSize.height/ 2;
	create_ball( ball_x , ball_y );

	// 障害物を作る
	create_objects();

	char temp[100];
	sprintf( temp , "scale=%f x=%d y=%d" , scale , (int)frameSize.width , (int)frameSize.height);
	//std::string test = sprints( "scale=%f" , scale );
	CCLog( "%s" , temp );

	// 毎フレーム処理の開始
	scheduleUpdate();

	// 翠ラッシュゲーム
	CCMenuItemImage *pButtonCrush = CCMenuItemImage::create("block/block_yellow.png", "block/block_red.png", this, menu_selector(CrushGameScene::callbackGotoTitleScene));
	CCMenu* pBtnCrs = CCMenu::create(pButtonCrush, NULL);
	pBtnCrs->setPosition(ccp(winSize.width*0.9f, winSize.height*0.9f + 32) );
	this->addChild(pBtnCrs , kZOrder_Button);


	return true;
}

void CrushGameScene::initPhysics()
{

	// 今回は重力なし
	b2Vec2 gravity;
	gravity.Set( 0.0f , 0.0f );			// 重力の影響はなし
	world = new b2World( gravity );

	// Do we want to let bodies sleep?
	world->SetAllowSleeping(true);

	world->SetContinuousPhysics(true);

	// 衝突判定処理を追加
	crushGameContactListener = new CrushGameContactListener(this , callfunc_selector(CrushGameScene::updateScore));
	world->SetContactListener(crushGameContactListener );

	return;
}

void CrushGameScene::create_back()
{
	CCLog("create_back");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	char dir[100];
	char stage_name[100];
	char filename[100];

	sprintf( dir , "crush_game"  );
	sprintf( stage_name , "stage_01"  );
	//sprintf( stage_name , "sample_stage_01"  );
	sprintf( filename , "%s/%s.png" ,dir , stage_name);

	CCLog( "%s" , filename );

	// 背景
	CCSprite* bg = CCSprite::create( filename );
	bg->setPosition(CCPoint(winSize.width / 2 , winSize.height / 2 ));

	CCLog( "%f : %f" , winSize.width/2 , winSize.height /2 );

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

void CrushGameScene::create_ball( float _fX , float _fY)
{
	CCLog("create_ball:_fX=%f , _fY=%f" , _fX , _fY);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	char dir[100];
	char ball_name[100];
	char filename[100];

	sprintf( dir , "crush_game"  );
	sprintf( ball_name , "ball"  );
	sprintf( filename , "%s/%s.png" ,dir , ball_name);
	CCLog( "ball load filename:%s" , filename );

	// 背景
	CCSprite* ball = CCSprite::create( filename );
	ball->setPosition(CCPoint(_fX , _fY ));
	this->addChild( ball , kZOrder_Ball );

	// 背景の物理構造
	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(ball->getPositionX() / PTM_RATIO , ball->getPositionY() / PTM_RATIO);
	ballBodyDef.userData = ball;
	m_pB2bodyBall = world->CreateBody(&ballBodyDef);

	gbox2d::GB2ShapeCache* sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(m_pB2bodyBall , ball_name );
	ball->setAnchorPoint(sc->anchorPointForShape(ball_name));

	// 物体に力を与える
	m_pB2bodyBall->ApplyForce(
		b2Vec2(0,50), // (0,0)から(0,50)へ上向きに垂直の力を作成
		m_pB2bodyBall->GetWorldCenter() // 起点を物体の中央にとる
		);
	//objectBody->SetAngularVelocity( 1.0f );
	m_pB2bodyBall->SetLinearDamping(0.2f);
	m_pB2bodyBall->SetAngularDamping(0.2f);

	return;
}

void CrushGameScene::create_object( int _iType , float _fX , float _fY , bool _bAnchor )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	char dir[100];
	char name[100];
	char fullname[100];

	sprintf( dir , "crush_game"  );
	sprintf( name , "object_%.2d" , _iType );
	sprintf( fullname , "%s/%s.png" ,dir , name);
	CCLog( "object load filename:%s" , fullname );

	// オブジェクト
	CCSprite* object = CCSprite::create( fullname );
	object->setPosition(CCPoint(_fX , _fY ));
	this->addChild( object , kZorder_Object );

	// 背景の物理構造
	b2BodyDef objectBodyDef;
	objectBodyDef.type = b2_dynamicBody;
	objectBodyDef.position.Set(object->getPositionX() / PTM_RATIO , object->getPositionY() / PTM_RATIO);
	objectBodyDef.userData = object;
	b2Body* objectBody = world->CreateBody(&objectBodyDef);

	//objectBody->SetAngularVelocity( 1.0f );
	objectBody->SetLinearDamping(1.0f);
	objectBody->SetAngularDamping(1.0f);

	float ang_damping = objectBody->GetAngularDamping();
	float ang_velo = objectBody->GetAngularVelocity();

	CCLog("GetAngularVelocity[%f] GetAngularVelocity[%f]" , ang_velo , ang_damping );

	gbox2d::GB2ShapeCache* sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(objectBody , name );
	object->setAnchorPoint(sc->anchorPointForShape(name));

	if( _bAnchor ){
		// ジョイントが必要な場合はここで作る
		b2RevoluteJointDef joint_def;
		joint_def.Initialize(objectBody , bgBody , objectBody->GetPosition());
		//joint_def.lowerAngle = CC_DEGREES_TO_RADIANS(-45);
		//joint_def.upperAngle=CC_DEGREES_TO_RADIANS(  0);
		joint_def.enableLimit=false;
		world->CreateJoint(&joint_def );
	}



	return;
}

void CrushGameScene::create_objects()
{
	create_object( 1  , 100.0f , 250.0f );
	create_object( 2  , 200.0f , 200.0f , false );
	create_object( 3  , 150.0f , 100.0f , false );
	create_object( 4  , 200.0f , 200.0f );
	return;
}




void CrushGameScene::updateScore()
{
	return;
}

void CrushGameScene::ccTouchesBegan( cocos2d::CCSet* touches , cocos2d::CCEvent* event)
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
		}
		else if( location.x < winSize.width/2){
			// 画面下左側
			//leftFlipperBody->ApplyTorque( 3000);
		}
		else {
			// 画面下右側
			//rightFlipperBody->ApplyTorque(-3000);
		}

		if( m_pB2bodyBall != NULL ){

			float angle = m_pB2bodyBall->GetAngle();
			m_pB2bodyBall->SetTransform(b2Vec2(location.x/ PTM_RATIO,location.y/ PTM_RATIO) , angle );

			CCLog( "x=%f,y=%f" , location.x , location.y );

			m_pB2bodyBall->SetLinearVelocity(b2Vec2(30,30));
/*
			m_pB2bodyBall->ApplyForce(
				b2Vec2(1000,1000), // (0,0)から(0,50)へ上向きに垂直の力を作成
				m_pB2bodyBall->GetWorldCenter() );// 起点を物体の中央にとる
*/
		}
	}
	return;
}


void CrushGameScene::update(float dt)
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





CrushGameContactListener::CrushGameContactListener(cocos2d::CCObject* target , cocos2d::SEL_CallFunc selector )
{
	m_target = target;
	m_selector = selector;
	return;
}

void CrushGameContactListener::BeginContact(b2Contact* contact)
{
	CCObject* userDataA = (CCObject*)contact->GetFixtureA()->GetUserData();
	CCObject* userDataB = (CCObject*)contact->GetFixtureB()->GetUserData();

	CCString* stringA = dynamic_cast<CCString*>(userDataA);
	CCString* stringB = dynamic_cast<CCString*>(userDataB);

	if(stringA->intValue() > 0 || stringB->intValue() > 0 ){
		//scorePoint += stringA->intValue();
		//scorePoint += stringB->intValue();
		//(m_target->*m_selector)();
	}

	return;
}




void CrushGameScene::callbackGotoTitleScene(CCObject* pSender)
{
	//次のシーンとして、HelloWorld2シーンをセット
	CCScene* nextScene = TitleScene::scene();
	//切り替えの時間を設定。ここでは1秒
	float duration = 1.0f;
	//フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
	CCScene* pScene = CCTransitionFade::create(duration, nextScene);
	if(pScene){
		CCDirector::sharedDirector()->replaceScene(pScene);
	}

	return;
}







