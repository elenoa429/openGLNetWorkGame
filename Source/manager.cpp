//==============================================================================
// タイトル     :   インスタンス管理クラス
// ファイル名   :   manager.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/09
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/09 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "client.h"

#include "manager.h"

#include "sceneGL.h"
#include "lightGL.h"
#include "soundAL.h"
#include "editorCameraGL.h"
#include "fade.h"
#include "autoRotationCamera.h"

// 各シーンのインクルード
#include "sceneGLModel.h"
#include "sceneGL3D.h"
#include "sceneGL2D.h"
#include "box.h"
#include "skyBox.h"
#include "editorModel.h"
#include "testBox.h"

// 各モードのインクルード
#include "title.h"
#include "game.h"

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
ALuint g_buffer , g_source;

//==============================================================================
// 静的変数
//==============================================================================

//==============================================================================
// 関数名 : CManager()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CManager::CManager()
{
	m_pRenderer = NULL;
	m_pCamera   = NULL;
	m_pMode     = NULL;

	m_pClient = NULL;
}

//==============================================================================
// 関数名 : ~CManager()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CManager::~CManager()
{
}

//==============================================================================
// 関数名 : bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
// 引数   : HINSTANCE hInstance
//          HWND hWnd
//          bool bWindow
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CManager::Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
{
	CDebugConsole::GetInstance()->Init();

	//---------------------------------------------
	// [ レンダラーの初期化 ]
	//---------------------------------------------
	m_pRenderer = CRenderer::Create( RENDERER_TYPE_GL );		// OpenGLで生成

	if( m_pRenderer->Init( hInstance , hWnd , bWindow ) == false )
	{
		return false;											// 処理失敗
	}

	//---------------------------------------------
	// [ 入力系統の生成 ]
	//---------------------------------------------
	CInput::Create( INPUT_TYPE_DX_KEYBOARD , hInstance , hWnd );	// DirectInput製キーボードの生成
	CInput::Create( INPUT_TYPE_DX_MOUSE , hInstance , hWnd );		// DirectInput製マウスの生成

	//---------------------------------------------
	// [ カメラの生成 ]
	//---------------------------------------------
	m_pCamera = new CAutoRotationCamera;
	//m_pCamera->Init( VECTOR3( 0.0f , 3.0f , 5.0f ) );

	m_pCamera->Init( VECTOR3( 0.0f , 80.0f , 80.0f ) );

	//---------------------------------------------
	// [ ライトの生成 ]
	//---------------------------------------------
	LIGHT_PARAM param;

	// 0番目
	param.pos = VECTOR4( -1.0f , 1.0f , -1.0f , 0.0f );

	param.dir = VECTOR3( 1.0f , -1.0f , 1.0f );
	Vec3Normalize( &param.dir , &param.dir );

	param.diffuse = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );
	param.specular = COLOR_F32( 0.5f , 0.5f , 0.5f , 1.0f );

	CLightGL::Create( LIGHT0 , &param , LIGHT_TYPE_DIRECTIONAL );	// 生成処理

	CLight::GetLight( LIGHT0 )->Enable();							// 有効化

	// 1番目
	param.pos = VECTOR4( 1.0f , -1.0f , 2.0f , 0.0f );

	param.dir = VECTOR3( -1.0f , 1.0f , -1.0f );
	Vec3Normalize( &param.dir , &param.dir );

	param.diffuse = COLOR_F32( 0.7f , 0.7f , 0.7f , 1.0f );
	param.specular = COLOR_F32( 0.5f , 0.5f , 0.5f , 1.0f );

	CLightGL::Create( LIGHT1 , &param , LIGHT_TYPE_DIRECTIONAL );	// 生成処理

	CLight::GetLight( LIGHT1 )->Enable();							// 有効化

	// 2番目
	param.pos = VECTOR4( 0.0f , -1.0f , -1.0f , 0.0f );

	param.dir = VECTOR3( 0.0f , 1.0f , 1.0f );
	Vec3Normalize( &param.dir , &param.dir );

	param.diffuse = COLOR_F32( 0.5f , 0.5f , 0.5f , 1.0f );
	param.specular = COLOR_F32( 0.5f , 0.5f , 0.5f , 1.0f );

	CLightGL::Create( LIGHT2 , &param , LIGHT_TYPE_DIRECTIONAL );	// 生成処理

	CLight::GetLight( LIGHT2 )->Enable();							// 有効化

	//---------------------------------------------
	// [ フェード処理の初期化 ]
	//---------------------------------------------
	CFade::Init();

	//---------------------------------------------
	// [ 各シーンの生成 ]
	//---------------------------------------------
	//CSkyBox* pSkyBox = new CSkyBox;

	//pSkyBox->Init( "data\\TEXTURE\\skyBox00.png" );

	//CSceneGL3D::Create( "data\\TEXTURE\\filed00.jpg" );

	//CSceneGL2D::Create( "data\\TEXTURE\\skyBox00.png" );

	//CSceneGLModel::Create( "data\\MODEL\\miku_01.obj" );

	//CMotionEditModel::Create();

	//---------------------------------------------
	// [ デバッグプロシージャの生成 ]
	//---------------------------------------------
	CDebugProc::Create();

	//---------------------------------------------
	// [ 初期モードの生成 ]
	//---------------------------------------------
	CFade::FadeStart( new CGame( 0 , 1 ) , 120 );

	//---------------------------------------------
	// [ サウンドの生成 ]
	//---------------------------------------------
	CSound* pSound = CSoundAL::Create( 64 );		// サウンド処理生成

	//pSound->Play( pSound->SOUND_LABEL_BGM_TEST00 );

	// クライアント生成
	//m_pClient = CClient::Create();

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CManager::Uninit( void )
{
	//---------------------------------------------
	// [ レンダラーの解放 ]
	//---------------------------------------------
	if( m_pRenderer != NULL )
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//---------------------------------------------
	// [ 入力系統の解放 ]
	//---------------------------------------------
	CInput::ReleaseALL();

	//---------------------------------------------
	// [ カメラの解放 ]
	//---------------------------------------------
	if( m_pCamera != NULL )
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//---------------------------------------------
	// [ ライトの解放 ]
	//---------------------------------------------
	CLight::ReleaseAll();		// ライト解放処理

	//---------------------------------------------
	// [ フェード処理の解放 ]
	//---------------------------------------------
	CFade::Uninit();

	//---------------------------------------------
	// [ モードの解放 ]
	//---------------------------------------------
	if( m_pMode != NULL )
	{
		m_pMode->Release();
		m_pMode = NULL;
	}

	//---------------------------------------------
	// [ デバッグプロシージャの解放 ]
	//---------------------------------------------
	CDebugProc::Release();

	//---------------------------------------------
	// [ サウンドの解放 ]
	//---------------------------------------------
	CSound* pSound = CSoundAL::GetSound();

	if( pSound != NULL )
	{
		pSound->Release();
		pSound = NULL;
	}

	//---------------------------------------------
	// [ モデルデータの解放 ]
	//---------------------------------------------
	CModel::ReleaseAll();

	// クライアント終了
	if( m_pClient != NULL )
	{
		m_pClient->SetFinishFlag( true );
	}

	CDebugConsole::GetInstance()->Uninit();
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CManager::Update( void )
{
	//---------------------------------------------
	// [ システム系の更新処理 ]
	//---------------------------------------------
	CInput::UpdateAll();		// 入力系統の更新処理

	if( m_pCamera != NULL )
	{
		m_pCamera->Update();	// カメラの更新処理
	}

	CLight::UpdateAll();		// ライトの更新処理

	//---------------------------------------------
	// [ 各シーンの更新処理 ]
	//---------------------------------------------
	if( m_pMode != NULL )
	{
		m_pMode->Update();
	}

	//---------------------------------------------
	// [ フェード処理の更新 ]
	//---------------------------------------------
	CFade::Update();

	//---------------------------------------------
	// [ デバッグプロシージャの更新処理 ]
	//---------------------------------------------
	int fps = GetFps();

	CDebugProc::GetDebugProc()->PrintDebugProc( "FPS : %d\n" , fps );

	CDebugProc::GetDebugProc()->Update();

	int test_i = 24;
	float test_f = 2.043f;

	//CDebugProc::GetDebugProc()->PrintDebugProc( "\ntest01\n\n\nt\n\n" , test_i , test_f );
	//CDebugProc::GetDebugProc()->PrintDebugProc( "test03" , test_i , test_f );

	//CDebugProc::GetDebugProc()->PrintDebugProc( "test00\n%d\f%1.2f\n" , test_i , test_f );
	//CDebugProc::GetDebugProc()->PrintDebugProc( "ＭＳゴシック\n" );
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CManager::Draw( void )
{
	//---------------------------------------
	// [ 描画処理 ]
	//---------------------------------------
	if( m_pRenderer->BeginScene() == true )
	{
		if( m_pCamera != NULL )
		{
			m_pCamera->Set();			// カメラ行列の設定
		}

		CLight::SetLightAll();			// ライトの設定処理

		if( m_pMode != NULL )
		{
			m_pMode->Draw();			// 各シーン描画
		}

		CFade::Draw();					// フェード描画

		//---------------------------------------------
		// [ デバッグプロシージャの描画処理 ]
		//---------------------------------------------
		CDebugProc::GetDebugProc()->Draw();

		//---------------------------------------------
		// [ 描画終了処理 ]
		//---------------------------------------------
		m_pRenderer->EndScene();
		m_pRenderer->SwapBuffer();
	}
}


//==============================================================================
// 関数名 : bool SetMode( CMode* pMode )
// 引数   : CMode* pMode : 設定するモード
// 戻り値 : bool型
// 説明   : モード設定処理
//==============================================================================
bool CManager::SetMode( CMode* pMode )
{
	// エラーチェック
	if( pMode == NULL )
	{
		MessageBox( NULL , "ErrorCode #0\n次のモードが設定されていません。\n" , "Error" , MB_OK | MB_ICONERROR );
		return false;	// モードが設定されていない
	}

	// 現在設定されているモードの破棄
	if( m_pMode != NULL )
	{
		m_pMode->Release();
		m_pMode = NULL;
	}

	// 新しいモードの設定
	m_pMode = pMode;

	if( m_pMode->Init() == false )
	{
		m_pMode->Release();
		m_pMode = NULL;

		MessageBox( NULL , "ErrorCode #1\n初期化失敗しました。ゲームを終了します。\n" , "Error" , MB_OK | MB_ICONERROR );

		exit( -1 );

		return false;
	}

	// 全処理成功
	return true;
}
