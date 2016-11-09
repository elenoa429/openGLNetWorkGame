//==============================================================================
// タイトル     :   グリッド線描画クラス
// ファイル名   :   grid3D.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/07/08
//==============================================================================

//==============================================================================
// 更新履歴: -2016/07/08 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "grid3D.h"
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
// 関数名 : CGrid3D()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CGrid3D::CGrid3D()
{
	m_numW    = 0;
	m_numH    = 0;
	m_marginW = 0.0f;
	m_marginH = 0.0f;
}

//==============================================================================
// 関数名 : ~CGrid3D()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CGrid3D::~CGrid3D()
{
}

//==============================================================================
// 関数名 : CGrid3D* Create( int w , int h , float mW , float mH )
// 引数   : char* texPath : テクスチャファイルパス
// 戻り値 : CGrid3D*型
// 説明   : 生成処理
//==============================================================================
CGrid3D* CGrid3D::Create( int w , int h , float mW , float mH )
{
	CGrid3D* pNewInstance = new CGrid3D;

	if( pNewInstance->Init( w , h , mW , mH ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// 関数名 : bool Init( int w , int h , float mW , float mH )
// 引数   : int w    : 横個数
//          int h    : 縦個数
//          float mW : 横間隔
//          float mH : 縦間隔
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CGrid3D::Init( int w , int h , float mW , float mH )
{
	//---------------------------------
	// [ 値初期化 ]
	//---------------------------------
	m_numW    = w;
	m_numH    = h;
	m_marginW = mW;
	m_marginH = mH;
	m_col     = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );
	m_scl     = VECTOR3( 1.0f , 1.0f , 1.0f );

	return true;		// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CGrid3D::Uninit( void )
{

}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CGrid3D::Update( void )
{

}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CGrid3D::Draw( void )
{
	//---------------------------------
	// [ 描画前処理 ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glDisable( GL_BLEND );
	glBlendFunc( GL_ONE , GL_ZERO );

	glDisable( GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );

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
	VECTOR3 lineFrom;
	VECTOR3 lineTo;

	float lenW = m_marginW * m_numW;
	float lenH = m_marginH * m_numH;

	glBegin( GL_LINES );
	{
		// 行描画
		lineFrom = VECTOR3( lenW * -0.5f , 0.0f , lenH * -0.5f );
		lineTo   = VECTOR3( lenW * 0.5f , 0.0f , lenH * -0.5f );

		for( int h = 0 ; h < m_numH + 1 ; h++ )
		{
			// From
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glVertex3f( lineFrom.x , lineFrom.y , lineFrom.z );

			// To
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glVertex3f( lineTo.x , lineTo.y , lineTo.z );

			lineFrom.z += m_marginH;
			lineTo.z   += m_marginH;
		}

		// 列描画
		lineFrom = VECTOR3( lenW * -0.5f , 0.0f , lenH * -0.5f );
		lineTo   = VECTOR3( lenW * -0.5f , 0.0f , lenH * 0.5f );

		for( int w = 0 ; w < m_numW + 1 ; w++ )
		{
			// From
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glVertex3f( lineFrom.x , lineFrom.y , lineFrom.z );

			// To
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glVertex3f( lineTo.x , lineTo.y , lineTo.z );

			lineFrom.x += m_marginW;
			lineTo.x   += m_marginW;
		}
		
	}
	glEnd();

	//---------------------------------
	// [ 描画後処理 ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glDisable( GL_BLEND );
	glBlendFunc( GL_ONE , GL_ZERO );

	glEnable( GL_LIGHTING );
	glEnable( GL_TEXTURE_2D );

}
