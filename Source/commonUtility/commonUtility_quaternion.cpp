//==============================================================================
// タイトル     :   クォータニオンクラス
// ファイル名   :   commonUtility_quaternion.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/16
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/16 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "commonUtility_quaternion.h"

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================

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
// 関数名 : QUATERNION()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
QUATERNION::QUATERNION()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

//==============================================================================
// 関数名 : ~QUATERNION()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
QUATERNION::~QUATERNION()
{

}
