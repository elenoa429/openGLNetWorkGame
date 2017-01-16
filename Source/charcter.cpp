//==============================================================================
// タイトル     :   キャラクター基底クラス
// ファイル名   :   charcter.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/11/21
//==============================================================================

//==============================================================================
// 更新履歴: -2016/11/21 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "charcter.h"
#include "game.h"
#include "cameraGL.h"
#include <math.h>
#include "wall.h"

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
// 関数名 : CCharcter()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CCharcter::CCharcter()
{
	m_pos = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_scl = VECTOR3( 5.0f , 5.0f , 5.0f );
	m_gensui = VECTOR3( 0.025f , 0.025f , 0.025f );

	m_id = 0;
	m_life = 0;

	m_pBoundingSphere = NULL;

	m_pModel = NULL;
	m_numMat = 0;
	m_pMat   = NULL;

}

//==============================================================================
// 関数名 : ~CCharcter()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CCharcter::~CCharcter()
{

}

//==============================================================================
// 関数名 : bool Init( int charcterType )
// 引数   : void
// 戻り値 : bool型 : 成功判定
// 説明   : 初期化処理
//==============================================================================
bool CCharcter::Init( int charcterType )
{
	m_pos = VECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	m_rot = VECTOR3(0.0f, 0.0f, 0.0f);			// 角度
	m_mov = VECTOR3(0.0f, 0.0f, 0.0f);			// 移動力
	m_rotMokuhyou = VECTOR3(0.0f, 0.0f, 0.0f);	// 目標角度
	m_spinAxcel = 0.0f;							// 回転の加速度
	m_spinGensui = 8.0f;						// 回転の減衰
	m_life = 3;									// ライフ
	//m_type = type;								// 種類
	m_actionState = ACTION_NONE;				// アクションなし

	m_Width = 4.0f;
	m_Height = 4.0f;
	m_Depth = 4.0f;
	
	switch( charcterType )
	{
		case CCharcter::CHARCTER_TYPE_RABBITS: m_type = CCharcter::CHARCTER_TYPE_RABBITS; break;
		case CCharcter::CHARCTER_TYPE_CAT:     m_type = CCharcter::CHARCTER_TYPE_CAT;     break;
		case CCharcter::CHARCTER_TYPE_PANDA:   m_type = CCharcter::CHARCTER_TYPE_PANDA;   break;
		case CCharcter::CHARCTER_TYPE_PENGUIN: m_type = CCharcter::CHARCTER_TYPE_PENGUIN; break;

		default:
		{
			m_type = CCharcter::CHARCTER_TYPE_RABBITS;
			CDebugConsole::GetInstance()->Print( "Charcter Type Range Over\nvalue : %d\n" , charcterType );
			break;
		}
	}

	char* pModelFilePath[ CHARCTER_TYPE_MAX ] = {
		{ "data\\MODEL\\playerRabbits.obj" },		// ウサギ
		{ "data\\MODEL\\playerCats.obj" },			// 猫
		{ "data\\MODEL\\playerBears.obj" },			// パンダ
		{ "data\\MODEL\\playerPenguins.obj" },		// ペンギン
	};

	char* pMaterialFilePath[ CHARCTER_TYPE_MAX ] = {
		{ "data\\MODEL\\playerRabbits.mtl" },		// ウサギ
		{ "data\\MODEL\\playerCats.mtl" },			// 猫
		{ "data\\MODEL\\playerBears.mtl" },			// パンダ
		{ "data\\MODEL\\playerPenguins.mtl" },		// ペンギン
	};

	//---------------------------------
	// [ モデル読み込み処理 ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();

	pRenderer->CreateModel( pModelFilePath[ m_type ] , NULL , &m_numMat , &m_pModel );		// モデル生成
	
	//m_pModelManager = CParentModelManagerGL::Create( "data\\MODEL\\miku_01.obj" , "data\\MODEL\\miku_01.mtl" );

	if( m_pModel == NULL )
	{
		return false;
	}

	// モーション生成
	//m_pMotion = CMotionGL::Create( "data\\ANIMATION\\miku_01_01.anm" );

	//if( m_pMotion == NULL )
	//{
	//	return false;
	//}

	//----------------------------------------------
	// [ 球当たり判定生成 ]
	//----------------------------------------------
	m_pBoundingSphere = CCollider3DSphere::Create( m_pos , 4.0f );		// TODO : 半径が決め打ちなので、のちほど修正予定？

	// 処理成功
	return true;
}

//==============================================================================
// 関数名 : void Uninit()
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CCharcter::Uninit()
{
	if( m_pMat != NULL )
	{
		m_pMat->Release();
		m_pMat = NULL;
	}

	if( m_pBoundingSphere != NULL )
	{
		m_pBoundingSphere->Release();
		m_pBoundingSphere = NULL;
	}
}

