/**
 *	@file	CollisionManager.cpp
 *	@brief	あたり判定管理
 *	@date	2014.05.11
 *	@author	senri0123
*/

/*-------------------------------------------------------------------
 *	includes
-------------------------------------------------------------------*/
#include "CollisionManager.h"
#include <algorithm>

USING_NS_CC;

/*-------------------------------------------------------------------
 *	macros
-------------------------------------------------------------------*/

/*-------------------------------------------------------------------
 *	statics
-------------------------------------------------------------------*/


/*=================================================================*/

CollisionManager::CollisionManager()
: m_RectArray()
{

}

CollisionManager::~CollisionManager()
{

}


/**
	あたり情報の作詞
	@param	layer		レイヤー情報
	@return 成功時は true 、
			失敗時は false を返します。
*/
bool CollisionManager::Create(CCTMXLayer* layer)
{
	/*	念のため破棄する	*/
	Release();

	if(NULL == layer)
	{
		CCLog("CollisionManager::Create NULL == layer");
		return false;
	}

	/*	タイルのサイズを取得	*/
	CCSize tile_size = layer->getMapTileSize();

	/*	マップのサイズを取得	*/
	CCSize map_size = layer->getLayerSize();
	int size_w = static_cast< int >( map_size.width );
	int size_h = static_cast< int >( map_size.height );

	/*	各タイルに情報があるかチェック	*/
	for(int h=0; h<size_h; h++)
	{
		for(int w=0; w<size_w; w++)
		{
			/*	この位置の座標	*/
			CCPoint coord = ccp(w, h);

			/*	GIDを取得。ここにタイルが存在すれば >0 の値が取れる	*/
			int gid = layer->tileGIDAt(coord);
			if(0 >= gid){
				continue;	/*	ここにタイルはないらしい	*/
			}

			/*	タイルの座標を取得	*/
			CCPoint position = layer->positionAt(coord);

			/*	矩形を登録	*/
			CCRect rect(position.x, position.y, tile_size.width, tile_size.height);
			m_RectArray.push_back(rect);

			CCLog("rect x=%f y=%f w=%f h=%f" , rect.getMinX(), rect.getMinY() , rect.getMaxX() , rect.getMaxY() );


		}
	}

	return true;
}

/**
	あたり検出
	@param	position	オブジェクトの位置
	@param	dx			オブジェクトのx方向の移動量
	@retval	result		あたり後の位置が格納されます。
*/
bool CollisionManager::DetectX(const CCRect& position, float dx, float& result) const
{
	/*	補正ベクトル	*/
	float adjust_posi = 0.0f;	/*	正方向	*/
	float adjust_nega = 0.0f;	/*	負方向	*/
	bool check_posi = false;	/*	正方向初回判定フラグ	*/
	bool check_nega = false;	/*	負方向初回判定フラグ	*/

	/*	移動後の位置	*/
	CCRect after = position;
	after.origin.x += dx;

	RectArray::const_iterator it = m_RectArray.begin();

	for( ; it!=m_RectArray.end(); it++)
	{
		const CCRect& rect = (*it);
		if(!rect.intersectsRect(after))
		{
			continue;	/*	あたってない	*/
		}

		/*	めり込み分を算出	*/
		if((after.origin.x + after.size.width) > rect.origin.x)
		{
			/*	正方向	*/
			float adjust = (after.origin.x + after.size.width) - rect.origin.x;
			if(!check_posi)
			{
				adjust_posi = adjust;
				check_posi = true;
			}
			else
			{
				adjust_posi = std::min(adjust_posi,adjust);
			}
		}
		else
		if((rect.origin.x + rect.size.width) > after.origin.x)
		{
			/*	負方向	*/
			float adjust = (rect.origin.x + rect.size.width) - after.origin.x;
			if(!check_nega)
			{
				adjust_nega = adjust;
				check_nega = true;
			}
			else
			{
				adjust_nega = std::min(adjust_nega,adjust);
			}
		}
	}

	/*	正方向、負方向の補正値を足したものが最終的な補正値	*/
	result = adjust_posi + adjust_nega;

	return true;
}

/**
	あたり検出
	@param	position	オブジェクトの位置
	@param	dy			オブジェクトのy方向の移動量
	@retval	result		あたり後の位置が格納されます。
*/
bool CollisionManager::DetectY(const CCRect& position, float dy, float& result) const
{
	/*	補正ベクトル	*/
	float adjust_posi = 0.0f;	/*	正方向	*/
	float adjust_nega = 0.0f;	/*	負方向	*/
	bool check_posi = false;	/*	正方向初回判定フラグ	*/
	bool check_nega = false;	/*	負方向初回判定フラグ	*/

	/*	移動後の位置	*/
	CCRect after = position;
	after.origin.y += dy;

	RectArray::const_iterator it = m_RectArray.begin();

	for( ; it!=m_RectArray.end(); it++)
	{
		const CCRect& rect = (*it);
		if(!rect.intersectsRect(after))
		{
			continue;	/*	あたってない	*/
		}
		else {
			CCLog("hit y");
		}

		/*	めり込み分を算出	*/
		if((after.origin.y + after.size.height) > rect.origin.y)
		{
			/*	正方向	*/
			float adjust = (after.origin.y + after.size.height) - rect.origin.y;
			if(!check_posi)
			{
				adjust_posi = adjust;
				check_posi = true;
			}
			else
			{
				adjust_posi = std::min(adjust_posi,adjust);
			}
		}
		else
		if((rect.origin.y + rect.size.height) > after.origin.y)
		{
			/*	負方向	*/
			float adjust = (rect.origin.y + rect.size.height) - after.origin.y;
			if(!check_nega)
			{
				adjust_nega = adjust;
				check_nega = true;
			}
			else
			{
				adjust_nega = std::min(adjust_nega,adjust);
			}
		}
	}

	/*	正方向、負方向の補正値を足したものが最終的な補正値	*/
	result = adjust_posi + adjust_nega;

	return true;
}

/**
	矩形リストの破棄
*/
void CollisionManager::Release()
{
	m_RectArray.clear();
}

/*= end of file ======e=============================================*/
