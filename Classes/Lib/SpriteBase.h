/*
 * SpriteBase.h
 *
 *  Created on: 2014/03/30
 *      Author: mainitiamai
 */

#ifndef SPRITEBASE_H_
#define SPRITEBASE_H_

#include "GB2ShapeCache-x.h"	// なんかしらんけどこれ入れるとCCSpriteが宣言できる
#include "cocos2d.h"

class SpriteBase : public CCSprite 
{
public:
	float GetPosX();
	float GetPosY();

	void SetPosX(float _fX );
	void SetPosY(float _fY );

	void AddPosX( float _fX );
	void AddPosY( float _fY );

	static SpriteBase* create(){
		return (SpriteBase*)CCSprite::create();
	}
	static SpriteBase* create(const char *pszFileName){
		return (SpriteBase*)CCSprite::create(pszFileName);
	}
	static SpriteBase* create(const char *pszFileName, const CCRect& rect){
		return (SpriteBase*)CCSprite::create(pszFileName,rect);
	}
	static SpriteBase* createWithTexture(CCTexture2D *pTexture){
		return (SpriteBase*)CCSprite::createWithTexture(pTexture);
	}
	static SpriteBase* createWithTexture(CCTexture2D *pTexture, const CCRect& rect){
		return (SpriteBase*)CCSprite::createWithTexture(pTexture,rect);
	}
	static SpriteBase* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame){
		return (SpriteBase*)CCSprite::createWithSpriteFrame(pSpriteFrame);
	}
	static SpriteBase* createWithSpriteFrameName(const char *pszSpriteFrameName){
		return (SpriteBase*)CCSprite::createWithSpriteFrameName(pszSpriteFrameName);
	}
	CCRect getRect ();


	
};



#endif /* SPRITEBASE_H_ */













