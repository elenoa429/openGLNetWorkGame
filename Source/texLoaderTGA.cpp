//==============================================================================
// タイトル     :   TGA画像読み込み用クラス
// ファイル名   :   texLoaderTGA.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/06
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/06 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// WARNING防止
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// インクルードファイル
//==============================================================================
#include "texLoaderTGA.h"
#include <stdio.h>

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
bool CTexLoaderTGA::TextuerLoadTGA( char* path , CTexture** ppTexture )
{
	//--------------------------------------
	// [ ファイルオープン ]
	//--------------------------------------
	FILE *fp;											// ファイルポインタ
	fp = fopen( path , "rb" );							// 指定されたビットマップ画像を開く

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
	BYTE headerBuff[ 18 ];

	fread( headerBuff , 1 , sizeof( headerBuff ) , fp );			// ヘッダーの読み込み

	m_header.IDFieldLength  = headerBuff[ 0 ];
	m_header.colormapType   = headerBuff[ 1 ];
	m_header.type           = headerBuff[ 2 ];
	m_header.colormapOrigin = headerBuff[ 3 ] | headerBuff[ 4 ];
	m_header.colormapLength = headerBuff[ 5 ] | headerBuff[ 6 ];
	m_header.colormapDepth  = headerBuff[ 7 ];
	m_header.originX        = headerBuff[ 8 ] | headerBuff[ 9 ];
	m_header.originY        = headerBuff[ 10 ] | headerBuff[ 11 ];
	m_header.width          = headerBuff[ 12 ] | headerBuff[ 13 ];
	m_header.height         = headerBuff[ 14 ] | headerBuff[ 15 ];
	m_header.depth          = headerBuff[ 16 ];
	m_header.descriptor     = headerBuff[ 17 ];

	GLubyte* bits = NULL;											// ビットデータ用のワークへのポインタ
	bits = new GLubyte[ m_header.width * m_header.height * 4 ];		// 画像データのワーク確保

	//--------------------------------------
	// [ データ読み込み処理 ]
	//--------------------------------------
	for( int y = ( m_header.height - 1 ) ; y >= 0 ; y-- )
	{
		int bitIdxH = y * m_header.width;		// ビットの行インデックス

		for( int x = 0 ; x < m_header.width ; x++ )
		{
			int bitIdx = ( bitIdxH + x ) * 4;	// ビットインデックス

			BYTE r , g , b , a;
			b = fgetc( fp );
			g = fgetc( fp );
			r = fgetc( fp );
			a = fgetc( fp );

			bits[ bitIdx + 0 ] = r;
			bits[ bitIdx + 1 ] = g;
			bits[ bitIdx + 2 ] = b;
			bits[ bitIdx + 3 ] = a;
		}
	}

	//for( int y = 0 ; y < m_header.height - 1 ; y++ )
	//{
	//	int bitIdxH = y * m_header.width;		// ビットの行インデックス

	//	for( int x = 0 ; x < m_header.width ; x++ )
	//	{
	//		int bitIdx = ( bitIdxH + x ) * 4;	// ビットインデックス

	//		BYTE r , g , b , a;
	//		b = fgetc( fp );
	//		g = fgetc( fp );
	//		r = fgetc( fp );
	//		a = fgetc( fp );

	//		bits[ bitIdx + 0 ] = r;
	//		bits[ bitIdx + 1 ] = g;
	//		bits[ bitIdx + 2 ] = b;
	//		bits[ bitIdx + 3 ] = a;
	//	}
	//}

	//--------------------------------------
	// [ テクスチャ生成処理 ]
	//--------------------------------------
	ppTexture[ 0 ] = CTextureGL::Create( ( int )m_header.width , ( int )m_header.height , GL_RGBA , bits );		// 生成処理の呼び出し

	//--------------------------------------
	// [ 読み込み終了処理 ]
	//--------------------------------------
	delete[] bits;													// ワーク解放
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
void CTexLoaderTGA::ErrorMsg( char* errorMsg , char* path )
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
