//==============================================================================
// �^�C�g��     :   OpenGL�p�e�q�֌W�t�����f������
// �t�@�C����   :   parentModelGL.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/09/05
//==============================================================================

//==============================================================================
// �X�V����: -2016/09/05 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "parentModelGL.h"
#include "rendererGL.h"

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
// �֐��� : CParentModelGL()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CParentModelGL::CParentModelGL()
{
	m_pModel    = NULL;
	m_subsetIdx = 0;
	m_pParent   = NULL;
	m_pos       = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot       = VECTOR3( 0.0f , 0.0f , 0.0f );

	MatrixIdentity( &m_mtxLocal );
}

//==============================================================================
// �֐��� : ~CParentModelGL()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CParentModelGL::~CParentModelGL()
{

}

//==============================================================================
// �֐��� : CParentModelGL* Create( CModelGL* pModel , DWORD subsetIdx )
// ����   : CModelGL* pModel : �`�悷�郂�f���ւ̃|�C���^
//          WORD subsetIdx   : �`�悷��T�u�Z�b�g�̃C���f�b�N�X
// �߂�l : void
// ����   : ��������
//==============================================================================
CParentModelGL* CParentModelGL::Create( CModelGL* pModel , DWORD subsetIdx )
{
	CParentModelGL* pNewInstance = new CParentModelGL;

	if( pNewInstance->Init( pModel , subsetIdx ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// �֐��� : void Release( void )
// ����   : void
// �߂�l : void
// ����   : �������
//==============================================================================
void CParentModelGL::Release( void )
{
	Uninit();
	delete this;
}

//==============================================================================
// �֐��� : bool Init( CModelGL* pModel , DWORD subsetIdx )
// ����   : CModelGL* pModel : �`�悷�郂�f���ւ̃|�C���^
//          WORD subsetIdx   : �`�悷��T�u�Z�b�g�̃C���f�b�N�X
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CParentModelGL::Init( CModelGL* pModel , DWORD subsetIdx )
{
	//---------------------------------------------
	// [ ���f���f�[�^�̐ݒ� ]
	//---------------------------------------------
	m_pModel    = pModel;
	m_subsetIdx = subsetIdx;

	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CParentModelGL::Uninit( void )
{
	// ���f���f�[�^�̉��
	if( m_pModel != NULL )
	{
		m_pModel = NULL;
	}

	m_pParent = NULL;
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CParentModelGL::Update( void )
{
	//-------------------------------------
	// [ ���[�J���}�g���N�X���� ]
	//-------------------------------------
	MATRIX mtxRot , mtxTrans;

	MatrixIdentity( &m_mtxLocal );

	MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );
	MatrixMultiply( &m_mtxLocal , &m_mtxLocal , &mtxRot );

	MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );
	MatrixMultiply( &m_mtxLocal , &m_mtxLocal , &mtxTrans );

}

//==============================================================================
// �֐��� : void Draw( MATRIX* pParentMatrix )
// ����   : MATRIX* pParentMatrix : �e�}�g���N�X( ���[�J������W( 0 ; 0 ; 0 ) )�ɂ�����
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CParentModelGL::Draw( MATRIX* pParentMatrix )
{
	//---------------------------------------------
	// [ ���[���h�}�g���N�X���� ]
	//---------------------------------------------
	MATRIX mtxWorld;

	//MatrixIdentity( &mtxWorld );									// �P�ʃ}�g���N�X��
	//MatrixMultiply( &mtxWorld , &mtxWorld , &GetMtxParent() );		// ���[�J���}�g���N�X���܂߂��e�}�g���N�X������
	//MatrixMultiply( &mtxWorld , &mtxWorld , pParentMatrix );		// ��}�g���N�X������

	//glMatrixMode( GL_MODELVIEW );
	//glPushMatrix();
	//glMultMatrixf( mtxWorld.m );

	glPushMatrix();

	glTranslatef( m_pos.x , m_pos.y , m_pos.z );

	glRotatef( RadToDeg( m_rot.z ) , 0.0f , 0.0f , 1.0f );
	glRotatef( RadToDeg( m_rot.y ) , 0.0f , 1.0f , 0.0f );
	glRotatef( RadToDeg( m_rot.x ) , 1.0f , 0.0f , 0.0f );
	

	//---------------------------------------------
	// [ �`�揈�� ]
	//---------------------------------------------
	m_pModel->SetMaterial( m_subsetIdx );
	m_pModel->SetMatTexture( m_subsetIdx );
	m_pModel->DrawSubset( m_subsetIdx );

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}

//==============================================================================
// �֐��� : bool SetSubsetIdx( DWORD idx )
// ����   : DWORD idx : �`��ΏۃT�u�Z�b�g�C���f�b�N�X
// �߂�l : bool�^
// ����   : �T�u�Z�b�g�C���f�b�N�X�ݒ菈��
//==============================================================================
bool CParentModelGL::SetSubsetIdx( DWORD idx )
{
	DWORD subsetNum = m_pModel->GetSubsetNum();

	if( idx >= subsetNum )
	{
		return false;
	}

	m_subsetIdx = idx;

	return true;
}

//==============================================================================
// �֐��� : void SetParent( CParentModelGL* pParent )
// ����   : CParentModelGL* pParent : �e���f���ւ̃|�C���^
// �߂�l : bool�^
// ����   : �e���f���ݒ菈��
//==============================================================================
void CParentModelGL::SetParent( CParentModelGL* pParent )
{
	m_pParent = pParent;
}

//==============================================================================
// �֐��� : MATRIX GetMtxParent( void );
// ����   : void
// �߂�l : MATRIX�^
// ����   : �e�}�g���N�X�擾����
//==============================================================================
MATRIX CParentModelGL::GetMtxParent( void )
{
	MATRIX mtxParent;
	MatrixIdentity( &mtxParent );

	// �ċA�I�ɐe�}�g���N�X���擾
	if( m_pParent != NULL )
	{
		MatrixMultiply( &mtxParent , &m_mtxLocal , &m_pParent->GetMtxParent() );
	}
	else
	{
		mtxParent = m_mtxLocal;
	}

	return mtxParent;
}

//==============================================================================
// �֐��� : void SetRotDegree( VECTOR3 rot )
// ����   : VECTOR3 rot : �p�x( Degree�l )
// �߂�l : void
// ����   : �p�x�ݒ菈��( Degree -> Radian )
//==============================================================================
void CParentModelGL::SetRotDegree( VECTOR3 rot )
{
	VECTOR3 rotRad;

	rotRad.x = DegToRad( rot.x );
	rotRad.y = DegToRad( rot.y );
	rotRad.z = DegToRad( rot.z );

	m_rot = rotRad;
}
