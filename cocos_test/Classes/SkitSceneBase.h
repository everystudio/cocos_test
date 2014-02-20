#ifndef __HELLOWORLD_SCENE2_H__
#define __HELLOWORLD_SCENE2_H__

#include "cocos2d.h"

class SkitSceneBase : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	void menuCloseCallback(CCObject* pSender);
	CREATE_FUNC(SkitSceneBase);

private:
	void myCallback(CCObject* pSender);
};
#endif // __HELLOWORLD_SCENE_H__
