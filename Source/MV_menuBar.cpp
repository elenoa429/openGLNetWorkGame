//==============================================================================
// タイトル     :   モデルビューアー用メニューバー
// ファイル名   :   MV_menuBar.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/07/01
//==============================================================================

//==============================================================================
// 更新履歴: -2016/07/01 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// WARNING防止
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// インクルードファイル
//==============================================================================
#include "MV_menuBar.h"
#include "modelViewerProc.h"
#include "sceneGLModel.h"
#include "light.h"

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
// 関数名 : CMenuBar()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CMenuBar::CMenuBar()
{
	m_menuName = NULL;
	m_hMenu    = NULL;
}

//==============================================================================
// 関数名 : bool CreateMenuName( WORD id )
// 引数   : WORD id : 生成対象のID
// 戻り値 : bool型
// 説明   : メニューバー名生成
//==============================================================================
bool CMenuBar::CreateMenuName( WORD id )
{
	m_menuName = MAKEINTRESOURCE( id );

	return true;
}

//==============================================================================
// 関数名 : bool OperateMenu( WPARAM wParam )
// 引数   : WPARAM wParam : コマンドの入ったパラメータ
// 戻り値 : bool型        : メニュー操作判定
// 説明   : メニュー操作処理( WM_COMMAND内で呼び出し )
//==============================================================================
bool CMenuBar::OperateMenu( WPARAM wParam )
{
	switch( LOWORD( wParam ) )
	{
		case FILE_OPEN:
		{
			// モデルオープン
			CModelViewerProc* pMVProc = CModelViewerProc::GetModelViewerProc();

			if( pMVProc == NULL )
			{
				return false;
			}

			char currentDirectory[ MAX_PATH ] = { 0 };		// このアプリケーションのディレクトリ
			char modelFileFullPath[ MAX_PATH ] = { 0 };		// モデルファイルのフルパス

			OPENFILENAME of = { 0 };

			GetCurrentDirectory( MAX_PATH , currentDirectory );
			strcpy( modelFileFullPath , currentDirectory );
			strcat( modelFileFullPath , "\\data\\MODEL\\_\0" );

			of.lStructSize = sizeof( OPENFILENAME );
			of.hwndOwner = pMVProc->GetHWND();
			of.lpstrFilter = "オブジェクトファイル(*.obj)\0*.obj\0";
			of.lpstrFile = modelFileFullPath;
			of.nMaxFile = MAX_PATH;
			of.lpstrDefExt = "obj";

			if( GetOpenFileName( &of ) )
			{
				CSceneGLModel* pModel = pMVProc->GetModel();

				if( pModel != NULL )
				{
					pModel->Release();
					pModel = NULL;
				}

				SetCurrentDirectory( currentDirectory );				// ディレクトリを戻す

																		// フルパスを分解し、モデルファイルのパスのみを取得
				char chrDrive[ MAX_PATH ];								// ドライブ名
				char chrDir[ MAX_PATH ];								// ディレクトリ名
				char chrFile[ MAX_PATH ];								// ファイル名
				char chrExt[ MAX_PATH ];								// 拡張子

				_splitpath( modelFileFullPath , chrDrive , chrDir , chrFile , chrExt );

				strcat( chrFile , chrExt );

				// 現在の階層からの相対パスを生成
				char modelFileName[ MAX_PATH ] = { 0 };

				strcpy( modelFileName , "data\\MODEL\\" );
				strcat( modelFileName , chrFile );

				// モデル処理生成
				pModel = CSceneGLModel::Create( modelFileName );

				pMVProc->SetModel( pModel );
			}

			return true;
		}

		case DESTROY_EXE:
		{
			// 終了処理
			CModelViewerProc* pMVProc = CModelViewerProc::GetModelViewerProc();

			if( pMVProc == NULL )
			{
				return false;
			}

			PostMessage( pMVProc->GetHWND() , WM_CLOSE , 0 , 0 );

			return true;
		}

		case CAMERA_DIAROG_OPEN:
		{
			// カメラダイアログオープン
			CModelViewerProc::GetModelViewerProc()->GetCameraDialog()->ShowDialog( SW_SHOW );

			// メニューバーのチェック状態を変更
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = MFS_CHECKED;
			menuInfo.fMask  = MIIM_STATE;

			SetMenuItemInfo( GetHandle() , CAMERA_DIAROG_OPEN , FALSE , &menuInfo );
			return true;
		}

		case SET_LIGHT:
		{
			// ライト切り替え
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = MFS_CHECKED;
			menuInfo.fMask  = MIIM_STATE;

			GetMenuItemInfo( GetHandle() , SET_LIGHT , FALSE , &menuInfo );

			bool eneble;

			if( menuInfo.fState == MFS_CHECKED )
			{
				eneble = false;
				menuInfo.fState = MFS_UNCHECKED;
			}
			else
			{
				eneble = true;
				menuInfo.fState = MFS_CHECKED;
			}

			CLight::SetLightAllEnable( eneble );

			SetMenuItemInfo( GetHandle() , SET_LIGHT , FALSE , &menuInfo );

			return true;
		}

		case SET_TEXTURE:
		{
			// テクスチャ切り替え
			CSceneGLModel* pModel = CModelViewerProc::GetModelViewerProc()->GetModel();

			if( pModel == NULL )
			{
				return false;
			}
			
			bool flags = pModel->GetTexEnable();
			pModel->SetTexEnable( flags ? false : true );

			// メニューバーのチェック状態を変更
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = flags ? MFS_UNCHECKED : MFS_CHECKED;
			menuInfo.fMask = MIIM_STATE;

			SetMenuItemInfo( GetHandle() , SET_TEXTURE , FALSE , &menuInfo );
			return true;
		}

		case SET_MATERIAL:
		{
			// マテリアル切り替え
			CSceneGLModel* pModel = CModelViewerProc::GetModelViewerProc()->GetModel();

			if( pModel == NULL )
			{
				return false;
			}

			bool flags = pModel->GetMatEnable();
			pModel->SetMatEnable( flags ? false : true );

			// メニューバーのチェック状態を変更
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = flags ? MFS_UNCHECKED : MFS_CHECKED;
			menuInfo.fMask = MIIM_STATE;

			SetMenuItemInfo( GetHandle() , SET_MATERIAL , FALSE , &menuInfo );
			return true;
		}

		case POLYGON_FILL:
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			return true;
		}

		case POLYGON_WIRE:
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			return true;
		}

		case POLYGON_POINT:
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
			return true;
		}

		default:
		{
			return false;	// 処理を実行していない
		}
	}

	return false;
}
