//==============================================================================
// タイトル     :   OpenGL用モデルクラス
// ファイル名   :   modelGL.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/05
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/05 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include "model.h"
#include "buffer.h"
#include "commonUtility.h"

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CModelGL : public CModel
{
	//---------------------------------------------
	// [ 構造体宣言 ]
	//---------------------------------------------
public:
	struct SUBSET
	{
		VECTOR3* pPosBuff;				// 位置情報バッファーへのポインタ
		VECTOR2* pTexBuff;				// テクスチャ座標バッファーへのポインタ
		VECTOR3* pNorBuff;				// 法線情報バッファーへのポインタ
		DWORD posDataNum;				// 位置情報の個数
		DWORD texDataNum;				// テクスチャ座標の個数
		DWORD norDataNum;				// 法線情報の個数

		DWORD* pPosIdxBuff;				// 位置インデックスバッファーへのポインタ
		DWORD* pTexIdxBuff;				// テクスチャ座標インデックスバッファーへのポインタ
		DWORD* pNorIdxBuff;				// 法線インデックスバッファーへのポインタ
		DWORD idxNum;					// インデックス数
	};

	//---------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------
public:
	CModelGL();
	~CModelGL();

	bool DrawSubset( DWORD attribId );

	void Release( void );
	void Uninit( void );

	bool SetSubsets( int subsetNum , SUBSET* pDataBuff );
	bool SetBuffers( int subsetIdx , VECTOR3* pPosBuff , VECTOR2* pTexBuff , VECTOR3* pNorBuff ,
						DWORD* pPosIdxBuff , DWORD* pTexIdxBuff , DWORD* pNorIdxBuff );

	DWORD GetSubsetNum( void ){ return m_subsetNum; }

	bool SetMaterial( DWORD attribId ){ return true; }
	bool SetMatTexture( DWORD attribId ){ return true; }
	// 頂点バッファー取得
	//LPVertexBuffer GetVertexBuffer( void ){ return m_ppVtxBuff[ 0 ]; }

	// インデックスバッファー取得
	//LPIndexBuffer GetIndexBuffer( void ){ return m_ppIdxBuff[ 0 ]; }

	//---------------------------------------------
	// [ メンバ変数 ]
	//---------------------------------------------
protected:
	SUBSET* m_pSubsets;					// 各モデルグループデータ群へのポインタ
	DWORD m_subsetNum;					// サブセット数
};

typedef class CModelGL* LPModelGL;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
