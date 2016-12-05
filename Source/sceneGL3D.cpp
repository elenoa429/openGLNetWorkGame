//==============================================================================
// タイトル     :   OpenGL用3D描画用クラス
// ファイル名   :   sceneGL3D.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/04/22
//==============================================================================

//==============================================================================
// 更新履歴: -2016/04/22 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "sceneGL3D.h"
#include "rendererGL.h"

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
// 関数名 : CSceneGL3D()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CSceneGL3D::CSceneGL3D()
{
	m_pos      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size     = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_col      = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );
	m_nor      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_scl      = VECTOR3( 1.0f , 1.0f , 1.0f );
	m_pTexture = NULL;

	MatrixIdentity( &m_mtxWorld );
}

//==============================================================================
// 関数名 : ~CSceneGL3D()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CSceneGL3D::~CSceneGL3D()
{
}

//==============================================================================
// 関数名 : CSceneGL3D* Create( char* texPath )
// 引数   : char* texPath : テクスチャファイルパス
// 戻り値 : CSceneGL3D*型
// 説明   : 生成処理
//==============================================================================
CSceneGL3D* CSceneGL3D::Create( char* texPath )
{
	CSceneGL3D* pNewInstance = new CSceneGL3D;

	if( pNewInstance->Init( texPath ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// 関数名 : bool Init( char* texPath )
// 引数   : char* texPath : テクスチャファイルパス
// 戻り値 : void
// 説明   : 初期化処理( テクスチャファイルパス有り版 )
//==============================================================================
bool CSceneGL3D::Init( char* texPath )
{
	//---------------------------------
	// [ 値初期化 ]
	//---------------------------------
	m_pos  = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot  = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_scl  = VECTOR3( 1.0f , 1.0f , 1.0f );
	m_nor  = VECTOR3( 0.0f , 1.0f , 0.0f );
	m_size = VECTOR3( 10000.0f , 0.0f , 10000.0f );
	m_col  = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );

	//---------------------------------
	// [ テクスチャ読み込み処理 ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();				// レンダラーの取得
	
	if( pRenderer != NULL )
	{
		pRenderer->CreateTexture( texPath , &m_pTexture );				// テクスチャ生成
	}

	return true;		// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CSceneGL3D::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CSceneGL3D::Update( void )
{
	/*m_rot.y += PI * 0.01f;

	if( m_rot.y > PI )
	{
		m_rot.y -= PI2;
	}*/

	//m_pos.x += 1.0f;
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CSceneGL3D::Draw( void )
{
	//---------------------------------
	// [ 描画前処理 ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	//---------------------------------
	// [ ワールドマトリクス算出 ]
	//---------------------------------
	MATRIX mtxScl , mtxRot , mtxTrans;

	MatrixIdentity( &m_mtxWorld );

	MatrixScaling( &mtxScl , m_scl.x , m_scl.y , m_scl.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxScl );

	MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxRot );

	MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxTrans );

	glMultMatrixf( m_mtxWorld.m );

	//---------------------------------
	// [ 描画処理 ]
	//---------------------------------
	if( m_pTexture != NULL )
	{
		m_pTexture->Set();						// テクスチャ設定
	}

	glBegin( GL_TRIANGLE_STRIP );
	{
		glTexCoord2f( 0.0f , 0.0f );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glNormal3f( m_nor.x , m_nor.y , m_nor.z );
		glVertex3f( -m_size.x , 0.0f , -m_size.z );

		glTexCoord2f( 1.0f , 0.0f );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glNormal3f( m_nor.x , m_nor.y , m_nor.z );
		glVertex3f( m_size.x , 0.0f , -m_size.z );

		glTexCoord2f( 0.0f , 1.0f );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glNormal3f( m_nor.x , m_nor.y , m_nor.z );
		glVertex3f( -m_size.x , 0.0f , m_size.z );

		glTexCoord2f( 1.0f , 1.0f );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glNormal3f( m_nor.x , m_nor.y , m_nor.z );
		glVertex3f( m_size.x , 0.0f , m_size.z );
	}
	glEnd();

	//---------------------------------
	// [ 描画後処理 ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glDisable( GL_BLEND );
	glBlendFunc( GL_ONE , GL_ZERO );

}
