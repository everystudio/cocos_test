/*
 * SpriteBase.cpp
 *
 *  Created on: 2014/03/30
 *      Author: mainitiamai
 */

#include "SpriteBase.h"

float SpriteBase::GetPosX()
{
	CCPoint tPos = this->getPosition();
	return tPos.x;
}

float SpriteBase::GetPosY()
{
	CCPoint tPos = this->getPosition();
	return tPos.y;
}

void SpriteBase::SetPosX(float _fX )
{
	CCPoint tPos = this->getPosition();
	tPos.x = _fX;
	this->setPosition(tPos);
	return;
}

void SpriteBase::SetPosY(float _fY )
{
	CCPoint tPos = this->getPosition();
	tPos.y = _fY;
	this->setPosition(tPos);
	return;
}

void SpriteBase::AddPosX( float _fX )
{
	CCPoint tPos = this->getPosition();
	tPos.x += _fX;
	this->setPosition(tPos);
	return;
}

void SpriteBase::AddPosY( float _fY )
{
	CCPoint tPos = this->getPosition();
	tPos.y += _fY;
	this->setPosition(tPos);
	return;
}

	// スプライトのCGRectを取得
CCRect SpriteBase::getRect () {
  return CCRectMake(
    this->getPosition().x - this->getContentSize().width * this->getAnchorPoint().x,
    this->getPosition().y - this->getContentSize().height * this->getAnchorPoint().y,
    this->getContentSize().width,
    this->getContentSize().height
  );
}







