/*
 * TitleScene.h
 *
 *  Created on: 2014/03/09
 *      Author: mainitiamai
 */

#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "cocos2d.h"
#include "Config.h"

class TitleScene : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(TitleScene);

	void CallbackToPinballBase(CCObject* pSender);
	void CallbackToActionGameBase(CCObject* pSender);
	void CallbackToCrushGameScene(CCObject* pSender);

};



#endif /* TITLESCENE_H_ */
