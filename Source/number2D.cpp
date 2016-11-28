//==============================================================================
// タイトル     :   2D用数字表示クラス
// ファイル名   :   number2D.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/19
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/19 数藤凌哉
//           ・制作開始
//           -2016/11/21数藤凌哉
//           ・OpenGL用に処理を一部変更
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "number2D.h"
#include "main.h"
#include "rendererDX.h"

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
const int CNumber2D::m_vtxNum  = 4;			// 必要頂点数
const int CNumber2D::m_primNum = 2;			// 必要プリミティブ数

//==============================================================================
// 関数名 : CNumber2D()
// 引数   : void
// 戻り値 : void
// 説明   : コンストラクタ
//==============================================================================
CNumber2D::CNumber2D()
{
	m_pTexture = NULL;
	m_length   = 0.0f;
	m_angle    = 0.0f;
}

//==============================================================================
// 関数名 : ~CNumber2D()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CNumber2D::~CNumber2D()
{

}

//==============================================================================
// 関数名 : CNumber2D* Create( VECTOR3 pos , VECTOR3 size , CTexture* pTexture )
// 引数   : VECTOR3 pos        : 位置
//          VECTOR3 size       : サイズ
//          CTexture* pTexture : テクスチャへのポインタ
// 戻り値 : bool型 : 処理結果
// 説明   : 生成処理
//==============================================================================
CNumber2D* CNumber2D::Create( VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , CTexture* pTexture )
{
	CNumber2D* newInstance;
	newInstance = new CNumber2D;

	if( newInstance->Init( pos , size , texDivW , texDivH , pTexture ) == false )
	{
		newInstance->Release();
		newInstance = NULL;
	}

	return newInstance;
}

//==============================================================================
// 関数名 : bool Init( VECTOR3 pos , VECTOR3 size , CTexture* pTexture )
// 引数   : VECTOR3 pos             : 位置
//          VECTOR3 size            : サイズ
//          CTexture* pTexture : テクスチャへのポインタ
// 戻り値 : bool型 : 処理結果
// 説明   : 初期化処理
//==============================================================================
bool CNumber2D::Init( VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , CTexture* pTexture )
{
	// 基底の初期化処理を行う
	CNumber::Init( texDivW , texDivH );

	// 座標情報の初期化
	m_pos      = pos;
	m_rot      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size     = size;
	m_pTexture = pTexture;

	VECTOR3 halfSize = VECTOR3( m_size.x * 0.5f , m_size.y * 0.5f , m_size.z * 0.5f );

	m_length = sqrtf( ( halfSize.x * halfSize.x ) + ( halfSize.y * halfSize.y ) );
	m_angle = atan2f( m_size.x , m_size.y );

	return true;	// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CNumber2D::Uninit( void )
{
	// テクスチャは外部から設定するので、ここでは解放しない
	m_pTexture = NULL;
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CNumber2D::Update( void )
{
	
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CNumber2D::Draw( void )
{
	//---------------------------------
	// [ 描画前設定 ]
	//---------------------------------
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_DEPTH_TEST );													// ZバッファーOFF

	if( m_pTexture != NULL )
	{
		m_pTexture->Set();		// テクスチャ設定
	}

	//---------------------------------
	// [ カメラ設定処理 ]
	//---------------------------------
	CCameraGL* pCamera = ( CCameraGL* )GetManager()->GetCamera();	// カメラ取得
	pCamera->Set2D();												// 2Dカメラ設定

	//---------------------------------
	// [ ポリゴン描画処理 ]
	//---------------------------------
	float halfX = m_size.x * 0.5f;
	float halfY = m_size.y * 0.5f;

	glBegin( GL_TRIANGLE_STRIP );
	{
		glTexCoord2f( m_tex.x , m_tex.y );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glVertex3f( m_pos.x - sinf( m_angle + m_rot.z ) * m_length , m_pos.y - cosf( m_angle + m_rot.z ) * m_length , 0.0f );

		glTexCoord2f( m_tex.x + m_texLen.x , m_tex.y );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glVertex3f( m_pos.x + sinf( m_angle - m_rot.z ) * m_length , m_pos.y - cosf( m_angle - m_rot.z ) * m_length , 0.0f );

		glTexCoord2f( m_tex.x , m_tex.y - m_texLen.y );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glVertex3f( m_pos.x - sinf( m_angle - m_rot.z ) * m_length , m_pos.y + cosf( m_angle - m_rot.z ) * m_length , 0.0f );

		glTexCoord2f( m_tex.x + m_texLen.x , m_tex.y - m_texLen.y );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glVertex3f( m_pos.x + sinf( m_angle + m_rot.z ) * m_length , m_pos.y + cosf( m_angle + m_rot.z ) * m_length , 0.0f );
	}
	glEnd();

	//---------------------------------
	// [ 描画後処理 ]
	//---------------------------------
	glBlendFunc( GL_ONE , GL_ZERO );
	glDisable( GL_BLEND );

	glEnable( GL_DEPTH_TEST );													// ZバッファーON

	pCamera->End2D();															// 2Dカメラ終了設定
}

//==============================================================================
// 関数名 : void SetSize( VECTOR3 size )
// 引数   : void
// 戻り値 : void
// 説明   : サイズ設定処理
//==============================================================================
void CNumber2D::SetSize( VECTOR3 size )
{
	m_size = size;

	// 対角線関連の算出
	VECTOR3 halfSize = VECTOR3( m_size.x * 0.5f , m_size.y * 0.5f , m_size.z * 0.5f );

	m_length = sqrtf( ( halfSize.x * halfSize.x ) + ( halfSize.y * halfSize.y ) );
	m_angle = atan2f( m_size.x , m_size.y );

}



