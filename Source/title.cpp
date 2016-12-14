//==============================================================================
// タイトル     :   タイトルモードオブジェクト
// ファイル名   :   title.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/07/11
//==============================================================================

//==============================================================================
// 更新履歴: -2016/07/11 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "title.h"
#include "skyBox.h"
#include "main.h"
#include "game.h"
#include "result.h"
#include "sceneGL2D.h"
#include "fade.h"

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
// 関数名 : CTitle()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CTitle::CTitle()
{

}

//==============================================================================
// 関数名 : ~CTitle()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CTitle::~CTitle()
{

}

//==============================================================================
// 関数名 : bool Init( void )
// 引数   : void
// 戻り値 : void
// 説明   : 初期化処理
//==============================================================================
bool CTitle::Init( void )
{
	CSceneGL2D::Create( "data\\TEXTURE\\sample000.jpg" );

	return true;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CTitle::Uninit( void )
{
	//---------------------------------------------
	// [ 各シーンの解放処理 ]
	//---------------------------------------------
	CScene::ReleaseAll();
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CTitle::Update( void )
{
	//---------------------------------------------
	// [ 各シーンの更新処理 ]
	//---------------------------------------------
	CScene::UpdateAll();

	//---------------------------------------------
	// [ モード切り替え ]
	//---------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	if( pInput != NULL )
	{
		if( pInput->GetTrigger( DIK_RETURN ) )
		{
			CFade::FadeStart( new CGame( 0 , 0 ) , 30 );
		}
	}

}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CTitle::Draw( void )
{
	//---------------------------------------------
	// [ 各シーンの描画処理 ]
	//---------------------------------------------
	CScene::DrawAll();
}
