//==============================================================================
// タイトル     :   数学系ライブラリ
// ファイル名   :   commonUtility.mathUtility.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/15
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/15 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "commonutility_mathutility.h"
#include "commonUtility_vector3.h"
#include "commonUtility_matrix.h"
#include "commonUtility_quaternion.h"
#include <math.h>

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
// 関数名 : VECTOR3* Vec3Normalize( VECTOR3* pOut , VECTOR3* pV )
// 引数   : MATRIX* pOut : 出力先
//          VECTOR3* pV  : 対象のベクトル
// 戻り値 : VECTOR3*型   : 算出した値の返却
// 説明   : 単位ベクトル化処理
//==============================================================================
VECTOR3* Vec3Normalize( VECTOR3* pOut , VECTOR3* pV )
{
	float norm;		// 対象のベクトルの長さ

	norm = Vec3Length( pV );

	if ( !norm )
	{
		pOut->x = 0.0f;
		pOut->y = 0.0f;
		pOut->z = 0.0f;
	}
	else
	{
		pOut->x = pV->x / norm;
		pOut->y = pV->y / norm;
		pOut->z = pV->z / norm;
	}

	return pOut;
}

//==============================================================================
// 関数名 : float Vec3Length( VECTOR3* pV )
// 引数   : VECTOR3* pV : 対象のベクトル
// 戻り値 : float型     : 算出した長さを返却
// 説明   : 3次元ベクトルの長さ算出関数
//==============================================================================
float Vec3Length( VECTOR3* pV )
{
	return sqrtf( pV->x * pV->x + pV->y * pV->y + pV->z * pV->z );
}

//==============================================================================
// 関数名 : float Vec3LengthSq( VECTOR3* pV )
// 引数   : VECTOR3* pV : 対象のベクトル
// 戻り値 : float型     : 算出した長さの二乗を返却
// 説明   : 3次元ベクトルの長さの二乗値算出関数
//==============================================================================
float Vec3LengthSq( VECTOR3* pV )
{
	return pV->x * pV->x + pV->y * pV->y + pV->z * pV->z;
}

//==============================================================================
// 関数名 : float Vec3Dot( VECTOR3* pV1 , VECTOR3* pV2 )
// 引数   : VECTOR3* pV1 : 対象1
//          VECTOR3* pV2 : 対象2
// 戻り値 : float型      : 算出したスカラー値返却
// 説明   : 3次元ベクトルの内積処理関数
//==============================================================================
float Vec3Dot( VECTOR3* pV1 , VECTOR3* pV2 )
{
	float scalar = 0.0f;

	scalar = pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;

	return scalar;
}

