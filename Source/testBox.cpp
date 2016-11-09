//==============================================================================
// タイトル     :   テスト用クラス
// ファイル名   :   testBox.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/08
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/08 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "testbox.h"
#include "rendererGL.h"

//==============================================================================
// 列挙型宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================
#define MOVE_SPEED		( 3.0f )			// 移動係数
#define ROTATION_SPEED	( PI * 0.01f )		// 回転角変化係数

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
// 関数名 : CTestBox()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CTestBox::CTestBox()
{
	m_pTexture = NULL;

	m_bMove       = false;
	m_isTexEnable = true;
	m_pVtxBuff    = NULL;
}

//==============================================================================
// 関数名 : ~CTestBox()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CTestBox::~CTestBox()
{
}

//==============================================================================
// 関数名 : bool Init( char* texPath )
// 引数   : char* texPath : テクスチャファイルパス
// 戻り値 : void
// 説明   : 初期化処理( テクスチャファイルパス有り版 )
//==============================================================================
bool CTestBox::Init( char* texPath )
{
	CSceneGL3D::Init( texPath );		// 基底クラスの初期化処理呼び出し

	m_size = VECTOR3( 100.0f , 100.0f , 100.0f );
	m_bMove = false;


	CRenderer* pRenderer = GetManager()->GetRenderer();					// レンダラーの取得

	//---------------------------------
	// [ テクスチャ読み込み処理 ]
	//---------------------------------
	pRenderer->CreateTexture( texPath , &m_pTexture );					// テクスチャ生成

	//---------------------------------
	// [ 頂点バッファー生成 ]
	//---------------------------------
	pRenderer->CreateVertexBuffer( sizeof( VERTEX_3D ) * 4 , &m_pVtxBuff );

	//---------------------------------
	// [ 頂点データ初期化 ]
	//---------------------------------
	VERTEX_3D* pVtx;

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );

	// 位置
	pVtx[ 0 ].pos = VECTOR3( -1000.0f , 1000.0f , 1000.0f );
	pVtx[ 1 ].pos = VECTOR3( 1000.0f , 1000.0f , 1000.0f );
	pVtx[ 2 ].pos = VECTOR3( -1000.0f , 1000.0f , -1000.0f );
	pVtx[ 3 ].pos = VECTOR3( 1000.0f , 1000.0f , -1000.0f );

	// 法線
	pVtx[ 0 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	pVtx[ 1 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	pVtx[ 2 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	pVtx[ 3 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );

	// 色
	pVtx[ 0 ].col = 0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0;
	pVtx[ 1 ].col = 0xff << 24 | 0x00 << 16 | 0xff << 8 | 0x00 << 0;
	pVtx[ 2 ].col = 0xff << 24 | 0x00 << 16 | 0x00 << 8 | 0xff << 0;
	pVtx[ 3 ].col = 0xff << 24 | 0x00 << 16 | 0x00 << 8 | 0x00 << 0;

	// テクスチャ
	pVtx[ 0 ].tex = VECTOR2( 0.0f , 0.0f );
	pVtx[ 1 ].tex = VECTOR2( 1.0f , 0.0f );
	pVtx[ 2 ].tex = VECTOR2( 0.0f , 1.0f );
	pVtx[ 3 ].tex = VECTOR2( 1.0f , 1.0f );

	m_pVtxBuff->Unlock();

	return true;		// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CTestBox::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	if( m_pVtxBuff != NULL )
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CTestBox::Update( void )
{
	//------------------------------------------
	// [ 入力情報の取得処理 ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isPressW     = false;
	bool isPressS     = false;
	bool isPressA     = false;
	bool isPressD     = false;
	bool isPressQ     = false;
	bool isPressE     = false;
	bool isPressZ     = false;
	bool isPressC     = false;
	bool isPressT     = false;
	bool isPressB     = false;
	bool isPressY     = false;
	bool isPressN     = false;
	bool isPressEnter = false;

	bool isTrigEnter  = false;
	bool isTrigF8     = false;
	bool isTrigF9     = false;

	bool isRepeat_1 = false;
	bool isRepeat_2 = false;
	bool isRepeat_3 = false;
	bool isRepeat_4 = false;
	bool isRepeat_5 = false;
	bool isRepeat_6 = false;
	bool isRepeat_7 = false;
	bool isRepeat_8 = false;
	bool isRepeat_9 = false;
	bool isRepeat_0 = false;

	if( pInput != NULL )
	{
		if( m_bMove == true )
		{
			isPressW     = pInput->GetPress( DIK_W );
			isPressS     = pInput->GetPress( DIK_S );
			isPressA     = pInput->GetPress( DIK_A );
			isPressD     = pInput->GetPress( DIK_D );
			isPressQ     = pInput->GetPress( DIK_Q );
			isPressE     = pInput->GetPress( DIK_E );
			isPressZ     = pInput->GetPress( DIK_Z );
			isPressC     = pInput->GetPress( DIK_C );
			isPressT     = pInput->GetPress( DIK_T );
			isPressB     = pInput->GetPress( DIK_B );
			isPressY     = pInput->GetPress( DIK_Y );
			isPressN     = pInput->GetPress( DIK_N );
			isPressEnter = pInput->GetPress( DIK_RETURN );
		}

		isTrigEnter = pInput->GetTrigger( DIK_RETURN );
		isTrigF8    = pInput->GetTrigger( DIK_F8 );
		isTrigF9    = pInput->GetTrigger( DIK_F9 );

		isRepeat_1 = pInput->GetRepeat( DIK_1 );
		isRepeat_2 = pInput->GetRepeat( DIK_2 );
		isRepeat_3 = pInput->GetRepeat( DIK_3 );
		isRepeat_4 = pInput->GetRepeat( DIK_4 );
		isRepeat_5 = pInput->GetRepeat( DIK_5 );
		isRepeat_6 = pInput->GetRepeat( DIK_6 );
		isRepeat_7 = pInput->GetRepeat( DIK_7 );
		isRepeat_8 = pInput->GetRepeat( DIK_8 );
		isRepeat_9 = pInput->GetRepeat( DIK_9 );
		isRepeat_0 = pInput->GetRepeat( DIK_0 );
	}

	//------------------------------------------
	// [ 移動処理 ]
	//------------------------------------------
	if( m_bMove == true )
	{
		// 平行移動
		if( isPressW || isPressA || isPressS || isPressD )
		{
			float fMoveRot = 0.0f;					// 移動方向

			// 方向の算出
			if( isPressW )
			{
				if( isPressA )
				{
					fMoveRot -= PI * -0.75f;		// 左奥
				}
				else if( isPressD )
				{
					fMoveRot -= PI * 0.75f;			// 右奥
				}
				else
				{
					fMoveRot -= PI;					// 奥
				}
			}
			else if( isPressS )
			{
				if( isPressA )
				{
					fMoveRot -= PI * -0.25f;		// 左手前
				}
				else if( isPressD )
				{
					fMoveRot -= PI * 0.25f;			// 右手前
				}
				else
				{
					fMoveRot -= 0.0f;				// 手前
				}
			}
			else if( isPressA )
			{
				fMoveRot -= PI * -0.5f;				// 左
			}
			else if( isPressD )
			{
				fMoveRot -= PI * 0.5f;				// 右
			}

			fMoveRot -= GetManager()->GetCamera()->GetRot().y;

			// 角度の正規化
			if( fMoveRot > PI )
			{
				fMoveRot -= PI2;
			}
			else if( fMoveRot < -PI )
			{
				fMoveRot += PI2;
			}

			// 方向に応じた移動処理
			m_pos.x -= -sinf( fMoveRot ) * MOVE_SPEED;
			m_pos.z -= cosf( fMoveRot ) * MOVE_SPEED;
		}

		// 上下移動
		if( isPressZ )
		{
			m_pos.y += MOVE_SPEED;
		}
		else if( isPressC )
		{
			m_pos.y -= MOVE_SPEED;
		}
	}

	//------------------------------------------
	// [ 回転処理 ]
	//------------------------------------------
	if( m_bMove == true )
	{
		if( isPressQ )
		{
			m_rot.y += ROTATION_SPEED;
		}
		else if( isPressE )
		{
			m_rot.y -= ROTATION_SPEED;
		}

		if( m_rot.y > PI )
		{
			m_rot.y -= PI2;
		}
		else if( m_rot.y < -PI )
		{
			m_rot.y += PI2;
		}
	}

	//------------------------------------------
	// [ 自動回転処理 ]
	//------------------------------------------
	static float moveRad = 0.0f;
	static float moveLen = 100.0f;

	//if( m_bMove == false )
	//{
	//	/*m_rot.x += PI * 0.01f;

	//	if( m_rot.x > PI )
	//	{
	//		m_rot.x -= PI2;
	//	}*/

	//	m_rot.y += PI * 0.01f;

	//	if( m_rot.y > PI )
	//	{
	//		m_rot.y -= PI2;
	//	}

	//	/*m_rot.z += PI * 0.02f;

	//	if( m_rot.z > PI )
	//	{
	//		m_rot.z -= PI2;
	//	}*/

	//	m_pos.y = sinf( moveRad ) * moveLen;
	//	//m_pos.x = cosf( moveRad ) * moveLen;

	//	moveRad += PI * 0.01f;

	//	if( moveRad > PI )
	//	{
	//		moveRad -= PI2;
	//	}
	//}

	//------------------------------------------
	// [ 移動フラグ切り替え処理 ]
	//------------------------------------------
	if( isTrigEnter )
	{
		m_bMove = m_bMove ? false : true;
	}

	//------------------------------------------
	// [ マテリアル処理 ]
	//------------------------------------------
	// テクスチャ有効・無効切り替え
	if( isTrigF9 )
	{
		m_isTexEnable = m_isTexEnable ? false : true;
	}
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CTestBox::Draw( void )
{
	//---------------------------------
	// [ 描画前処理 ]
	//---------------------------------
	LPRenderer pRenderer = GetManager()->GetRenderer();		// レンダラー取得

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	//glCullFace( GL_FRONT );
	//glCullFace( GL_FRONT_AND_BACK );

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
	//---------------------------------------------------------------------
	if( m_pTexture != NULL && m_isTexEnable )
	{
		m_pTexture->Set();						// テクスチャ設定
	}
	else
	{
		glDisable( GL_TEXTURE_2D );
	}

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	glDisable( GL_LIGHTING );

	pRenderer->SetStreamSource(
		0 ,
		m_pVtxBuff ,
		0 ,
		sizeof( VERTEX_3D ) );

	pRenderer->SetFVF( GL_FVF_VERTEX_3D );			// 頂点フォーマットの設定

	pRenderer->DrawPrimitive(
		PT_TRIANGLE_STRIP ,
		0 ,
		2 );

	//float sizeHalfX = m_size.x * 0.5f;			// X軸のサイズの半分
	//float sizeHalfZ = m_size.z * 0.5f;			// Z軸のサイズの半分

	//// 頂点ポインターを利用した描画処理
	//int sizeV3 = sizeof( VECTOR3 );
	//int sizeV2 = sizeof( VECTOR2 );

	//int sizeCF32 = sizeof( COLOR_F32 );

	//VECTOR3 posData[ 3 ] = {
	//	VECTOR3( 100.0f , 0.0f , 100.0f ),
	//	VECTOR3( 100.0f , 100.0f , -100.0f ),
	//	VECTOR3( -100.0f , 0.0f , -100.0f ),
	//};

	//VECTOR3 norData[ 3 ] = {
	//	VECTOR3( 0.0f , 1.0f , 0.0f ),
	//	VECTOR3( 0.0f , 1.0f , 0.0f ),
	//	VECTOR3( 0.0f , 1.0f , 0.0f ),
	//};

	///*DWORD colData[ 3 ] = {
	//	COLOR_F32( 1.0f , 0.0f , 0.0f , 1.0f ),
	//	COLOR_F32( 1.0f , 0.0f , 0.0f , 1.0f ),
	//	COLOR_F32( 1.0f , 0.0f , 0.0f , 1.0f ),
	//};*/

	//// 色 : 『 A B G R 』の順に格納されていたっ！！
	//// └レンダラーに色変換関数を持たせる必要有りかも...
	//DWORD colData[ 3 ] = {
	//	0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0 ,
	//	0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0 ,
	//	0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0 ,
	//};

	///*COLOR_F32( 0.0f , 0.0f , 1.0f , 1.0f ),
	//COLOR_F32( 0.0f , 0.0f , 1.0f , 1.0f ),
	//COLOR_F32( 0.0f , 0.0f , 1.0f , 1.0f ),*/

	//VECTOR2 texData[ 3 ] = {
	//	VECTOR2( 0.0f , 0.0f ),
	//	VECTOR2( 1.0f , 0.0f ),
	//	VECTOR2( 0.0f , 1.0f ),
	//};

	//VERTEX_3D vtxData[ 3 ];

	//// 位置
	//vtxData[ 0 ].pos = VECTOR3( 100.0f , 0.0f , 100.0f );
	//vtxData[ 1 ].pos = VECTOR3( 100.0f , 100.0f , -100.0f );
	//vtxData[ 2 ].pos = VECTOR3( -100.0f , 0.0f , -100.0f );

	//// 法線
	//vtxData[ 0 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	//vtxData[ 1 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	//vtxData[ 2 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );

	//// 色
	//vtxData[ 0 ].col = 0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0;
	//vtxData[ 1 ].col = 0xff << 24 | 0x00 << 16 | 0xff << 8 | 0x00 << 0;
	//vtxData[ 2 ].col = 0xff << 24 | 0x00 << 16 | 0x00 << 8 | 0xff << 0;

	//// テクスチャ
	//vtxData[ 0 ].tex = VECTOR2( 0.0f , 0.0f );
	//vtxData[ 1 ].tex = VECTOR2( 1.0f , 0.0f );
	//vtxData[ 2 ].tex = VECTOR2( 0.0f , 1.0f );

	//glEnableClientState( GL_VERTEX_ARRAY );
	//glEnableClientState( GL_NORMAL_ARRAY );
	//glEnableClientState( GL_COLOR_ARRAY );
	//glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	///*glVertexPointer( 3 , GL_FLOAT , 0 , posData );
	//glNormalPointer( GL_FLOAT , 0 , norData );
	//glColorPointer( 4 , GL_UNSIGNED_BYTE , 0 , colData );
	//glTexCoordPointer( 2 , GL_FLOAT , 0 , texData );*/

	//char* pTop = ( char* )vtxData;
	//int stride = 0;

	//void* pPosPointer = pTop + stride;

	//stride += sizeof( float ) * 3;

	//void* pNorPointer = pTop + stride;

	//stride += sizeof( float ) * 3;

	//void* pColPointer = pTop + stride;

	//stride += sizeof( DWORD );

	//void* pTexPointer = pTop + stride;

	//glVertexPointer( 3 , GL_FLOAT , sizeof( VERTEX_3D ) , pPosPointer );
	//glNormalPointer( GL_FLOAT , sizeof( VERTEX_3D ) , pNorPointer );
	//glColorPointer( 4 , GL_UNSIGNED_BYTE , sizeof( VERTEX_3D ) , pColPointer );
	//glTexCoordPointer( 2 , GL_FLOAT , sizeof( VERTEX_3D ) , pTexPointer );

	//glDrawArrays( GL_TRIANGLE_STRIP , 0 , 3 );

	//glDisableClientState( GL_VERTEX_ARRAY );
	//glDisableClientState( GL_NORMAL_ARRAY );
	//glDisableClientState( GL_COLOR_ARRAY );
	//glDisableClientState( GL_TEXTURE_COORD_ARRAY );

	glEnable( GL_LIGHTING );

	glBlendFunc( GL_ONE , GL_ZERO );
	glDisable( GL_BLEND );

	///////////////////////////////////////////////////////////////////
	// 旧バージョン
	///////////////////////////////////////////////////////////////////
		//glBegin( GL_TRIANGLE_STRIP );
		//{
		//	/* ==0== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , -1.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , -1.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , -1.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 1.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , -1.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

		//	}

		//	/* ==1== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 1.0f , 0.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 1.0f , 0.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 1.0f , 0.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 1.0f , 0.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );
		//	}

		//	/* ==2== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , 1.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , 1.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , 1.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , 1.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );
		//	}

		//	/* ==3== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( -1.0f , 0.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( -1.0f , 0.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( -1.0f , 0.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( -1.0f , 0.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );
		//	}

		//	/* ==4== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , -1.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , -1.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , -1.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , -1.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );
		//	}

		//	/* ==5== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 1.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 1.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 1.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 1.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );
		//	}
		//}
		//glEnd();

	//---------------------------------
	// [ 描画後処理 ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glDisable( GL_BLEND );
	glBlendFunc( GL_ONE , GL_ZERO );

	glDisable( GL_CULL_FACE );

	if( !m_isTexEnable )
	{
		glEnable( GL_TEXTURE_2D );
	}

}
