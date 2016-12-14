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
#include "input.h"
#include "cameraGL.h"


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
	m_axcel = 0.0275f;
	m_axcelAttack = 0.0f;
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
// 関数名 : CPlayer* Create( int charcterType )
// 引数   : int charcterType : キャラクタータイプ
// 戻り値 : CPlayer*型
// 説明   : 生成処理
//==============================================================================
CPlayer* CPlayer::Create( int charcterType )
{
	CPlayer* pNewInstance = new CPlayer;

	if( pNewInstance->Init( charcterType ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// 関数名 : bool Init( int charcterType )
// 引数   : int charcterType
// 戻り値 : bool型 : 成功判定
// 説明   : 初期化処理
//==============================================================================
bool CPlayer::Init( int charcterType )
{
	if( CCharcter::Init( charcterType ) == false )
	{
		return false;
	}

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
	CCharcter::Uninit();
}

//==============================================================================
// 関数名 : void Update()
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CPlayer::Update( void )
{
	CCharcter::Update();

	if( m_actionState != ACTION_ATTACK && m_actionState != ACTION_DEAD)
		walk();		// アタック状態に移行

	else if( m_actionState == ACTION_ATTACK &&
		abs(m_mov.x) <= 0.0001f &&
		abs(m_mov.z) <= 0.0001f )
	{// アタック状態から元に戻る
		m_actionState = ACTION_NONE;		// 状態なし
		m_axcel -= m_axcelAttack;			// 加速度を元に戻す
		m_gensui.x -= m_gensuiAttack.x;		// 減衰を
		m_gensui.y -= m_gensuiAttack.y;		// もとに
		m_gensui.z -= m_gensuiAttack.z;		// 戻す
	}

	// 情報表示
	CDebugProc::GetDebugProc()->PrintDebugProc( "[ PLAYER ]\n" );
	CDebugProc::GetDebugProc()->PrintDebugProc( "POS : ( %3.3f : %3.3f : %3.3f )\n" , m_pos.x , m_pos.y , m_pos.z );
	CDebugProc::GetDebugProc()->PrintDebugProc( "ROT : ( %3.3f : %3.3f : %3.3f )\n" , m_rot.x , m_rot.y , m_rot.z );
	CDebugProc::GetDebugProc()->PrintDebugProc( "MOV : ( %3.3f : %3.3f : %3.3f )\n" , m_mov.x , m_mov.y , m_mov.z );

	//------------------------------------------
	// [ 回転 ]
	//------------------------------------------
	Rotation();
}

//==============================================================================
// 関数名 : void Draw()
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CPlayer::Draw( void )
{
	CCharcter::Draw();
}

//==============================================================================
// 関数名 : void walk( void )
// 引数   : void
// 戻り値 : void
// 説明   : 移動処理
//==============================================================================
void CPlayer::walk( void )
{
	//---------------------------------------------------
	// [ カメラの角度を取得 ]
	//---------------------------------------------------
	CManager* manager = GetManager();
	CCameraGL* camera = manager->GetCamera();
	VECTOR3 cameraRot = camera->GetRot();

	//------------------------------------------
	// [ 入力情報の取得処理 ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	if( pInput->GetPress( DIK_W ) == true &&
		pInput->GetPress( DIK_A ) == false &&
		pInput->GetPress( DIK_D ) == false)
	{// 上キーのみで真上に移動
		m_actionState = ACTION_MOVE;				// 移動状態
		m_rotMokuhyou.y = cameraRot.y;				// 目標角度を設定
		m_mov.x -= sinf(cameraRot.y) * (m_axcel);	// 移動力Ｘを設定
		m_mov.z -= cosf(cameraRot.y) * (m_axcel);	// 移動力Ｚを設定
	}
	else if( pInput->GetPress( DIK_S ) == true &&
			 pInput->GetPress( DIK_A ) == false &&
			 pInput->GetPress( DIK_D ) == false)
	{// 下キーのみで真上に移動
		m_actionState = ACTION_MOVE;				// 移動状態
		m_rotMokuhyou.y = cameraRot.y + PI;			// 目標角度を設定
		m_mov.x += sinf(cameraRot.y) * (m_axcel);	// 移動力Ｘを設定
		m_mov.z += cosf(cameraRot.y) * (m_axcel);	// 移動力Ｚを設定
	}
	else if( pInput->GetPress( DIK_A ) == true )
    {
		m_actionState = ACTION_MOVE;				// 移動状態

        if( pInput -> GetPress( DIK_W ) )
        {//左上へ
            m_rotMokuhyou.y = cameraRot.y + PI / 4;// 何度に傾けるか
            m_mov.x += sinf( cameraRot.y - PI / 4 - PI / 2 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 4 - PI / 2 ) * ( m_axcel );
        }
        else if( pInput -> GetPress( DIK_S ) )
        {//左下へ
            m_rotMokuhyou.y = cameraRot.y + PI / 1.5; //何度に傾けるか
            m_mov.x += sinf( cameraRot.y - PI / 4 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 4 ) * ( m_axcel );
        }
        else
        {//左へ
            m_rotMokuhyou.y = cameraRot.y + PI / 2; //何度に傾けるか
            m_mov.x += sinf( cameraRot.y - PI / 2 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 2 ) * ( m_axcel );
        }
    }
    else if( pInput->GetPress( DIK_D ) == true )
    {
		m_actionState = ACTION_MOVE;				// 移動状態

        if( pInput -> GetPress( DIK_W ) )
        {//右上へ
            m_rotMokuhyou.y = cameraRot.y - PI / 4;// 何度に傾けるか
            m_mov.x -= sinf( cameraRot.y - PI / 4 - PI / 2 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 4 - PI / 2 ) * ( m_axcel );
        }
        else if( pInput -> GetPress( DIK_S ) )
        {//右下へ
            m_rotMokuhyou.y = cameraRot.y - PI / 1.5; //何度に傾けるか
            m_mov.x -= sinf( cameraRot.y - PI / 4 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 4 ) * ( m_axcel );
        }
        else
        {//右キーで右
            m_rotMokuhyou.y = cameraRot.y - PI / 2; //何度に傾けるか
            m_mov.x -= sinf( cameraRot.y - PI / 2 ) * ( m_axcel );
            m_mov.z -= cosf( cameraRot.y - PI / 2 ) * ( m_axcel );
        }
    }


	if( pInput -> GetPress( DIK_J ) )
	{//アタック
		if( m_actionState != ACTION_ATTACK)				// 移動状態
		m_actionState = ACTION_ATTACK;
		m_axcel += m_axcelAttack;
		m_gensui.x += m_gensuiAttack.x;
		m_gensui.y += m_gensuiAttack.y;
		m_gensui.z += m_gensuiAttack.z;
		m_mov.x += sinf( m_rotMokuhyou.y ) * ( m_axcel );
        m_mov.z += cosf( m_rotMokuhyou.y ) * ( m_axcel );
	}
}

//==============================================================================
// 関数名 : サンプル
// 引数   : void
// 戻り値 : void
// 説明   : サンプル処理
//==============================================================================

