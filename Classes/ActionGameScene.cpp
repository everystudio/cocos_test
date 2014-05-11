/*
 * ActionGame.cpp
 *
 *  Created on: 2014/02/27
 *      Author: mainitiamai
 */


#include "ActionGameScene.h"
#include "GB2ShapeCache-x.h"
#include "AppMacros.h"

#include "TitleScene.h"

static int PTM_RATIO = 32;
static int scorePoint = 0;

// ブランチテスト
// これもブランチテスト
// さらにブランチテスト

//#include "SkitSceneBase.h"
//#include "BlockGameScene.h"

USING_NS_CC;


CCScene* ActionGameScene::scene()
{
	CCScene *scene = CCScene::create();

	ActionGameScene* layer = ActionGameScene::create();
	scene->addChild(layer);

	return scene;
}


bool ActionGameScene::init()
{
	if(!CCLayer::init()){
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// タップを有効にする
	setTouchEnabled(true);

	// シングルタッチのみ
	setTouchMode(kCCTouchesOneByOne);

	// マップチップ表示 　ここから
	//CCTMXTiledMap* pTileMap = CCTMXTiledMap::create("desert.tmx");
	CCTMXTiledMap* pTileMap = CCTMXTiledMap::create("sample_map.tmx");
	this->addChild(pTileMap);

	CCLog("mapwidth:%f" , pTileMap->getMapSize().width);
	CCLog("mapehight:%f" , pTileMap->getMapSize().height);
	CCLog("tilewidth:%f" , pTileMap->getTileSize().width);
	CCLog("tilewidth:%f" , pTileMap->getTileSize().height);

	//レイアーの名前で取り出す
	CCTMXLayer *collisionLayer = pTileMap->layerNamed("collision");

	// マップチップ表示 　ここまで

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("totoki_airi_dot.plist");

	CCString* filename = CCString::createWithFormat("totoki_airi_03.png");

	//CCSprite* m_pTotoki = CCSprite::createWithSpriteFrameName( filename->getCString());
	m_pTotoki = SpriteBase::createWithSpriteFrameName( filename->getCString());

	m_pTotoki->setPosition(ccp((int)winSize.width / 2 , (int)winSize.height/2));

	this->addChild(m_pTotoki);

	CCAnimation* totoki_anim = CCAnimation::create();
	totoki_anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("totoki_airi_03.png"));
	totoki_anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("totoki_airi_04.png"));
	totoki_anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("totoki_airi_05.png"));
	totoki_anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("totoki_airi_06.png"));

	totoki_anim->setDelayPerUnit(0.5f); //アニメーションのスピード
	totoki_anim->setRestoreOriginalFrame(true); // 画像が元に戻るかどうか

	/// 無限ループさせる
	/// [例]
	/// 1  ... 一回ループさせる
	/// 2  ... 二回ループさせる
	/// -1 ... 無限ループさせる
	totoki_anim->setLoops(-1);

	CCAnimate *action = CCAnimate::create(totoki_anim);

	CCRepeatForever *actionreq = CCRepeatForever::create(action);
	CCRepeat *actionrrepeat =    CCRepeat::create(action , 1);

	m_pTotoki->runAction(actionrrepeat);
	//totoki->runAction(sequence);

	// b.pngへ変える
	//CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("totoki_airi_05.png");
	//totoki->setDisplayFrame(spriteFrame);


	//CCSprite* sample = CCSprite::create( "totoki_airi_dot/totoki_airi_01.png");
	//this->addChild( sample );


	//プレイヤー初期位置
	CCTMXObjectGroup *obj_group_player = pTileMap->objectGroupNamed("player");
	CCDictionary* dict_player_prop = obj_group_player->objectNamed("player_prop");

	int x = dict_player_prop->valueForKey("x")->intValue();
	int y = dict_player_prop->valueForKey("y")->intValue();

	m_pTotoki->setPosition(ccp(x , y));
	m_ptPosition = m_pTotoki->getPosition();
	m_ptSpeed.setPoint(0.0f , 0.0f);
	m_ptAccel.setPoint(0.0f , -0.001f);

	//totoki->setPosition(ccp((int)winSize.width / 2 + x, (int)winSize.height/2 + y));

	char log_buf[100];

	sprintf( log_buf, "x=%d y=%d" , x , y );

	CCLog( "test%s" , log_buf );

	CCLabelTTF *text = CCLabelTTF::create(log_buf, "arial", 20);
	text->setPosition(CCPointMake(150, 200));
	this->addChild(text);

	//properties->

	//pLoc = [self _getPositionFromObjectProperties:properties];

	// タイトル画面へ戻る
	CCMenuItemImage *pButtonTitle = CCMenuItemImage::create("block/block_yellow.png", "block/block_red.png", this, menu_selector(ActionGameScene::callbackGotoTitleScene));
	CCMenu* pBtnTitle = CCMenu::create(pButtonTitle, NULL);
	pBtnTitle->setPosition(ccp(winSize.width*0.9f, winSize.height*0.9f + 32) );
	this->addChild(pBtnTitle , kZOrder_Button);

		// 毎フレーム処理の開始
	scheduleUpdate();

	return true;
}

void ActionGameScene::ccTouchesBegan(CCSet* touches , CCEvent* event)
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
			/*
			CCPoint pos = m_pTotoki->getPosition();
			pos.x += 1.0f;
			m_pTotoki->setPosition(pos);
			*/
			//m_pTotoki->AddPosX(-1.0f);
			m_pTotoki->setFlipX(false);
			m_ptPosition.x +=-3.0f;
		}
		else {
			// 画面下右側
			//m_pTotoki->AddPosX( 1.0f);
			m_pTotoki->setFlipX(true);
			m_ptPosition.x += 3.0f;
		}
	}

	//CCRect test = m_pTotoki->getTextureRect();
	CCRect test = m_pTotoki->getRect();
	CCLog("totoki x=%f y=%f w=%f h=%f" , test.getMinX(), test.getMinY() , test.getMaxX() , test.getMaxY() );


	return;
}


void ActionGameScene::update(float dt)
{
	// オペレータでうまいこと加算できなかった
	m_ptSpeed.x += m_ptAccel.x;
	m_ptSpeed.y += m_ptAccel.y;

	m_ptPosition.x += m_ptSpeed.x;
	m_ptPosition.y += m_ptSpeed.y;

	m_pTotoki->setPosition( m_ptPosition );

	// 
	if( m_ptPosition.y < -72.0f){
		m_ptPosition.y = 200.0f;
	}

	return;
}







void ActionGameScene::callbackGotoTitleScene(CCObject* pSender)
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






