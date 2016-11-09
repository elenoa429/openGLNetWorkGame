//==============================================================================
// タイトル     :   JPG画像読み込み用クラス
// ファイル名   :   texLoaderJPG.cpp
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
#include "texLoaderJPG.h"
#include <stdio.h>

extern "C"
{
#define XMD_H
#include "lib\libjpeg\include\jpeglib.h"
#include "lib\libjpeg\include\jerror.h"
}

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================
#ifdef _DEBUG
#pragma comment( lib, "lib\\libjpeg\\lib\\libjpegd.lib" )
#else
#pragma comment( lib, "lib\\libjpeg\\lib\\libjpeg.lib" )
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
bool CTexLoaderJPG::TextuerLoadJPG( char* path , CTexture** ppTexture )
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
	jpeg_decompress_struct cInfo;
	jpeg_error_mgr jErr;

	cInfo.err = jpeg_std_error( &jErr );

	jpeg_create_decompress( &cInfo );

	// 読み込みファイル設定
	jpeg_stdio_src( &cInfo , fp );

	// ヘッダー読み込み
	jpeg_read_header( &cInfo , TRUE );

	// デコードスタート
	jpeg_start_decompress( &cInfo );

	// 画像パラメータ設定
	LONG biWidth  = ( ( cInfo.output_width + 3 ) & 0xFFFFFFFC );
	LONG biHeight = cInfo.output_height;

	// JPEG 1ラインのバイト数
	int nJpegLineBytes = biWidth * cInfo.output_components;

	// Bitmap 1ラインのバイト数
	long nBmpLineBytes = ( biWidth * 3 + 3 ) & 0xFFFFFFFC;

	// Bitmap の最下ラインにポインタ設定
	LPBYTE lpJpgData = new BYTE[ cInfo.output_height * nBmpLineBytes ];
	LPBYTE lpJpgDataTop = lpJpgData;											// バッファの先頭位置を記録

	lpJpgData += cInfo.output_height * nBmpLineBytes;
	while( cInfo.output_scanline < cInfo.output_height )
	{
		// ポインタを 1ライン分ずらす
		lpJpgData -= nBmpLineBytes;
		JSAMPROW praw = ( JSAMPROW )lpJpgData;

		// Jpeg を 1ライン読み込む
		jpeg_read_scanlines( &cInfo , ( JSAMPARRAY )&praw , 1 );
	}

	jpeg_finish_decompress( &cInfo );
	jpeg_destroy_decompress( &cInfo );

	// 画像のビット情報をUV座標で使えるようにスワップする
	GLubyte* bits = new GLubyte[ cInfo.output_height * nBmpLineBytes ];									// スワップしたものを格納するワーク
	int heightNum = cInfo.output_height;																// 高さ数

	for( int i = 0 ; i < heightNum; i++  )
	{
		long setPointDst = i * nBmpLineBytes;															// Dstの格納地点( 上から下へ )
		long setPointSrc = ( cInfo.output_height * nBmpLineBytes - nBmpLineBytes ) - setPointDst;		// Srcの格納地点( 下から上へ )
		long setSize     = nBmpLineBytes * sizeof( GLubyte );											// 格納サイズ( １行あたりの大きさ )

		memcpy( &bits[ setPointDst ] , &lpJpgDataTop[ setPointSrc ] , setSize );						// メモリコピー
	}

	//--------------------------------------
	// [ テクスチャ生成処理 ]
	//--------------------------------------
	*ppTexture = CTextureGL::Create( ( int )biWidth , ( int )biHeight , GL_RGB , bits );	// 生成処理の呼び出し

	//--------------------------------------
	// [ 読み込み終了処理 ]
	//--------------------------------------
	fclose( fp );													// ファイルクローズ

	delete[] bits;
	bits = NULL;

	delete[] lpJpgData;
	lpJpgData = NULL;

	return true;	// 処理成功
}


//==============================================================================
// 関数名 : void ErrorMsg( char* errorMsg , char* path )
// 引数   : char* errorMsg : エラーメッセージ
//          char* path     : 読み込みに失敗したファイルパス
// 戻り値 : void
// 説明   : 読み込み失敗時のエラー文表示用
//==============================================================================
void CTexLoaderJPG::ErrorMsg( char* errorMsg , char* path )
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
