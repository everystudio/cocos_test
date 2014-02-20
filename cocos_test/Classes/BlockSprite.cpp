//
//  BlockSprite.cpp
//  MyProject
//
//  Created by mainitiamai on 2013/08/17.
//
//

#include "BlockSprite.h"

BlockSprite::BlockSprite()
{
	initNextPos();
	return;
}

BlockSprite::~BlockSprite()
{
	return;
}

BlockSprite* BlockSprite::createWithBlockType(EBlockType _EBlockType)
{
	BlockSprite *pRet = new BlockSprite();
	if(pRet && pRet->initWithBlockType(_EBlockType)){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
		pRet = NULL;
	}
	return pRet;
}

bool BlockSprite::initWithBlockType(EBlockType _EBlockType)
{
	if(!CCSprite::initWithFile(getBlockImageFileName(_EBlockType))){
		return false;
	}
	m_EBlockType = _EBlockType;
	return true;
}

const char* BlockSprite::getBlockImageFileName(EBlockType _EBlockType)
{
	switch(_EBlockType)
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
			CCAssert(false, "invalid EBlockType");
			return "";
	}
}

void BlockSprite::initNextPos()
{
	m_iNextPosX = -1;
	m_iNextPosY = -1;
}

void BlockSprite::setNextPos(int _iNextPosX , int _iNextPosY)
{
	m_iNextPosX = _iNextPosX;
	m_iNextPosY = _iNextPosY;
	return;
}

















