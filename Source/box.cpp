//==============================================================================
// タイトル     :   3D立方体描画用クラス
// ファイル名   :   box.cpp
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
#include "box.h"
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
CMaterial* pMat;				// マテリアルへのポインタ

enum MAT_TYPE
{								/* ==マテリアル種類識別子== */
	MAT_TYPE_AMBIENT = 0,			// アンビエント
	MAT_TYPE_DIFFUSE,				// ディフューズ
	MAT_TYPE_SPECULAR,				// スペキュラー
	MAT_TYPE_EMISSION,				// エミッション
	MAT_TYPE_SINESS,				// 鏡面反射光子数
	MAT_TYPE_MAX,					// 総数
};

MAT_TYPE matSelect;				// 現在選択しているマテリアル

//==============================================================================
// 関数名 : CBox()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CBox::CBox()
{
	m_pTexture = NULL;

	m_bMove       = false;
	m_isTexEnable = true;

	pMat = NULL;
	matSelect = MAT_TYPE_AMBIENT;
}

//==============================================================================
// 関数名 : ~CBox()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CBox::~CBox()
{
}

//==============================================================================
// 関数名 : bool Init( char* texPath )
// 引数   : char* texPath : テクスチャファイルパス
// 戻り値 : void
// 説明   : 初期化処理( テクスチャファイルパス有り版 )
//==============================================================================
bool CBox::Init( char* texPath )
{
	CSceneGL3D::Init( texPath );		// 基底クラスの初期化処理呼び出し

	m_size = VECTOR3( 100.0f , 100.0f , 100.0f );
	m_bMove = false;
	pMat = CMaterialGL::Create();	// マテリアル生成
	pMat->m_isShininessEnable = true;


	//---------------------------------
	// [ テクスチャ読み込み処理 ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();					// レンダラーの取得
	pRenderer->CreateTexture( texPath , &m_pTexture );					// テクスチャ生成

	return true;		// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CBox::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CBox::Update( void )
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
	if( pMat != NULL )
	{
		CDebugProc::GetDebugProc()->PrintDebugProc( "[ Material ]\n" );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Ambient  : ( %1.3f : %1.3f : %1.3f : %1.3f )\n" , pMat->m_ambient.r , pMat->m_ambient.g , pMat->m_ambient.b , pMat->m_ambient.a );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Diffuse  : ( %1.3f : %1.3f : %1.3f : %1.3f )\n" , pMat->m_diffuse.r , pMat->m_diffuse.g , pMat->m_diffuse.b , pMat->m_diffuse.a );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Specular : ( %1.3f : %1.3f : %1.3f : %1.3f )\n" , pMat->m_specular.r , pMat->m_specular.g , pMat->m_specular.b , pMat->m_specular.a );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Emission : ( %1.3f : %1.3f : %1.3f : %1.3f )\n" , pMat->m_emission.r , pMat->m_emission.g , pMat->m_emission.b , pMat->m_emission.a );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Shiness  : ( %1.3f )\n\n" , pMat->m_shininess );

		// 変化量パラメータ設定
		float rMove = 0.0f;
		float gMove = 0.0f;
		float bMove = 0.0f;
		float aMove = 0.0f;

		if( isRepeat_1 ) rMove = -0.02f;
		else if( isRepeat_2 ) rMove = 0.02f;

		if( isRepeat_3 ) gMove = -0.02f;
		else if( isRepeat_4 ) gMove = 0.02f;

		if( isRepeat_5 ) bMove = -0.02f;
		else if( isRepeat_6 ) bMove = 0.02f;

		if( isRepeat_7 ) aMove = -0.02f;
		else if( isRepeat_8 ) aMove = 0.02f;

		// 変化量代入
		CDebugProc::GetDebugProc()->PrintDebugProc( "SelectType :" );

		switch( matSelect )
		{
			case MAT_TYPE_AMBIENT:
			{
				pMat->m_ambient.r += rMove;
				pMat->m_ambient.g += gMove;
				pMat->m_ambient.b += bMove;
				pMat->m_ambient.a += aMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Ambient\n" );
				break;
			}

			case MAT_TYPE_DIFFUSE:
			{
				pMat->m_diffuse.r += rMove;
				pMat->m_diffuse.g += gMove;
				pMat->m_diffuse.b += bMove;
				pMat->m_diffuse.a += aMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Diffuse\n" );
				break;
			}

			case MAT_TYPE_SPECULAR:
			{
				pMat->m_specular.r += rMove;
				pMat->m_specular.g += gMove;
				pMat->m_specular.b += bMove;
				pMat->m_specular.a += aMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Specular\n" );
				break;
			}

			case MAT_TYPE_EMISSION:
			{
				pMat->m_emission.r += rMove;
				pMat->m_emission.g += gMove;
				pMat->m_emission.b += bMove;
				pMat->m_emission.a += aMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Emission\n" );
				break;
			}

			case MAT_TYPE_SINESS:
			{
				rMove *= 100.0f;

				pMat->m_shininess += rMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Shiness\n" );
				break;
			}

			default:
			{
				break;
			}
		}

		// 操作対象の切り替え
		if( isRepeat_9 )
		{
			matSelect = ( MAT_TYPE )( matSelect - 1 );

			if( matSelect <= -1 )
			{
				matSelect = ( MAT_TYPE )( MAT_TYPE_MAX - 1 );
			}
		}
		else if( isRepeat_0 )
		{
			matSelect = ( MAT_TYPE )( matSelect + 1 );

			if( matSelect >= MAT_TYPE_MAX )
			{
				matSelect = ( MAT_TYPE )0;
			}
		}

		// デフォルトの値に戻す
		if( isTrigF8 )
		{
			CMaterialGL matDef;

			*pMat = matDef;
			pMat->m_isShininessEnable = true;
		}
	}

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
void CBox::Draw( void )
{
	//---------------------------------
	// [ 描画前処理 ]
	//---------------------------------
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

	if( pMat != NULL )
	{
		pMat->Set();							// マテリアル設定
	}

	float sizeHalfX = m_size.x * 0.5f;			// X軸のサイズの半分
	float sizeHalfZ = m_size.z * 0.5f;			// Z軸のサイズの半分

	glBegin( GL_TRIANGLE_STRIP );
	{
		/* ==0== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , -1.0f , 0.0f );
			glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , -1.0f , 0.0f );
			glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , -1.0f , 0.0f );
			glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 1.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , -1.0f , 0.0f );
			glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

		}

		/* ==1== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 1.0f , 0.0f , 0.0f );
			glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 1.0f , 0.0f , 0.0f );
			glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 1.0f , 0.0f , 0.0f );
			glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 1.0f , 0.0f , 0.0f );
			glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );
		}

		/* ==2== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );
		}

		/* ==3== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( -1.0f , 0.0f , 0.0f );
			glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( -1.0f , 0.0f , 0.0f );
			glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( -1.0f , 0.0f , 0.0f );
			glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 1.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( -1.0f , 0.0f , 0.0f );
			glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );
		}

		/* ==4== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , -1.0f );
			glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , -1.0f );
			glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , -1.0f );
			glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 1.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , -1.0f );
			glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );
		}

		/* ==5== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 1.0f , 0.0f );
			glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 1.0f , 0.0f );
			glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 1.0f , 0.0f );
			glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );

			glTexCoord2f( 1.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 1.0f , 0.0f );
			glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );
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

	if( !m_isTexEnable )
	{
		glEnable( GL_TEXTURE_2D );
	}

	if( pMat != NULL )
	{
		CMaterialGL pDefMat;

		pDefMat.Set();							// マテリアル設定
	}
}
