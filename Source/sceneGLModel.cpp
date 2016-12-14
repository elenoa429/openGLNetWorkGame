//==============================================================================
// タイトル     :   OpenGL用モデル描画用クラス
// ファイル名   :   sceneGLModel.cpp
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
#include "sceneGLModel.h"
#include "rendererGL.h"

#include "loader.h"

//==============================================================================
// 列挙型宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================
#define MOVE_SPEED		( 20.0f )			// 移動係数
#define ROTATION_SPEED	( PI * 0.01f )		// 回転角変化係数

enum MAT_TYPE
{								/* ==マテリアル種類識別子== */
	MAT_TYPE_AMBIENT = 0 ,			// アンビエント
	MAT_TYPE_DIFFUSE ,				// ディフューズ
	MAT_TYPE_SPECULAR ,				// スペキュラー
	MAT_TYPE_EMISSION ,				// エミッション
	MAT_TYPE_SINESS ,				// 鏡面反射光子数
	MAT_TYPE_MAX ,					// 総数
};

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// プロトタイプ宣言
//==============================================================================

//==============================================================================
// グローバル宣言
//==============================================================================
MAT_TYPE g_matSelect;				// 現在選択しているマテリアル

//==============================================================================
// 関数名 : CSceneGLModel()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CSceneGLModel::CSceneGLModel()
{
	m_pos      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size     = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_col      = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );
	m_pTexture = NULL;
	m_nor      = VECTOR3( 0.0f , 0.0f , 0.0f );

	m_pModel   = NULL;
	m_numMat   = 0;
	m_pMat     = NULL;

	m_isTexEnable = true;
	m_isMatEnable = true;
}

//==============================================================================
// 関数名 : ~CSceneGLModel()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CSceneGLModel::~CSceneGLModel()
{
}