//==============================================================================
// 関数名 : VECTOR3* Vec3Cross( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
// 引数   : VECTOR3 *pOut : 出力先
//          VECTOR3* pV1  : 対象1
//          VECTOR3* pV2  : 対象2
// 戻り値 : VECTOR3*型
// 説明   : 3次元ベクトルの外積処理関数
//==============================================================================
VECTOR3* Vec3Cross( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
{
	pOut->x = pV1->y * pV2->z - pV1->z * pV2->y;
	pOut->y = pV1->z * pV2->x - pV1->x * pV2->z;
	pOut->z = pV1->x * pV2->y - pV1->y * pV2->x;

	return pOut;
}

//==============================================================================
// 関数名 : VECTOR3* Vec3Add( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
// 引数   : VECTOR3 *pOut : 出力先
//          VECTOR3* pV1  : 対象1
//          VECTOR3* pV2  : 対象2
// 戻り値 : VECTOR3*型
// 説明   : 3次元ベクトルの加算処理関数
//==============================================================================
VECTOR3* Vec3Add( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
{
	pOut->x = pV1->x + pV2->x;
	pOut->y = pV1->y + pV2->y;
	pOut->z = pV1->z + pV2->z;

	return pOut;
}

//==============================================================================
// 関数名 : VECTOR3* Vec3Subtract( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
// 引数   : VECTOR3 *pOut : 出力先
//          VECTOR3* pV1  : 対象1
//          VECTOR3* pV2  : 対象2
// 戻り値 : VECTOR3*型
// 説明   : 3次元ベクトルの減算処理関数
//==============================================================================
VECTOR3* Vec3Subtract( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
{
	pOut->x = pV1->x - pV2->x;
	pOut->y = pV1->y - pV2->y;
	pOut->z = pV1->z - pV2->z;

	return pOut;
}

//==============================================================================
// 関数名 : VECTOR3* Vec3TransformCoord( VECTOR3 *pOut , VECTOR3 *pV , MATRIX *pM )
// 引数   : VECTOR3 *pOut : 出力先
//          VECTOR3 *pV   : 変換対象のベクトル
//          MATRIX *pM    : 変換用行列
// 戻り値 : VECTOR3*型
// 説明   : 3次元ベクトルの行列変換処理関数
//==============================================================================
VECTOR3* Vec3TransformCoord( VECTOR3 *pOut , VECTOR3 *pV , MATRIX *pM )
{
	VECTOR3 out;
	float norm;

	norm = pM->m44[ 0 ][ 3 ] * pV->x + pM->m44[ 1 ][ 3 ] * pV->y + pM->m44[ 2 ][ 3 ] * pV->z + pM->m44[ 3 ][ 3 ];

	out.x = ( pM->m44[ 0 ][ 0 ] * pV->x + pM->m44[ 1 ][ 0 ] * pV->y + pM->m44[ 2 ][ 0 ] * pV->z + pM->m44[ 3 ][ 0 ] ) / norm;
	out.y = ( pM->m44[ 0 ][ 1 ] * pV->x + pM->m44[ 1 ][ 1 ] * pV->y + pM->m44[ 2 ][ 1 ] * pV->z + pM->m44[ 3 ][ 1 ] ) / norm;
	out.z = ( pM->m44[ 0 ][ 2 ] * pV->x + pM->m44[ 1 ][ 2 ] * pV->y + pM->m44[ 2 ][ 2 ] * pV->z + pM->m44[ 3 ][ 2 ] ) / norm;

	*pOut = out;

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixIdentity( MATRIX* pOut )
// 引数   : MATRIX* pOut : 出力先行列
// 戻り値 : MATRIX*型
// 説明   : 単位行列化処理
//==============================================================================
MATRIX* MatrixIdentity( MATRIX* pOut )
{
	pOut->_12 = pOut->_13 = pOut->_14 =
	pOut->_21 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_34 =
	pOut->_41 = pOut->_42 = pOut->_43 = 0.0f;

	pOut->_11 = pOut->_22 = pOut->_33 = pOut->_44 = 1.0f;

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixMultiply( MATRIX* pOut , MATRIX *pM1 , MATRIX *pM2 )
// 引数   : MATRIX* pOut              : 出力先行列
//          MATRIX *pM1 , MATRIX *pM2 : 合成するマトリクス
// 戻り値 : MATRIX*型
// 説明   : 行列合成処理
//==============================================================================
MATRIX* MatrixMultiply( MATRIX* pOut , MATRIX *pM1 , MATRIX *pM2 )
{
	//------------------------------------
	// [ 行列合成計算 ]
	//------------------------------------
	MATRIX mtxMulti;		// 計算結果格納用ワーク

	mtxMulti._11 = pM1->_11 * pM2->_11 + pM1->_12 * pM2->_21 + pM1->_13 * pM2->_31 + pM1->_14 * pM2->_41;
	mtxMulti._12 = pM1->_11 * pM2->_12 + pM1->_12 * pM2->_22 + pM1->_13 * pM2->_32 + pM1->_14 * pM2->_42;
	mtxMulti._13 = pM1->_11 * pM2->_13 + pM1->_12 * pM2->_23 + pM1->_13 * pM2->_33 + pM1->_14 * pM2->_43;
	mtxMulti._14 = pM1->_11 * pM2->_14 + pM1->_12 * pM2->_24 + pM1->_13 * pM2->_34 + pM1->_14 * pM2->_44;

	mtxMulti._21 = pM1->_21 * pM2->_11 + pM1->_22 * pM2->_21 + pM1->_23 * pM2->_31 + pM1->_24 * pM2->_41;
	mtxMulti._22 = pM1->_21 * pM2->_12 + pM1->_22 * pM2->_22 + pM1->_23 * pM2->_32 + pM1->_24 * pM2->_42;
	mtxMulti._23 = pM1->_21 * pM2->_13 + pM1->_22 * pM2->_23 + pM1->_23 * pM2->_33 + pM1->_24 * pM2->_43;
	mtxMulti._24 = pM1->_21 * pM2->_14 + pM1->_22 * pM2->_24 + pM1->_23 * pM2->_34 + pM1->_24 * pM2->_44;

	mtxMulti._31 = pM1->_31 * pM2->_11 + pM1->_32 * pM2->_21 + pM1->_33 * pM2->_31 + pM1->_34 * pM2->_41;
	mtxMulti._32 = pM1->_31 * pM2->_12 + pM1->_32 * pM2->_22 + pM1->_33 * pM2->_32 + pM1->_34 * pM2->_42;
	mtxMulti._33 = pM1->_31 * pM2->_13 + pM1->_32 * pM2->_23 + pM1->_33 * pM2->_33 + pM1->_34 * pM2->_43;
	mtxMulti._34 = pM1->_31 * pM2->_14 + pM1->_32 * pM2->_24 + pM1->_33 * pM2->_34 + pM1->_34 * pM2->_44;

	mtxMulti._41 = pM1->_41 * pM2->_11 + pM1->_42 * pM2->_21 + pM1->_43 * pM2->_31 + pM1->_44 * pM2->_41;
	mtxMulti._42 = pM1->_41 * pM2->_12 + pM1->_42 * pM2->_22 + pM1->_43 * pM2->_32 + pM1->_44 * pM2->_42;
	mtxMulti._43 = pM1->_41 * pM2->_13 + pM1->_42 * pM2->_23 + pM1->_43 * pM2->_33 + pM1->_44 * pM2->_43;
	mtxMulti._44 = pM1->_41 * pM2->_14 + pM1->_42 * pM2->_24 + pM1->_43 * pM2->_34 + pM1->_44 * pM2->_44;

	//------------------------------------
	// [ 計算結果の格納 ]
	//------------------------------------
	pOut->_11 = mtxMulti._11;
	pOut->_12 = mtxMulti._12;
	pOut->_13 = mtxMulti._13;
	pOut->_14 = mtxMulti._14;

	pOut->_21 = mtxMulti._21;
	pOut->_22 = mtxMulti._22;
	pOut->_23 = mtxMulti._23;
	pOut->_24 = mtxMulti._24;

	pOut->_31 = mtxMulti._31;
	pOut->_32 = mtxMulti._32;
	pOut->_33 = mtxMulti._33;
	pOut->_34 = mtxMulti._34;

	pOut->_41 = mtxMulti._41;
	pOut->_42 = mtxMulti._42;
	pOut->_43 = mtxMulti._43;
	pOut->_44 = mtxMulti._44;

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixScaling( MATRIX *pOut , float sx , float sy , float sz )
// 引数   : MATRIX *pOut
//          float sx , float sy , float sz
// 戻り値 : MATRIX*型
// 説明   : スケール行列計算処理
//==============================================================================
MATRIX* MatrixScaling( MATRIX *pOut , float sx , float sy , float sz )
{
	pOut->_12 = pOut->_13 = pOut->_14 =
	pOut->_21 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_34 =
	pOut->_41 = pOut->_42 = pOut->_43 = 0.0f;

	pOut->_11 = sx;
	pOut->_22 = sy;
	pOut->_33 = sz;
	pOut->_44 = 1.0f;

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixTranslation( MATRIX *pOut , float x , float y , float z )
// 引数   : MATRIX *pOut
//          float x , float y , float z
// 戻り値 : MATRIX*型
// 説明   : 位置行列計算処理
//==============================================================================
MATRIX* MatrixTranslation( MATRIX *pOut , float x , float y , float z )
{
	pOut->_12 = pOut->_13 = pOut->_14 = 
	pOut->_21 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_34 = 0.0f;

	pOut->_11 = 1.0f;
	pOut->_22 = 1.0f;
	pOut->_33 = 1.0f;
	pOut->_44 = 1.0f;

	pOut->_41 = x;
	pOut->_42 = y;
	pOut->_43 = z;

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixRotationX( MATRIX *pOut , float angle )
// 引数   : MATRIX *pOut
//          float angle
// 戻り値 : MATRIX*型
// 説明   : X軸回転行列計算処理
//==============================================================================
MATRIX* MatrixRotationX( MATRIX *pOut , float angle )
{
	pOut->_11 = pOut->_12 = pOut->_13 = pOut->_14 =
	pOut->_21 = pOut->_22 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_33 = pOut->_34 =
	pOut->_41 = pOut->_42 = pOut->_43 = pOut->_44 = 0.0f;

	pOut->_11 = 1.0f;
	pOut->_44 = 1.0f;

	pOut->_22 = cosf( angle );
	pOut->_23 = sinf( angle );
	pOut->_32 = -sinf( angle );
	pOut->_33 = cosf( angle );

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixRotationY( MATRIX *pOut , float angle )
// 引数   : MATRIX *pOut
//          float angle
// 戻り値 : MATRIX*型
// 説明   : Y軸回転行列計算処理
//==============================================================================
MATRIX* MatrixRotationY( MATRIX *pOut , float angle )
{
	pOut->_11 = pOut->_12 = pOut->_13 = pOut->_14 =
	pOut->_21 = pOut->_22 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_33 = pOut->_34 =
	pOut->_41 = pOut->_42 = pOut->_43 = pOut->_44 = 0.0f;

	pOut->_22 = 1.0f;
	pOut->_44 = 1.0f;

	pOut->_11 = cosf( angle );
	pOut->_13 = -sinf( angle );
	pOut->_31 = sinf( angle );
	pOut->_33 = cosf( angle );

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixRotationZ( MATRIX *pOut , float angle )
// 引数   : MATRIX *pOut
//          float angle
// 戻り値 : MATRIX*型
// 説明   : Z軸回転行列計算処理
//==============================================================================
MATRIX* MatrixRotationZ( MATRIX *pOut , float angle )
{
	pOut->_11 = pOut->_12 = pOut->_13 = pOut->_14 =
	pOut->_21 = pOut->_22 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_33 = pOut->_34 =
	pOut->_41 = pOut->_42 = pOut->_43 = pOut->_44 = 0.0f;

	pOut->_33 = 1.0f;
	pOut->_44 = 1.0f;

	pOut->_11 = cosf( angle );
	pOut->_12 = sinf( angle );
	pOut->_21 = -sinf( angle );
	pOut->_22 = cosf( angle );

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixRotationYawPitchRoll( MATRIX *pOut , float Yaw , float Pitch , float Roll )
// 引数   : MATRIX *pOut : 出力先
//          float Yaw    : ヨー角( Y軸 )
//          float Pitch  : ピッチ角( X軸 )
//          float Roll   : ロー角( Z軸 )
// 戻り値 : MATRIX*型
// 説明   : ヨー・ピッチ・ロール回転行列計算処理
//==============================================================================
MATRIX* MatrixRotationYawPitchRoll( MATRIX *pOut , float Yaw , float Pitch , float Roll )
{
	MATRIX x , y , z;

	MatrixRotationX( &x , Pitch );
	MatrixRotationY( &y , Yaw );
	MatrixRotationZ( &z , Roll );

	*pOut = z * x * y;

	return pOut;
}

//==============================================================================
// 関数名 : MATRIX* MatrixRotationQuaternion( MATRIX* pOut , QUATERNION* pQ )
// 引数   : MATRIX* pOut   : 出力先
//          QUATERNION* pQ : 対象
// 戻り値 : QUATERNION*型
// 説明   : クォータニオン回転行列出力処理
//==============================================================================
MATRIX* MatrixRotationQuaternion( MATRIX* pOut , QUATERNION* pQ )
{
	return pOut;
}

//==============================================================================
// 関数名 : QUATERNION* QuaternionIdentity( QUATERNION* pOut )
// 引数   : QUATERNION* pOut : 出力先
// 戻り値 : QUATERNION*型
// 説明   : クォータニオン単位化処理
//==============================================================================
QUATERNION* QuaternionIdentity( QUATERNION* pOut )
{
	// 単位化
	pOut->x = 0.0f;
	pOut->y = 0.0f;
	pOut->z = 0.0f;
	pOut->w = 1.0f;

	return pOut;
}

//==============================================================================
// 関数名 : QUATERNION* QuaternionRotationAxis( QUATERNION* pOut , VECTOR3* pAxis , float angle )
// 引数   : QUATERNION* pOut : 回転させたいクォータニオン
//          VECTOR3* pAxis   : 軸方向ベクトル
//          float angle      : ラジアン角
// 戻り値 : QUATERNION*型
// 説明   : 任意軸回転なクォータニオン取得処理
//==============================================================================
QUATERNION* QuaternionRotationAxis( QUATERNION* pOut , VECTOR3* pAxis , float angle )
{
	// 軸回転クォータニオンを生成
	QUATERNION rot1;				// 四元数
	QUATERNION rot2;				// 共役四元数
	float theta = angle / 2.0f;		// θ

	rot1.x = pAxis->x * sinf( theta );
	rot1.y = pAxis->y * sinf( theta );
	rot1.z = pAxis->z * sinf( theta );
	rot1.w = cosf( theta );

	rot2.x = -pAxis->x * sinf( theta );
	rot2.y = -pAxis->y * sinf( theta );
	rot2.z = -pAxis->z * sinf( theta );
	rot2.w = cosf( theta );

	// 合成
	QuaternionMultiply( pOut , &rot2 , pOut );
	QuaternionMultiply( pOut , pOut , &rot1 );

	return pOut;
}

//==============================================================================
// 関数名 : QUATERNION* QuaternionMultiply( QUATERNION* pOut , QUATERNION* pQ1 , QUATERNION* pQ2 )
// 引数   : QUATERNION* pOut : 出力先
//          QUATERNION* pQ1  : 対象1
//          QUATERNION* pQ2  : 対象2
// 戻り値 : QUATERNION*型
// 説明   : クォータニオン合成処理
//==============================================================================
QUATERNION* QuaternionMultiply( QUATERNION* pOut , QUATERNION* pQ1 , QUATERNION* pQ2 )
{
	// 合成に必要な要素を準備
	VECTOR3 v1 = VECTOR3( pQ1->x , pQ1->y , pQ1->z );		// Q1の虚数部
	VECTOR3 v2 = VECTOR3( pQ2->x , pQ2->y , pQ2->z );		// Q2の虚数部
	VECTOR3 vc;												// 虚数部のクロス積

	Vec3Cross( &vc , &v1 , &v2 );

	// クォータニオンを合成
	pOut->w = pQ1->w * pQ2->w - ( Vec3Dot( &v1 , &v2 ) );

	pOut->x = pQ1->w * pQ2->x + pQ2->w * pQ1->x + vc.x;
	pOut->y = pQ1->w * pQ2->y + pQ2->w * pQ1->y + vc.y;
	pOut->z = pQ1->w * pQ2->z + pQ2->w * pQ1->z + vc.z;

	return pOut;
}

//==============================================================================
// 関数名 : float QuaternionDot( QUATERNION* pQ1 , QUATERNION* pQ2 )
// 引数   : QUATERNION* pQ1 : 対象1
//          QUATERNION* pQ2 : 対象2
// 戻り値 : float型
// 説明   : クォータニオンの内積算出処理
//==============================================================================
float QuaternionDot( QUATERNION* pQ1 , QUATERNION* pQ2 )
{
	float scalar = 0.0f;

	scalar = pQ1->x * pQ2->x + pQ1->y * pQ2->y + pQ1->z * pQ2->z + pQ1->w * pQ2->w;

	return scalar;
}

//==============================================================================
// 関数名 : QUATERNION* QuaternionSlerp( QUATERNION* pRes , QUATERNION* pFrom , QUATERNION* pTo , float t )
// 引数   : QUATERNION* pRes  : 媒介変数が示すクォータニオン
//          QUATERNION* pFrom : 『t=0』の時に示すクォータニオン
//          QUATERNION* pTo   : 『t=1』の時に示すクォータニオン
//          float t           : 媒介変数( 0.0 ～ 1.0 )
// 戻り値 : QUATERNION*型
// 説明   : クォータニオンの球面線形補間処理
//==============================================================================
QUATERNION* QuaternionSlerp( QUATERNION* pRes , QUATERNION* pFrom , QUATERNION* pTo , float t )
{
	// 球面線形補間処理
	float theta = acosf( QuaternionDot( pFrom , pTo ) );	// 球面上のθ値

	float t0 = sinf( theta * ( 1.0f - t ) );				// Fromにかかる重み
	float t1 = sinf( theta * t );							// Toにかかる重み

	pRes->x = pFrom->x * t0 + pTo->x * t1;
	pRes->y = pFrom->y * t0 + pTo->y * t1;
	pRes->z = pFrom->z * t0 + pTo->z * t1;
	pRes->w = pFrom->w * t0 + pTo->w * t1;

	return pRes;
}
