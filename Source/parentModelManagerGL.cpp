//==============================================================================
// タイトル     :   親子関係付きモデル用マネージャ( OpenGL用 )
// ファイル名   :   parentModelManagerGL.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/09/09
//==============================================================================

//==============================================================================
// 更新履歴: -2016/09/09 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "parentModelManagerGL.h"
#include "main.h"
#include "loader.h"

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
// 関数名 : CParentModelManagerGL()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CParentModelManagerGL::CParentModelManagerGL()
{

}

//==============================================================================
// 関数名 : ~CParentModelManagerGL()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CParentModelManagerGL::~CParentModelManagerGL()
{

}

//==============================================================================
// 関数名 : CParentModelManagerGL* Create( void )
// 引数   : void
// 戻り値 : CParentModelManagerGL*型
// 説明   : 生成処理
//==============================================================================
CParentModelManagerGL* CParentModelManagerGL::Create( void )
{
	CParentModelManagerGL* pNewInstance = new CParentModelManagerGL;

	if( pNewInstance->Init() == false )
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
void CParentModelManagerGL::Release( void )
{
	this->Uninit();
	delete this;
}

//==============================================================================
// 関数名 : bool Init( void )
// 引数   : void
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CParentModelManagerGL::Init( void )
{
	CModel* pModel;
	DWORD numMat;

	//---------------------------------
	// [ モデル読み込み処理 ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();										// レンダラーの取得

	pRenderer->CreateModel( "data\\MODEL\\miku_01.obj" , NULL , &numMat , &pModel );		// モデル生成

	//---------------------------------
	// [ 親子関係設定処理 ]
	//---------------------------------
	CModelGL* pModelGL = dynamic_cast< CModelGL* >( pModel );

	CParentModelGL* pModelWork[ 3 ] = { NULL };

	pModelWork[ 0 ] = CParentModelGL::Create( pModelGL , 0 );
	PushModelData( pModelWork[ 0 ] );

	pModelWork[ 1 ] = CParentModelGL::Create( pModelGL , 1 );
	PushModelData( pModelWork[ 1 ] );

	pModelWork[ 2 ] = CParentModelGL::Create( pModelGL , 2 );
	PushModelData( pModelWork[ 2 ] );

	pModelWork[ 0 ]->SetParent( pModelWork[ 2 ] );
	pModelWork[ 1 ]->SetParent( pModelWork[ 2 ] );

	//---------------------------------------------
	// [ マテリアル読み込み処理( 仮で埋め込み ) ]
	//---------------------------------------------
	CLoader* pLoader = new CLoader;

	pLoader->MaterialLoad( "data\\MODEL\\miku_01.mtl" , &m_pMat );

	delete pLoader;
	pLoader = NULL;

	//---------------------------------
	// [ テクスチャ読み込み処理 ]
	//---------------------------------
	pRenderer->CreateTexture( "data\\MODEL\\miku_01.bmp" , &m_pTexture );	// テクスチャ生成

	return true;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CParentModelManagerGL::Uninit( void )
{
	// モデルデータ解放
	std::vector< CParentModelGL* >::iterator itr;	// モデルリストのイテレータ

	for( itr = m_modelList.begin() ; itr != m_modelList.end() ; itr++ )
	{
		CParentModelGL* pModel = *itr;
		pModel->Release();
		pModel = NULL;
	}

	m_modelList.clear();	// リスト内削除
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CParentModelManagerGL::Update( void )
{
	std::vector< CParentModelGL* >::iterator itr;	// モデルリストのイテレータ

	for( itr = m_modelList.begin() ; itr != m_modelList.end() ; itr++ )
	{
		CParentModelGL* pModel = *itr;
		pModel->Update();
	}
}

//==============================================================================
// 関数名 : void Draw( D3DXMATRIX* pMtxParent )
// 引数   : MATRIX* pMtxParent : 基準親マトリクス( ローカル座標( 0 ; 0 ; 0 ) )にあたる
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CParentModelManagerGL::Draw( MATRIX* pMtxParent )
{
	std::vector< CParentModelGL* >::iterator itr;	// モデルリストのイテレータ

	if( m_pTexture != NULL )
	{
		m_pTexture->Set();						// テクスチャ設定
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D , 0 );
		glDisable( GL_TEXTURE_2D );
	}

	if( m_pMat != NULL )
	{
		m_pMat->Set();							// マテリアル設定
	}

	for( itr = m_modelList.begin() ; itr != m_modelList.end() ; itr++ )
	{
		CParentModelGL* pModel = *itr;
		pModel->Draw( pMtxParent );
	}

	if( m_pMat != NULL )
	{
		CMaterialGL pDefMat;

		pDefMat.Set();							// 初期マテリアル設定
	}
}

//==============================================================================
// 関数名 : bool PushModelData( CParentModelGL* pModelData )
// 引数   : void
// 戻り値 : void
// 説明   : モデル登録処理
//==============================================================================
bool CParentModelManagerGL::PushModelData( CParentModelGL* pModelData )
{
	// エラーチェック
	if( pModelData == NULL )
	{
		return false;
	}

	// データ登録
	m_modelList.push_back( pModelData );

	return true;
}

//==============================================================================
// 関数名 : bool RemoveModelData( int idx )
// 引数   : int idx : 削除するモデルのインデックス( -1で最後尾 )
// 戻り値 : bool型
// 説明   : 対応したモデルを削除する処理
//==============================================================================
bool CParentModelManagerGL::RemoveModelData( int idx )
{
	// エラーチェック
	int size = m_modelList.size();

	if( idx > size || idx < -1 )
	{
		return false;
	}

	// モデル削除
	if( idx == -1 )
	{
		m_modelList.pop_back();
	}
	else
	{
		m_modelList.erase( m_modelList.begin() + idx );
	}

	return true;
}

//==============================================================================
// 関数名 : CParentModelGL* GetModelData( int idx )
// 引数   : int idx : 取得対象インデックス
// 戻り値 : CParentModelGL*型
// 説明   : 指定した位置のモデルデータ取得処理
//==============================================================================
CParentModelGL* CParentModelManagerGL::GetModelData( int idx )
{
	// エラーチェック
	int size = m_modelList.size();

	if( idx >= size || idx < 0 )
	{
		return NULL;
	}

	// 指定した要素の返却
	std::vector< CParentModelGL* >::iterator itr = m_modelList.begin();

	return *( itr + idx );
}

//==============================================================================
// 関数名 : int GetModelListSize( void )
// 引数   : void
// 戻り値 : int型
// 説明   : モデルリストのサイズ取得処理
//==============================================================================
int CParentModelManagerGL::GetModelListSize( void )
{
	return m_modelList.size();
}
