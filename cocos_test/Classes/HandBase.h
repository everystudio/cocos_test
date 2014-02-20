//
//  CHandBase.h
//  MyProject
//
//  Created by mainitiamai on 2013/08/31.
//
//

#ifndef __MyProject__CHandBase__
#define __MyProject__CHandBase__

#include "cocos2d.h"
#include "Config.h"

class HandBase : public cocos2d::CCSprite
{
protected:
public:
	bool catchBlock( int _iBlockTag);
	
	CC_SYNTHESIZE_READONLY(int , m_iType , HandType);
	CC_SYNTHESIZE_READONLY(int , m_iStatus , Status);
	CC_SYNTHESIZE_READONLY(int , m_iBlockTag , BlockTag);

	bool resetBlockTag();
	virtual bool init();
	HandBase( int _iType );
	virtual ~HandBase(){}
	
public:
	static HandBase* create(int _iType);     // 効果音のファイル名を指定する
	
};

#endif /* defined(__MyProject__CHandBase__) */
