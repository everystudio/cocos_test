#include "SkitSceneBase.h"
#include "BlockGameScene.h"

USING_NS_CC;
CCScene* SkitSceneBase::scene()
{
	CCScene *scene = CCScene::create();
	SkitSceneBase *layer = SkitSceneBase::create();
	scene->addChild(layer);

	return scene;
}

bool SkitSceneBase::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize s = CCDirector::sharedDirector()->getWinSize();

	//シーン切り替えのトリガーになる"2"のボタン
	//ボタンをクリックすると、SkitSceneBase::myCallbackが発動
	CCMenuItemImage *pBtnItem = CCMenuItemImage::create("totoki_airi_00.png", "totoki_airi_00.png", this, menu_selector(SkitSceneBase::myCallback));
	CCMenu* pBtn = CCMenu::create(pBtnItem, NULL);
	pBtn->setPosition(ccp(s.width*.5, s.height*.5));
	this->addChild(pBtn);

	return true;
}
//"2"を押したときの関数。
void SkitSceneBase::myCallback(CCObject* pSender)
{
	//次のシーンとして、BlockGameSceneシーンをセット
	CCScene* nextScene = BlockGameScene::scene();
	//切り替えの時間を設定。ここでは1秒
	float duration = 1.0f;
	//フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
	CCScene* pScene = CCTransitionFade::create(duration, nextScene);
	if(pScene){
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void SkitSceneBase::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
