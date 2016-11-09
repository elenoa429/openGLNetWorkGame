//==============================================================================
// タイトル     :   OpenGL用エディターカメラ処理
// ファイル名   :   editorCameraGL.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/07/10
//==============================================================================

//==============================================================================
// 更新履歴: -2016/07/10 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "editorCameraGL.h"
#include "rendererGL.h"
#include "input_DX_mause.h"

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
// 関数名 : CEditorCameraGL()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CEditorCameraGL::CEditorCameraGL()
{
	m_angleH = 0.0f;
	m_angleV = 0.0f;
}

//==============================================================================
// 関数名 : ~CEditorCameraGL()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CEditorCameraGL::~CEditorCameraGL()
{
}

//==============================================================================
// 関数名 : bool Init( VECTOR3 posV , VECTOR3 posR )
// 引数   : void
// 戻り値 : void
// 説明   : 初期化処理
//==============================================================================
bool CEditorCameraGL::Init( VECTOR3 posV , VECTOR3 posR )
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
void CEditorCameraGL::Uninit( void )
{
}

//==============================================================================
// 関数名 : void Update( void )
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CEditorCameraGL::Update( void )
{
	//------------------------------------------
	// [ 入力情報の取得処理 ]
	//------------------------------------------
	CInput*        pInputKeyboard = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );
	CInputDXMause* pInputMause    = dynamic_cast< CInputDXMause* >( CInput::GetInput( INPUT_TYPE_DX_MOUSE ) );

	bool bPressW            = false;
	bool bPressS            = false;
	bool bPressA            = false;
	bool bPressD            = false;
	bool bPressQ            = false;
	bool bPressE            = false;
	bool bPressZ            = false;
	bool bPressC            = false;
	bool bPressT            = false;
	bool bPressB            = false;
	bool bPressY            = false;
	bool bPressN            = false;
	bool bPressEnter        = false;
	bool isPressMauseRight  = false;
	bool isPressMauseCenter = false;

	bool bTrigEnter         = false;

	VECTOR3 mauseVel;			// マウスの加速度

	if( pInputKeyboard != NULL )
	{
		if( m_bMove == true )
		{
			bPressW     = pInputKeyboard->GetPress( DIK_W );
			bPressS     = pInputKeyboard->GetPress( DIK_S );
			bPressA     = pInputKeyboard->GetPress( DIK_A );
			bPressD     = pInputKeyboard->GetPress( DIK_D );
			bPressQ     = pInputKeyboard->GetPress( DIK_Q );
			bPressE     = pInputKeyboard->GetPress( DIK_E );
			bPressZ     = pInputKeyboard->GetPress( DIK_Z );
			bPressC     = pInputKeyboard->GetPress( DIK_C );
			bPressT     = pInputKeyboard->GetPress( DIK_T );
			bPressB     = pInputKeyboard->GetPress( DIK_B );
			bPressY     = pInputKeyboard->GetPress( DIK_Y );
			bPressN     = pInputKeyboard->GetPress( DIK_N );
			bPressEnter = pInputKeyboard->GetPress( DIK_RETURN );
		}

		bTrigEnter = pInputKeyboard->GetTrigger( DIK_RETURN );
	}

	if( pInputMause == NULL )
	{
		return;		// マウスデバイスが必要不可欠なため、これ以上処理をしない
	}

	mauseVel.x = pInputMause->GetVelocity().x;
	mauseVel.y = pInputMause->GetVelocity().y;
	mauseVel.z = pInputMause->GetVelocity().z;

	isPressMauseRight  = pInputMause->GetPress( DIM_RIGHT );
	isPressMauseCenter = pInputMause->GetPress( DIM_CENTER );

	//------------------------------------------
	// [ カメラ操作処理 ]
	//------------------------------------------
	// 視点・注視点→回転座標への変換
	m_angleH = GetHAngle( &m_posR , &m_posV );
	m_angleV = GetVAngle( &m_posR , &m_posV );
	
	// 入力を元に回転する
	// 視点移動( 回転 )
	VECTOR2 radMove = VECTOR2( 0.0f , 0.0f );	// マウス移動値を元にしたカメラ角度の移動量

	if( isPressMauseRight )
	{
		radMove = MoveRad( mauseVel );
	}

	m_angleH += radMove.x;		// 水平方向への回転

	// -π～πにクランプ
	if( m_angleH > PI )  { m_angleH -= PI2; }
	if( m_angleH < -PI ) { m_angleH += PI2; }

	m_angleV += radMove.y;		// 垂直方向への回転

	// -π/2～π/2にクランプ
	if( m_angleV > PI * 0.50f )  { m_angleV = PI * 0.499f; }
	if( m_angleV < -PI * 0.50f ) { m_angleV = -PI * 0.499f; }
	
	// 平行移動
	VECTOR3 vTranslate = VECTOR3( 0.0f , 0.0f , 0.0f );

	if( isPressMauseCenter )
	{
		vTranslate = MoveTranslate( mauseVel );
	}

	// ズーム処理
	if( fabs( mauseVel.z ) > 0.10f )
	{
		mauseVel.z < 0.0f ? m_fDistance += 0.10f : m_fDistance -= 0.10f;

		if( m_fDistance < 0.10f ){ m_fDistance = 0.10f; }
	}

	//------------------------------------------
	// [ 回転座標→３次元座標への変換 ]
	//------------------------------------------
	m_posV = VECTOR3( 0.0f , 0.0f , 0.0f );						// 視点の初期化をしておく

	// HAngle/VAngleを行列に変換する
	MATRIX mRot;

	MatrixIdentity( &mRot );
	MatrixRotationYawPitchRoll( &mRot , m_angleH , m_angleV , 0.0f );

	// 平行移動
	Vec3TransformCoord( &vTranslate , &vTranslate , &mRot );
	vTranslate.y = 0.0f;										// XZ平面での移動なのでY移動値は無視する
	Vec3Add( &m_posR , &m_posR , &vTranslate );					// 視点を動かす
	
	// 回転
	VECTOR3 vDir = VECTOR3( 0.0f , 0.0f , m_fDistance );
	Vec3TransformCoord( &vDir , &vDir , &mRot );				// 方向ベクトルの回転
	Vec3Add( &m_posV , &m_posR , &vDir );

}

