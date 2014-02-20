//
//  BlockBase.h
//  MyProject
//
//  Created by mainitiamai on 2013/08/22.
//
//

#ifndef __MyProject__BlockBase__
#define __MyProject__BlockBase__

#include "cocos2d.h"
#include "Config.h"

class BlockBase : public cocos2d::CCSprite
{
protected:
	const char* getBlockImageFileName(EBlockType _eBlockType);

	static const int m_iScale = 75;		// 知らんけど宣言する場所をしたの方にするとエラーになる。

public:
	CC_SYNTHESIZE_READONLY(EBlockType, m_eBlockType , BlockType);
	CC_SYNTHESIZE_READONLY(int , m_iNextPosX , NextPosX);
	CC_SYNTHESIZE_READONLY(int , m_iNextPosY , NextPosY);

	void setNextPos(int _iNextPosX , int _iNextPosY);
	void initNextPos();

	BlockBase();
	virtual ~BlockBase();
	virtual bool initWithBlockType(EBlockType _eBlockType);
	static BlockBase* createBlockTypePos(EBlockType _eBlockType,int _iX , int _iY);
	static BlockBase* createWithBlockType(EBlockType _eBlockType);
	static float getBlockScale();
protected:

};



#endif /* defined(__MyProject__BlockBase__) */
