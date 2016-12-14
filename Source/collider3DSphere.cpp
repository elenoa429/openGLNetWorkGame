//==============================================================================
// タイトル     :   3D:球当たり判定クラス
// ファイル名   :   collider3DSphere.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/11/29
//==============================================================================

//==============================================================================
// 更新履歴: -2016/11/29 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "collider3DSphere.h"
#include "manager.h"
#include "main.h"

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
// 関数名 : CCollider3DSphere()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CCollider3DSphere::CCollider3DSphere()
{
	m_radius = 0.0f;
}

//==============================================================================
// 関数名 : ~CCollider3DSphere()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CCollider3DSphere::~CCollider3DSphere()
{

}

//==============================================================================
// 関数名 : CCollider3DSphere* Create( VECTOR3 pos , float radius )
// 引数   : VECTOR3 pos  : 基準位置
//          float radius : 半径
// 戻り値 : CCollider3DSphere*型
// 説明   : 生成処理
//==============================================================================
CCollider3DSphere* CCollider3DSphere::Create( VECTOR3 pos , float radius )
{
	CCollider3DSphere* pNewInstance = new CCollider3DSphere;

	if( pNewInstance->Init( pos , radius ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// 関数名 : bool Init( VECTOR3 pos , float radius )
// 引数   : VECTOR3 pos : 基準位置
//          float radius    : 半径
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CCollider3DSphere::Init( VECTOR3 pos , float radius )
{
	if( CCollider3D::Init( "data\\MODEL\\colliedObj_sphere.x" ) == false )
	{
		return false;	// モデル読み込み失敗
	}

	m_pos    = pos;
	m_radius = radius;

	return true;
}

//==============================================================================
// 関数名 : void Uninit( void )
// 引数   : void
// 戻り値 : void
// 説明   : 終了処理
//==============================================================================
void CCollider3DSphere::Uninit( void )
{
	CCollider3D::Uninit();
}

//==============================================================================
// 関数名 : void Draw( void )
// 引数   : void
// 戻り値 : void
// 説明   : 描画処理
//==============================================================================
void CCollider3DSphere::Draw( void )
{
	// ----------------------------------------------------------------------
	// [ デバイス取得 ]
	// ----------------------------------------------------------------------
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice()->m_pD3DDevice;
	//
	//// ----------------------------------------------------------------------
	//// [ ワールドマトリックスの生成処理 ]
	//// ----------------------------------------------------------------------
	//Matrix mtxWorld , mtxScl , mtxRot , mtxTrans;								// 行列用ワーク
	//D3DXMatrixIdentity( &mtxWorld );											// 行列初期化
	//
	//D3DXMatrixScaling( &mtxScl , m_radius , m_radius , m_radius );				// スケールの行列を算出
	//D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxScl );						// スケール行列の合成
	//
	//D3DXMatrixRotationYawPitchRoll( &mtxRot , 0.0f , 0.0f , 0.0f );				// 回転の行列を算出
	//D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxRot );						// 回転行列の合成
	//
	//D3DXMatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );			// 位置の行列を算出
	//D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxTrans );					// 位置行列の合成
	//
	//pDevice->SetTransform( D3DTS_WORLD , &mtxWorld );							// デバイスへ反映
	//
	//// ----------------------------------------------------------------------
	//// [ 描画処理 ]
	//// ----------------------------------------------------------------------
	//CCollider3D::Draw();
}

//==============================================================================
// 関数名 : bool Collide( CCollider3D& collider )
// 引数   : CCollider3D& collider : 当たり判定用オブジェクト
// 戻り値 : bool型
// 説明   : 当たり判定確認処理
//==============================================================================
inline bool CCollider3DSphere::Collide( CCollider3D& collider )
{
	// ダブルディスパッチによる当たり判定
	bool isHit = collider.Collide( *this );

	SetHitEffect( isHit );
	return isHit;
}

//==============================================================================
// 関数名 : VECTOR3 GetDent( CCollider3D& collider , float rate )
// 引数   : CCollider3D& collider : 当たり判定用オブジェクト
//          float rate            : 割合
// 戻り値 : VECTOR3型             : 判定位置からのめり込み量をベクトルで返却
// 説明   : めり込みベクトル取得処理
//==============================================================================
inline VECTOR3 CCollider3DSphere::GetDent( CCollider3D& collider , float rate )
{
	// ダブルディスパッチによる当たり判定
	return collider.GetDent( *this );
}

//==============================================================================
// 関数名 : bool Collide( CCollider3DSphere& sphere )
// 引数   : CCollider3DSphere& sphere : 球オブジェクト
// 戻り値 : bool型
// 説明   : 当たり判定処理( 対球 )
//==============================================================================
inline bool CCollider3DSphere::Collide( CCollider3DSphere& sphere )
{
	// 球対球の判定処理
	VECTOR3 hitPos = sphere.GetPos();

	float dx = hitPos.x - m_pos.x;
	float dy = hitPos.y - m_pos.y;
	float dz = hitPos.z - m_pos.z;

	float dr = m_radius + sphere.GetRadius();

	return dx * dx + dy * dy + dz * dz <= dr * dr ? true : false;
}

//==============================================================================
// 関数名 : VECTOR3 GetDent( CCollider3D& collider , float rate )
// 引数   : CCollider3DSphere& sphere : 球当たり判定オブジェクト
//          float rate                : 割合( 0～1 )
// 戻り値 : VECTOR3型                 : 判定位置からのめり込み量をベクトルで返却
// 説明   : めり込みベクトル取得処理( 対球 )
//==============================================================================
inline VECTOR3 CCollider3DSphere::GetDent( CCollider3DSphere& sphere , float rate )
{
	// めり込み距離を算出
	D3DXVECTOR3 vBetween;				// 当たり判定間のベクトル
	
	VECTOR3 spherePos = sphere.GetPos();

	vBetween.x = m_pos.x - spherePos.x;
	vBetween.y = m_pos.y - spherePos.y;
	vBetween.z = m_pos.z - spherePos.z;

	float lenBetween = D3DXVec3Length( &D3DXVECTOR3( vBetween.x , vBetween.y , vBetween.z ) );			// 当たり判定間のベクトル長
	float lenAll     = m_radius + sphere.GetRadius();		// 合計の長さ
	float lenDent    = lenAll - lenBetween;					// めり込み距離

	// めり込みベクトルを返却
	D3DXVECTOR3 vDir;											// 方向ベクトル
	D3DXVec3Normalize( &vDir , &vBetween );

	D3DXVECTOR3 vDent = vDir * ( lenDent * rate );
	return VECTOR3( vDent.x , vDent.y , vDent.z );
}

//==============================================================================
// 関数名 : サンプル
// 引数   : void
// 戻り値 : void
// 説明   : サンプル処理
//==============================================================================
