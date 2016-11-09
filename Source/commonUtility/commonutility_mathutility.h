//==============================================================================
// タイトル     :   数学系ライブラリ
// ファイル名   :   commonUtility_mathUtility.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/15
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/15 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================
#define PI	( 3.141592654f )								// 円周率
#define PI2	( PI * 2 )										// 円周率の2倍値

#define DegToRad( deg )	( ( deg ) * ( PI / 180.0f ) )		// 角度をラジアン角に変換
#define RadToDeg( rad )	( ( rad ) * ( 180.0f / PI ) )		// ラジアン角を角度に変換

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================

//==============================================================================
// 前方宣言
//==============================================================================
class VECTOR3;
class MATRIX;
class QUATERNION;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
// 3次元ベクトル
VECTOR3* Vec3Normalize( VECTOR3* pOut , VECTOR3* pV );
float Vec3Length( VECTOR3* pV );
float Vec3LengthSq( VECTOR3* pV );
float Vec3Dot( VECTOR3* pV1 , VECTOR3* pV2 );
VECTOR3* Vec3Cross( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 );
VECTOR3* Vec3Add( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 );
VECTOR3* Vec3Subtract( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 );
VECTOR3* Vec3TransformCoord( VECTOR3 *pOut , VECTOR3 *pV , MATRIX *pM );

// 行列系
MATRIX* MatrixIdentity( MATRIX* pOut );
MATRIX* MatrixMultiply( MATRIX* pOut , MATRIX *pM1 , MATRIX *pM2 );
MATRIX* MatrixScaling( MATRIX *pOut , float sx , float sy , float sz );
MATRIX* MatrixTranslation( MATRIX *pOut , float x , float y , float z );
MATRIX* MatrixRotationX( MATRIX *pOut , float angle );
MATRIX* MatrixRotationY( MATRIX *pOut , float angle );
MATRIX* MatrixRotationZ( MATRIX *pOut , float angle );
MATRIX* MatrixRotationYawPitchRoll( MATRIX *pOut , float Yaw , float Pitch , float Roll );
MATRIX* MatrixRotationQuaternion( MATRIX* pOut , QUATERNION* pQ );

// クォータニオン系
QUATERNION* QuaternionIdentity( QUATERNION* pOut );
QUATERNION* QuaternionRotationAxis( QUATERNION* pOut , VECTOR3* pAxis , float angle );
QUATERNION* QuaternionMultiply( QUATERNION* pOut , QUATERNION* pQ1 , QUATERNION* pQ2 );
float QuaternionDot( QUATERNION* pQ1 , QUATERNION* pQ2 );
QUATERNION* QuaternionSlerp( QUATERNION* pRes , QUATERNION* pFrom , QUATERNION* pTo , float t );
