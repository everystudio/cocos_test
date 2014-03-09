//
//  CHandBase.cpp
//  MyProject
//
//  Created by mainitiamai on 2013/08/31.
//
//

#include "HandBase.h"
#include "BlockBase.h"

HandBase::HandBase( int _iType )
{
	m_iType = _iType;
	m_iBlockTag =-1;
	return;
}

HandBase* HandBase::create( int _iType )
{
	HandBase* pRet = new HandBase(_iType);
	if( pRet && pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	float fSetScale = BlockBase::getBlockScale();
	pRet->setScale(fSetScale);
	return pRet;
}

bool HandBase::init()
{
	if(!CCSprite::initWithFile("block_blue.png")){
		return false;
	}
	return true;
}

bool HandBase::catchBlock( int _iBlockTag)
{
	if( m_iBlockTag == -1 ){
		m_iBlockTag = _iBlockTag;
		return true;
	}

	return false;
}

bool HandBase::resetBlockTag()
{
	bool bRet = false;
	if( m_iBlockTag != -1 ){
		m_iBlockTag  = -1;
		bRet = true;
	}
	return bRet;
}











//
