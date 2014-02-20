//
//  BlockGameScene.cpp
//  MyProject
//
//  Created by mainitiamai on 2013/08/11.
//
//

#include "BlockGameScene.h"
#include "SimpleAudioEngine.h"
#include "BlockBase.h"
#include "BlockBase.h"
#include "CCPlaySE.h"
#include "HandBase.h"

#include "SkitSceneBase.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* BlockGameScene::scene()
{
	CCScene* scene = CCScene::create();
	BlockGameScene* layer = BlockGameScene::create();
	scene->addChild(layer);
	return scene;
}

// 初期化
bool BlockGameScene::init()
{
	if(!CCLayer::init()){
		return false;
	}

	m_iBlockTagSerial = eTagBlockBaseStart;
	for( int i = 0 ; i<(MAX_BLOCK_X*(MAX_BLOCK_Y));i++){
		m_iBlockTags[i] = -1;
	}

	// タップイベントを取得する
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	// 変数の初期化
	initForVariables();
	// 背景表示
	showBackground();
	// コマ表示
	showBlock();

	// hand
	initHand();

	// 効果音の事前読み込み
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MP3_REMOVE_BLOCK);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//シーン切り替えのトリガーになる"1"のボタン
	//ボタンをクリックすると、HelloWorld::myCallbackが発動
	CCMenuItemImage *pBtnItem = CCMenuItemImage::create("icon_exit.png", "icon_exit.png", this, menu_selector(BlockGameScene::CallbackToSkitSceneBase));
	CCMenu* pBtn = CCMenu::create(pBtnItem, NULL);
	pBtn->setPosition(ccp(s.width*.5, s.height*.5));
	//pBtn->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//pBtn->setPosition(ccp(visibleSize.width/2 , visibleSize.height/2 ));
	pBtn->setPosition(visibleSize.width/2 ,visibleSize.height*0.1f);
	this->addChild(pBtn);

	return true;
}


