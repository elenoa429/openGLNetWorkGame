//==============================================================================
// タイトル     :   メイン処理
// ファイル名   :   main.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/04/18
//==============================================================================

//==============================================================================
// 更新履歴: -2016/04/18 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "main.h"
#include "manager.h"
#include <CommCtrl.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

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
// ウィンドウ関連
#define WND_CLASS_NAME		"ONION_S"						// ウィンドウクラス名
#define WND_NAME			"OpenGL_ModelViewer"			// ウィンドウ名

// FPS関連
#define FRAME_PER_SECOND	( 1000 / 60 )					// FPSの計測単位
#define FPS_GET_TIME		( 500 )							// FPS取得時間( 単位：ms )

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// プロトタイプ宣言
//==============================================================================
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

//==============================================================================
// グローバル宣言
//==============================================================================
int g_nCountFPS = 0;									// FPSカウンタ
RECT g_WindowSize;										// ウィンドウサイズの記録用

CManager* g_pManager = NULL;							// 管理クラスへのポインタ

//================================================================================================================
// 関数名 : int WINAPI WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
//
// 引数   : HINSTANCE hInstance      : アプリケーションのインスタンスハンドル
//          HINSTANCE hPrevInstance  : 拡張用？( 常に NULL でＯＫ )
//          LPSTR lpCmdLine          : コマンドラインから受け取った引数へのポインタ
//          int nCmdShow             : アプリケーションの初期ウィンドウ表示方法設定
//
// 戻り値 : int型                    : 0 : 正常終了
// 説明   : メイン関数
//================================================================================================================
int WINAPI WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
#ifdef _DEBUG
	// メモリリーク検出
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// ----------------------------------------------------------------------
	// [ モデルビューアープロシージャ生成 ]
	// ----------------------------------------------------------------------
	//CModelViewerProc* pModelViewerProc = CModelViewerProc::Create( hInstance , IDR_MENU1 , IDR_ACCELERATOR1 );
	//CMenuBar* pMenuBar = pModelViewerProc->GetMenu();

	//----------------------------------------------
	// [ ウィンドウ生成 ]
	//----------------------------------------------
	DWORD dwFrameCount;																// フレームカウンタ
	DWORD dwCurrentTime;															// 現在時刻
	DWORD dwExecLastTime;															// アプリ更新の最終時刻
	DWORD dwFPSLastTime;															// FPS取得時の最終時刻

	WNDCLASSEX wcex;																// ウィンドウクラス

	wcex.cbSize         = sizeof( WNDCLASSEX );										// メモリサイズ指定
	wcex.style          = CS_HREDRAW | CS_VREDRAW;									// 表示するウィンドウのスタイル設定
	wcex.lpfnWndProc    = WndProc;													// ウィンドウプロシージャのアドレス指定
	wcex.cbClsExtra     = 0;														// 使用しない
	wcex.cbWndExtra     = 0;														// 使用しない
	wcex.hInstance      = hInstance;												// インスタンスハンドル
	wcex.hIcon          = LoadIcon( hInstance , MAKEINTRESOURCE( IDI_ICON1 ) );		// アプリケーションのアイコン指定
	wcex.hCursor        = LoadCursor( NULL, IDC_ARROW );							// マウスカーソルの指定
	wcex.hbrBackground  = ( HBRUSH )( COLOR_WINDOW + 1 );							// クライアント領域の背景色指定
	wcex.lpszMenuName   = NULL;
	//wcex.lpszMenuName   = pMenuBar->GetMenuName();									// メニューの指定
	wcex.lpszClassName  = WND_CLASS_NAME;											// ウィンドウクラスの名前
	wcex.hIconSm        = NULL;														// 小アイコン指定時の設定

	HWND hWnd;																		// ウィンドウハンドル
	MSG msg;																		// メッセージ用
	RegisterClassEx( &wcex );														// ウィンドウクラスの登録
	RECT rect ={ 0 , 0 , ( LONG ) SCREEN_WIDTH , ( LONG ) SCREEN_HEIGHT };			// ウィンドウ作成用

	AdjustWindowRect(																/* ==ウィンドウ調整== */
		&rect ,																			// 調整用の変数
		WS_OVERLAPPEDWINDOW ,															// スタイル
		false );																		// 

	hWnd = CreateWindowEx(															/* ==ウィンドウ作成== */
		0 ,																				//
		WND_CLASS_NAME ,																// ウィンドウクラスの名前
		WND_NAME ,																		// ウィンドウ自体の名前
		WS_OVERLAPPEDWINDOW ,															// ウィンドウスタイル
		CW_USEDEFAULT ,																	// ウィンドウ左上Ｘ座標
		CW_USEDEFAULT ,																	// ウィンドウ左上Ｙ座標
		( rect.right - rect.left ) ,													// ウィンドウ幅
		( rect.bottom - rect.top ) ,													// ウィンドウ高さ
		NULL ,																			// 親ウィンドウハンドル
		NULL ,																			// 子ウィンドウＩＤ
		hInstance ,																		// インスタンスハンドル
		NULL );																			// ウィンドウ作成データ

	if( hWnd == NULL )
	{
		return -1;
	}

	// モデルビューワー構成要素の生成・初期化
	//pModelViewerProc->SetHWND( hWnd );												// ウィンドウハンドル設定
	//pModelViewerProc->MV_CreateDialog( hInstance , hWnd );							// ダイアログ生成

	//----------------------------------------------
	// [ 初期化処理 ]
	//----------------------------------------------
	// ウィンドウ表示部分
	ShowWindow( hWnd , nCmdShow );
	UpdateWindow( hWnd );

	// 現在のウィンドウサイズの取得
	GetWindowRect( hWnd , &g_WindowSize );

	// 管理クラスの生成・初期化
	g_pManager = new CManager;							// 管理クラス生成

	if( g_pManager->Init( hInstance , hWnd , true ) == false )
	{
		g_pManager->Uninit();
		delete g_pManager;
		g_pManager = NULL;
		return -1;										// 処理失敗
	}

	// FPS関連
	timeBeginPeriod( 1 );								// 分解能
	dwFrameCount = dwCurrentTime = 0;					// カウンタ系の初期化
	dwExecLastTime = dwFPSLastTime = timeGetTime();		// 時刻の初期化

	//----------------------------------------------
	// [ メインループ ]
	//----------------------------------------------
	//HACCEL hAccel = pModelViewerProc->GetAccelerator()->GetHandle();

	while( 1 )
	{
		if( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) != 0 )
		{
			//if( !TranslateAccelerator( hWnd , hAccel , &msg ) )
			//{
				// Windowsの処理
				if( msg.message == WM_QUIT )
				{
					// 終了判定ＯＮ
					break;
				}
				else
				{
					// メッセージの翻訳・送出部分
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
			//}
		}
		else
		{
			// アプリケーションの処理
			dwCurrentTime = timeGetTime();	// 時刻取得

			// フレーム数取得処理
			if( ( dwCurrentTime - dwFPSLastTime ) >= FPS_GET_TIME )
			{
				g_nCountFPS = ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );	// フレーム数の取得
				dwFPSLastTime = dwCurrentTime;												// 取得時刻の更新
				dwFrameCount = 0;															// カウントリセット
			}

			// アプリケーションの更新・描画処理
			if( ( dwCurrentTime - dwExecLastTime ) >= FRAME_PER_SECOND )
			{
				dwExecLastTime = dwCurrentTime;		// 取得時刻の更新

				g_pManager->Update();				// 管理クラスの更新処理
				g_pManager->Draw();					// 管理クラスの描画処理

				dwFrameCount++;						// フレーム数カウントアップ
			}
		}
	}

	//----------------------------------------------
	// [ 終了処理部分 ]
	//----------------------------------------------
	// モデルビューアープロシージャ解放
	//CModelViewerProc::GetModelViewerProc()->Release();

	// 管理クラスの解放処理
	if( g_pManager != NULL )
	{
		g_pManager->Uninit();
		delete g_pManager;
		g_pManager = NULL;
	}

	UnregisterClass( WND_CLASS_NAME , wcex.hInstance );		// ウィンドウクラスの登録解除
	timeEndPeriod( 1 );										// 更新時刻の終了処理

	return ( int ) msg.wParam;
}

