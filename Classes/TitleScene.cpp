/*
 * TitleScene.cpp
 *
 *  Created on: 2014/03/09
 *      Author: mainitiamai
 */
#include "TitleScene.h"

#include "CrushGameScene.h"
#include "PinballScene.h"
#include "ActionGameScene.h"

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

	// 青ピンボールへ
	CCMenuItemImage *pBtnItem = CCMenuItemImage::create("block/block_blue.png", "block/block_red.png", this, menu_selector(TitleScene::CallbackToPinballBase));
	CCMenu* pBtn = CCMenu::create(pBtnItem, NULL);
	pBtn->setPosition(ccp(s.width*.5, s.height*.5));
	this->addChild(pBtn);

	// 翠ラッシュゲーム
	CCMenuItemImage *pButtonCrush = CCMenuItemImage::create("block/block_green.png", "block/block_red.png", this, menu_selector(TitleScene::CallbackToCrushGameScene));
	CCMenu* pBtnCrs = CCMenu::create(pButtonCrush, NULL);
	pBtnCrs->setPosition(ccp(s.width*.5, s.height*.5 + 32) );
	this->addChild(pBtnCrs);

	// アクションゲーム
	CCMenuItemImage *pButtonAction = CCMenuItemImage::create("block/block_yellow.png", "block/block_red.png", this, menu_selector(TitleScene::CallbackToActionGameScene));
	CCMenu* pBtnAct = CCMenu::create(pButtonAction, NULL);
	pBtnAct->setPosition(ccp(s.width*.5, s.height*.5 + (32*2)) );
	this->addChild(pBtnAct);

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

void TitleScene::CallbackToCrushGameScene(CCObject* pSender)
{
	//次のシーンとして、HelloWorld2シーンをセット
	CCScene* nextScene = CrushGameScene::scene();
	//切り替えの時間を設定。ここでは1秒
	float duration = 1.0f;
	//フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
	CCScene* pScene = CCTransitionFade::create(duration, nextScene);
	if(pScene){
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void TitleScene::CallbackToActionGameScene(CCObject* pSender)
{
	//次のシーンとして、HelloWorld2シーンをセット
	CCScene* nextScene = ActionGameScene::scene();
	//切り替えの時間を設定。ここでは1秒
	float duration = 1.0f;
	//フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
	CCScene* pScene = CCTransitionFade::create(duration, nextScene);
	if(pScene){
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}






