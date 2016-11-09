//==============================================================================
// タイトル     :   OpenGL用親子関係付きモデル処理
// ファイル名   :   parentModelGL.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/09/05
//==============================================================================

//==============================================================================
// 更新履歴: -2016/09/05 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "parentModelGL.h"
#include "rendererGL.h"

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
// 関数名 : CParentModelGL()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CParentModelGL::CParentModelGL()
{
	m_pModel    = NULL;
	m_subsetIdx = 0;
	m_pParent   = NULL;
	m_pos       = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot       = VECTOR3( 0.0f , 0.0f , 0.0f );

	MatrixIdentity( &m_mtxLocal );
}

//==============================================================================
// 関数名 : ~CParentModelGL()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CParentModelGL::~CParentModelGL()
{

}

//==============================================================================
// 関数名 : CParentModelGL* Create( CModelGL* pModel , DWORD subsetIdx )
// 引数   : CModelGL* pModel : 描画するモデルへのポインタ
//          WORD subsetIdx   : 描画するサブセットのインデックス
// 戻り値 : void
// 説明   : 生成処理
//==============================================================================
CParentModelGL* CParentModelGL::Create( CModelGL* pModel , DWORD subsetIdx )
{
	CParentModelGL* pNewInstance = new CParentModelGL;

	if( pNewInstance->Init( pModel , subsetIdx ) == false )
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
void CParentModelGL::Release( void )
{
	Uninit();
	delete this;
}

//==============================================================================
// 関数名 : bool Init( CModelGL* pModel , DWORD subsetIdx )
// 引数   : CModelGL* pModel : 描画するモデルへのポインタ
//          WORD subsetIdx   : 描画するサブセットのインデックス
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CParentModelGL::Init( CModelGL* pModel , DWORD subsetIdx )
{
	//---------------------------------------------
	// [ モデルデータの設定 ]
	//---------------------------------------------
	m_pModel    = pModel;
	m_subsetIdx = subsetIdx;

	return true;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CParentModelGL::Uninit( void )
{
	// モデルデータの解放
	if( m_pModel != NULL )
	{
		m_pModel = NULL;
	}

	m_pParent = NULL;
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CParentModelGL::Update( void )
{
	//-------------------------------------
	// [ ローカルマトリクス生成 ]
	//-------------------------------------
	MATRIX mtxRot , mtxTrans;

	MatrixIdentity( &m_mtxLocal );

	MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );
	MatrixMultiply( &m_mtxLocal , &m_mtxLocal , &mtxRot );

	MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );
	MatrixMultiply( &m_mtxLocal , &m_mtxLocal , &mtxTrans );

}

//==============================================================================
// 関数名 : void Draw( MATRIX* pParentMatrix )
// 引数   : MATRIX* pParentMatrix : 親マトリクス( ローカル基準座標( 0 ; 0 ; 0 ) )にあたる
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CParentModelGL::Draw( MATRIX* pParentMatrix )
{
	//---------------------------------------------
	// [ ワールドマトリクス生成 ]
	//---------------------------------------------
	MATRIX mtxWorld;

	//MatrixIdentity( &mtxWorld );									// 単位マトリクス化
	//MatrixMultiply( &mtxWorld , &mtxWorld , &GetMtxParent() );		// ローカルマトリクスを含めた親マトリクスを合成
	//MatrixMultiply( &mtxWorld , &mtxWorld , pParentMatrix );		// 基準マトリクスを合成

	//glMatrixMode( GL_MODELVIEW );
	//glPushMatrix();
	//glMultMatrixf( mtxWorld.m );

	glPushMatrix();

	glTranslatef( m_pos.x , m_pos.y , m_pos.z );

	glRotatef( RadToDeg( m_rot.z ) , 0.0f , 0.0f , 1.0f );
	glRotatef( RadToDeg( m_rot.y ) , 0.0f , 1.0f , 0.0f );
	glRotatef( RadToDeg( m_rot.x ) , 1.0f , 0.0f , 0.0f );
	

	//---------------------------------------------
	// [ 描画処理 ]
	//---------------------------------------------
	m_pModel->SetMaterial( m_subsetIdx );
	m_pModel->SetMatTexture( m_subsetIdx );
	m_pModel->DrawSubset( m_subsetIdx );

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}

//==============================================================================
// 関数名 : bool SetSubsetIdx( DWORD idx )
// 引数   : DWORD idx : 描画対象サブセットインデックス
// 戻り値 : bool型
// 説明   : サブセットインデックス設定処理
//==============================================================================
bool CParentModelGL::SetSubsetIdx( DWORD idx )
{
	DWORD subsetNum = m_pModel->GetSubsetNum();

	if( idx >= subsetNum )
	{
		return false;
	}

	m_subsetIdx = idx;

	return true;
}

//==============================================================================
// 関数名 : void SetParent( CParentModelGL* pParent )
// 引数   : CParentModelGL* pParent : 親モデルへのポインタ
// 戻り値 : bool型
// 説明   : 親モデル設定処理
//==============================================================================
void CParentModelGL::SetParent( CParentModelGL* pParent )
{
	m_pParent = pParent;
}

//==============================================================================
// 関数名 : MATRIX GetMtxParent( void );
// 引数   : void
// 戻り値 : MATRIX型
// 説明   : 親マトリクス取得処理
//==============================================================================
MATRIX CParentModelGL::GetMtxParent( void )
{
	MATRIX mtxParent;
	MatrixIdentity( &mtxParent );

	// 再帰的に親マトリクスを取得
	if( m_pParent != NULL )
	{
		MatrixMultiply( &mtxParent , &m_mtxLocal , &m_pParent->GetMtxParent() );
	}
	else
	{
		mtxParent = m_mtxLocal;
	}

	return mtxParent;
}

//==============================================================================
// 関数名 : void SetRotDegree( VECTOR3 rot )
// 引数   : VECTOR3 rot : 角度( Degree値 )
// 戻り値 : void
// 説明   : 角度設定処理( Degree -> Radian )
//==============================================================================
void CParentModelGL::SetRotDegree( VECTOR3 rot )
{
	VECTOR3 rotRad;

	rotRad.x = DegToRad( rot.x );
	rotRad.y = DegToRad( rot.y );
	rotRad.z = DegToRad( rot.z );

	m_rot = rotRad;
}
