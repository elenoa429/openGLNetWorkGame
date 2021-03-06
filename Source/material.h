//==============================================================================
// タイトル     :   マテリアルデータ
// ファイル名   :   material.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/04
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/04 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
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
class CMaterial
{
	//---------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------
public:
	CMaterial();											// デフォルトコンストラクタ
	~CMaterial();											// デストラクタ

	virtual void Release( void ) = 0;						// 解放処理

	virtual void Set( void ) = 0;							// マテリアル設定

	//---------------------------------------------
	// [ メンバ変数 ]
	//---------------------------------------------
public:
	COLOR_F32 m_ambient;									// 環境光
	COLOR_F32 m_diffuse;									// 拡散反射光
	COLOR_F32 m_specular;									// 鏡面反射光
	COLOR_F32 m_emission;									// 放射輝度

	float m_shininess;										// 鏡面反射光指数
	bool  m_isShininessEnable;								// 鏡面反射光有効判定

};

typedef class CMaterial* LPMaterial;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
