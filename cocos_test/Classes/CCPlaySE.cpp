//
//  CCPlaySE.cpp
//  MyProject
//
//  Created by mainitiamai on 2013/08/11.
//
//

#include "CCPlaySE.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCPlaySE::CCPlaySE(std::string _strSound)
{
    m_strSound = _strSound;
    return;
}

CCPlaySE* CCPlaySE::create( std::string _strSound)
{
    CCPlaySE* pRet = new CCPlaySE(_strSound);
    if( pRet ){
        pRet->autorelease();
    }
    return pRet;
}

void CCPlaySE::Update(float _fTime )
{
    CC_UNUSED_PARAM(_fTime);
    SimpleAudioEngine::sharedEngine()->playEffect(m_strSound.c_str());
    return;
}

CCFiniteTimeAction* CCPlaySE::reverse()
{
    return (CCFiniteTimeAction*)(CCPlaySE::create(m_strSound));
}

CCObject* CCPlaySE::copyWithZone(cocos2d::CCZone* _pZone)
{
    CCZone* pNewZone = NULL;
    CCPlaySE* pRet = NULL;
    if(_pZone && _pZone->m_pCopyObject){
        pRet = (CCPlaySE*)(_pZone->m_pCopyObject);
    }
    else{
        pRet = new CCPlaySE(m_strSound);
        _pZone = pNewZone = new CCZone(pRet);
    }
    
    CCActionInstant::copyWithZone(_pZone);
    CC_SAFE_DELETE( pNewZone );
    return pRet;
}

















