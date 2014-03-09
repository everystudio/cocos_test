/*
 * TitleScene.cpp
 *
 *  Created on: 2014/03/09
 *      Author: mainitiamai
 */
#include "TitleScene.h"

#include "PinballScene.h"

USING_NS_CC;

CCScene* TitleScene::scene()
{
	CCScene* scene = CCScene::create();
	TitleScene* layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

// 初期化
bool TitleScene::init()
{
	if(!CCLayer::init()){
		return false;
	}

	// タップイベントを取得する
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//シーン切り替えのトリガーになる"1"のボタン
	//ボタンをクリックすると、HelloWorld::myCallbackが発動
	CCMenuItemImage *pBtnItem = CCMenuItemImage::create("block/block_blue.png", "block/block_red.png", this, menu_selector(TitleScene::CallbackToPinballBase));
	CCMenu* pBtn = CCMenu::create(pBtnItem, NULL);
	pBtn->setPosition(ccp(s.width*.5, s.height*.5));
	//pBtn->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//pBtn->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2 ));
	pBtn->setPosition(visibleSize.width/2 ,visibleSize.height*0.1f);
	pBtn->setPosition(0.0f , 0.0f );
	this->addChild(pBtn);

	return true;
}


//"1"を押したときの関数。
void TitleScene::CallbackToPinballBase(CCObject* pSender)
{
	//次のシーンとして、HelloWorld2シーンをセット
	CCScene* nextScene = PinballScene::scene();
	//切り替えの時間を設定。ここでは1秒
	float duration = 1.0f;
	//フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
	CCScene* pScene = CCTransitionFade::create(duration, nextScene);
	if(pScene){
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}