//==============================================================================
// 関数名 : float GetHAngle( VECTOR3* vEye , VECTOR3* vTgt )
// 引数   : VECTOR3* vPosV : 視点
//          VECTOR3* vPosR : 注視点
// 戻り値 : float型        : 方向のラジアン角を返却
// 説明   : 水平方向取得処理
//==============================================================================
float CEditorCameraGL::GetHAngle( VECTOR3* vPosV , VECTOR3* vPosR )
{
	// 注視点への向きベクトルを求める
	VECTOR3 vDir;
	Vec3Subtract( &vDir , vPosR , vPosV );

	// HAngle(XZ平面での角度)を求める
	float rad = atan2f( -vDir.z , vDir.x );

	rad += PI * 0.5f;

	// -π～πにクランプ
	if( rad > PI )  { rad -= PI2; }
	if( rad < -PI ) { rad += PI2; }

	return rad;
}

//==============================================================================
// 関数名 : float GetVAngle( VECTOR3* vPosV , VECTOR3* vPosR )
// 引数   : VECTOR3* vPosV : 視点
//          VECTOR3* vPosR : 注視点
// 戻り値 : float型        : 方向のラジアン角を返却
// 説明   : 垂直方向取得
//==============================================================================
float CEditorCameraGL::GetVAngle( VECTOR3* vPosV , VECTOR3* vPosR )
{
	// 注視点への向きベクトルを求める
	VECTOR3 vDir;
	Vec3Subtract( &vDir , vPosR , vPosV );

	float fFront;
	{
		// カメラの前方方向値
		VECTOR3 vFront;
		vFront = vDir;

		vFront.y = 0;	// XZ平面での距離なのでYはいらない
		fFront = Vec3Length( &vFront );
	}

	// Y軸とXZ平面の前方方向との角度を求める
	float rad = atan2f( -vDir.y , fFront );

	// -π/2～π/2にクランプ
	if( rad > PI * 0.50f )  { rad = PI * 0.50f; }
	if( rad < -PI * 0.50f ) { rad = -PI * 0.50f; }

	return rad;
}

//==============================================================================
// 関数名 : float GetVAngle( VECTOR3* vPosV , VECTOR3* vPosR )
// 引数   : VECTOR3 vel : マウス加速度
// 戻り値 : VECTOR2型   : ラジアン移動量を返却
// 説明   : マウスの加速度から角度移動量を生成する処理
//==============================================================================
VECTOR2 CEditorCameraGL::MoveRad( VECTOR3 vel )
{
	VECTOR2 out;
	const float maxMoveRad = PI * 0.010f;

	// 移動量係数を絶対値で『 1.0 』にクランプ
	out.x = vel.x < 0.0f ? max( vel.x , -1.0f ) : min( vel.x , 1.0f );
	out.y = vel.y < 0.0f ? max( vel.y , -1.0f ) : min( vel.y , 1.0f );

	// デッドゾーンを設定
	out.x = fabs( vel.x ) < 0.10f ? 0.0f : vel.x;
	out.y = fabs( vel.y ) < 0.10f ? 0.0f : vel.y;

	// 算出した係数を元に、移動量を設定
	out.x *= maxMoveRad;
	out.y *= maxMoveRad;

	return out;
}

//==============================================================================
// 関数名 : float GetVAngle( VECTOR3* vPosV , VECTOR3* vPosR )
// 引数   : VECTOR3 vel : マウス加速度
// 戻り値 : VECTOR2型   : ラジアン移動量を返却
// 説明   : マウスの加速度から、平行移動量を算出
//==============================================================================
VECTOR3 CEditorCameraGL::MoveTranslate( VECTOR3 vel )
{
	VECTOR3 out = VECTOR3( 0.0f , 0.0f , 0.0f );
	const float maxMoveT = 10.0f;

	// 移動量係数を絶対値で『 1.0 』にクランプ
	out.x = vel.x < 0.0f ? max( vel.x , -1.0f ) : min( vel.x , 1.0f );
	out.z = vel.y < 0.0f ? max( vel.y , -1.0f ) : min( vel.y , 1.0f );

	// デッドゾーンを設定
	out.x = fabs( vel.x ) < 0.10f ? 0.0f : vel.x;
	out.z = fabs( vel.y ) < 0.10f ? 0.0f : vel.y;

	// 算出した係数を元に、移動量を設定
	out.x *= maxMoveT;
	out.z *= maxMoveT;

	return out;
}

