//==============================================================================
// タイトル     :   DirectX用マウス入力処理
// ファイル名   :   input.DX.mause.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/03
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/03 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "input_DX_mause.h"
#include "debugProc.h"

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
// 関数名 : CInputDXMause()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CInputDXMause::CInputDXMause()
{
	m_pDevInput = NULL;

	for ( int i = 0 ; i < DIM_KEY_MAX ; i++ )
	{
		m_aKeyState[ i ] = 0;
		m_aKeyStateTrigger[ i ] = 0;
		m_aKeyStateRelease[ i ] = 0;
		m_aKeyStateRepeat[ i ] = 0;
		m_aKeyStateRepeatCount[ i ] = 0;
	}

	m_repeatDelayTime = 0;

	m_screenPos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	m_velocity  = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
}

//==============================================================================
// 関数名 : ~CInputDXMause()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CInputDXMause::~CInputDXMause()
{

}

//==============================================================================
// 関数名 : bool Init( HINSTANCE hInstance , HWND hWnd )
// 引数   : HINSTANCE hInstance : インスタンスハンドル
//          HWND hWnd           : ウィンドウハンドル
// 戻り値 : void
// 説明   : 初期化処理
//==============================================================================
bool CInputDXMause::Init( HINSTANCE hInstance , HWND hWnd )
{
	// DirectInputオブジェクトの生成
	if( CreateInputObject( hInstance , hWnd ) == false )
	{
		return false;		// 処理失敗
	}

	// 入力デバイスの生成
	if ( FAILED( GetInputObject()->CreateDevice(
		GUID_SysMouse,
		&m_pDevInput,
		NULL ) ) )
	{
		return false;		// 処理失敗
	}

	// データフォーマットの設定
	if ( FAILED( m_pDevInput->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		return false;		// 処理失敗
	}

	// 軸モードの設定
	DIPROPDWORD DIProp;																// モード設定用変数

	DIProp.diph.dwSize       = sizeof( DIProp );									// 
	DIProp.diph.dwHeaderSize = sizeof( DIProp.diph );								// 
	DIProp.diph.dwObj        = 0;													// 
	DIProp.diph.dwHow        = DIPH_DEVICE;											// 
	DIProp.dwData            = DIPROPAXISMODE_REL;									// 軸の値のモード設定

	if( FAILED( m_pDevInput->SetProperty( DIPROP_AXISMODE , &DIProp.diph ) ) )	// 設定部分
	{
		return false;
	}

	// 入力系統本体の生成
	if( FAILED( m_pDevInput->SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return false;
	}

	// アクセス権の取得
	m_pDevInput->Acquire();

	// リピート時間の代入
	m_repeatDelayTime = 20;

	// ウィンドウハンドル格納
	m_hwnd = hWnd;

	return true;	// 初期化成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CInputDXMause::Uninit( void )
{
	// 入力デバイスの解放
	if ( m_pDevInput != NULL )
	{
		m_pDevInput->Unacquire();	// アクセス権解放
		m_pDevInput->Release();
		m_pDevInput = NULL;
	}

	// DirectInputオブジェクトの解放
	ReleaseInputObject();
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CInputDXMause::Update( void )
{
	// 入力状況の取得
	DIMOUSESTATE2 DIMouseState2;						// マウスのステータス

	if ( SUCCEEDED( m_pDevInput->GetDeviceState( sizeof( DIMOUSESTATE2 ) , &DIMouseState2 ) ) )
	{
		for ( int nKeyCnt = 0; nKeyCnt < DIM_KEY_MAX; nKeyCnt++ )
		{
			m_aKeyStateTrigger[ nKeyCnt ] = DIMouseState2.rgbButtons[ nKeyCnt ] & ~m_aKeyState[ nKeyCnt ];		// トリガー判定取得

			m_aKeyStateRelease[ nKeyCnt ] = ~DIMouseState2.rgbButtons[ nKeyCnt ] & m_aKeyState[ nKeyCnt ];		// リリース判定取得

			// リピート処理
			if ( m_aKeyStateRepeatCount[ nKeyCnt ] == m_repeatDelayTime )
			{
				m_aKeyStateRepeat[ nKeyCnt ] = DIMouseState2.rgbButtons[ nKeyCnt ];		// リピートON
			}
			// リピート判定部分
			else if ( DIMouseState2.rgbButtons[ nKeyCnt ] )
			{
				m_aKeyStateRepeatCount[ nKeyCnt ]++;						// リピートタイマーカウントアップ
			}

			// ピート終了判定
			if ( m_aKeyStateRelease[ nKeyCnt ] )
			{
				m_aKeyStateRepeatCount[ nKeyCnt ] = 0;						// タイマーカウントリセット
			}

			m_aKeyState[ nKeyCnt ] = DIMouseState2.rgbButtons[ nKeyCnt ];	// プレス判定取得
		}

		//-------------------------------------------------------
		// [ マウス座標の現在位置を取得・格納 ]
		//-------------------------------------------------------
		// カーソル移動速度の取得
		m_velocity.x = ( float )DIMouseState2.lX;	// X
		m_velocity.y = ( float )DIMouseState2.lY;	// Y
		m_velocity.z = ( float )DIMouseState2.lZ;	// Z

		// クライアント領域でのマウス座標を求める
		POINT mausePos;											// マウス位置

		GetCursorPos( &mausePos );								// マウス座標取得
		ScreenToClient( m_hwnd , &mausePos );

		m_screenPos.x = ( float )mausePos.x;
		m_screenPos.y = ( float )mausePos.y;
		m_screenPos.z += ( float )DIMouseState2.lZ;
		
		// クランプ処理
		if( m_screenPos.x < 0.0f ) m_screenPos.x = 0.0f;
		else if( m_screenPos.x > SCREEN_WIDTH ) m_screenPos.x = SCREEN_WIDTH;
		
		if( m_screenPos.y < 0.0f ) m_screenPos.y = 0.0f;
		else if( m_screenPos.y > SCREEN_HEIGHT ) m_screenPos.y = SCREEN_HEIGHT;

	}
	else
	{
		m_pDevInput->Acquire();		// アクセス権取得
	}
}


//==============================================================================
// 関数名 : bool GetPress( int nKey )
// 引数   : int nKey : 判定対象のキー
// 戻り値 : bool型   : 処理結果
// 説明   : Press判定取得処理
//==============================================================================
bool CInputDXMause::GetPress( int nKey )
{
	return ( m_aKeyState[ nKey ] & 0x80 ) ? true : false;	// 先頭bitから、押下判定を取得する
}

//==============================================================================
// 関数名 : bool GetTrigger( int nKey )
// 引数   : int nKey : 判定対象のキー
// 戻り値 : bool型   : 処理結果
// 説明   : Trigger判定取得処理
//==============================================================================
bool CInputDXMause::GetTrigger( int nKey )
{
	return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false;	// 先頭bitから、押下判定を取得する
}

//==============================================================================
// 関数名 : bool GetRelease( int nKey )
// 引数   : int nKey : 判定対象のキー
// 戻り値 : bool型   : 処理結果
// 説明   : Release判定取得処理
//==============================================================================
bool CInputDXMause::GetRelease( int nKey )
{
	return ( m_aKeyStateRelease[ nKey ] & 0x80 ) ? true : false;	// 先頭bitから、押下判定を取得する
}

//==============================================================================
// 関数名 : bool GetRepeat( int nKey )
// 引数   : int nKey : 判定対象のキー
// 戻り値 : bool型   : 処理結果
// 説明   : Repeat判定取得処理
//==============================================================================
bool CInputDXMause::GetRepeat( int nKey )
{
	if ( m_aKeyStateRepeatCount[ nKey ] == 1 )
	{
		return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false;	// 最初の一回は、triggerで判定をとる
	}
	else
	{
		return ( m_aKeyStateRepeat[ nKey ] & 0x80 ) ? true : false;		// 先頭bitから、押下判定を取得する
	}
}

//==============================================================================
// 関数名 : D3DXVECTOR3 GetPosToWorld( D3DXMATRIX mtxProj , D3DXMATRIX mtxView , float fZ )
// 引数   : D3DXMATRIX mtxProj : プロジェクション行列
//          D3DXMATRIX mtxView : ビュー行列
//          float fZ           : 射影空間のZ値( 0.0 ～ 1.0 )
// 戻り値 : D3DXVECTOR3型      : 処理結果
// 説明   : マウスワールド座標取得処理
//==============================================================================
D3DXVECTOR3 CInputDXMause::GetPosToWorld( D3DXMATRIX mtxProj , D3DXMATRIX mtxView , float fZ )
{
	D3DXMATRIX mtxInvView;				// ビュー行列用
	D3DXMATRIX mtxInvProj;				// プロジェクション行列用
	D3DXMATRIX mtxVp , mtxInvVp;		// ビューポート行列用

	// ビューの逆行列取得
	D3DXMatrixInverse( &mtxInvView , NULL , &mtxView );

	// プロジェクションの逆行列取得
	D3DXMatrixInverse( &mtxInvProj , NULL , &mtxProj );

	// ビューポートの逆行列取得
	D3DXMatrixIdentity( &mtxVp );

	mtxVp._11 = SCREEN_WIDTH / 2.0f;
	mtxVp._22 = -SCREEN_HEIGHT / 2.0f;
	mtxVp._41 = SCREEN_WIDTH / 2.0f;
	mtxVp._42 = SCREEN_HEIGHT / 2.0f;

	D3DXMatrixInverse( &mtxInvVp , NULL , &mtxVp );

	// 逆変換
	D3DXVECTOR3 out;
	D3DXVECTOR3 mausePos = m_screenPos;
	mausePos.z = fZ;
	D3DXMATRIX tmp = mtxInvVp * mtxInvProj * mtxInvView;
	D3DXVec3TransformCoord( &out , &mausePos , &tmp );

	return out;
}

//==============================================================================
// 関数名 : ~CInputDXMause()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
