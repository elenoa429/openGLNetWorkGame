//==============================================================================
// �^�C�g��     :   ���w�n���C�u����
// �t�@�C����   :   commonUtility_mathUtility.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/15
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/15 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
#define PI	( 3.141592654f )								// �~����
#define PI2	( PI * 2 )										// �~������2�{�l

#define DegToRad( deg )	( ( deg ) * ( PI / 180.0f ) )		// �p�x�����W�A���p�ɕϊ�
#define RadToDeg( rad )	( ( rad ) * ( 180.0f / PI ) )		// ���W�A���p���p�x�ɕϊ�

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �N���X�錾
//==============================================================================

//==============================================================================
// �O���錾
//==============================================================================
class VECTOR3;
class MATRIX;
class QUATERNION;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
// 3�����x�N�g��
VECTOR3* Vec3Normalize( VECTOR3* pOut , VECTOR3* pV );
float Vec3Length( VECTOR3* pV );
float Vec3LengthSq( VECTOR3* pV );
float Vec3Dot( VECTOR3* pV1 , VECTOR3* pV2 );
VECTOR3* Vec3Cross( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 );
VECTOR3* Vec3Add( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 );
VECTOR3* Vec3Subtract( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 );
VECTOR3* Vec3TransformCoord( VECTOR3 *pOut , VECTOR3 *pV , MATRIX *pM );

// �s��n
MATRIX* MatrixIdentity( MATRIX* pOut );
MATRIX* MatrixMultiply( MATRIX* pOut , MATRIX *pM1 , MATRIX *pM2 );
MATRIX* MatrixScaling( MATRIX *pOut , float sx , float sy , float sz );
MATRIX* MatrixTranslation( MATRIX *pOut , float x , float y , float z );
MATRIX* MatrixRotationX( MATRIX *pOut , float angle );
MATRIX* MatrixRotationY( MATRIX *pOut , float angle );
MATRIX* MatrixRotationZ( MATRIX *pOut , float angle );
MATRIX* MatrixRotationYawPitchRoll( MATRIX *pOut , float Yaw , float Pitch , float Roll );
MATRIX* MatrixRotationQuaternion( MATRIX* pOut , QUATERNION* pQ );

// �N�H�[�^�j�I���n
QUATERNION* QuaternionIdentity( QUATERNION* pOut );
QUATERNION* QuaternionRotationAxis( QUATERNION* pOut , VECTOR3* pAxis , float angle );
QUATERNION* QuaternionMultiply( QUATERNION* pOut , QUATERNION* pQ1 , QUATERNION* pQ2 );
float QuaternionDot( QUATERNION* pQ1 , QUATERNION* pQ2 );
QUATERNION* QuaternionSlerp( QUATERNION* pRes , QUATERNION* pFrom , QUATERNION* pTo , float t );
