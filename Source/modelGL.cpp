//==============================================================================
// タイトル     :   OpenGL用モデルクラス
// ファイル名   :   modelGL.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/05
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/05 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "modelGL.h"
#include "rendererGL.h"
#include "main.h"

//==============================================================================
// 列挙型宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// プロトタイプ宣言
//==============================================================================

//==============================================================================
// グローバル宣言
//==============================================================================

//==============================================================================
// 静的変数
//==============================================================================

//==============================================================================
// 関数名 : CModelGL()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CModelGL::CModelGL()
{
	m_subsetNum = 0;
	m_pSubsets  = NULL;
}

//==============================================================================
// 関数名 : ~CModelGL()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CModelGL::~CModelGL()
{

}

//==============================================================================
// 関数名 : bool DrawSubset( DWORD attribId )
// 引数   : DWORD AttribId : 描画対象ID
// 戻り値 : void
// 説明   : サブセットごとの描画処理
//==============================================================================
bool CModelGL::DrawSubset( DWORD attribId )
{
	if( attribId >= m_subsetNum )
	{
		return false;	// 範囲外のため処理失敗
	}

	glEnable( GL_DEPTH_TEST );

	// データ準備
	SUBSET modelData = m_pSubsets[ attribId ];

	VECTOR3* pPos = modelData.pPosBuff;
	VECTOR3* pNor = modelData.pNorBuff;
	VECTOR2* pTex = modelData.pTexBuff;

	DWORD idxNum = modelData.idxNum;

	// モデルの描画処理
	glBegin( GL_TRIANGLES );
	{
		for( DWORD idxCnt = 0 ; idxCnt < idxNum ; idxCnt++ )
		{
			// インデックスデータ取得
			DWORD posIdx = m_pSubsets[ attribId ].pPosIdxBuff[ idxCnt ];
			DWORD norIdx = m_pSubsets[ attribId ].pNorIdxBuff[ idxCnt ];
			DWORD texIdx = m_pSubsets[ attribId ].pTexIdxBuff[ idxCnt ];

			// 各データ取得
			VECTOR3 pos = pPos[ posIdx ];
			VECTOR3 nor = pNor[ norIdx ];
			VECTOR2 tex = pTex[ texIdx ];

			// 描画処理呼び出し
			glTexCoord2f( tex.x , tex.y );
			glNormal3f( nor.x , nor.y , nor.z );
			glVertex3f( pos.x , pos.y , pos.z );
		}
	}
	glEnd();

	glDisable( GL_DEPTH_TEST );

	return true;		// 処理成功
}

//==============================================================================
// 関数名 : void Release( void )
// 引数   : void
// 戻り値 : void
// 説明   : 解放処理
//==============================================================================
void CModelGL::Release( void )
{
	this->Uninit();
	delete this;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CModelGL::Uninit( void )
{
	// データ群解放
	if( m_pSubsets != NULL )
	{
		for( DWORD i = 0 ; i < m_subsetNum ; i++ )
		{
			delete[] m_pSubsets[ i ].pPosBuff;
			delete[] m_pSubsets[ i ].pTexBuff;
			delete[] m_pSubsets[ i ].pNorBuff;
			delete[] m_pSubsets[ i ].pPosIdxBuff;
			delete[] m_pSubsets[ i ].pTexIdxBuff;
			delete[] m_pSubsets[ i ].pNorIdxBuff;

			m_pSubsets[ i ].pPosBuff = NULL;
			m_pSubsets[ i ].pTexBuff = NULL;
			m_pSubsets[ i ].pNorBuff = NULL;
			m_pSubsets[ i ].pPosIdxBuff = NULL;
			m_pSubsets[ i ].pTexIdxBuff = NULL;
			m_pSubsets[ i ].pNorIdxBuff = NULL;
		}

		delete[] m_pSubsets;
		m_pSubsets = NULL;
	}

	// 基底クラスの終了処理
	CModel::Uninit();
}

//==============================================================================
// 関数名 : bool SetSubsets( int subsetNum , SUBSET* pDataBuff )
// 引数   : int subsetNum     : サブセット数
//          SUBSET* pDataBuff : データ群へのポインタ
// 戻り値 : bool型            : 処理結果
// 説明   : サブセットデータ設定処理
//==============================================================================
bool CModelGL::SetSubsets( int subsetNum , SUBSET* pDataBuff )
{
	if( subsetNum <= 0 )
	{
		return false;
	}

	if( pDataBuff == NULL )
	{
		return false;
	}

	// 設定処理
	m_subsetNum = subsetNum;
	m_pSubsets  = pDataBuff;

	return true;
}

//==============================================================================
// 関数名 : bool SetBuffers( int subsetIdx , VECTOR3* pPosBuff , VECTOR2* pTexBuff , VECTOR3* pNorBuff ,
//                            DWORD* pPosIdxBuff , DWORD* pTexIdxBuff , DWORD* pNorIdxBuff )
// 引数   : 
// 戻り値 : bool型 : 処理結果
// 説明   : バッファーの登録処理
//==============================================================================
bool CModelGL::SetBuffers( int subsetIdx , VECTOR3* pPosBuff , VECTOR2* pTexBuff , VECTOR3* pNorBuff , DWORD* pPosIdxBuff , DWORD* pTexIdxBuff , DWORD* pNorIdxBuff )
{
	//m_pPosBuff    = pPosBuff;
	//m_pTexBuff    = pTexBuff;
	//m_pNorBuff    = pNorBuff;
	//m_pPosIdxBuff = pPosIdxBuff;
	//m_pTexIdxBuff = pTexIdxBuff;
	//m_pNorIdxBuff = pNorIdxBuff;

	return true;
}

//==============================================================================
// 関数名 : サンプル
// 引数   : void
// 戻り値 : void
// 説明   : サンプル処理
//==============================================================================

