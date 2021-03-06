//==============================================================================
// タイトル     :   PNG画像読み込み用クラス
// ファイル名   :   texLoaderPNG.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/12
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/12 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// WARNING防止
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// インクルードファイル
//==============================================================================
#include "texLoaderPNG.h"
#include "lib\libpng\include\png.h"
#include "lib\libpng\include\pngstruct.h"
#include "lib\libpng\include\pnginfo.h"
#include "lib\libpng\include\zlib.h"
#include "lib\libpng\include\zconf.h"

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================
#ifdef _DEBUG
#pragma comment( lib , "lib\\libpng\\lib\\libpng16d.lib" )			// png読み込み用
#pragma comment( lib , "lib\\libpng\\lib\\zlibd.lib" )				// png読み込み用
#else
#pragma comment( lib , "lib\\libpng\\lib\\libpng16.lib" )			// png読み込み用
#pragma comment( lib , "lib\\libpng\\lib\\zlib.lib" )				// png読み込み用
#endif

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
// 関数名 : bool TextuerLoadTGA( char* path , CTexture** ppTexture )
// 引数   : char* path           : ファイルパス
//          CTexture** ppTexture : テクスチャクラスへのダブルポインタ
// 戻り値 : bool型               : 処理結果
// 説明   : TGA画像読み込み処理
//==============================================================================
bool CTexLoaderPNG::TextuerLoadPNG( char* path , CTexture** ppTexture )
{
	//--------------------------------------
	// [ ファイルオープン ]
	//--------------------------------------
	FILE *fp;													// ファイルポインタ
	fp = fopen( path , "rb" );									// 指定されたビットマップ画像を開く

	/* ===エラーチェック=== */
	if( fp == NULL )
	{
		ErrorMsg(
			"画像の読み込みに失敗しました。\nファイル名 : " ,
			path );												// エラーメッセージ表示
		return false;											// 処理失敗
	}

	//--------------------------------------
	// [ ファイル読み込み ]
	//--------------------------------------
	// png画像ファイルのロード
	png_structp sp = png_create_read_struct( PNG_LIBPNG_VER_STRING , NULL , NULL , NULL );
	png_infop   ip = png_create_info_struct( sp );
	GLubyte* data;												 // 生データを保持する
	int width , height;
	int depth , colortype , interlacetype;

	png_init_io( sp , fp );
	png_read_info( sp , ip );
	png_get_IHDR( sp , ip , ( png_uint_32* )&width , ( png_uint_32* )&height ,
		&depth , &colortype , &interlacetype , NULL , NULL );

	// メモリ領域確保
	int rb = png_get_rowbytes( sp , ip );

	data = new GLubyte[ height * rb ];
	
	GLubyte **recv = new GLubyte*[ height ];
	
	for( int i = 0; i < height; i++ )
		recv[ i ] = &data[ ( height - 1 - i ) * rb ];

	png_read_image( sp , recv );
	png_read_end( sp , ip );
	png_destroy_read_struct( &sp , &ip , NULL );

	//--------------------------------------
	// [ テクスチャ生成処理 ]
	//--------------------------------------
	*ppTexture = CTextureGL::Create( ( int )width , ( int )height , GL_RGBA , ( GLubyte* )data );		// 生成処理の呼び出し

	//--------------------------------------
	// [ 読み込み終了処理 ]
	//--------------------------------------
	delete[] data;													// データのワーク破棄
	data = NULL;

	delete[] recv;													// ワーク破棄
	recv = NULL;

	fclose( fp );													// ファイルクローズ

	return true;	// 処理成功
}


//==============================================================================
// 関数名 : void ErrorMsg( char* errorMsg , char* path )
// 引数   : char* errorMsg : エラーメッセージ
//          char* path     : 読み込みに失敗したファイルパス
// 戻り値 : void
// 説明   : 読み込み失敗時のエラー文表示用
//==============================================================================
void CTexLoaderPNG::ErrorMsg( char* errorMsg , char* path )
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

//==============================================================
// [ 参考にしたソースコード ]
// http://d.hatena.ne.jp/yatt/20090817/1250508825
//==============================================================
