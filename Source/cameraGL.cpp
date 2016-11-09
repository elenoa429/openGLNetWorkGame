//==============================================================================
// タイトル     :   OpenGL用カメラ処理
// ファイル名   :   cameraGL.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/13
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/13 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "cameraGL.h"
#include "rendererGL.h"

//==============================================================================
// 列挙型宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================
#define MOVE_SPEED		( 20.0f )
#define ROTATION_SPEED	( PI * 0.01f )

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
// 関数名 : CCameraGL()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CCameraGL::CCameraGL()
{
}

//==============================================================================
// 関数名 : ~CCameraGL()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CCameraGL::~CCameraGL()
{
}

//==============================================================================
// 関数名 : bool Init( VECTOR3 posV , VECTOR3 posR )
// 引数   : void
// 戻り値 : void
// 説明   : 初期化処理
//==============================================================================
bool CCameraGL::Init( VECTOR3 posV , VECTOR3 posR )
{
	m_posV = posV;
	m_posR = posR;
	m_VecU = VECTOR3( 0.0f , 1.0f , 0.0f );

	float dx = m_posR.x - m_posV.x;
	float dy = m_posR.y - m_posV.y;
	float dz = m_posR.z - m_posV.z;

	m_rot       = VECTOR3( 0.0f , atan2f( dx , dz ) , 0.0f );
	m_fDistance = sqrtf( dx * dx + dz * dz );
	m_fov       = 60.0f;		// 視野角は『度』で設定
	m_nearZ     = 1.0f;
	m_farZ      = 200000.0f;

	m_posR.x = m_posV.x + sinf( m_rot.y ) * m_fDistance;
	m_posR.z = m_posV.z + cosf( m_rot.y ) * m_fDistance;
	m_bMove  = true;

	return true;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CCameraGL::Uninit( void )
{
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CCameraGL::Update( void )
{
	//------------------------------------------
	// [ 入力情報の取得処理 ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool bPressW     = false;
	bool bPressS     = false;
	bool bPressA     = false;
	bool bPressD     = false;
	bool bPressQ     = false;
	bool bPressE     = false;
	bool bPressZ     = false;
	bool bPressC     = false;
	bool bPressT     = false;
	bool bPressB     = false;
	bool bPressY     = false;
	bool bPressN     = false;
	bool bPressEnter = false;

	bool bTrigEnter  = false;

	if( pInput != NULL )
	{
		if( m_bMove == true )
		{
			bPressW     = pInput->GetPress( DIK_W );
			bPressS     = pInput->GetPress( DIK_S );
			bPressA     = pInput->GetPress( DIK_A );
			bPressD     = pInput->GetPress( DIK_D );
			bPressQ     = pInput->GetPress( DIK_Q );
			bPressE     = pInput->GetPress( DIK_E );
			bPressZ     = pInput->GetPress( DIK_Z );
			bPressC     = pInput->GetPress( DIK_C );
			bPressT     = pInput->GetPress( DIK_T );
			bPressB     = pInput->GetPress( DIK_B );
			bPressY     = pInput->GetPress( DIK_Y );
			bPressN     = pInput->GetPress( DIK_N );
			bPressEnter = pInput->GetPress( DIK_RETURN );
		}

		bTrigEnter = pInput->GetTrigger( DIK_RETURN );
	}

	//------------------------------------------
	// [ カメラ並行移動処理 ]
	//------------------------------------------
	if( bPressW || bPressA || bPressS || bPressD )
	{
		float fMoveRot = 0.0f;					// 移動方向

		/* ===方向の算出=== */
		if( bPressW )
		{
			if( bPressA )
			{
				fMoveRot -= PI * -0.75f;		// 左奥
			}
			else if( bPressD )
			{
				fMoveRot -= PI * 0.75f;			// 右奥
			}
			else
			{
				fMoveRot -= PI;					// 奥
			}
		}
		else if( bPressS )
		{
			if( bPressA )
			{
				fMoveRot -= PI * -0.25f;		// 左手前
			}
			else if( bPressD )
			{
				fMoveRot -= PI * 0.25f;			// 右手前
			}
			else
			{
				fMoveRot -= 0.0f;				// 手前
			}
		}
		else if( bPressA )
		{
			fMoveRot -= PI * -0.5f;				// 左
		}
		else if( bPressD )
		{
			fMoveRot -= PI * 0.5f;				// 右
		}

		fMoveRot -= m_rot.y;

		/* ===角度の正規化=== */
		if( fMoveRot > PI )
		{
			fMoveRot -= PI2;
		}
		else if( fMoveRot < -PI )
		{
			fMoveRot += PI2;
		}

		/* ===方向に応じた視点移動処理=== */
		m_posV.x -= -sinf( fMoveRot ) * MOVE_SPEED;
		m_posV.z -= cosf( fMoveRot ) * MOVE_SPEED;

		/* ===注視点の設定=== */
		m_posR.x = m_posV.x + sinf( m_rot.y ) * m_fDistance;
		m_posR.z = m_posV.z + cosf( m_rot.y ) * m_fDistance;
	}

	if( bPressT )
	{
		m_posV.y += MOVE_SPEED;
	}
	else if( bPressB )
	{
		m_posV.y -= MOVE_SPEED;
	}

	if( bPressY )
	{
		m_posR.y += MOVE_SPEED;
	}
	else if( bPressN )
	{
		m_posR.y -= MOVE_SPEED;
	}

	//------------------------------------------
	// [ カメラ回転処理 ]
	//------------------------------------------
	/* ===注視点=== */
	if( bPressQ )
	{
		m_rot.y += ROTATION_SPEED;
		m_posR.x = m_posV.x + sinf( m_rot.y ) * m_fDistance;
		m_posR.z = m_posV.z + cosf( m_rot.y ) * m_fDistance;
	}
	else if( bPressE )
	{
		m_rot.y -= ROTATION_SPEED;
		m_posR.x = m_posV.x + sinf( m_rot.y ) * m_fDistance;
		m_posR.z = m_posV.z + cosf( m_rot.y ) * m_fDistance;
	}

	/* ===視点=== */
	if( bPressZ )
	{
		m_rot.y += ROTATION_SPEED;
		m_posV.x = m_posR.x - sinf( m_rot.y ) * m_fDistance;
		m_posV.z = m_posR.z - cosf( m_rot.y ) * m_fDistance;
	}
	else if( bPressC )
	{
		m_rot.y -= ROTATION_SPEED;
		m_posV.x = m_posR.x - sinf( m_rot.y ) * m_fDistance;
		m_posV.z = m_posR.z - cosf( m_rot.y ) * m_fDistance;
	}

	if( m_rot.y > PI )
	{
		m_rot.y -= PI2;
	}
	else if( m_rot.y < -PI )
	{
		m_rot.y += PI2;
	}

	//------------------------------------------
	// [ カメラリセット処理 ]
	//------------------------------------------
	if( bPressEnter )
	{
		//CCameraGL::Init();
	}

	if( bTrigEnter )
	{
		m_bMove = m_bMove ? false : true;
	}

	//------------------------------------------
	// [ 情報表示処理 ]
	//------------------------------------------
	//CDebugProc::GetDebugProc()->PrintDebugProc( "\n\n\nCAMERA_POSV : ( %3.3f : %3.3f : %3.3f )\n" , m_posV.x , m_posV.y , m_posV.z );
	//CDebugProc::GetDebugProc()->PrintDebugProc( "CAMERA_POSR : ( %3.3f : %3.3f : %3.3f )\n" , m_posR.x , m_posR.y , m_posR.z );
}

//==============================================================================
// 関数名 : void Set( void )
// 引数   : void
// 戻り値 : void
// 説明   : カメラ設定処理
//==============================================================================
void CCameraGL::Set( void )
{
	/* ===カメラ設定( 3D )=== */
	glViewport( 0 , 0 , ( int ) SCREEN_WIDTH , ( int ) SCREEN_HEIGHT );			// ビューポートの設定

	glMatrixMode( GL_PROJECTION );												// 行列モード切替
	glLoadIdentity();															// 射影行列の初期化

	float aspect = ( float )SCREEN_WIDTH / ( float )SCREEN_HEIGHT;				// アスペクト比

	gluPerspective( m_fov , aspect , m_nearZ , m_farZ );						// 射影行列の設定

	glMatrixMode( GL_MODELVIEW );												// 行列モードを戻す
	glLoadIdentity();															// ビュー行列の初期化

	gluLookAt(																	/* ===カメラビュー設定=== */
		m_posV.x , m_posV.y , m_posV.z,												// 視点
		m_posR.x , m_posR.y , m_posR.z,												// 注視点
		m_VecU.x , m_VecU.y , m_VecU.z );											// 上方向ベクトル

	glEnable( GL_DEPTH_TEST );													// ZバッファーON
}

//==============================================================================
// 関数名 : void Set2D( void )
// 引数   : void
// 戻り値 : void
// 説明   : 2Dカメラ設定処理
//==============================================================================
void CCameraGL::Set2D( void )
{
	glMatrixMode( GL_PROJECTION );												// 行列モード切替
	glPushMatrix();																// 射影行列の退避
	glLoadIdentity();															// 射影行列の初期化
	glOrtho( 0 , SCREEN_WIDTH , SCREEN_HEIGHT , 0 , 0.0f , 1.0f );				// 正射影変換設定

	glMatrixMode( GL_MODELVIEW );												// 行列モード切替
	glPushMatrix();																// ビュー行列の退避
	glLoadIdentity();															// ビュー行列の初期化

	glDisable( GL_LIGHTING );													// ライトOFF
}

//==============================================================================
// 関数名 : void End2D( void )
// 引数   : void
// 戻り値 : void
// 説明   : 2D用カメラ行列終了設定
//==============================================================================
void CCameraGL::End2D( void )
{
	glMatrixMode( GL_PROJECTION );												// 行列モード切替
	glPopMatrix();																// 射影行列の復元

	glMatrixMode( GL_MODELVIEW );												// 行列モード切替
	glPopMatrix();																// ビュー行列の復元

	glEnable( GL_LIGHTING );													// ライトON
}