//================================================================================================================
// 関数名 : CManager* GetManager( void )
// 引数   : void
// 戻り値 : CManager*型
// 説明   : 管理クラス取得処理
//================================================================================================================
CManager* GetManager( void )
{
	return g_pManager;	// 管理クラスへのポインタを返却
}

//================================================================================================================
// 関数名 : void DrawFPS( void )
// 引数   : void
// 戻り値 : void
// 説明   : FPS描画用
//================================================================================================================
#ifdef _DEBUG
void DrawFPS( void )
{
	/* ===FPSの確認=== */
	//PrintDebugProc( "FPS : %d" , g_nCountFPS );
	return;
}
#endif


//============================================================================================
// 関数名 : LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wPram , LPARAM lParam )
//
// 引数   : HWND hWnd     : 
//          UINT uMsg     : 
//          WPARAM wPram  : 
//          LPARAM lParam : 
//
// 戻り値 : LRESULT型
// 説明   : ウィンドウプロシージャ
//============================================================================================
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	int nID;																				// メッセージボックスからの命令判断用
	CMenuBar* pMenuBar = NULL;																// メニューバー処理へのポインタ

	switch( uMsg )
	{
		case WM_CLOSE:
		{
			ShowCursor( TRUE );																// カーソルの出現
			nID = MessageBox( hWnd , "終了しますか？" , "確認" , MB_OKCANCEL );				// 終了判定の取得

			if( nID == IDOK )
			{
				DestroyWindow( hWnd );
			}
			else
			{
				ShowCursor( FALSE );														// カーソルの消去
				return 0;																	// 非終了のため、WM_DESTROYを送らないようにする
			}
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}

		case WM_LBUTTONDOWN:
		{
			SetFocus( hWnd );
			break;
		}

		case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostMessage( hWnd , WM_CLOSE , 0 , 0 );
					break;

				default:
					break;
			}

			break;
		}

		case WM_COMMAND:
		{
			//pMenuBar = CModelViewerProc::GetModelViewerProc()->GetMenu();
			//pMenuBar->OperateMenu( wParam );
			break;
		}

		case WM_CREATE:
		{
			// コモンコントロール初期化
			//InitCommonControls();
			//
			//// ステータスバー生成
			//CModelViewerProc::GetModelViewerProc()->MV_CreateStatusBar( hWnd );
			//
			//// ツールバー生成
			//CModelViewerProc::GetModelViewerProc()->MV_CreateToolBar( hWnd );
			//
			//// メニューバーハンドル取得
			//CModelViewerProc::GetModelViewerProc()->GetMenu()->SetHandle( GetMenu( hWnd ) );

			break;
		}

		case WM_SIZE:
		{
			// コモンコントロールのサイズ調整
			//SendMessage( CModelViewerProc::GetModelViewerProc()->GetStatusBar()->GetHandle() , uMsg , wParam , lParam );
			//SendMessage( CModelViewerProc::GetModelViewerProc()->GetToolBar()->GetHandle() , uMsg , wParam , lParam );
			break;
		}

		default:
		{
			break;
		}
	}

	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}