//"1"を押したときの関数。
void BlockGameScene::CallbackToSkitSceneBase(CCObject* pSender)
{
	//次のシーンとして、HelloWorld2シーンをセット
	CCScene* nextScene = SkitSceneBase::scene();
	//切り替えの時間を設定。ここでは1秒
	float duration = 1.0f;
	//フェードイン＆フェードアウト（CCTransitionFade）でトランジショーーーン
	CCScene* pScene = CCTransitionFade::create(duration, nextScene);
	if(pScene){
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void BlockGameScene::initHand()
{
	HandBase* pHand = HandBase::create(0);
	if( pHand ){
		m_pBackground->addChild(pHand , EZOrderHand , eTagHand);
		setHandPosition(pHand, CCPoint(5.0f,5.0f));
	}

	return;
}

// 背景表示
void BlockGameScene::showBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// 背景を生成
	float fGameAreaScale = 2.0f;
	m_pBackground = CCSprite::create(PNG_BACKGROUND);
	m_pBackground->setPosition(ccp(winSize.width/2,winSize.height/2-10.0f));
	//m_pBackground->setScale(1280.0f/324.0f);
	//m_pBackground->setScale(winSize.width/324.0f);
	m_pBackground->setScale(fGameAreaScale);
	addChild(m_pBackground,eZOrderBackground , eTagBackground);
/*
	float fScoreScale = 0.5f;
	m_pScoreBase = CCSprite::create(SCORE_BASE);
	m_pScoreBase->setScale(fScoreScale);
	float fScoreWidth = m_pScoreBase->getContentSize().width * fScoreScale;
	float fScoreHeight= m_pScoreBase->getContentSize().height* fScoreScale;
	m_pScoreBase->setPosition(ccp(fScoreWidth*0.5f,winSize.height-fScoreHeight*0.5f));
	addChild(m_pScoreBase);

	float fGaugeScale = 0.5f;
	m_pGaugeBase = CCSprite::create(GAUGE_BASE);
	m_pGaugeBase->setScale(fGaugeScale);
	float fGaugeWidth = m_pGaugeBase->getContentSize().width * fGaugeScale;
	float fGaugeHeight= m_pGaugeBase->getContentSize().height*fGaugeScale;
	m_pGaugeBase->setPosition(ccp(fGaugeWidth*0.5f,winSize.height-fScoreHeight-fGaugeHeight*0.5f));
	addChild(m_pGaugeBase);
*/

	//SimpleAudioEngine::sharedEngine()->playEffect(OGG_SAMPLE_BGM);
	return;
}

void BlockGameScene::initForVariables()
{
	// 乱数初期か
	srand((unsigned)time(NULL));

	// コマの一辺の長さを取得
	BlockBase* pBlock = BlockBase::createWithBlockType(EBlockTypeRed);
	m_fBlockSize = pBlock->getContentSize().height * pBlock->getBlockScale();
	//m_fBlockSize = pBlock->getScaleX();					// 正方形だからいい

	// コマ種類の配列生成
	m_vecBlockTypes.push_back( EBlockTypeRed );
	m_vecBlockTypes.push_back( EBlockTypeBlue );
	m_vecBlockTypes.push_back( EBlockTypeYellow );
	m_vecBlockTypes.push_back( EBlockTypeGreen );
	m_vecBlockTypes.push_back( EBlockTypeGray );

	return;
}

CCPoint BlockGameScene::getPosition(int _iPosIndexX, int _iPosIndexY)
{
	float fOffsetX = m_pBackground->getContentSize().width * 0.168;
	float fOffsetY = m_pBackground->getContentSize().height * 0.028;

	fOffsetX = 0.0f;
	fOffsetY = 0.0f;

	return CCPoint((_iPosIndexX+0.5) * m_fBlockSize + fOffsetX , (_iPosIndexY + 0.5)*m_fBlockSize+fOffsetY);
}

// タグ取得
int BlockGameScene::getTag(int _iPosIndexX, int _iPosIndexY)
{
	return eTagBaseBlock + _iPosIndexX * 100 + _iPosIndexY;
}

// 未使用のブロックタグを取得する
int BlockGameScene::getEmptyBlockIndex()
{
	int iRet=-1;
	int iUsedBlockTags[MAX_BLOCK_X*MAX_BLOCK_Y];
	memset( iUsedBlockTags , 0 , sizeof(iUsedBlockTags));

	// iUsedBlockTagsの中に空きがある番号を入れる
	// 注意されたいのはインデックスとごちゃごちゃにならないように注意してください
	for(int i = 0 ; i < MAX_BLOCK_X*MAX_BLOCK_Y ; i++ ){
		if( m_iBlockTags[i] == -1){
			iUsedBlockTags[m_iBlockTags[i]] = 1;
		}
		else{
			return -1;
		}
	}

	// 初期値０以外になっているものは利用中なので
	// ０になっているものを見つけたらその場でブレークする
	for(int i = 0 ; i < MAX_BLOCK_X*MAX_BLOCK_Y ; i++ ){
		if( iUsedBlockTags[i] == 0){
			iRet = i;
			break;
		}
	}
	return iRet;
}
cocos2d::CCPoint BlockGameScene::getBlockPos(int _iX , int _iY)
{
	float fOffsetX = m_pBackground->getContentSize().width * 0.168;
	float fOffsetY = m_pBackground->getContentSize().height * 0.028;

	fOffsetX = BLOCK_OFFSET_X;
	fOffsetY = 10.0f;

	return CCPoint((_iX+0.5) * m_fBlockSize + fOffsetX , ((MAX_BLOCK_X-_iY) + 0.5)*m_fBlockSize+fOffsetY);
}

bool BlockGameScene::addBlockBase(BlockBase *_pBlockBase,int _iX , int _iY)
{
	int iIndex = _iX+MAX_BLOCK_X*_iY;
	if( m_iBlockTags[iIndex] == -1 ){
		m_iBlockTagSerial += 1;
		if( eTagBlockBaseEnd <= m_iBlockTagSerial){
			m_iBlockTagSerial = eTagBlockBaseStart;
		}
		m_iBlockTags[iIndex] = m_iBlockTagSerial;
	}
	else{
		return false;
	}

	_pBlockBase->setPosition(getBlockPos(_iX,_iY));

	m_pBackground->addChild(_pBlockBase,eZorderBlock, m_iBlockTagSerial);
	return true;
}


void BlockGameScene::showBlock()
{
	for(int x = 0 ; x < MAX_BLOCK_X ; x++){
		for(int y = 0 ; y < MAX_BLOCK_Y-2 ; y++ ){
			// ランダムでコマを作成する
			EBlockType block_type = (EBlockType)(rand() % EBlockTypeCount);
			//EBlockType EBlockType = (EBlockType)block_type;

			// 対応するコマ配列
			int iTag = getTag(x,y);
			m_mapBlockTags[block_type].push_back(iTag);

			// まじめな方
			BlockBase* pBlockBase = BlockBase::createWithBlockType(block_type);
			addBlockBase(pBlockBase,x,y);
		}
	}
}

// タッチ開始イベント
bool BlockGameScene::ccTouchBegan(cocos2d::CCTouch *_pTouch, cocos2d::CCEvent *_pEvent)
{


	return true;
}

void BlockGameScene::fallBlocks()
{
	// 縦方向に着地点を検索
	for( int x = 0 ; x < MAX_BLOCK_X ; x++){
		int iBottomIndex = -1;
		int iBottomX = x;
		int iBottomY = -1;
		int iSpaceArea = 0;
		for( int y = 0 ; y < MAX_BLOCK_Y ; y++ ){
			int iIndex = x+(y*MAX_BLOCK_X);

			// まだボトムのインデックス指定ができてない場合
			if( iBottomIndex == -1){
				if( m_iBlockTags[iIndex] == -1){
					iBottomIndex = iIndex;
					iBottomY = y;
				}
			}
			else if(m_iBlockTags[iIndex] != -1){
				int iTagTemp = m_iBlockTags[iIndex];
				m_iBlockTags[iIndex] = -1;
				m_iBlockTags[iBottomIndex] = iTagTemp;

				BlockBase* pBlockBase = (BlockBase*)m_pBackground->getChildByTag(iTagTemp);
				// アニメーションをセットする
				CCMoveTo* pMove = CCMoveTo::create(MOVING_TIME,getBlockPos(iBottomX, iBottomY));
				pBlockBase->runAction(pMove);

				// 一番したの更新
				iBottomIndex += MAX_BLOCK_X;
				iBottomY += 1;
			}
			else {
				// なんか偉そうに変数講師してるけどなんも機能してません
				iSpaceArea += 1;
			}
		}
	}
	return;
}

int BlockGameScene::getBlockIndexX( cocos2d::CCPoint _tPoint)
{
	int iIndexX = 0;
	float fOffsetX = m_pBackground->getContentSize().width * 0.168;
	fOffsetX = BLOCK_OFFSET_X;

	float left_limit_x = (0.0f+0.5f) * m_fBlockSize + fOffsetX;
	float right_limit_x = ((float)MAX_BLOCK_X-1.0f+0.5f) * m_fBlockSize + fOffsetX;

	if( _tPoint.x < left_limit_x ){
		iIndexX = 0;
	}
	else if( right_limit_x < _tPoint.x ){
		iIndexX = (MAX_BLOCK_X-1);
	}
	else{
		for( int i = 0 ; i < MAX_BLOCK_X ; i++ ){
			float fBlockLeft = ((float)i+1.0f) * m_fBlockSize + fOffsetX;
			if( _tPoint.x < fBlockLeft){
				iIndexX = i;
				break;
			}
		}
	}
	return iIndexX;
}

cocos2d::CCPoint BlockGameScene::getHandPosition( cocos2d::CCPoint _tTouchPoint )
{
	_tTouchPoint.y = -10.0f;
	CCPoint tHandPoint = _tTouchPoint;

	float fOffsetX = m_pBackground->getContentSize().width * 0.168;
	fOffsetX = BLOCK_OFFSET_X;

	int index_x = getBlockIndexX(_tTouchPoint);
	float fPosX = ((float)index_x+0.5f) * m_fBlockSize + fOffsetX;

	tHandPoint.x = fPosX;
	return tHandPoint;
}

void BlockGameScene::moveHandPosition( HandBase* _pHandBase , cocos2d::CCPoint _tPoint )
{
	CCPoint tMovePoint = getHandPosition(_tPoint);

	CCMoveTo* pMove = CCMoveTo::create(MOVING_TIME,tMovePoint);
	_pHandBase->runAction(pMove);


	int iBlockTag = _pHandBase->getBlockTag();
	if( iBlockTag != -1){

		CCPoint tBlockPoint = tMovePoint;
		tBlockPoint.y += m_fBlockSize;
		moveBlock(iBlockTag,tBlockPoint);
	}

	return;
}

void BlockGameScene::setHandPosition(HandBase *_pHandBase, cocos2d::CCPoint _tPoint)
{
	CCPoint tSetPoint = getHandPosition(_tPoint);
	_pHandBase->setPosition(tSetPoint);

	return;
}

// これはコールバックでしか呼ばないようにする
void BlockGameScene::blockHit( CCNode* _pNode )
{
	list<int>::iterator it = listReserveHitBlockIndexs.begin();
	while(it != listReserveHitBlockIndexs.end()){
		list<int> listSameColorBlockIndexs = getSameColorBlockIndexs(*it);

		if( 4 <= listSameColorBlockIndexs.size()){
			// 隣接するコマを削除する
			removeBlock2(listSameColorBlockIndexs);
			fallBlocks();
		}
		it++;
	}

	return;
}

void BlockGameScene::moveBlock( int _iBlockTag , CCPoint _tPoint)
{
	BlockBase* pBlockBase = (BlockBase*)m_pBackground->getChildByTag(_iBlockTag);
	// アニメーションをセットする
	CCMoveTo* pMove = CCMoveTo::create(MOVING_TIME,_tPoint);
	pBlockBase->runAction(pMove);
	return;
}

void BlockGameScene::shotBlock( int _iBlockTag , cocos2d::CCPoint _tPoint , int _iSearchIndex)
{
	listReserveHitBlockIndexs.clear();
	listReserveHitBlockIndexs.push_back(_iSearchIndex);

	CCMoveTo* pMove = CCMoveTo::create(MOVING_TIME,_tPoint);

	CCCallFuncN* func = CCCallFuncN::create(this,callfuncN_selector(BlockGameScene::blockHit));
	CCFiniteTimeAction* sequence = CCSequence::create( pMove , func ,NULL);

	BlockBase* pBlockBase = (BlockBase*)m_pBackground->getChildByTag(_iBlockTag);
	pBlockBase->runAction(sequence);


	return;
}



// タッチ終了イベント
void BlockGameScene::ccTouchEnded(cocos2d::CCTouch *_pTouch, cocos2d::CCEvent *_pEvent)
{
	// タップポイント
	CCPoint touchPoint = m_pBackground->convertTouchToNodeSpace(_pTouch);

	// タップしたコマのTagとコマの種類を取得
	int iBaseIndex = -1;
	EBlockType EBlockType;
	getTouchBlockIndex(touchPoint , iBaseIndex, EBlockType);

	{
		HandBase* pHandBase = (HandBase*)m_pBackground->getChildByTag(eTagHand);
		// アニメーションをセットする

		CCPoint tHandPoint = touchPoint;
		if( pHandBase && pHandBase->boundingBox().containsPoint(touchPoint)){
			// 列を特定
			int iIndexX = getBlockIndexX(touchPoint);

			if( pHandBase->getBlockTag() == -1 ){

				// 一番手前のブロックを調べる
				int iSearchIndex = -1;
				int iIndexY =-1;
				for( int y = 0 ; y < MAX_BLOCK_Y ; y++ ){
					int iIndex = iIndexX+y*MAX_BLOCK_X;
					if( m_iBlockTags[iIndex] != -1){
						iSearchIndex = iIndex;
						iIndexY = y;
					}
					else {
						break;
					}
				}
				if( iSearchIndex != -1){
					int iCatchBlockTag = m_iBlockTags[iSearchIndex];
					/*
					CCLog( "search_index=%d" , iSearchIndex);
					CCLog( "catch_tag=%d" , iCatchBlockTag);
					 */
					if( pHandBase->catchBlock(iCatchBlockTag) ){
						CCPoint tPoint = pHandBase->getPosition();
						tPoint.y += m_fBlockSize;

						moveBlock(iCatchBlockTag,tPoint);
						//shotBlock(iCatchBlockTag,tPoint);
						m_iBlockTags[iSearchIndex] = -1;
					}
				}
			}
			else { // ブロック持ってる方
				// 一番手前のブロックを調べる
				int iSearchIndex = -1;
				int iIndexY =-1;
				for( int y = 0 ; y < MAX_BLOCK_Y ; y++ ){
					int iIndex = iIndexX+y*MAX_BLOCK_X;
					if( m_iBlockTags[iIndex] == -1){
						iSearchIndex = iIndex;
						iIndexY = y;
						break;
					}
				}

				// 落ちる場所を取得できました
				if( iSearchIndex != -1 ){
					CCPoint tPoint = getBlockPos(iIndexX, iIndexY);

					int iMoveTag = pHandBase->getBlockTag();
					//moveBlock(iMoveTag,tPoint);
					shotBlock(iMoveTag,tPoint,iSearchIndex);
					m_iBlockTags[iSearchIndex] = iMoveTag;
					pHandBase->resetBlockTag();
				}
			}
		}
		else {
			moveHandPosition(pHandBase,touchPoint);
		}
	}
	return;
}

// タップされたコマのタグを取得
void BlockGameScene::getTouchBlockTag(cocos2d::CCPoint _tTouchPoint, int &_tag, EBlockType &_EBlockType)
{
	for(int x = 0 ; x < MAX_BLOCK_X ; x++ ){
		for( int y = 0 ; y < MAX_BLOCK_Y ; y++ ){
			int iCurrentTag = getTag(x,y);
			CCNode* pNode = m_pBackground->getChildByTag(iCurrentTag);
			if( pNode && pNode->boundingBox().containsPoint(_tTouchPoint)){
				_tag = iCurrentTag;
				_EBlockType = ((BlockBase*)pNode)->getBlockType();
				return;
			}
		}
	}
	return;
}


// タップされたコマのタグを取得
void BlockGameScene::getTouchBlockIndex(cocos2d::CCPoint _tTouchPoint, int &_iBaseIndex, EBlockType &_EBlockType)
{
	for(int x = 0 ; x < MAX_BLOCK_X ; x++ ){
		for( int y = 0 ; y < MAX_BLOCK_Y ; y++ ){
			int iIndex = x+y*MAX_BLOCK_X;
			int iCurrentTag = m_iBlockTags[iIndex];
			if( iCurrentTag != -1){
				CCNode* pNode = m_pBackground->getChildByTag(iCurrentTag);
				if( pNode && pNode->boundingBox().containsPoint(_tTouchPoint)){
					_iBaseIndex = iIndex;
					_EBlockType = ((BlockBase*)pNode)->getBlockType();
					return;
				}
			}
		}
	}
}

// コマ配列にあるか検索
bool BlockGameScene::hasSameColorBlock(std::list<int> _listBlockTag , int _iSearchBlockTag)
{
	list<int>::iterator it;
	for(it = _listBlockTag.begin(); it != _listBlockTag.end(); ++it){
		if(*it==_iSearchBlockTag){
			return true;
		}
	}
	return false;
}

bool BlockGameScene::hasSameIndexBlock(std::list<int> _listBlockIndex , int _iSearchBlockIndex)
{
	list<int>::iterator it;
	for(it = _listBlockIndex.begin();it != _listBlockIndex.end();++it){
		if(*it==_iSearchBlockIndex){
			return true;
		}
	}
	return false;
}


// タップされたこまと同じ色でかつ接しているコマの配列を返す
std::list<int> BlockGameScene::getSameColorBlockTags(int _iBaseTag, EBlockType _EBlockType)
{
	// 同色のコマを書く王する歯入れ鵜tの初期化
	list<int> listSameColorBlockTags;
	listSameColorBlockTags.push_back(_iBaseTag);

	list<int>::iterator it = listSameColorBlockTags.begin();
	while(it != listSameColorBlockTags.end()){
		int tags[] = {
			*it + 100, // right tag
			*it - 100, // left block tag
			*it + 1 , // up block tag
			*it - 1 , // down block tag
		};
		for( int i = 0 ; i < sizeof(tags)/sizeof(tags[0]);i++){
			// すでにリストにあるか検索
			if(!hasSameColorBlock(listSameColorBlockTags, tags[i])){
				// コマ配列にあるか検索
				if( hasSameColorBlock(m_mapBlockTags[_EBlockType],tags[i])){
					listSameColorBlockTags.push_back(tags[i]);
				}
			}
		}
		it++;
	}
	return listSameColorBlockTags;
}

// タップされたこまと同じ色でかつ接しているコマの配列を返す
std::list<int> BlockGameScene::getSameColorBlockIndexs(int _iBaseIndex)
{
	EBlockType eCheckBlockType = EBlockTypeCount;
	// 同色のコマを書く王する歯入れ鵜tの初期化
	list<int> listSameColorBlockIndexs;
	listSameColorBlockIndexs.clear();
	if( _iBaseIndex != -1 ){
		int iTag = m_iBlockTags[_iBaseIndex];
		if( iTag != -1 ){
			// コマ配列にあるか検索
			CCNode* pNode = m_pBackground->getChildByTag(iTag);
			if( pNode ){
				eCheckBlockType = ((BlockBase*)pNode)->getBlockType();
				listSameColorBlockIndexs.push_back(_iBaseIndex);
			}
		}
	}

	list<int>::iterator it = listSameColorBlockIndexs.begin();
	while(it != listSameColorBlockIndexs.end()){
		int iIndex = *it;
		int iX = iIndex%MAX_BLOCK_X;
		int iY = iIndex/MAX_BLOCK_X;
		list<int> listIndex;
		listIndex.clear();
		if( 0<iX){
			listIndex.push_back((iX-1)+iY*MAX_BLOCK_X);
		}
		if( (iX+1)<MAX_BLOCK_X){
			listIndex.push_back((iX+1)+iY*MAX_BLOCK_X);
		}
		if( 0<iY){
			listIndex.push_back(iX+(iY-1)*MAX_BLOCK_X);
		}
		if( (iY+1)<MAX_BLOCK_Y){
			listIndex.push_back(iX+(iY+1)*MAX_BLOCK_X);
		}
		list<int>::iterator it_search = listIndex.begin();
		while( it_search != listIndex.end()){
			int iSearchIndex = *it_search;
			// 既にリストにあるか検索
			if( !hasSameIndexBlock(listSameColorBlockIndexs,iSearchIndex)){
				int iTag = m_iBlockTags[iSearchIndex];
				if( iTag != -1 ){
					// コマ配列にあるか検索
					CCNode* pNode = m_pBackground->getChildByTag(iTag);
					if( pNode ){
						EBlockType EBlockType = ((BlockBase*)pNode)->getBlockType();
						if( eCheckBlockType == EBlockType){
							listSameColorBlockIndexs.push_back(iSearchIndex);
						}
					}
				}
			}
			it_search++;
		}
		it++;
	}
/*
	list<int>::iterator it = listSameColorBlockTags.begin();
	while(it != listSameColorBlockTags.end()){
		int tags[] = {
			*it + 100, // right tag
			*it - 100, // left block tag
			*it + 1 , // up block tag
			*it - 1 , // down block tag
		};
		for( int i = 0 ; i < sizeof(tags)/sizeof(tags[0]);i++){
			// すでにリストにあるか検索
			if(!hasSameColorBlock(listSameColorBlockTags, tags[i])){
				// コマ配列にあるか検索
				if( hasSameColorBlock(m_mapBlockTags[_EBlockType],tags[i])){
					listSameColorBlockTags.push_back(tags[i]);
				}
			}
		}
		it++;
	}
*/
	return listSameColorBlockIndexs;
}

// 配列のコマを削除
void BlockGameScene::removeBlock2(std::list<int> _listBlockIndexs)
{
	list<int>::iterator it = _listBlockIndexs.begin();
	while(it != _listBlockIndexs.end()){
		// 既存配列から街頭コマを削除
		int iTag = m_iBlockTags[*it];
		if( iTag != -1){
			m_iBlockTags[*it] = -1;
		}

		// 対象となるコマを取得
		CCNode* pBlock = m_pBackground->getChildByTag(iTag);
		if(pBlock){
			pBlock->removeFromParentAndCleanup(true);
			/*
			// コマが消えるアニメーションを生成
			CCScaleTo* pScale = CCScaleTo::create(REMOVING_TIME,0);

			// コマを削除するアクションを生成
			CCCallFuncN* pFunc = CCCallFuncN::create(this,callfuncN_selector(BlockGameScene::removingBlock));

			// アクションをつなげる
			CCFiniteTimeAction* pSequence = CCSequence::create(pScale,pFunc,NULL);

			CCFiniteTimeAction* pAction;
			if( bFirst ){
				// コマが消えるサウンドアクションを生成
				CCPlaySE* pPlaySe = CCPlaySE::create(MP3_REMOVE_BLOCK);

				// アクションにつなげる
				pAction = CCSpawn::create(pSequence,pPlaySe,NULL);

				bFirst = false;
			}
			else {
				pAction = pSequence;
			}
			pBlock->runAction(pAction);
			*/
		}
		it++;
	}

	SimpleAudioEngine::sharedEngine()->playEffect(MP3_REMOVE_BLOCK);
	return;
}
// 配列のコマを削除
void BlockGameScene::removeBlock(std::list<int> _listBlockTags, EBlockType _EBlockType)
{
	bool bFirst = true;
	list<int>::iterator it = _listBlockTags.begin();
	while(it != _listBlockTags.end()){
		// 既存配列から街頭コマを削除
		m_mapBlockTags[_EBlockType].remove(*it);

		// 対象となるコマを取得
		CCNode* pBlock = m_pBackground->getChildByTag(*it);
		if(pBlock){
			//pBlock->removeFromParentAndCleanup(true);

			// コマが消えるアニメーションを生成
			CCScaleTo* pScale = CCScaleTo::create(REMOVING_TIME,0);

			// コマを削除するアクションを生成
			CCCallFuncN* pFunc = CCCallFuncN::create(this,callfuncN_selector(BlockGameScene::removingBlock));

			// アクションをつなげる
			CCFiniteTimeAction* pSequence = CCSequence::create(pScale,pFunc,NULL);

			CCFiniteTimeAction* pAction;
			if( bFirst ){
				// コマが消えるサウンドアクションを生成
				CCPlaySE* pPlaySe = CCPlaySE::create(MP3_REMOVE_BLOCK);

				// アクションにつなげる
				pAction = CCSpawn::create(pSequence,pPlaySe,NULL);

				bFirst = false;
			}
			else {
				pAction = pSequence;
			}
			pBlock->runAction(pAction);
		}
		it++;
	}

	SimpleAudioEngine::sharedEngine()->playEffect(MP3_REMOVE_BLOCK);
	return;
}

// コマの削除
void BlockGameScene::removingBlock(cocos2d::CCNode *_pBlock)
{
	_pBlock->removeFromParentAndCleanup(true);
	return;
}

BlockGameScene::TPositionIndex BlockGameScene::getPositionIndex(int _iTag)
{
	int iPos1_x = (_iTag - eTagBaseBlock)/100;
	int iPos1_y = (_iTag - eTagBaseBlock)%100;
	return TPositionIndex(iPos1_x,iPos1_y);
}

void BlockGameScene::setNewPosition(int _iTag, BlockGameScene::TPositionIndex _tPosIndex)
{
	BlockBase* pBlockBase = (BlockBase*)m_pBackground->getChildByTag(_iTag);
	int iNextPosY = pBlockBase->getNextPosY();
	if(iNextPosY == -1 ){
		iNextPosY = _tPosIndex.iY;
	}

	// 移動先の位置をセット
	pBlockBase->setNextPos( _tPosIndex.iX , --iNextPosY);
	return;
}

// 消えたコマを埋めるように新しい位置をセット
void BlockGameScene::searchNewPosition1(std::list<int> _listBlocks)
{
	// 消えるコマ数分のループ
	list<int>::iterator it1 = _listBlocks.begin();
	while( it1 != _listBlocks.end()){
		TPositionIndex tPosIndex1 = getPositionIndex(*it1);

		// コマ種類のループ
		vector<EBlockType>::iterator it2 = m_vecBlockTypes.begin();
		while(it2 != m_vecBlockTypes.end()){
			// 各種類のコマ数分のループ
			list<int>::iterator it3 = m_mapBlockTags[*it2].begin();
			while( it3 != m_mapBlockTags[*it2].end()){
				TPositionIndex tPosIndex2 = getPositionIndex(*it3);

				if(tPosIndex1.iX == tPosIndex2.iX && tPosIndex1.iY < tPosIndex2.iY){
					// 消えるコマの上に位置するコマに大して移動先の位置をセットする
					setNewPosition(*it3,tPosIndex2);
				}
				it3++;
			}
			it2++;
		}
		it1++;
	}
	return;
}

void BlockGameScene::moveBlock()
{
	// コマ種類のループ
	vector<EBlockType>::iterator it1 = m_vecBlockTypes.begin();
	while(it1 != m_vecBlockTypes.end()){
		// 各種類のコマ数分のループ
		list<int>::iterator it2 = m_mapBlockTags[*it1].begin();
		while(it2 != m_mapBlockTags[*it1].end()){
			BlockBase* pBlockBase = (BlockBase*)m_pBackground->getChildByTag(*it2);
			int iNextPosX = pBlockBase->getNextPosX();
			int iNextPosY = pBlockBase->getNextPosY();

			if( iNextPosX != -1 || iNextPosY != -1){
				// 新しいタグをセットする
				int iNewTag = getTag(iNextPosX,iNextPosY);
				pBlockBase->initNextPos();
				pBlockBase->setTag(iNewTag);

				// タグ一覧の値も新しいタグに変更する
				*it2 = iNewTag;

				// アニメーションをセットする
				CCMoveTo* pMove = CCMoveTo::create(MOVING_TIME,getPosition(iNextPosX,iNextPosY));
				pBlockBase->runAction(pMove);
			}
			it2++;
		}
		it1++;
	}
	return;
}

// コマ削除後のアニメーション
void BlockGameScene::movingBlocksAnimation1(std::list<int> _listBlocks)
{
	// コマの新しい位置をセットする
	searchNewPosition1(_listBlocks);

	// 新しい位置がセットされた駒野アニメーション
	moveBlock();
}






