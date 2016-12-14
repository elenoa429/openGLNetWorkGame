//==============================================================================
// タイトル     :   スカイボックスクラス
// ファイル名   :   skyBox.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/16
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/16 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "skyBox.h"
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
// 関数名 : CSkyBox()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CSkyBox::CSkyBox()
{
}

//==============================================================================
// 関数名 : ~CSkyBox()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CSkyBox::~CSkyBox()
{
}

//==============================================================================
// 関数名 : CSkyBox* Create( char* texPath )
// 引数   : char* texPath : テクスチャファイルパス
// 戻り値 : CSkyBox*型
// 説明   : 生成処理
//==============================================================================
CSkyBox* CSkyBox::Create( char* texPath )
{
	CSkyBox* pNewInstance = new CSkyBox;

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
bool CSkyBox::Init( char* texPath )
{
	CSceneGL3D::Init( texPath );

	m_size = VECTOR3( 50000.0f , 50000.0f , 50000.0f );
	m_DivTexU = 4;
	m_DivTexV = 3;
	m_texUnitSize.x = 1.0f / ( float )m_DivTexU;
	m_texUnitSize.y = 1.0f / ( float )m_DivTexV;

	return true;		// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CSkyBox::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	CSceneGL3D::Uninit();
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CSkyBox::Update( void )
{
	CCameraGL* pCamera = GetManager()->GetCamera();

	m_pos = pCamera->GetPosV();

	//m_rot.y += 0.001f;

	if( m_rot.y > PI )
	{
		m_rot.y -= PI2;
	}
	else if( m_rot.y < -PI )
	{
		m_rot.y += PI2;
	}
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CSkyBox::Draw( void )
{
	//---------------------------------
	// [ 描画前処理 ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_FRONT );

	glDisable( GL_LIGHTING );

	//const GLfloat borderCol[] = { 0.0f , 0.0f , 0.0f , 0.0f };
	//glTexParameterfv( GL_TEXTURE_2D , GL_TEXTURE_BORDER_COLOR , borderCol );
	//glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP );
	//glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP );

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

	//---------------------------------------------------------------------
	// [ 描画処理 ]
	//
	//              [5]
	//   [1][2][3][4]     <= [0]番のポリゴンの左下から描画
	// [0]                <= 左図の順番でN字に描画
	//
	//    [5]
	// [1][2][3][4]       <= 左図のような展開されたテクスチャを利用するため、
	//    [0]                手打ちで座標を代入
	//---------------------------------------------------------------------
	if( m_pTexture != NULL )
	{
		m_pTexture->Set();						// テクスチャ設定
	}

	float sizeHalfX = m_size.x * 0.5f;			// X軸のサイズの半分
	float sizeHalfY = m_size.y * 0.5f;			// Y軸のサイズの半分
	float sizeHalfZ = m_size.z * 0.5f;			// Z軸のサイズの半分

	glBegin( GL_TRIANGLE_STRIP );
	{
		/* ==0== */
		{
			glTexCoord2f(texUPos(2), texVPos(0));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(0));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, -sizeHalfZ);

		}

		/* ==1== */
		{
			glTexCoord2f(texUPos(3), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(4), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(4), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, +sizeHalfZ);
		}

		/* ==2== */
		{
			glTexCoord2f(texUPos(0), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(0), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(1), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(1), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, +sizeHalfZ);
		}

		/* ==3== */
		{
			glTexCoord2f(texUPos(1), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(1), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, -sizeHalfZ);
		}

		/* ==4== */
		{
			glTexCoord2f(texUPos(2), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, -sizeHalfZ);
		}

		/* ==5== */
		{
			glTexCoord2f(texUPos(2), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(3));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(3));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, +sizeHalfZ);
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

	glDisable( GL_CULL_FACE );

	glEnable( GL_LIGHTING );

	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT );

}

//==============================================================================
// 関数名 : float CSkyBox::texUPos( int uPos )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
float CSkyBox::texUPos( int uPos )
{
	float fPosU = m_texUnitSize.x * uPos;

	if( fPosU <= 0.0f )
	{
		fPosU = 0.001f;
	}
	else if( fPosU >= 1.0f )
	{
		fPosU = 0.999f;
	}

	return fPosU;
}

//==============================================================================
// 関数名 : float CSkyBox::texVPos( int vPos )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
float CSkyBox::texVPos( int vPos )
{
	float fPosV = m_texUnitSize.y * vPos;

	if( fPosV <= 0.0f )
	{
		fPosV = 0.001f;
	}
	else if( fPosV >= 1.0f )
	{
		fPosV = 0.999f;
	}

	return fPosV;
}
