//==============================================================================
// タイトル     :   モデルビューアー用カメラダイアログ
// ファイル名   :   MV_cameraDialog.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/07/01
//==============================================================================

//==============================================================================
// 更新履歴: -2016/07/01 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "MV_cameraDialog.h"
#include "resource.h"
#include "cameraGL.h"
#include "modelViewerProc.h"

using namespace ModelViewer;

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================

//==============================================================================
// 列挙型宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================
enum OPERATE_DIALOG
{
	AXIS_X = IDC_BUTTON1 ,
	AXIS_Y = IDC_BUTTON2 ,
	AXIS_Z = IDC_BUTTON3 ,
};

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
// 関数名 : CCameraDialog()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CCameraDialog::CCameraDialog()
{
	m_hDlg = NULL;
}

//==============================================================================
// 関数名 : ~CCameraDialog()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CCameraDialog::~CCameraDialog()
{

}

//==============================================================================
// 関数名 : CCameraDialog* Create( HINSTANCE hInstance , HWND hWndParent , WORD id )
// 引数   : HINSTANCE hInstance : インスタンスハンドル
//          HWND hWndParent     : 親ウィンドウハンドル
//          WORD id             : 生成対象のダイアログID
// 戻り値 : CCameraDialog*型
// 説明   : 生成処理
//==============================================================================
CCameraDialog* CCameraDialog::Create( HINSTANCE hInstance , HWND hWndParent , WORD id )
{
	CCameraDialog* pNewInstance = new CCameraDialog;

	if( pNewInstance->Init( hInstance , hWndParent , id ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// 関数名 : void Release( void )
// 引数   : void
// 戻り値 : void
// 説明   : 解放処理
//==============================================================================
void CCameraDialog::Release( void )
{
	CCameraDialog::Uninit();

	delete this;
}

//==============================================================================
// 関数名 : bool Init( HINSTANCE hInstance , HWND hWndParent , WORD id )
// 引数   : HINSTANCE hInstance : インスタンスハンドル
//          HWND hWndParent     : 親ウィンドウハンドル
//          WORD id             : 生成対象のダイアログID
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CCameraDialog::Init( HINSTANCE hInstance , HWND hWndParent , WORD id )
{
	m_hDlg = CreateDialog(
				hInstance,
				MAKEINTRESOURCE( id ),
				hWndParent,
				CameraDialogProc );

	if( m_hDlg == NULL )
	{
		return false;
	}

	ShowWindow( m_hDlg , SW_SHOW );

	return true;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CCameraDialog::Uninit( void )
{
	if( m_hDlg != NULL )
	{
		DestroyWindow( m_hDlg );
		m_hDlg = NULL;
	}
}

//==============================================================================
// 関数名 : BOOL CALLBACK CameraDialogProc( HWND hDlg , UINT msg , WPARAM wParam , LPARAM lParam )
// 引数   : void
// 戻り値 : void
// 説明   : カメラダイアログ用プロシージャ
//==============================================================================
BOOL CALLBACK CameraDialogProc( HWND hDlg , UINT msg , WPARAM wParam , LPARAM lParam )
{
	//----------------------------------------
	// [ 各種処理 ]
	//----------------------------------------
	switch( msg )
	{
		case WM_INITDIALOG:
		{
			return TRUE;
		}

		case WM_COMMAND:
		{
			CCameraGL* pCamera = GetManager()->GetCamera();
			VECTOR3 posV;
			VECTOR3 posR;
			VECTOR3 rot;

			switch( LOWORD( wParam ) )
			{
				case AXIS_X:
				{
					pCamera->Init( VECTOR3( 1000.0f , 0.0f , 0.0f ) );
					break;
				}

				case AXIS_Y:
				{
					pCamera->SetPosV( VECTOR3( 0.0f , 1000.0f , 0.0f ) );

					break;
				}

				case AXIS_Z:
				{
					pCamera->Init( VECTOR3( 0.0f , 0.0f , 1000.0f ) );

					break;
				}

				default:
				{
					break;
				}
			}

			break;
		}

		case WM_CLOSE:
		{
			// ウィンドウ隠蔽
			ShowWindow( hDlg , SW_HIDE );

			// メニューバーのチェック状態を変更
			CMenuBar* pMenu = CModelViewerProc::GetModelViewerProc()->GetMenu();
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = MFS_UNCHECKED;
			menuInfo.fMask  = MIIM_STATE;

			SetMenuItemInfo( 
				pMenu->GetHandle(),
				pMenu->CAMERA_DIAROG_OPEN,
				FALSE,
				&menuInfo );

			return TRUE;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}
