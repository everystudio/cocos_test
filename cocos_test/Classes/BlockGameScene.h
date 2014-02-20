//
//  BlockGameScene.h
//  MyProject
//
//  Created by mainitiamai on 2013/08/11.
//
//

#ifndef __MyProject__BlockGameScene__
#define __MyProject__BlockGameScene__

#include "cocos2d.h"

#include "BlockBase.h"
#include "HandBase.h"
#include "Config.h"

#define MAX_BLOCK_X 8
#define MAX_BLOCK_Y 8
#define BLOCK_OFFSET_X 20.0f

#define GAUGE_BASE			"gauge_samlpe.png"
#define SCORE_BASE			"score_sample.png"
#define PNG_BACKGROUND		"sample_bg01.png"
#define MP3_REMOVE_BLOCK	"se_decide_00.wav"
#define OGG_SAMPLE_BGM		"sample_bgm_loop.ogg"
#define REMOVING_TIME 1.0f
#define MOVING_TIME 0.2f

class BlockGameScene : public cocos2d::CCLayer
{
protected:
	enum{
		eTagBackground		= 1,
		eTagGaugeBase		,
		eTagScoreBase		,
		eTagBlockBaseStart	= 100,
		eTagBlockBaseEnd	= eTagBlockBaseStart+(MAX_BLOCK_X*(MAX_BLOCK_Y*2)),
		eTagHand			= 500,
		eTagBaseBlock		= 10000,
	};

	enum eZOrder{
		eZOrderBackground,
		eZorderBlock,
		EZOrderBlock,
		EZOrderHand,
	};

	struct TPositionIndex{
		TPositionIndex(int _iX , int _iY){
			iX = _iX;
			iY = _iY;
		}
		int iX;
		int iY;
	};


	int m_iBlockTagSerial;		// シリアルとかいってるけどループして再利用させます
	int m_iBlockTags[MAX_BLOCK_X*MAX_BLOCK_Y];
	int getEmptyBlockIndex();
	bool addBlockBase( BlockBase* _pBlockBase ,int _iX , int _iY);
	cocos2d::CCPoint getBlockPos(int _iX , int _iY);

	// 2-2-3
	cocos2d::CCSprite* m_pBackground;
	cocos2d::CCSprite* m_pGaugeBase;
	cocos2d::CCSprite* m_pScoreBase;
	void showBackground();

	// 2-2-4
	float m_fBlockSize;
	std::map<EBlockType,std::list<int> >m_mapBlockTags;
	void initForVariables();
	void showBlock();
	cocos2d::CCPoint getPosition(int _iPosIndexX , int _iPosIndexY);
	int getTag(int _iPosIndexX , int _iPosIndexY);

	// 2-2-5
	void getTouchBlockTag(cocos2d::CCPoint _tTouchPoint , int &_tag , EBlockType &_EBlockType);
	void getTouchBlockIndex(cocos2d::CCPoint _tTouchPoint , int &_iBaseIndex , EBlockType &_EBlockType);
	std::list<int> getSameColorBlockTags(int _iBaseTag , EBlockType _EBlockType);
	std::list<int> getSameColorBlockIndexs(int _iBaseIndex );
	void removeBlock(std::list<int> _listBlockTags , EBlockType _EBlockType);
	void removeBlock2(std::list<int> _listBlockIndexs );
	bool hasSameColorBlock(std::list<int> _listBlockTag , int _iSearchBlockTag);
	bool hasSameIndexBlock(std::list<int> _listBlockIndex , int _iSearchBlockIndex);

	// 2-3-1
	void removingBlock(cocos2d::CCNode* _pBlock);

	// 2-3-2
	std::vector<EBlockType> m_vecBlockTypes;
	TPositionIndex getPositionIndex( int _iTag );
	void setNewPosition( int _iTag , TPositionIndex _tPosIndex);
	void searchNewPosition1(std::list<int> _listBlocks);
	void movingBlocksAnimation1(std::list<int> _listBlocks);

	void fallBlocks();

	//
	void initHand();
	cocos2d::CCPoint getHandPosition( cocos2d::CCPoint _tTouchPoint );
	void moveHandPosition( HandBase* _pHandBase , cocos2d::CCPoint _tPoint );
	void setHandPosition( HandBase* _pHandBase , cocos2d::CCPoint _tPoint );


	void blockHit( CCNode* _pNode );
	std::list<int> listReserveHitBlockIndexs;

	void moveBlock();
	void moveBlock( int _iBlockTag , cocos2d::CCPoint _tPoint);
	void shotBlock( int _iBlockTag , cocos2d::CCPoint _tPoint , int _iSearchIndex);

	int getBlockIndexX( cocos2d::CCPoint _tPoint);


public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(BlockGameScene);

	virtual bool ccTouchBegan(cocos2d::CCTouch* _pTouch , cocos2d::CCEvent* _pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* _pTouch , cocos2d::CCEvent* _pEvent);

	void CallbackToSkitSceneBase(CCObject* pSender);

};





#endif /* defined(__MyProject__BlockGameScene__) */

























