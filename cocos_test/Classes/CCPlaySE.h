//
//  CCPlaySE.h
//  MyProject
//
//  Created by mainitiamai on 2013/08/11.
//
//

#ifndef __MyProject__CCPlaySE__
#define __MyProject__CCPlaySE__

#include <iostream>

#include "cocos2d.h"

class CCPlaySE : public cocos2d::CCActionInstant
{
public:

	CCPlaySE(std::string _strSound);
	virtual ~CCPlaySE(){}

	virtual void Update( float _fTime );                // ここに実行する処理を
	virtual CCFiniteTimeAction* reverse(void);
	virtual CCObject* copyWithZone(cocos2d::CCZone* _pZone);

public:
	static CCPlaySE* create(std::string _strSound);     // 効果音のファイル名を指定する


protected:
	std::string m_strSound;
};


#endif /* defined(__MyProject__CCPlaySE__) */
