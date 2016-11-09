//==============================================================================
// タイトル     :   モデルビューアー用プロシージャ
// ファイル名   :   modelViewerProc.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/27
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/27 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// WARNING防止
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// インクルードファイル
//==============================================================================
#include "modelViewerProc.h"
#include "sceneGLModel.h"
#include "axis.h"
#include "grid3D.h"
#include <CommCtrl.h>

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================
#pragma comment( lib , "comctl32.lib" )		// コモンコントロール用

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
CModelViewerProc* CModelViewerProc::m_pModelViewerProc = NULL;

//==============================================================================
// 関数名 : CModelViewerProc()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CModelViewerProc::CModelViewerProc()
{
	m_hInstance     = NULL;
	m_hWnd          = NULL;
	m_pMenuBar      = NULL;
	m_pStatusBar    = NULL;
	m_pToolBar      = NULL;
	m_pCameraDialog = NULL;
	m_pAccelerator  = NULL;
	m_pModel        = NULL;

	m_pAxis[ 0 ]    = NULL;
	m_pAxis[ 1 ]    = NULL;
	m_pAxis[ 2 ]    = NULL;
	m_pGrid         = NULL;
}

//==============================================================================
// 関数名 : ~CModelViewerProc()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CModelViewerProc::~CModelViewerProc()
{

}

//==============================================================================
// 関数名 : CModelViewerProc* Create( HINSTANCE hInstance , WORD menuID , WORD accelID )
// 引数   : HINSTANCE hInstance : インスタンスハンドル
//          WORD menuID         : メニューバー用ID
//          WORD accelID        : アクセラレータ用ID
// 戻り値 : CModelViewerProc*型
// 説明   : 生成処理
//==============================================================================
CModelViewerProc* CModelViewerProc::Create( HINSTANCE hInstance , WORD menuID , WORD accelID )
{
	if( m_pModelViewerProc == NULL )
	{
		m_pModelViewerProc = new CModelViewerProc();

		if( m_pModelViewerProc->Init( hInstance , menuID , accelID ) == false )
		{
			m_pModelViewerProc->Release();
			m_pModelViewerProc = NULL;
		}
	}

	return m_pModelViewerProc;
}

//==============================================================================
// 関数名 : void Release( void )
// 引数   : void
// 戻り値 : void
// 説明   : 解放処理
//==============================================================================
void CModelViewerProc::Release( void )
{
	// 終了処理
	CModelViewerProc::Uninit();

	// 自身の破棄
	delete this;
}

//==============================================================================
// 関数名 : bool Init( HINSTANCE hInstance , WORD menuID , WORD accelID )
// 引数   : HINSTANCE hInstance : インスタンスハンドル
//          WORD menuID         : メニューバー用ID
//          WORD accelID        : アクセラレータ用ID
// 戻り値 : bool型              : 処理結果
// 説明   : 初期化処理
//==============================================================================
bool CModelViewerProc::Init( HINSTANCE hInstance , WORD menuID , WORD accelID )
{
	// アクセラレータの生成
	m_pAccelerator = CAccelerator::Create( hInstance , accelID );

	if( m_pAccelerator == NULL )
	{
		return false;
	}

	// メニューの生成
	m_pMenuBar = new CMenuBar;
	m_pMenuBar->CreateMenuName( menuID );

	// グリッド生成
	m_pGrid = CGrid3D::Create( 20 , 20 , 200.0f , 200.0f );

	// 軸生成
	VECTOR3 root = VECTOR3( 0.0f , 0.0f , 0.0f );

	VECTOR3 axisX = VECTOR3( 2400.0f , 0.0f , 0.0f );
	VECTOR3 axisY = VECTOR3( 0.0f , 2400.0f , 0.0f );
	VECTOR3 axisZ = VECTOR3( 0.0f , 0.0f , 2400.0f );

	float lineVold = 4.0f;

	COLOR_F32 colorX = COLOR_F32( 1.0f , 0.0f , 0.0f , 1.0f );
	COLOR_F32 colorY = COLOR_F32( 0.0f , 1.0f , 0.0f , 1.0f );
	COLOR_F32 colorZ = COLOR_F32( 0.0f , 0.0f , 1.0f , 1.0f );

	m_pAxis[ 0 ] = CAxis::Create( root , axisX , lineVold , colorX );
	m_pAxis[ 1 ] = CAxis::Create( root , axisY , lineVold , colorY );
	m_pAxis[ 2 ] = CAxis::Create( root , axisZ , lineVold , colorZ );

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CModelViewerProc::Uninit( void )
{
	if( m_pMenuBar != NULL )
	{
		delete m_pMenuBar;
		m_pMenuBar = NULL;
	}

	if( m_pCameraDialog != NULL )
	{
		delete m_pCameraDialog;
		m_pCameraDialog = NULL;
	}

	if( m_pStatusBar != NULL )
	{
		m_pStatusBar->Release();
		m_pStatusBar = NULL;
	}

	if( m_pToolBar != NULL )
	{
		m_pToolBar->Release();
		m_pToolBar = NULL;
	}

	if( m_pAccelerator != NULL )
	{
		m_pAccelerator->Release();
		m_pAccelerator = NULL;
	}

	m_pModel = NULL;

	m_pAxis[ 0 ] = NULL;
	m_pAxis[ 1 ] = NULL;
	m_pAxis[ 2 ] = NULL;

	m_pGrid = NULL;
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CModelViewerProc::Update( void )
{
	if( m_pStatusBar != NULL )
	{
		m_pStatusBar->Update();
	}

	if( m_pToolBar != NULL )
	{
		m_pToolBar->Update();
	}
}

//==============================================================================
// 関数名 : bool MV_CreateDialog( HINSTANCE hInstance , HWND hWndParent )
// 引数   : HINSTANCE hInstance : インスタンスハンドル
//          HWND hWndParen      : 親ウィンドウハンドル
// 戻り値 : bool型
// 説明   : モデルビューアー用ダイアログ生成処理
//==============================================================================
bool CModelViewerProc::MV_CreateDialog( HINSTANCE hInstance , HWND hWndParent )
{
	// カメラ操作に関するダイアログの生成
	m_pCameraDialog = CCameraDialog::Create( hInstance , hWndParent , IDD_DIALOG1 );

	if( m_pCameraDialog == NULL )
	{
		return false;
	}

	return true;
}

//==============================================================================
// 関数名 : bool MV_CreateStatusBar( HWND hWndParent )
// 引数   : HWND hWndParen      : 親ウィンドウハンドル
// 戻り値 : bool型
// 説明   : モデルビューアー用ステータスバー生成処理
//==============================================================================
bool CModelViewerProc::MV_CreateStatusBar( HWND hWndParent )
{
	m_pStatusBar = CStatusBar::Create( hWndParent );

	return m_pStatusBar != NULL ? true : false;
}

//==============================================================================
// 関数名 : bool MV_CreateToolBar( HWND hWndParent )
// 引数   : HWND hWndParen      : 親ウィンドウハンドル
// 戻り値 : bool型
// 説明   : モデルビューアー用ツールバー生成処理
//==============================================================================
bool CModelViewerProc::MV_CreateToolBar( HWND hWndParent )
{
	m_pToolBar = CToolBar::Create( hWndParent );

	return m_pToolBar != NULL ? true : false;
}
