//==============================================================================
// タイトル     :   OpenGL用モーションクラス
// ファイル名   :   motionGL.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/09/16
//==============================================================================

//==============================================================================
// 更新履歴: -2016/09/16 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// WARNING防止
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// インクルードファイル
//==============================================================================
#include "motionGL.h"
#include <stdio.h>
#include <string.h>

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
// 関数名 : CMotionGL()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CMotionGL::CMotionGL()
{
	m_motionInfo.motionNum   = 0;
	m_motionInfo.pMotionData = NULL;
	m_motionIdx              = 0;
	m_flameCnt               = 0;;
}

//==============================================================================
// 関数名 : ~CMotionGL()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CMotionGL::~CMotionGL()
{

}

//==============================================================================
// 関数名 : CMotionGL* Create( const char* pMotionFileName )
// 引数   : const char* pMotionFileName : 読み込みモーションファイル名
// 戻り値 : CMotionGL*型                : 生成したインスタンス
// 説明   : 生成処理
//==============================================================================
CMotionGL* CMotionGL::Create( const char* pMotionFileName )
{
	CMotionGL* pNewInstance = new CMotionGL;

	if( pNewInstance->Init( pMotionFileName ) == false )
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
void CMotionGL::Release( void )
{
	Uninit();
	delete this;
}

//==============================================================================
// 関数名 : bool Init( const char* pMotionFileName )
// 引数   : const char* pMotionFileName : 読み込みモーションファイル名
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CMotionGL::Init( const char* pMotionFileName )
{
	// 仮の処理
	m_motionInfo.pMotionData = new MOTION;
	m_motionInfo.motionNum   = 1;

	// モーション読み込み処理
	if( LoadMotion( pMotionFileName , 0 ) == false )
	{
		return false;
	}

	return true;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CMotionGL::Uninit( void )
{
	if( m_motionInfo.pMotionData != NULL )
	{
		for( int i = 0 ; i < m_motionInfo.motionNum ; i++ )
		{
			delete[] m_motionInfo.pMotionData[ i ].pKeyInfoData;
			m_motionInfo.pMotionData[ i ].pKeyInfoData = NULL;
		}

		delete[] m_motionInfo.pMotionData;
		m_motionInfo.pMotionData = NULL;
	}
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CMotionGL::Update( void )
{
	m_flameCnt++;

	if( m_flameCnt >= m_motionInfo.pMotionData[ m_motionIdx ].keyNum )
	{
		m_flameCnt = 0;
	}
}

//==============================================================================
// 関数名 : bool SetMotionData( CParentModelManagerGL* pSetModel )
// 引数   : CParentModelManagerGL* pSetModel : 設定対象のモデルデータ
// 戻り値 : bool型
// 説明   : モーション設定処理
//==============================================================================
bool CMotionGL::SetMotionData( CParentModelManagerGL* pSetModel )
{
	int modelNum = pSetModel->GetModelListSize();

	for( int i = 0 ; i < modelNum ; i++ )
	{
		CParentModelGL* pModel = pSetModel->GetModelData( i );

		float posX = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].posX;
		float posY = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].posY;
		float posZ = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].posZ;
		float rotX = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].rotX;
		float rotY = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].rotY;
		float rotZ = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].rotZ;

		pModel->SetPos( VECTOR3( posX , posY , posZ ) );
		pModel->SetRotDegree( VECTOR3( rotX , rotY , rotZ ) );
	}

	return true;
}

//==============================================================================
// 関数名 : bool LoadMotion( const char* pMotionFileName )
// 引数   : const char* pMotionFileName : モーションファイル名
//          int motionIdx               : 設定先インデックス
// 戻り値 : bool型
// 説明   : モーション読み込み処理
//==============================================================================
bool CMotionGL::LoadMotion( const char* pMotionFileName , int motionIdx )
{
	// anmファイルオープン
	FILE* fp;
	
	fopen_s( &fp , pMotionFileName , "rt" );

	if( fp == NULL )
	{
		return false;
	}

	// 要素数取得
	int flameNum = 0;

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
		if( strcmp( token , "fr" ) == 0 )
		{
			flameNum++;
		}
	}

	// ワーク確保
	m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData = new KEY_INFO[ flameNum ];
	m_motionInfo.pMotionData[ motionIdx ].joinyNum = 3;
	m_motionInfo.pMotionData[ motionIdx ].keyNum   = flameNum;

	// データ読み込み
	int flameIdx = -1;
	int jointIdx = 0;
	
	fseek( fp , 0 , SEEK_SET );					// ファイル位置を先頭にセット

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
		if( strcmp( token , "fr" ) == 0 )
		{
			flameIdx++;
			jointIdx = 0;

			fscanf( fp , "%d" , &m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].flame );
		}
		else if( strcmp( token , "ky" ) == 0 )
		{
			fscanf( fp , "%f %f %f %f %f %f" ,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].posX,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].posY,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].posZ,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].rotX,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].rotY,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].rotZ );

			jointIdx++;
		}
	}

	// ファイルクローズ
	fclose( fp );

	return true;
}
