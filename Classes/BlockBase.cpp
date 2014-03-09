//
//  BlockBase.cpp
//  MyProject
//
//  Created by mainitiamai on 2013/08/22.
//
//

#include "BlockBase.h"

BlockBase::BlockBase()
{
	//m_fBlockScale = 0.75f;
	//m_fScale = 0.75f;
	initNextPos();
	return;
}

BlockBase::~BlockBase()
{
	return;
}

BlockBase* BlockBase::createBlockTypePos(EBlockType _eBlockType,int _iX , int _iY)
{
	BlockBase *pRet = new BlockBase();
	if(pRet && pRet->initWithBlockType(_eBlockType)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}


BlockBase* BlockBase::createWithBlockType(EBlockType _eBlockType)
{
	BlockBase *pRet = new BlockBase();
	if(pRet && pRet->initWithBlockType(_eBlockType)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	pRet->setScale(((float)BlockBase::m_iScale*0.01f));
	return pRet;
}

float BlockBase::getBlockScale()
{
	return (float)BlockBase::m_iScale*0.01f;
}

bool BlockBase::initWithBlockType(EBlockType _eBlockType)
{
	if(!CCSprite::initWithFile(getBlockImageFileName(_eBlockType))){
		return false;
	}
	m_eBlockType = _eBlockType;
	return true;
}

void BlockBase::initNextPos()
{
	m_iNextPosX = -1;
	m_iNextPosY = -1;
}

void BlockBase::setNextPos(int _iNextPosX , int _iNextPosY)
{
	m_iNextPosX = _iNextPosX;
	m_iNextPosY = _iNextPosY;
	return;
}


const char* BlockBase::getBlockImageFileName(EBlockType _eBlockType)
{
	switch(_eBlockType)
	{
		case EBlockTypeRed		:
			return "block_red.png";
		case EBlockTypeBlue		:
			return "block_blue.png";
		case EBlockTypeYellow	:
			return "block_yellow.png";
		case EBlockTypeGreen	:
			return "block_green.png";
		case EBlockTypeGray		:
			return "block_gray.png";
		default:
			CCAssert(false, "invalid eBlockType");
			return "";
	}
}





