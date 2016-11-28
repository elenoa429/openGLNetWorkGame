//==============================================================================
// タイトル     :   プレイヤークラス
// ファイル名   :   player.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/11/28
//==============================================================================

//==============================================================================
// 更新履歴: -2016/11/28 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "player.h"

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
// 関数名 : CPlayer()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CPlayer::CPlayer()
{

}

//==============================================================================
// 関数名 : ~CPlayer()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CPlayer::~CPlayer()
{

}

//==============================================================================
// 関数名 : CPlayer* Create()
// 引数   : void
// 戻り値 : CPlayer*型
// 説明   : 生成処理
//==============================================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pNewInstance = new CPlayer;

	if( pNewInstance->Init() == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// 関数名 : bool Init()
// 引数   : void
// 戻り値 : bool型 : 成功判定
// 説明   : 初期化処理
//==============================================================================
bool CPlayer::Init()
{
	return true;
}

//==============================================================================
// 関数名 : void Uninit()
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CPlayer::Uninit()
{

}

//==============================================================================
// 関数名 : void Update()
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CPlayer::Update( void )
{
}

//==============================================================================
// 関数名 : void Draw()
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CPlayer::Draw( void )
{
}

//==============================================================================
// 関数名 : サンプル
// 引数   : void
// 戻り値 : void
// 説明   : サンプル処理
//==============================================================================

