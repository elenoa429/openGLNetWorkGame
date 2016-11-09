//==============================================================================
// タイトル     :   ファイル読み込み用クラス
// ファイル名   :   loader.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/02
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/02 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// WARNING防止
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// インクルードファイル
//==============================================================================
#include "loader.h"
#include <string.h>

/* ===各種ローダーのインクルード=== */
#include "texLoaderBMP.h"
#include "texLoaderTGA.h"
#include "texLoaderJPG.h"
#include "texLoaderPNG.h"

#include "ModelLoaderOBJ.h"

#include "materialLoaderMTL.h"

//==============================================================================
// 列挙型宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================
#define EXTENSION_LEN_MAX	( 64 )		// 拡張子の最大文字数( ここまで使うかは不明 )

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
// 関数名 : bool TextuerLoad( char* path , CTexture** ppTexture )
// 引数   : char* path           : ファイルパス( exeからの相対座標が望ましい )
//          CTexture** ppTexture : テクスチャ格納先ポインタ
// 戻り値 : bool型 : 処理結果
// 説明   : テクスチャ読み込み処理
//==============================================================================
bool CLoader::TextuerLoad( char* path , CTexture** ppTexture )
{
	//--------------------------------------
	// [ 拡張子の取得 ]
	//--------------------------------------
	char pathBuff[ MAX_PATH ] = { '\0' };	// ファイルパス用バッファー
	char* extension = NULL;					// 拡張子格納用ポインタ

	strcpy( pathBuff , path );				// バッファにパスを保存
	strtok( pathBuff , "." );				// ファイルパスの拡張子以外の部分を排除( 厳密にはちがうが... )
	extension = strtok( NULL , "." );		// 拡張子を取得

	/* ===エラーチェック=== */
	if( extension == NULL )
	{
		ErrorMsg(
			"拡張子が見つかりません。\nファイル名 : ",
			path );							// エラーメッセージ表示

		return false;						// 拡張子が見つからないor取得失敗
	}

	//--------------------------------------
	// [ 拡張子に対応した処理の呼び出し ]
	//--------------------------------------
	bool bResult = false;	// 処理結果

	if( strcmp( extension , "bmp" ) == 0 )
	{
		CTexLoaderBMP* pTexLoaderBMP = new CTexLoaderBMP;				// ローダーの生成
		bResult = pTexLoaderBMP->TextuerLoadBMP( path , ppTexture );	// BMP画像読み込み
		delete pTexLoaderBMP;											// ローダー削除
		pTexLoaderBMP = NULL;											// NULL埋め
	}
	else if( strcmp( extension , "tga" ) == 0 )
	{
		CTexLoaderTGA* pTexLoaderTGA = new CTexLoaderTGA;				// ローダーの生成
		bResult = pTexLoaderTGA->TextuerLoadTGA( path , ppTexture );	// TGA画像読み込み
		delete pTexLoaderTGA;											// ローダー削除
		pTexLoaderTGA = NULL;											// NULL埋め
	}
	else if( strcmp( extension , "png" ) == 0 )
	{
		CTexLoaderPNG* pTexLoaderPNG = new CTexLoaderPNG;				// ローダーの生成
		bResult = pTexLoaderPNG->TextuerLoadPNG( path , ppTexture );	// PNG画像読み込み
		delete pTexLoaderPNG;											// ローダー削除
		pTexLoaderPNG = NULL;											// NULL埋め
	}
	else if( strcmp( extension , "jpg" ) == 0 )
	{
		CTexLoaderJPG* pTexLoaderJPG = new CTexLoaderJPG;				// ローダーの生成
		bResult = pTexLoaderJPG->TextuerLoadJPG( path , ppTexture );	// JPG画像読み込み
		delete pTexLoaderJPG;											// ローダー削除
		pTexLoaderJPG = NULL;											// NULL埋め
	}
	else
	{
		ErrorMsg(
			"処理未実装の拡張子です。\nファイル名 : " ,
			path );							// エラーメッセージ表示
	}

	return bResult;		// 処理結果の返却
}