//==============================================================================
// 関数名 : CSceneGLModel* Create( char* modelFileName )
// 引数   : char* modelFileName : モデルファイル名
// 戻り値 : CSceneGLModel*型
// 説明   : 生成処理
//==============================================================================
CSceneGLModel* CSceneGLModel::Create( char* modelFileName )
{
	CSceneGLModel* pNewInstance = new CSceneGLModel();

	if( pNewInstance->Init( modelFileName ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// 関数名 : bool Init( char* modelFileName )
// 引数   : char* modelFileName : モデルファイル名
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CSceneGLModel::Init( char* modelPath )
{
	//---------------------------------
	// [ パラメータ初期化処理 ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();						// レンダラーの取得

	m_pos = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_scl = VECTOR3( 1.0f , 1.0f , 1.0f );
	m_nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	m_size = VECTOR3( 1.0f , 0.0f , 1.0f );
	m_col = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );

	MatrixIdentity( &m_mtxWorld );
	m_pTexture = NULL;

	m_bMove = false;

	//---------------------------------
	// [ モデル読み込み処理 ]
	//---------------------------------
	pRenderer->CreateModel( modelPath , NULL , &m_numMat , &m_pModel );		// モデル生成

	//---------------------------------------------
	// [ マテリアル読み込み処理( 仮で埋め込み ) ]
	//---------------------------------------------
	CLoader* pLoader = new CLoader;

	//pLoader->MaterialLoad( "data\\MODEL\\miku_01.mtl" , &m_pMat );

	delete pLoader;
	pLoader = NULL;

	//---------------------------------
	// [ テクスチャ読み込み処理 ]
	//---------------------------------
	//pRenderer->CreateTexture( "data\\MODEL\\miku_01.bmp" , &m_pTexture );	// テクスチャ生成

	return true;		// 処理成功
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CSceneGLModel::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	if( m_pMat != NULL )
	{
		m_pMat->Release();
		m_pMat = NULL;
	}
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CSceneGLModel::Update( void )
{
	//------------------------------------------
	// [ 入力情報の取得処理 ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isPressW = false;
	bool isPressS = false;
	bool isPressA = false;
	bool isPressD = false;
	bool isPressQ = false;
	bool isPressE = false;
	bool isPressZ = false;
	bool isPressC = false;
	bool isPressT = false;
	bool isPressB = false;
	bool isPressY = false;
	bool isPressN = false;
	bool isPressEnter = false;

	bool isTrigEnter = false;
	bool isTrigSpace = false;
	bool isTrigF8 = false;
	bool isTrigF9 = false;

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
			isPressW = pInput->GetPress( DIK_W );
			isPressS = pInput->GetPress( DIK_S );
			isPressA = pInput->GetPress( DIK_A );
			isPressD = pInput->GetPress( DIK_D );
			isPressQ = pInput->GetPress( DIK_Q );
			isPressE = pInput->GetPress( DIK_E );
			isPressZ = pInput->GetPress( DIK_Z );
			isPressC = pInput->GetPress( DIK_C );
			isPressT = pInput->GetPress( DIK_T );
			isPressB = pInput->GetPress( DIK_B );
			isPressY = pInput->GetPress( DIK_Y );
			isPressN = pInput->GetPress( DIK_N );
			isPressEnter = pInput->GetPress( DIK_RETURN );
		}

		isTrigEnter = pInput->GetTrigger( DIK_RETURN );
		isTrigSpace = pInput->GetTrigger( DIK_SPACE );
		isTrigF8 = pInput->GetTrigger( DIK_F8 );
		isTrigF9 = pInput->GetTrigger( DIK_F9 );

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
	// [ テクスチャ有効・無効切り替え ]
	//------------------------------------------
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
void CSceneGLModel::Draw( void )
{
	//---------------------------------
	// [ 描画前処理 ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glEnable( GL_NORMALIZE );

	//---------------------------------
	// [ ワールドマトリクス算出 ]
	//---------------------------------
	glTranslatef( m_pos.x , m_pos.y , m_pos.z );

	glRotatef( RadToDeg( m_rot.z ) , 0.0f , 0.0f , 1.0f );
	glRotatef( RadToDeg( m_rot.y ) , 0.0f , 1.0f , 0.0f );
	glRotatef( RadToDeg( m_rot.x ) , 1.0f , 0.0f , 0.0f );

	glScalef( m_scl.x , m_scl.y , m_scl.z );

	//MATRIX mtxScl , mtxRot , mtxTrans;
	//
	//MatrixIdentity( &m_mtxWorld );
	//
	//MatrixScaling( &mtxScl , m_scl.x , m_scl.y , m_scl.z );
	//MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxScl );
	//
	//MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );
	//MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxRot );
	//
	//MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );
	//MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxTrans );
	//
	//glMultMatrixf( m_mtxWorld.m );

	//---------------------------------
	// [ 描画処理 ]
	//---------------------------------
	if( m_isTexEnable && m_pTexture != NULL )
	{
		m_pTexture->Set();						// テクスチャ設定
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D , 0 );
		glDisable( GL_TEXTURE_2D );
	}

	if( m_isMatEnable && m_pMat != NULL )
	{
		m_pMat->Set();							// マテリアル設定
	}

	//glPolygonMode( GL_FRONT_AND_BACK , GL_LINE );

	for( DWORD matCnt = 0 ; matCnt < m_numMat ; matCnt++ )
	{
		m_pModel->DrawSubset( matCnt );
	}

	//m_pModel->DrawSubset( 0 );
	//m_pModel->DrawSubset( 1 );
	//m_pModel->DrawSubset( 2 );

	//glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );

	//---------------------------------
	// [ 描画後処理 ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glDisable( GL_NORMALIZE );

	if( m_pMat != NULL )
	{
		CMaterialGL pDefMat;

		pDefMat.Set();							// 初期マテリアル設定
	}

	if( !m_isTexEnable )
	{
		glEnable( GL_TEXTURE_2D );
	}

}
