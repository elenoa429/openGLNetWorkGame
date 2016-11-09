//==============================================================================
// タイトル     :   マテリアルデータ
// ファイル名   :   material.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/04
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/04 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "material.h"

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
// 関数名 : CMaterial()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CMaterial::CMaterial()
{
	m_ambient = COLOR_F32( 0.0f , 0.0f , 0.0f , 0.0f );
	m_diffuse = COLOR_F32( 0.0f , 0.0f , 0.0f , 0.0f );
	m_specular = COLOR_F32( 0.0f , 0.0f , 0.0f , 1.0f );
	m_emission = COLOR_F32( 0.0f , 0.0f , 0.0f , 1.0f );

	m_shininess = 0.0f;

	m_isShininessEnable = false;
}

//==============================================================================
// 関数名 : ~CMaterial()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CMaterial::~CMaterial()
{

}
