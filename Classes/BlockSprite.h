//
//  BlockSprite.h
//  MyProject
//
//  Created by mainitiamai on 2013/08/17.
//
//

#ifndef __MyProject__BlockSprite__
#define __MyProject__BlockSprite__

#include "cocos2d.h"
#include "Config.h"

class BlockSprite : public cocos2d::CCSprite
{
protected:
	const char* getBlockImageFileName(EBlockType _EBlockType);

public:
	CC_SYNTHESIZE_READONLY(EBlockType, m_EBlockType , BlockType);
	CC_SYNTHESIZE_READONLY(int , m_iNextPosX , NextPosX);
	CC_SYNTHESIZE_READONLY(int , m_iNextPosY , NextPosY);

	void initNextPos();
	void setNextPos(int _iNextPosX , int _iNextPosY);

	BlockSprite();
	virtual ~BlockSprite();
	virtual bool initWithBlockType(EBlockType _EBlockType);
	static BlockSprite* createWithBlockType(EBlockType _EBlockType);

};

#endif /* defined(__MyProject__BlockSprite__) */
