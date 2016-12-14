//==============================================================================
// �^�C�g��     :   3D:�������蔻��N���X
// �t�@�C����   :   collider3DSphere.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/11/29
//==============================================================================

//==============================================================================
// �X�V����: -2016/11/29 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "collider3DSphere.h"
#include "manager.h"
#include "main.h"

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================

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
// �ÓI�ϐ�
//==============================================================================

//==============================================================================
// �֐��� : CCollider3DSphere()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CCollider3DSphere::CCollider3DSphere()
{
	m_radius = 0.0f;
}

//==============================================================================
// �֐��� : ~CCollider3DSphere()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CCollider3DSphere::~CCollider3DSphere()
{

}

//==============================================================================
// �֐��� : CCollider3DSphere* Create( VECTOR3 pos , float radius )
// ����   : VECTOR3 pos  : ��ʒu
//          float radius : ���a
// �߂�l : CCollider3DSphere*�^
// ����   : ��������
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
// �֐��� : bool Init( VECTOR3 pos , float radius )
// ����   : VECTOR3 pos : ��ʒu
//          float radius    : ���a
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CCollider3DSphere::Init( VECTOR3 pos , float radius )
{
	if( CCollider3D::Init( "data\\MODEL\\colliedObj_sphere.x" ) == false )
	{
		return false;	// ���f���ǂݍ��ݎ��s
	}

	m_pos    = pos;
	m_radius = radius;

	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CCollider3DSphere::Uninit( void )
{
	CCollider3D::Uninit();
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CCollider3DSphere::Draw( void )
{
	// ----------------------------------------------------------------------
	// [ �f�o�C�X�擾 ]
	// ----------------------------------------------------------------------
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice()->m_pD3DDevice;
	//
	//// ----------------------------------------------------------------------
	//// [ ���[���h�}�g���b�N�X�̐������� ]
	//// ----------------------------------------------------------------------
	//Matrix mtxWorld , mtxScl , mtxRot , mtxTrans;								// �s��p���[�N
	//D3DXMatrixIdentity( &mtxWorld );											// �s�񏉊���
	//
	//D3DXMatrixScaling( &mtxScl , m_radius , m_radius , m_radius );				// �X�P�[���̍s����Z�o
	//D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxScl );						// �X�P�[���s��̍���
	//
	//D3DXMatrixRotationYawPitchRoll( &mtxRot , 0.0f , 0.0f , 0.0f );				// ��]�̍s����Z�o
	//D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxRot );						// ��]�s��̍���
	//
	//D3DXMatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );			// �ʒu�̍s����Z�o
	//D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxTrans );					// �ʒu�s��̍���
	//
	//pDevice->SetTransform( D3DTS_WORLD , &mtxWorld );							// �f�o�C�X�֔��f
	//
	//// ----------------------------------------------------------------------
	//// [ �`�揈�� ]
	//// ----------------------------------------------------------------------
	//CCollider3D::Draw();
}

//==============================================================================
// �֐��� : bool Collide( CCollider3D& collider )
// ����   : CCollider3D& collider : �����蔻��p�I�u�W�F�N�g
// �߂�l : bool�^
// ����   : �����蔻��m�F����
//==============================================================================
inline bool CCollider3DSphere::Collide( CCollider3D& collider )
{
	// �_�u���f�B�X�p�b�`�ɂ�铖���蔻��
	bool isHit = collider.Collide( *this );

	SetHitEffect( isHit );
	return isHit;
}

//==============================================================================
// �֐��� : VECTOR3 GetDent( CCollider3D& collider , float rate )
// ����   : CCollider3D& collider : �����蔻��p�I�u�W�F�N�g
//          float rate            : ����
// �߂�l : VECTOR3�^             : ����ʒu����̂߂荞�ݗʂ��x�N�g���ŕԋp
// ����   : �߂荞�݃x�N�g���擾����
//==============================================================================
inline VECTOR3 CCollider3DSphere::GetDent( CCollider3D& collider , float rate )
{
	// �_�u���f�B�X�p�b�`�ɂ�铖���蔻��
	return collider.GetDent( *this );
}

//==============================================================================
// �֐��� : bool Collide( CCollider3DSphere& sphere )
// ����   : CCollider3DSphere& sphere : ���I�u�W�F�N�g
// �߂�l : bool�^
// ����   : �����蔻�菈��( �΋� )
//==============================================================================
inline bool CCollider3DSphere::Collide( CCollider3DSphere& sphere )
{
	// ���΋��̔��菈��
	VECTOR3 hitPos = sphere.GetPos();

	float dx = hitPos.x - m_pos.x;
	float dy = hitPos.y - m_pos.y;
	float dz = hitPos.z - m_pos.z;

	float dr = m_radius + sphere.GetRadius();

	return dx * dx + dy * dy + dz * dz <= dr * dr ? true : false;
}

//==============================================================================
// �֐��� : VECTOR3 GetDent( CCollider3D& collider , float rate )
// ����   : CCollider3DSphere& sphere : �������蔻��I�u�W�F�N�g
//          float rate                : ����( 0�`1 )
// �߂�l : VECTOR3�^                 : ����ʒu����̂߂荞�ݗʂ��x�N�g���ŕԋp
// ����   : �߂荞�݃x�N�g���擾����( �΋� )
//==============================================================================
inline VECTOR3 CCollider3DSphere::GetDent( CCollider3DSphere& sphere , float rate )
{
	// �߂荞�݋������Z�o
	D3DXVECTOR3 vBetween;				// �����蔻��Ԃ̃x�N�g��
	
	VECTOR3 spherePos = sphere.GetPos();

	vBetween.x = m_pos.x - spherePos.x;
	vBetween.y = m_pos.y - spherePos.y;
	vBetween.z = m_pos.z - spherePos.z;

	float lenBetween = D3DXVec3Length( &D3DXVECTOR3( vBetween.x , vBetween.y , vBetween.z ) );			// �����蔻��Ԃ̃x�N�g����
	float lenAll     = m_radius + sphere.GetRadius();		// ���v�̒���
	float lenDent    = lenAll - lenBetween;					// �߂荞�݋���

	// �߂荞�݃x�N�g����ԋp
	D3DXVECTOR3 vDir;											// �����x�N�g��
	D3DXVec3Normalize( &vDir , &vBetween );

	D3DXVECTOR3 vDent = vDir * ( lenDent * rate );
	return VECTOR3( vDent.x , vDent.y , vDent.z );
}

//==============================================================================
// �֐��� : �T���v��
// ����   : void
// �߂�l : void
// ����   : �T���v������
//==============================================================================
