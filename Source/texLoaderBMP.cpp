//==============================================================================
// タイトル     :   BMP画像読み込み用クラス
// ファイル名   :   texLoaderBMP.cpp
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
#include "texLoaderBMP.h"
#include <string.h>

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================

//==============================================================================
// 列挙型宣言
//==============================================================================
enum BMP_BITCOUNT
{								/* ===ビットマップ画像のビットカウント識別子=== */
	BMP_COLOR_2         = 1,		// 2色モノクロ画像
	BMP_COLOR_16        = 4,		// 16色画像
	BMP_COLOR_256       = 8,		// 256色画像
	BMP_COLOR_TRUE      = 24,		// true color画像( 1677万色 )
	BMP_COLOR_TRUE_PLUS = 32,		// true color画像( 1677万色 )( 基本的には上と同じ処理...かな？ )
};

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
// 関数名 : bool TextuerLoadBMP( char* path , CTexture** ppTexture )
// 引数   : char* path           : bmp画像のファイルパス
//          CTexture** ppTexture : テクスチャ格納先ポインタ
// 戻り値 : bool型 : 処理結果
// 説明   : bmp画像読み込み処理
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP( char* path , CTexture** ppTexture )
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
			"画像の読み込みに失敗しました。\nファイル名 : ",
			path );												// エラーメッセージ表示
		return false;											// 処理失敗
	}

	//--------------------------------------
	// [ ヘッダーの読み込み ]
	//--------------------------------------
	BITMAPFILEHEADER bmfh;										// ビットマップファイルヘッダー
	BITMAPINFOHEADER bmih;										// ビットマップインフォヘッダー

	fread( &bmfh , sizeof( BITMAPFILEHEADER ) , 1 , fp );		// ビットマップファイルヘッダーの読み込み
	fread( &bmih , sizeof( BITMAPINFOHEADER ) , 1 , fp );		// ビットマップインフォヘッダーの読み込み

	//--------------------------------------
	// [ 共通部分の読み込み ]
	//--------------------------------------
	LONG width    = bmih.biWidth;								// 画像幅
	LONG height   = bmih.biHeight;								// 画像高さ
	WORD bitCount = bmih.biBitCount;							// 色ビット数

	//--------------------------------------
	// [ ビット数に応じた色情報の取得処理 ]
	//--------------------------------------
	GLubyte* bits = NULL;										// ビットデータ用のワークへのポインタ
	bool bResult = false;										// 処理結果

	bits = new GLubyte[ width * height * 3 ];					// 画像サイズ分のワークを動的確保

	switch( bitCount )
	{
		case BMP_COLOR_2:
		{
			ErrorMsg(
				"モノクロ画像読み込み処理は未実装です。\nファイル名 : ",
				path );															// エラーメッセージ表示
			bResult = TextuerLoadBMP_BIT_1( fp , width , height , bits );		// 読み込み処理
			break;
		}

		case BMP_COLOR_16:
		{
			ErrorMsg(
				"16色画像読み込み処理は未実装です。\nファイル名 : ",
				path );															// エラーメッセージ表示
			bResult = TextuerLoadBMP_BIT_4( fp , width , height , bits );		// 読み込み処理
			break;
		}

		case BMP_COLOR_256:
		{
			bResult = TextuerLoadBMP_BIT_8( fp , width , height , bits );		// 読み込み処理
			break;
		}

		case BMP_COLOR_TRUE:
		{
			bResult = TextuerLoadBMP_BIT_24( fp , width , height , bits );		// 読み込み処理
			break;
		}

		case BMP_COLOR_TRUE_PLUS:
		{
			bResult = TextuerLoadBMP_BIT_32( fp , width , height , bits );		// 読み込み処理
			break;
		}

		default:
		{
			ErrorMsg(
				"ビット情報がうまく読み取れません。\nファイルが壊れている可能性があります。\nファイル名 : " ,
				path );												// エラーメッセージ表示
			bResult = false;
			break;
		}
	}

	/* ===エラーチェック=== */
	if( bResult == false )
	{
		return false;	// 処理失敗
	}

	//--------------------------------------
	// [ テクスチャ生成処理 ]
	//--------------------------------------
	ppTexture[ 0 ] = CTextureGL::Create( ( int )width , ( int )height , GL_RGB , bits );		// 生成処理の呼び出し

	//--------------------------------------
	// [ 読み込み終了処理 ]
	//--------------------------------------
	delete[] bits;													// ワーク解放
	fclose( fp );													// ファイルクローズ

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : bool TextuerLoadBMP_BIT_1( FILE* fp , LONG width , LONG height , GLubyte* bits )
// 引数   : FILE* fp           : bmp画像のファイルポインタ( 読み込み済み )
//          LONG width         : 画像幅
//          LONG height        : 画像高さ
//          GLubyte* bits      : テクスチャ格納先ポインタ( 領域確保済み )
// 戻り値 : bool型             : 処理結果
// 説明   : 色ビット数1のビットマップ読み込み関数
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_1( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	return false;	// 処理失敗

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : bool TextuerLoadBMP_BIT_4( FILE* fp , LONG width , LONG height , GLubyte* bits )
// 引数   : FILE* fp           : bmp画像のファイルポインタ( 読み込み済み )
//          LONG width         : 画像幅
//          LONG height        : 画像高さ
//          GLubyte* bits      : テクスチャ格納先ポインタ( 領域確保済み )
// 戻り値 : bool型             : 処理結果
// 説明   : 色ビット数4のビットマップ読み込み関数
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_4( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	return false;	// 処理失敗

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : bool TextuerLoadBMP_BIT_8( FILE* fp , LONG width , LONG height , GLubyte* bits )
// 引数   : FILE* fp           : bmp画像のファイルポインタ( 読み込み済み )
//          LONG width         : 画像幅
//          LONG height        : 画像高さ
//          GLubyte* bits      : テクスチャ格納先ポインタ( 領域確保済み )
// 戻り値 : bool型             : 処理結果
// 説明   : 色ビット数8のビットマップ読み込み関数
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_8( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	//--------------------------------------
	// [ パレットデータの生成・取得処理 ]
	//--------------------------------------
	int nWidthByteNum = ( int )width % 4;							// 横幅のビット数のあまり
	BYTE colIdx;													// 色インデックス格納先ワーク

	RGBQUAD *pColPalette = NULL;									// カラーパレットデータ
	pColPalette = new RGBQUAD[ 256 ];								// パレット数だけ動的確保
	fread( &pColPalette[ 0 ] , sizeof( RGBQUAD ) , 256 , fp );		// カラーパレットデータの読み込み

	//--------------------------------------
	// [ 色データの取得処理 ]
	//--------------------------------------
	for( int y = ( height - 1 ); y >= 0; y-- )									// 逆順から読み込む
	{
		int bitIdxH = ( width * y * 3 );										// 現在読み込んでいるビットの行インデックス( 3はRGB成分のビットを考慮した数 )

		for( int x = 0; x < width; x++ )										// 1行読み込み
		{
			/* ===データ読込処理=== */
			fread( &colIdx , 1 , 1 , fp );										// カラーインデックス読み込み

			/* ===ワークにデータ代入=== */
			int bitIdx = bitIdxH + ( x * 3 );									// 現在読み込んでいるビットのインデックス( 3はRGB成分のビットを考慮した数 )

			bits[ bitIdx + 0 ] = ( GLubyte )pColPalette[ colIdx ].rgbRed;		// R成分代入
			bits[ bitIdx + 1 ] = ( GLubyte )pColPalette[ colIdx ].rgbGreen;		// G成分代入
			bits[ bitIdx + 2 ] = ( GLubyte )pColPalette[ colIdx ].rgbBlue;		// B成分代入
		}

		/* ===1Byteきざみのため、あまりを読み込む=== */
		if( nWidthByteNum != 0 )
		{
			for( int i = 0; ( i + nWidthByteNum ) < 4; i++ )
			{
				fread( &colIdx , 1 , 1 , fp );									// 余りの読み込み
			}
		}
	}

	/* ===終了処理=== */
	delete[] pColPalette;									// カラーパレット解放
	

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : bool TextuerLoadBMP_BIT_24( FILE* fp , LONG width , LONG height , GLubyte* bits )
// 引数   : FILE* fp           : bmp画像のファイルポインタ( 読み込み済み )
//          LONG width         : 画像幅
//          LONG height        : 画像高さ
//          GLubyte* bits      : テクスチャ格納先ポインタ( 領域確保済み )
// 戻り値 : bool型             : 処理結果
// 説明   : 色ビット数24のビットマップ読み込み関数
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_24( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	//--------------------------------------
	// [ 備考 : 左下から右上に読み込む ]
	//--------------------------------------
	GLubyte r , g , b;										// RGBカラー

	for( int y = ( height - 1 ) ; y >= 0 ; y-- )			// 逆順から読み込む
	{
		int bitIdxH = ( width * y * 3 );					// 現在読み込んでいるビットの行インデックス( 3はRGB成分のビットを考慮した数 )

		for( int x = 0 ; x < width ; x++ )					// 1行読み込み
		{
			/* ===データ読込=== */
			fread( &b , 1 , 1 , fp );						// B成分読み込み
			fread( &g , 1 , 1 , fp );						// G成分読み込み
			fread( &r , 1 , 1 , fp );						// R成分読み込み

			/* ===ワークにデータ代入=== */
			int bitIdx = bitIdxH + ( x * 3 );				// 現在読み込んでいるビットのインデックス( 3はRGB成分のビットを考慮した数 )

			bits[ bitIdx + 0 ] = r;							// R成分代入
			bits[ bitIdx + 1 ] = g;							// G成分代入
			bits[ bitIdx + 2 ] = b;							// B成分代入
		}
	}

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : bool TextuerLoadBMP_BIT_32( FILE* fp , LONG width , LONG height , GLubyte* bits )
// 引数   : FILE* fp           : bmp画像のファイルポインタ( 読み込み済み )
//          LONG width         : 画像幅
//          LONG height        : 画像高さ
//          GLubyte* bits      : テクスチャ格納先ポインタ( 領域確保済み )
// 戻り値 : bool型             : 処理結果
// 説明   : 色ビット数32のビットマップ読み込み関数
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_32( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	//--------------------------------------
	// [ 備考 : 左下から右上に読み込む ]
	//--------------------------------------
	GLubyte r , g , b , a;									// RGBAカラー

	for( int y = ( height - 1 ); y >= 0; y-- )				// 逆順から読み込む
	{
		int bitIdxH = ( width * y * 3 );					// 現在読み込んでいるビットの行インデックス( 3はRGB成分のビットを考慮した数 )

		for( int x = 0; x < width; x++ )					// 1行読み込み
		{
			/* ===データ読込=== */
			fread( &b , 1 , 1 , fp );						// B成分読み込み
			fread( &g , 1 , 1 , fp );						// G成分読み込み
			fread( &r , 1 , 1 , fp );						// R成分読み込み
			fread( &a , 1 , 1 , fp );						// 無駄な部分を読み込む処理

			/* ===ワークにデータ代入=== */
			int bitIdx = bitIdxH + ( x * 3 );				// 現在読み込んでいるビットのインデックス( 3はRGB成分のビットを考慮した数 )

			bits[ bitIdx + 0 ] = r;							// R成分代入
			bits[ bitIdx + 1 ] = g;							// G成分代入
			bits[ bitIdx + 2 ] = b;							// B成分代入
		}
	}

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : void ErrorMsg( char* errorMsg , char* path )
// 引数   : char* errorMsg : エラーメッセージ
//          char* path     : 読み込みに失敗したファイルパス
// 戻り値 : void
// 説明   : 読み込み失敗時のエラー文表示用
//==============================================================================
void CTexLoaderBMP::ErrorMsg( char* errorMsg , char* path )
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
