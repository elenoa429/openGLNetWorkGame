//==============================================================================
// タイトル     :   OpenGL用親子関係付きモデル処理
// ファイル名   :   parentModelGL.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/09/05
//==============================================================================

//==============================================================================
// 更新履歴: -2016/09/05 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include "modelGL.h"
#include "commonUtility.h"

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CParentModelGL
{
	//---------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------
public:
	CParentModelGL();
	~CParentModelGL();

	static CParentModelGL* Create( CModelGL* pModel , DWORD subsetIdx = 0 );

	void Release( void );
	bool Init( CModelGL* pModel , DWORD subsetIdx );
	void Uninit( void );
	void Update( void );
	void Draw( MATRIX* pParentMatrix );

	void SetPos( VECTOR3 pos ){ m_pos = pos; }
	void SetRotDegree( VECTOR3 rot );
	bool SetSubsetIdx( DWORD idx );
	void SetParent( CParentModelGL* pParent );

	VECTOR3 GetPos( void ){ return m_pos; }
	VECTOR3 GetRot( void ){ return m_rot; }
	DWORD GetSubsetIdx( void ){ return m_subsetIdx; }

private:
	MATRIX GetMtxParent( void );

	//---------------------------------------------
	// [ メンバ変数 ]
	//---------------------------------------------
private:
	LPModelGL m_pModel;				// モデルデータの処理へのポインタ
	DWORD m_subsetIdx;				// 対象のサブセットインデックス

	CParentModelGL* m_pParent;		// 親モデルへのポインタ

	MATRIX m_mtxLocal;				// ローカルマトリクス

	VECTOR3 m_pos;					// ローカル位置
	VECTOR3 m_rot;					// ローカル角度
};

//==============================================================================
// プロトタイプ宣言
//==============================================================================
