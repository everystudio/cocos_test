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








