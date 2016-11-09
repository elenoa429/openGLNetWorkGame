//==============================================================================
// タイトル     :   OBJファイルからのモデル読み込み処理用クラス
// ファイル名   :   ModelLoaderOBJ.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/11
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/11 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// インクルードファイル
//==============================================================================
#include "ModelLoaderOBJ.h"
#include <stdio.h>
#include "modelGL.h"

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
// 関数名 : bool ModelLoadOBJ( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
// 引数   : char* pFileName               : ファイル名
//          CMaterialBuffer** ppMaterials : マテリアル用バッファーへのダブルポインタ
//          DWORD* pNumMaterials          : マテリアル数格納先ポインタ
//          CModel** ppModelMesh          : モデルデータへのダブルポインタ
// 戻り値 : bool型 : 処理結果
// 説明   : データ読み込み処理
//==============================================================================
bool CModelLoaderOBJ::ModelLoadOBJ( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
{
	// ファイルオープン
	FILE* fp = fopen( pFileName , "rt" );

	if( fp == NULL )
	{
		return false;	// ファイルオープン失敗により処理失敗
	}

	//-------------------------------------------------
	// [ データワークの生成処理 ]
	//-------------------------------------------------
	// データテーブルの生成
	CModelGL::SUBSET* pSubsetTable = NULL;			// データテーブルの先頭ポインタ
	DWORD numGroup = 0;								// グループ数

	while( 1 )
	{
		// トークン取得
		char token[ 256 ] = { 0 };

		fscanf( fp , "%s" , token );

		// ファイルの終端まで到達により処理終了
		if( feof( fp ) != 0 )
		{
			break;
		}

		// トークン解析
		if( strcmp( token , "g" ) == 0 )
		{
			numGroup++;
		}
	}

	pSubsetTable = new CModelGL::SUBSET[ numGroup ];			// データテーブル生成

	// ワーク内初期化
	for( DWORD i = 0 ; i < numGroup ; i++ )
	{
		pSubsetTable[ i ].pPosBuff   = NULL;
		pSubsetTable[ i ].pTexBuff   = NULL;
		pSubsetTable[ i ].pNorBuff   = NULL;
		pSubsetTable[ i ].posDataNum = 0;
		pSubsetTable[ i ].texDataNum = 0;
		pSubsetTable[ i ].norDataNum = 0;

		pSubsetTable[ i ].pPosIdxBuff = NULL;
		pSubsetTable[ i ].pTexIdxBuff = NULL;
		pSubsetTable[ i ].pNorIdxBuff = NULL;
		pSubsetTable[ i ].idxNum      = 0;
	}

	fseek( fp , 0 , SEEK_SET );									// ファイル位置を先頭にセット

	// 最初のグループ先頭へ飛ぶ
	while( 1 )
	{
		// トークン取得
		char token[ 256 ] = { 0 };

		fscanf( fp , "%s" , token );

		// ファイルの終端まで到達により処理終了
		if( feof( fp ) != 0 )
		{
			break;
		}

		// トークン解析
		if( strcmp( token , "g" ) == 0 )
		{
			break;
		}
	}

	// ワーク生成
	for( UINT groupCnt = 0 ; groupCnt < numGroup ; groupCnt++ )
	{
		// 各要素数の確認
		DWORD numPos = 0;						// 頂点座標数
		DWORD numTex = 0;						// テクスチャ座標数
		DWORD numNor = 0;						// 法線数
		DWORD numFace = 0;						// 面数
		char token[ 256 ] = { 0 };				// トークン用ワーク
		DWORD groupIdxNum = 0;					// グループ内の頂点インデックス数

		while( 1 )
		{
			// トークン取得
			fscanf( fp , "%s" , token );

			// トークン解析
			if( feof( fp ) != 0 || strcmp( token , "g" ) == 0 )
			{
				break;		// ファイルの終端まで到達or次のグループの先頭に到達により処理終了
			}

			if( strcmp( token , "v" ) == 0 )
			{
				numPos++;
			}
			else if( strcmp( token , "vt" ) == 0 )
			{
				numTex++;
			}
			else if( strcmp( token , "vn" ) == 0 )
			{
				numNor++;
			}
			else if( strcmp( token , "f" ) == 0 )
			{
				numFace++;
				groupIdxNum++;
			}
		}

		// データワーク確保
		pSubsetTable[ groupCnt ].pPosBuff = new VECTOR3[ numPos ];
		pSubsetTable[ groupCnt ].pTexBuff = new VECTOR2[ numTex ];
		pSubsetTable[ groupCnt ].pNorBuff = new VECTOR3[ numNor ];
		pSubsetTable[ groupCnt ].posDataNum = numPos;
		pSubsetTable[ groupCnt ].texDataNum = numTex;
		pSubsetTable[ groupCnt ].norDataNum = numNor;

		DWORD idxNum = numFace * 3;		// 頂点インデックス数

		pSubsetTable[ groupCnt ].pPosIdxBuff = new DWORD[ idxNum ];
		pSubsetTable[ groupCnt ].pTexIdxBuff = new DWORD[ idxNum ];
		pSubsetTable[ groupCnt ].pNorIdxBuff = new DWORD[ idxNum ];
		pSubsetTable[ groupCnt ].idxNum      = idxNum;
	}

	fseek( fp , 0 , SEEK_SET );									// ファイル位置を先頭にセット

	//-------------------------------------------------
	// [ データ格納処理 ]
	//-------------------------------------------------
	// 各要素数の確認
	DWORD idxPos       = 0;			// 頂点座標格納位置
	DWORD idxTex       = 0;			// テクスチャ座標格納位置
	DWORD idxNor       = 0;			// 法線格納位置
	DWORD idxOffsetPos = 0;			// 頂点座標格納位置までのオフセット
	DWORD idxOffsetTex = 0;			// テクスチャ座標格納位置までのオフセット
	DWORD idxOffsetNor = 0;			// 法線格納位置までのオフセット
	DWORD idxIdx       = 0;			// インデックス格納位置
	int idxGroup       = -1;		// 現在参照しているグループのインデックス
	char token[ 256 ]  = { 0 };		// トークン用ワーク

	while( 1 )
	{
		// トークン取得
		fscanf( fp , "%s" , token );

		// トークン解析
		if( feof( fp ) != 0 )
		{
			break;		// ファイルの終端まで到達or次のグループの先頭に到達により処理終了
		}

		if( strcmp( token , "v" ) == 0 )
		{
			fscanf( fp , "%f%f%f" ,
				&pSubsetTable[ idxGroup ].pPosBuff[ idxPos ].x ,
				&pSubsetTable[ idxGroup ].pPosBuff[ idxPos ].y ,
				&pSubsetTable[ idxGroup ].pPosBuff[ idxPos ].z );

			idxPos++;
		}
		else if( strcmp( token , "vt" ) == 0 )
		{
			fscanf( fp , "%f%f" ,
				&pSubsetTable[ idxGroup ].pTexBuff[ idxTex ].x ,
				&pSubsetTable[ idxGroup ].pTexBuff[ idxTex ].y );

			idxTex++;
		}
		else if( strcmp( token , "vn" ) == 0 )
		{
			fscanf( fp , "%f%f%f" ,
				&pSubsetTable[ idxGroup ].pNorBuff[ idxNor ].x ,
				&pSubsetTable[ idxGroup ].pNorBuff[ idxNor ].y ,
				&pSubsetTable[ idxGroup ].pNorBuff[ idxNor ].z );

			idxNor++;
		}
		else if( strcmp( token , "f" ) == 0 )
		{
			for( int i = 0 ; i < 3 ; i++ )
			{
				fscanf( fp , "%d/%d/%d" ,
					&pSubsetTable[ idxGroup ].pPosIdxBuff[ idxIdx ] ,
					&pSubsetTable[ idxGroup ].pTexIdxBuff[ idxIdx ] ,
					&pSubsetTable[ idxGroup ].pNorIdxBuff[ idxIdx ] );

				pSubsetTable[ idxGroup ].pPosIdxBuff[ idxIdx ] = pSubsetTable[ idxGroup ].pPosIdxBuff[ idxIdx ] - ( idxOffsetPos + 1 );
				pSubsetTable[ idxGroup ].pTexIdxBuff[ idxIdx ] = pSubsetTable[ idxGroup ].pTexIdxBuff[ idxIdx ] - ( idxOffsetTex + 1 );
				pSubsetTable[ idxGroup ].pNorIdxBuff[ idxIdx ] = pSubsetTable[ idxGroup ].pNorIdxBuff[ idxIdx ] - ( idxOffsetNor + 1 );

				idxIdx++;
			}
		}
		else if( strcmp( token , "g" ) == 0 )
		{
			idxGroup++;
			idxOffsetPos += idxPos;
			idxOffsetTex += idxTex;
			idxOffsetNor += idxNor;
			idxPos = 0;
			idxTex = 0;
			idxNor = 0;
			idxIdx = 0;
		}
	}

	// 格納したデータを引数の各要素に登録
	*pNumMaterials = numGroup;											// 厳密にはグループ数==マテリアル数ではないのだが、一旦これで
	
	*ppModelMesh = new CModelGL;
	LPModelGL modelGL = dynamic_cast< LPModelGL >( *ppModelMesh );
	modelGL->Init( pFileName );
	modelGL->SetSubsets( numGroup , pSubsetTable );

	// 終了処理
	fclose( fp );

	return true;		// 処理成功
}

