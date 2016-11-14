//==============================================================================
// �^�C�g��     :   ���w�n���C�u����
// �t�@�C����   :   commonUtility.mathUtility.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/15
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/15 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "commonutility_mathutility.h"
#include "commonUtility_vector3.h"
#include "commonUtility_matrix.h"
#include "commonUtility_quaternion.h"
#include <math.h>

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================

//==============================================================================
// �O���[�o���錾
//==============================================================================

//==============================================================================
// �֐��� : VECTOR3* Vec3Normalize( VECTOR3* pOut , VECTOR3* pV )
// ����   : MATRIX* pOut : �o�͐�
//          VECTOR3* pV  : �Ώۂ̃x�N�g��
// �߂�l : VECTOR3*�^   : �Z�o�����l�̕ԋp
// ����   : �P�ʃx�N�g��������
//==============================================================================
VECTOR3* Vec3Normalize( VECTOR3* pOut , VECTOR3* pV )
{
	float norm;		// �Ώۂ̃x�N�g���̒���

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
// �֐��� : float Vec3Length( VECTOR3* pV )
// ����   : VECTOR3* pV : �Ώۂ̃x�N�g��
// �߂�l : float�^     : �Z�o����������ԋp
// ����   : 3�����x�N�g���̒����Z�o�֐�
//==============================================================================
float Vec3Length( VECTOR3* pV )
{
	return sqrtf( pV->x * pV->x + pV->y * pV->y + pV->z * pV->z );
}

//==============================================================================
// �֐��� : float Vec3LengthSq( VECTOR3* pV )
// ����   : VECTOR3* pV : �Ώۂ̃x�N�g��
// �߂�l : float�^     : �Z�o���������̓���ԋp
// ����   : 3�����x�N�g���̒����̓��l�Z�o�֐�
//==============================================================================
float Vec3LengthSq( VECTOR3* pV )
{
	return pV->x * pV->x + pV->y * pV->y + pV->z * pV->z;
}

//==============================================================================
// �֐��� : float Vec3Dot( VECTOR3* pV1 , VECTOR3* pV2 )
// ����   : VECTOR3* pV1 : �Ώ�1
//          VECTOR3* pV2 : �Ώ�2
// �߂�l : float�^      : �Z�o�����X�J���[�l�ԋp
// ����   : 3�����x�N�g���̓��Ϗ����֐�
//==============================================================================
float Vec3Dot( VECTOR3* pV1 , VECTOR3* pV2 )
{
	float scalar = 0.0f;

	scalar = pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z;

	return scalar;
}

//==============================================================================
// �֐��� : VECTOR3* Vec3Cross( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
// ����   : VECTOR3 *pOut : �o�͐�
//          VECTOR3* pV1  : �Ώ�1
//          VECTOR3* pV2  : �Ώ�2
// �߂�l : VECTOR3*�^
// ����   : 3�����x�N�g���̊O�Ϗ����֐�
//==============================================================================
VECTOR3* Vec3Cross( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
{
	pOut->x = pV1->y * pV2->z - pV1->z * pV2->y;
	pOut->y = pV1->z * pV2->x - pV1->x * pV2->z;
	pOut->z = pV1->x * pV2->y - pV1->y * pV2->x;

	return pOut;
}

//==============================================================================
// �֐��� : VECTOR3* Vec3Add( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
// ����   : VECTOR3 *pOut : �o�͐�
//          VECTOR3* pV1  : �Ώ�1
//          VECTOR3* pV2  : �Ώ�2
// �߂�l : VECTOR3*�^
// ����   : 3�����x�N�g���̉��Z�����֐�
//==============================================================================
VECTOR3* Vec3Add( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
{
	pOut->x = pV1->x + pV2->x;
	pOut->y = pV1->y + pV2->y;
	pOut->z = pV1->z + pV2->z;

	return pOut;
}

//==============================================================================
// �֐��� : VECTOR3* Vec3Subtract( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
// ����   : VECTOR3 *pOut : �o�͐�
//          VECTOR3* pV1  : �Ώ�1
//          VECTOR3* pV2  : �Ώ�2
// �߂�l : VECTOR3*�^
// ����   : 3�����x�N�g���̌��Z�����֐�
//==============================================================================
VECTOR3* Vec3Subtract( VECTOR3 *pOut , VECTOR3 *pV1 , VECTOR3 *pV2 )
{
	pOut->x = pV1->x - pV2->x;
	pOut->y = pV1->y - pV2->y;
	pOut->z = pV1->z - pV2->z;

	return pOut;
}

//==============================================================================
// �֐��� : VECTOR3* Vec3TransformCoord( VECTOR3 *pOut , VECTOR3 *pV , MATRIX *pM )
// ����   : VECTOR3 *pOut : �o�͐�
//          VECTOR3 *pV   : �ϊ��Ώۂ̃x�N�g��
//          MATRIX *pM    : �ϊ��p�s��
// �߂�l : VECTOR3*�^
// ����   : 3�����x�N�g���̍s��ϊ������֐�
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
// �֐��� : MATRIX* MatrixIdentity( MATRIX* pOut )
// ����   : MATRIX* pOut : �o�͐�s��
// �߂�l : MATRIX*�^
// ����   : �P�ʍs�񉻏���
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
// �֐��� : MATRIX* MatrixMultiply( MATRIX* pOut , MATRIX *pM1 , MATRIX *pM2 )
// ����   : MATRIX* pOut              : �o�͐�s��
//          MATRIX *pM1 , MATRIX *pM2 : ��������}�g���N�X
// �߂�l : MATRIX*�^
// ����   : �s�񍇐�����
//==============================================================================
MATRIX* MatrixMultiply( MATRIX* pOut , MATRIX *pM1 , MATRIX *pM2 )
{
	//------------------------------------
	// [ �s�񍇐��v�Z ]
	//------------------------------------
	MATRIX mtxMulti;		// �v�Z���ʊi�[�p���[�N

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
	// [ �v�Z���ʂ̊i�[ ]
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
// �֐��� : MATRIX* MatrixScaling( MATRIX *pOut , float sx , float sy , float sz )
// ����   : MATRIX *pOut
//          float sx , float sy , float sz
// �߂�l : MATRIX*�^
// ����   : �X�P�[���s��v�Z����
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
// �֐��� : MATRIX* MatrixTranslation( MATRIX *pOut , float x , float y , float z )
// ����   : MATRIX *pOut
//          float x , float y , float z
// �߂�l : MATRIX*�^
// ����   : �ʒu�s��v�Z����
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
// �֐��� : MATRIX* MatrixRotationX( MATRIX *pOut , float angle )
// ����   : MATRIX *pOut
//          float angle
// �߂�l : MATRIX*�^
// ����   : X����]�s��v�Z����
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
// �֐��� : MATRIX* MatrixRotationY( MATRIX *pOut , float angle )
// ����   : MATRIX *pOut
//          float angle
// �߂�l : MATRIX*�^
// ����   : Y����]�s��v�Z����
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
// �֐��� : MATRIX* MatrixRotationZ( MATRIX *pOut , float angle )
// ����   : MATRIX *pOut
//          float angle
// �߂�l : MATRIX*�^
// ����   : Z����]�s��v�Z����
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
// �֐��� : MATRIX* MatrixRotationYawPitchRoll( MATRIX *pOut , float Yaw , float Pitch , float Roll )
// ����   : MATRIX *pOut : �o�͐�
//          float Yaw    : ���[�p( Y�� )
//          float Pitch  : �s�b�`�p( X�� )
//          float Roll   : ���[�p( Z�� )
// �߂�l : MATRIX*�^
// ����   : ���[�E�s�b�`�E���[����]�s��v�Z����
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
// �֐��� : MATRIX* MatrixRotationQuaternion( MATRIX* pOut , QUATERNION* pQ )
// ����   : MATRIX* pOut   : �o�͐�
//          QUATERNION* pQ : �Ώ�
// �߂�l : QUATERNION*�^
// ����   : �N�H�[�^�j�I����]�s��o�͏���
//==============================================================================
MATRIX* MatrixRotationQuaternion( MATRIX* pOut , QUATERNION* pQ )
{
	return pOut;
}

//==============================================================================
// �֐��� : QUATERNION* QuaternionIdentity( QUATERNION* pOut )
// ����   : QUATERNION* pOut : �o�͐�
// �߂�l : QUATERNION*�^
// ����   : �N�H�[�^�j�I���P�ʉ�����
//==============================================================================
QUATERNION* QuaternionIdentity( QUATERNION* pOut )
{
	// �P�ʉ�
	pOut->x = 0.0f;
	pOut->y = 0.0f;
	pOut->z = 0.0f;
	pOut->w = 1.0f;

	return pOut;
}

//==============================================================================
// �֐��� : QUATERNION* QuaternionRotationAxis( QUATERNION* pOut , VECTOR3* pAxis , float angle )
// ����   : QUATERNION* pOut : ��]���������N�H�[�^�j�I��
//          VECTOR3* pAxis   : �������x�N�g��
//          float angle      : ���W�A���p
// �߂�l : QUATERNION*�^
// ����   : �C�ӎ���]�ȃN�H�[�^�j�I���擾����
//==============================================================================
QUATERNION* QuaternionRotationAxis( QUATERNION* pOut , VECTOR3* pAxis , float angle )
{
	// ����]�N�H�[�^�j�I���𐶐�
	QUATERNION rot1;				// �l����
	QUATERNION rot2;				// �����l����
	float theta = angle / 2.0f;		// ��

	rot1.x = pAxis->x * sinf( theta );
	rot1.y = pAxis->y * sinf( theta );
	rot1.z = pAxis->z * sinf( theta );
	rot1.w = cosf( theta );

	rot2.x = -pAxis->x * sinf( theta );
	rot2.y = -pAxis->y * sinf( theta );
	rot2.z = -pAxis->z * sinf( theta );
	rot2.w = cosf( theta );

	// ����
	QuaternionMultiply( pOut , &rot2 , pOut );
	QuaternionMultiply( pOut , pOut , &rot1 );

	return pOut;
}

//==============================================================================
// �֐��� : QUATERNION* QuaternionMultiply( QUATERNION* pOut , QUATERNION* pQ1 , QUATERNION* pQ2 )
// ����   : QUATERNION* pOut : �o�͐�
//          QUATERNION* pQ1  : �Ώ�1
//          QUATERNION* pQ2  : �Ώ�2
// �߂�l : QUATERNION*�^
// ����   : �N�H�[�^�j�I����������
//==============================================================================
QUATERNION* QuaternionMultiply( QUATERNION* pOut , QUATERNION* pQ1 , QUATERNION* pQ2 )
{
	// �����ɕK�v�ȗv�f������
	VECTOR3 v1 = VECTOR3( pQ1->x , pQ1->y , pQ1->z );		// Q1�̋�����
	VECTOR3 v2 = VECTOR3( pQ2->x , pQ2->y , pQ2->z );		// Q2�̋�����
	VECTOR3 vc;												// �������̃N���X��

	Vec3Cross( &vc , &v1 , &v2 );

	// �N�H�[�^�j�I��������
	pOut->w = pQ1->w * pQ2->w - ( Vec3Dot( &v1 , &v2 ) );

	pOut->x = pQ1->w * pQ2->x + pQ2->w * pQ1->x + vc.x;
	pOut->y = pQ1->w * pQ2->y + pQ2->w * pQ1->y + vc.y;
	pOut->z = pQ1->w * pQ2->z + pQ2->w * pQ1->z + vc.z;

	return pOut;
}

//==============================================================================
// �֐��� : float QuaternionDot( QUATERNION* pQ1 , QUATERNION* pQ2 )
// ����   : QUATERNION* pQ1 : �Ώ�1
//          QUATERNION* pQ2 : �Ώ�2
// �߂�l : float�^
// ����   : �N�H�[�^�j�I���̓��ώZ�o����
//==============================================================================
float QuaternionDot( QUATERNION* pQ1 , QUATERNION* pQ2 )
{
	float scalar = 0.0f;

	scalar = pQ1->x * pQ2->x + pQ1->y * pQ2->y + pQ1->z * pQ2->z + pQ1->w * pQ2->w;

	return scalar;
}

//==============================================================================
// �֐��� : QUATERNION* QuaternionSlerp( QUATERNION* pRes , QUATERNION* pFrom , QUATERNION* pTo , float t )
// ����   : QUATERNION* pRes  : �}��ϐ��������N�H�[�^�j�I��
//          QUATERNION* pFrom : �wt=0�x�̎��Ɏ����N�H�[�^�j�I��
//          QUATERNION* pTo   : �wt=1�x�̎��Ɏ����N�H�[�^�j�I��
//          float t           : �}��ϐ�( 0.0 �` 1.0 )
// �߂�l : QUATERNION*�^
// ����   : �N�H�[�^�j�I���̋��ʐ��`��ԏ���
//==============================================================================
QUATERNION* QuaternionSlerp( QUATERNION* pRes , QUATERNION* pFrom , QUATERNION* pTo , float t )
{
	// ���ʐ��`��ԏ���
	float theta = acosf( QuaternionDot( pFrom , pTo ) );	// ���ʏ�̃ƒl

	float t0 = sinf( theta * ( 1.0f - t ) );				// From�ɂ�����d��
	float t1 = sinf( theta * t );							// To�ɂ�����d��

	pRes->x = pFrom->x * t0 + pTo->x * t1;
	pRes->y = pFrom->y * t0 + pTo->y * t1;
	pRes->z = pFrom->z * t0 + pTo->z * t1;
	pRes->w = pFrom->w * t0 + pTo->w * t1;

	return pRes;
}
