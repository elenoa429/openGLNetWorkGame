//==============================================================================
// タイトル     :   モデルビューアープロシージャ
// ファイル名   :   modelViewerProc.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/27
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/27 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include <Windows.h>
#include "resource.h"
#include "MV_menuBar.h"
#include "MV_cameraDialog.h"
#include "MV_statusBar.h"
#include "MV_toolBar.h"
#include "MV_accelerator.h"

using namespace ModelViewer;

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// 前方宣言
//==============================================================================
class CSceneGLModel;
class CAxis;
class CGrid3D;

//==============================================================================
// クラス宣言
//==============================================================================
class CModelViewerProc
{
	//---------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------
public:
	// 生成処理
	static CModelViewerProc* Create( HINSTANCE hInstance , WORD menuID , WORD accelID );

	// 破棄処理
	void Release( void );

	// 初期化処理
	bool Init( HINSTANCE hInstance , WORD menuID , WORD accelID );

	// 終了処理
	void Uninit( void );

	// 更新処理
	void Update( void );

	// インスタンス取得
	static CModelViewerProc* GetModelViewerProc( void ){ return m_pModelViewerProc; }

	// メニューバー処理取得
	CMenuBar* GetMenu( void ){ return m_pMenuBar; }

	// ウィンドウハンドル関連
	HWND GetHWND( void ){ return m_hWnd; }
	void SetHWND( HWND hWnd ){ m_hWnd = hWnd; }

	// モデル関連
	CSceneGLModel* GetModel( void ){ return m_pModel; }
	void SetModel( CSceneGLModel* pModel ){ m_pModel = pModel; }

	// ダイアログ関連
	bool MV_CreateDialog( HINSTANCE hInstance , HWND hWndParent );

	CCameraDialog* GetCameraDialog( void ){ return m_pCameraDialog; }

	// ステータスバー関連
	bool MV_CreateStatusBar( HWND hWndParent );

	CStatusBar* GetStatusBar( void ){ return m_pStatusBar; }

	// ツールバー関連
	bool MV_CreateToolBar( HWND hWndParent );

	CToolBar* GetToolBar( void ){ return m_pToolBar; }

	// アクセラレータ関連
	CAccelerator* GetAccelerator( void ){ return m_pAccelerator; }

private:
	// コンストラクタ
	CModelViewerProc();
	CModelViewerProc( const CModelViewerProc& ){};

	// デストラクタ
	~CModelViewerProc();

	// オペレーター
	void operator=( const CModelViewerProc& ){};

	//---------------------------------------------
	// [ メンバ変数 ]
	//---------------------------------------------
private:
	static CModelViewerProc* m_pModelViewerProc;		// プロシージャ処理へのポインタ

	HINSTANCE m_hInstance;								// インスタンスハンドル
	HWND m_hWnd;										// ウィンドウハンドル

	CMenuBar*      m_pMenuBar;							// メニューバー処理へのポインタ
	CStatusBar*    m_pStatusBar;						// ステータスバー処理へのポインタ
	CToolBar*      m_pToolBar;							// ツールバー処理へのポインタ
	CCameraDialog* m_pCameraDialog;						// カメラ操作に関するダイアログ処理のポインタ
	CAccelerator*  m_pAccelerator;						// アクセラレータ処理へのポインタ

	CSceneGLModel* m_pModel;							// 閲覧対象モデル処理へのポインタ

	CAxis* m_pAxis[ 3 ];								// 軸描画用
	CGrid3D* m_pGrid;									// グリッド線用
};

//==============================================================================
// プロトタイプ宣言
//==============================================================================