//==============================================================================
// 関数名 : void Update()
// 引数   : void
// 戻り値 : void
// 説明   : 更新処理
//==============================================================================
void CCharcter::Update( void )
{
	/*動かす
	**********************************************/
	m_pos.x += m_mov.x;
	m_pos.z += m_mov.z;

	/*移動量を減衰
	*************************************************/
	m_mov.x += ( 0.0f - m_mov.x ) * m_gensui.x;
	m_mov.z += ( 0.0f - m_mov.z ) * m_gensui.z;

	// 当たり判定更新
	m_pBoundingSphere->SetPos( m_pos );

	// 他のプレイヤーとの当たり判定処理
	CGame* pGameMode = dynamic_cast< CGame* >( GetManager()->GetMode() );

	if( pGameMode != NULL )
	{
		for( int i = 0 ; i < PLAYER_MAX ; i++ )
		{
			if( i != m_id )
			{
				CCharcter* pOtherPlayer = pGameMode->GetCharcter( i );
				CCollider3DSphere* pCollider = pOtherPlayer->GetBoundingSphere();

				if( m_pBoundingSphere->Collide( *pCollider ) )
				{
					VECTOR3 dentValue = m_pBoundingSphere->GetDent( *pCollider , 1.0f );
					m_pos.x += dentValue.x * 0.1f;
					m_pos.z += dentValue.z * 0.1f;

					VECTOR3 setMove = pOtherPlayer->GetMov();

					setMove.x += m_mov.x * 1.75f;
					setMove.z += m_mov.z * 1.75f;

					setMove.x -= dentValue.x;
					setMove.z -= dentValue.z;
					pOtherPlayer->SetMov( setMove );

					CDebugConsole::GetInstance()->Print( "HIT : %d->%d\n" , m_id , i );
				}
			}
		}
	}

	// 壁との当たり判定
	if( m_pos.x + m_mov.x - m_Width / 2 < -WALL_WIDTH / 2 ||
		m_pos.x + m_mov.x + m_Width / 2 > WALL_WIDTH / 2 )
	{
		m_mov.x *= -2.0f;
		CDebugConsole::GetInstance()->Print( "WALL HIT X : %d\n" , m_id );
		m_life--;
	}

	if( m_pos.z + m_mov.z - m_Depth / 2 < -WALL_DEPTH / 2 ||
		m_pos.z + m_mov.z + m_Depth / 2 > WALL_DEPTH / 2 )
	{
		m_mov.z *= -2.0f;
		CDebugConsole::GetInstance()->Print( "WALL HIT Z : %d\n" , m_id  );
		m_life--;
	}

	//---------------------------------------
	// [ 状態処理 ]
	//---------------------------------------
	if( m_life <= 0 )
	{
		// TODO : ここに状態遷移で死亡状態を入れる
	}
}

//==============================================================================
// 関数名 : void Draw()
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CCharcter::Draw( void )
{
	// ----------------------------------------------------------------------
	// [ ワールドマトリックスの生成処理 ]
	// ----------------------------------------------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glTranslatef( m_pos.x , m_pos.y , m_pos.z );

	glRotatef( RadToDeg( m_rot.z ) , 0.0f , 0.0f , 1.0f );
	glRotatef( RadToDeg( m_rot.y ) , 0.0f , 1.0f , 0.0f );
	glRotatef( RadToDeg( m_rot.x ) , 1.0f , 0.0f , 0.0f );

	glScalef( m_scl.x , m_scl.y , m_scl.z );

	//---------------------------------
	// [ 描画前処理 ]
	//---------------------------------
	glEnable( GL_NORMALIZE );
	glBindTexture( GL_TEXTURE_2D , 0 );
	glDisable( GL_TEXTURE_2D );

	//---------------------------------
	// [ 描画処理 ]
	//---------------------------------
	if( m_life > 0 )
	{
		for( DWORD matCnt = 0 ; matCnt < m_numMat ; matCnt++ )
		{
			m_pModel->DrawSubset( matCnt );
		}
	}

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

	glEnable( GL_TEXTURE_2D );
}

//==============================================================================
// 関数名 : void CCharcter :: Rotation( void )
// 引数   : void
// 戻り値 : void
// 説明   : キャラクターを回転させる
//==============================================================================
void CCharcter :: Rotation( void )
{
	if( m_rotMokuhyou.y < -PI )
	{//目標角度が小さすぎると調整
		m_rotMokuhyou.y = PI * 2 + m_rotMokuhyou.y;
	}
	else if( m_rotMokuhyou.y > PI )
	{//目標角度が大きすぎると調整
		m_rotMokuhyou.y = m_rotMokuhyou.y - PI * 2;
	}

	if( m_rot.y < -PI )
	{//最小値を過ぎたので角度は戻す
		m_rot.y = PI;
	}
	else if( m_rot.y > PI )
	{//最大値を過ぎたので角度は戻す
		m_rot.y = -PI;
	}

	if( m_rotMokuhyou.y != m_rot.y )
	{//プレイヤーキャラの角度を変える

		if ( m_rotMokuhyou.y - m_rot.y < -PI )
		{//目標角と今の角度が正負をまたいでいるとき

			m_rot.y += ( PI * 2 + m_rotMokuhyou.y - m_rot.y ) / m_spinGensui;      // 回す
		}
		else if ( m_rotMokuhyou.y - m_rot.y > PI )
		{//目標角と今の角度が正負をまたいでいるとき

			m_rot.y += ( -PI * 2 + m_rotMokuhyou.y - m_rot.y ) / m_spinGensui;     // 回す
		}
		else
		{//それ以外の時

			m_rot.y += ( m_rotMokuhyou.y - m_rot.y ) / m_spinGensui;  // 回す
		}
	}
}

//==============================================================================
// 関数名 : サンプル
// 引数   : void
// 戻り値 : void
// 説明   : サンプル処理
//==============================================================================

