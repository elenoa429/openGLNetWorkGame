//==============================================================================
// タイトル     :   DirectX用キーボード入力処理
// ファイル名   :   input.DX.Keyboard.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/04/26
//==============================================================================

//==============================================================================
// 更新履歴: -2016/04/26 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "input_DX_Keyboard.h"

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
// 関数名 : CInputDXKeyboard()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CInputDXKeyboard::CInputDXKeyboard()
{
	m_pDevKeyboard = NULL;

	for( int i = 0 ; i < DX_KEYBOARD_KEY_MAX ; i++ )
	{
		m_aKeyState[ i ]            = 0;
		m_aKeyStateTrigger[ i ]     = 0;
		m_aKeyStateRelease[ i ]     = 0;
		m_aKeyStateRepeat[ i ]      = 0;
		m_aKeyStateRepeatCount[ i ] = 0;
	}

	m_repeatDelayTime = 0;
}

//==============================================================================
// 関数名 : ~CInputDXKeyboard()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CInputDXKeyboard::~CInputDXKeyboard()
{

}

//==============================================================================
// 関数名 : bool Init( HINSTANCE hInstance , HWND hWnd )
// 引数   : HINSTANCE hInstance : インスタンスハンドル
//          HWND hWnd           : ウィンドウハンドル
// 戻り値 : void
// 説明   : 初期化処理
//==============================================================================
bool CInputDXKeyboard::Init( HINSTANCE hInstance , HWND hWnd )
{
	/* ===DirectInputオブジェクトの生成=== */
	if( CreateInputObject( hInstance , hWnd ) == false )
	{
		return false;		// 処理失敗
	}

	/* ===入力デバイスの生成=== */
	if( FAILED( GetInputObject()->CreateDevice(
		GUID_SysKeyboard,
		&m_pDevKeyboard,
		NULL ) ) )
	{
		return false;		// 処理失敗
	}

	/* ===データフォーマットの設定=== */
	if( FAILED( m_pDevKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		return false;		// 処理失敗
	}

	/* ===入力系統本体の生成=== */
	if( FAILED( m_pDevKeyboard->SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return false;		// 処理失敗
	}

	/* ===アクセス権の取得=== */
	m_pDevKeyboard->Acquire();

	/* ===リピート時間の代入=== */
	m_repeatDelayTime = 20;

	return true;	// 初期化成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CInputDXKeyboard::Uninit( void )
{
	/* ===入力デバイスの解放=== */
	if( m_pDevKeyboard != NULL )
	{
		m_pDevKeyboard->Unacquire();	// アクセス権解放
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	/* ===DirectInputオブジェクトの解放=== */
	ReleaseInputObject();
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CInputDXKeyboard::Update( void )
{
	/* ===入力状況の取得=== */
	BYTE aKeyState[ DX_KEYBOARD_KEY_MAX ];			// キーステータス

	if( SUCCEEDED( m_pDevKeyboard->GetDeviceState( sizeof( aKeyState ) , &aKeyState[ 0 ] ) ) )
	{
		for( int nKeyCnt = 0; nKeyCnt < DX_KEYBOARD_KEY_MAX; nKeyCnt++ )
		{
			m_aKeyStateTrigger[ nKeyCnt ] = aKeyState[ nKeyCnt ] & ~m_aKeyState[ nKeyCnt ];		// トリガー判定取得

			m_aKeyStateRelease[ nKeyCnt ] = ~aKeyState[ nKeyCnt ] & m_aKeyState[ nKeyCnt ];		// リリース判定取得

			/* ===リピート処理=== */
			if( m_aKeyStateRepeatCount[ nKeyCnt ] == m_repeatDelayTime )
			{
				m_aKeyStateRepeat[ nKeyCnt ] = aKeyState[ nKeyCnt ];		// リピートON
			}
			/* ===リピート判定部分=== */
			else if( aKeyState[ nKeyCnt ] )
			{
				m_aKeyStateRepeatCount[ nKeyCnt ]++;						// リピートタイマーカウントアップ
			}

			/* ===リピート終了判定=== */
			if( m_aKeyStateRelease[ nKeyCnt ] )
			{
				m_aKeyStateRepeatCount[ nKeyCnt ] = 0;						// タイマーカウントリセット
			}

			m_aKeyState[ nKeyCnt ] = aKeyState[ nKeyCnt ];					// プレス判定取得
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();	// アクセス権取得
	}
}


//==============================================================================
// 関数名 : bool GetPress( int nKey )
// 引数   : int nKey : 判定対象のキー
// 戻り値 : bool型   : 処理結果
// 説明   : Press判定取得処理
//==============================================================================
bool CInputDXKeyboard::GetPress( int nKey )
{
	return ( m_aKeyState[ nKey ] & 0x80 ) ? true : false;	// 先頭bitから、押下判定を取得する
}

//==============================================================================
// 関数名 : bool GetTrigger( int nKey )
// 引数   : int nKey : 判定対象のキー
// 戻り値 : bool型   : 処理結果
// 説明   : Trigger判定取得処理
//==============================================================================
bool CInputDXKeyboard::GetTrigger( int nKey )
{
	return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false;	// 先頭bitから、押下判定を取得する
}

//==============================================================================
// 関数名 : bool GetRelease( int nKey )
// 引数   : int nKey : 判定対象のキー
// 戻り値 : bool型   : 処理結果
// 説明   : Release判定取得処理
//==============================================================================
bool CInputDXKeyboard::GetRelease( int nKey )
{
	return ( m_aKeyStateRelease[ nKey ] & 0x80 ) ? true : false;	// 先頭bitから、押下判定を取得する
}

//==============================================================================
// 関数名 : bool GetRepeat( int nKey )
// 引数   : int nKey : 判定対象のキー
// 戻り値 : bool型   : 処理結果
// 説明   : Repeat判定取得処理
//==============================================================================
bool CInputDXKeyboard::GetRepeat( int nKey )
{
	if( m_aKeyStateRepeatCount[ nKey ] == 1 )
	{
		return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false;	// 最初の一回は、triggerで判定をとる
	}
	else
	{
		return ( m_aKeyStateRepeat[ nKey ] & 0x80 ) ? true : false;		// 先頭bitから、押下判定を取得する
	}
}

//==============================================================================
// 関数名 : ~CInputDXKeyboard()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