//==============================================================================
// 関数名 : bool ModelLoad( char* pFileName , CMaterialBuffe** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
// 引数   : char* pFileName               : ファイル名
//          CMaterialBuffer *ppMaterials  : マテリアル用バッファーへのダブルポインタ
//          DWORD* pNumMaterials          : マテリアル数格納先ポインタ
//          CModel** ppModelMesh          : モデルデータへのダブルポインタ
// 戻り値 : bool型 : 処理結果
// 説明   : テクスチャ読み込み処理
//==============================================================================
bool CLoader::ModelLoad( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
{
	//--------------------------------------
	// [ 拡張子の取得 ]
	//--------------------------------------
	char pathBuff[ MAX_PATH ] = { '\0' };	// ファイルパス用バッファー
	char* extension = NULL;					// 拡張子格納用ポインタ

	strcpy( pathBuff , pFileName );			// バッファにファイルネームを保存
	strtok( pathBuff , "." );				// ファイルパスの拡張子以外の部分を排除( 厳密にはちがうが... )
	extension = strtok( NULL , "." );		// 拡張子を取得

	/* ===エラーチェック=== */
	if( extension == NULL )
	{
		ErrorMsg(
			"拡張子が見つかりません。\nファイル名 : ",
			pFileName );

		return false;						// 拡張子が見つからないor取得失敗
	}

	//--------------------------------------
	// [ 拡張子に対応した処理の呼び出し ]
	//--------------------------------------
	bool bResult = false;	// 処理結果

	if( strcmp( extension , "obj" ) == 0 )
	{
		CModelLoaderOBJ* pModelLoaderOBJ = new CModelLoaderOBJ;			// ローダーの生成
		bResult = pModelLoaderOBJ->ModelLoadOBJ( pFileName , ppMaterials , pNumMaterials , ppModelMesh );	// OBJファイルからのデータ読み込み
		delete pModelLoaderOBJ;											// ローダー削除
		pModelLoaderOBJ = NULL;											// NULL埋め
	}
	else
	{
		ErrorMsg(
			"処理未実装の拡張子です。\nファイル名 : " ,
			pFileName );
	}

	return bResult;		// 処理結果の返却
}

//==============================================================================
// 関数名 : bool MaterialLoad( char* pFileName , CMaterial** ppMaterial )
// 引数   : char* pFileName        : ファイル名
//          CMaterial** ppMaterial : マテリアル処理へのダブルポインタ
// 戻り値 : bool型                 : 処理結果
// 説明   : マテリアルデータ読み込み処理
//==============================================================================
bool CLoader::MaterialLoad( char* pFileName , CMaterial** ppMaterial )
{
	//--------------------------------------
	// [ 拡張子の取得 ]
	//--------------------------------------
	char pathBuff[ MAX_PATH ] = { '\0' };	// ファイルパス用バッファー
	char* extension = NULL;					// 拡張子格納用ポインタ

	strcpy( pathBuff , pFileName );			// バッファにファイルネームを保存
	strtok( pathBuff , "." );				// ファイルパスの拡張子以外の部分を排除( 厳密にはちがうが... )
	extension = strtok( NULL , "." );		// 拡張子を取得

	// エラーチェック
	if( extension == NULL )
	{
		ErrorMsg(
			"拡張子が見つかりません。\nファイル名 : " ,
			pFileName );

		return false;						// 拡張子が見つからないor取得失敗
	}

	//--------------------------------------
	// [ 拡張子に対応した処理の呼び出し ]
	//--------------------------------------
	bool bResult = false;	// 処理結果

	if( strcmp( extension , "mtl" ) == 0 )
	{
		CMaterialLoaderMTL* pMaterialLoaderMTL = new CMaterialLoaderMTL;			// ローダーの生成
		bResult = pMaterialLoaderMTL->MaterialLoadMTL( pFileName , ppMaterial );	// MTLファイルからのデータ読み込み
		delete pMaterialLoaderMTL;													// ローダー削除
		pMaterialLoaderMTL = NULL;													// NULL埋め
	}
	else
	{
		ErrorMsg(
			"処理未実装の拡張子です。\nファイル名 : " ,
			pFileName );
	}

	return bResult;		// 処理結果の返却
}

//==============================================================================
// 関数名 : void ErrorMsg( char* errorMsg , char* path )
// 引数   : char* errorMsg : エラーメッセージ
//          char* path     : 読み込みに失敗したファイルパス
// 戻り値 : void
// 説明   : 読み込み失敗時のエラー文表示用
//==============================================================================
void CLoader::ErrorMsg( char* errorMsg , char* path )
{
	char errorMSG[ 1024 ] ={ '\0' };								// エラーメッセージ用バッファー
	
	strcpy( errorMSG , errorMsg );									// エラー文の文字列挿入

	if( path != NULL )
	{
		char pathBuff[ MAX_PATH ] ={ '\0' };						// ファイルパス用バッファー
		strcpy( pathBuff , path );									// バッファにパスを保存
		strcat( errorMSG , pathBuff );								// ファイルパスを挿入
	}

	MessageBox( NULL , errorMSG , "ERROR!!" , MB_ICONWARNING );		// エラーメッセージ表示
}
