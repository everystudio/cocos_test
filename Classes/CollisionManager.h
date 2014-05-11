/**
 *	@file	CollisionManager.h
 *	@brief	あたり判定管理
 *	@date	2014.05.11
 *	@author	senri0123
*/

#ifndef	__CollisionManager_h__
#define	__CollisionManager_h__

/*-------------------------------------------------------------------
 *	includes
-------------------------------------------------------------------*/
#include "cocos2d.h"
#include <vector>

/*-------------------------------------------------------------------
 *	consts
-------------------------------------------------------------------*/

/*-------------------------------------------------------------------
 *	macros
-------------------------------------------------------------------*/

/*-------------------------------------------------------------------
 *	globals
-------------------------------------------------------------------*/


/*=================================================================*/
namespace cocos2d
{
class CCTMXLayer;
class CCRect;
}

class CollisionManager
{
public:
	CollisionManager();
	virtual ~CollisionManager();

public:
	/**
		あたり情報の作成
		@param	layer		レイヤー情報
		@return 成功時は true 、
				失敗時は false を返します。
	*/
	bool Create(cocos2d::CCTMXLayer* layer);

	/**
		あたり検出
		@param	position	オブジェクトの位置
		@param	dx			オブジェクトのx方向の移動量
		@retval	result		あたり後の位置が格納されます。
	*/
	bool DetectX(const cocos2d::CCRect& position, float dx, float& result) const;

	/**
		あたり検出
		@param	position	オブジェクトの位置
		@param	dy			オブジェクトのy方向の移動量
		@retval	result		あたり後の位置が格納されます。
	*/
	bool DetectY(const cocos2d::CCRect& position, float dy, float& result) const;

	/**
		矩形リストの破棄
	*/
	void Release();

protected:
	///	矩形リスト
	typedef std::vector<cocos2d::CCRect> RectArray;

protected:
	RectArray	m_RectArray;

};


#endif	/*	__CollisionManager_h__	*/

/*= end of file ===================================================*/
