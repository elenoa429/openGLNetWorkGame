//==============================================================================
// �^�C�g��     :   OpenGL�p3D�`��p�N���X
// �t�@�C����   :   sceneGL3D.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/04/22
//==============================================================================

//==============================================================================
// �X�V����: -2016/04/22 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "sceneGL3D.h"
#include "rendererGL.h"

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
// �֐��� : CSceneGL3D()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CSceneGL3D::CSceneGL3D()
{
	m_pos      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size     = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_col      = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );
	m_nor      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_scl      = VECTOR3( 1.0f , 1.0f , 1.0f );
	m_pTexture = NULL;

	MatrixIdentity( &m_mtxWorld );
}

//==============================================================================
// �֐��� : ~CSceneGL3D()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CSceneGL3D::~CSceneGL3D()
{
}

//==============================================================================
// �֐��� : CSceneGL3D* Create( char* texPath )
// ����   : char* texPath : �e�N�X�`���t�@�C���p�X
// �߂�l : CSceneGL3D*�^
// ����   : ��������
//==============================================================================
CSceneGL3D* CSceneGL3D::Create( char* texPath )
{
	CSceneGL3D* pNewInstance = new CSceneGL3D;

	if( pNewInstance->Init( texPath ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// �֐��� : bool Init( char* texPath )
// ����   : char* texPath : �e�N�X�`���t�@�C���p�X
// �߂�l : void
// ����   : ����������( �e�N�X�`���t�@�C���p�X�L��� )
//==============================================================================
bool CSceneGL3D::Init( char* texPath )
{
	//---------------------------------
	// [ �l������ ]
	//---------------------------------
	m_pos  = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot  = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_scl  = VECTOR3( 1.0f , 1.0f , 1.0f );
	m_nor  = VECTOR3( 0.0f , 1.0f , 0.0f );
	m_size = VECTOR3( 10000.0f , 0.0f , 10000.0f );
	m_col  = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );

	//---------------------------------
	// [ �e�N�X�`���ǂݍ��ݏ��� ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();				// �����_���[�̎擾
	
	if( pRenderer != NULL )
	{
		pRenderer->CreateTexture( texPath , &m_pTexture );				// �e�N�X�`������
	}

	return true;		// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CSceneGL3D::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CSceneGL3D::Update( void )
{
	/*m_rot.y += PI * 0.01f;

	if( m_rot.y > PI )
	{
		m_rot.y -= PI2;
	}*/

	//m_pos.x += 1.0f;
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CSceneGL3D::Draw( void )
{
	//---------------------------------
	// [ �`��O���� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	//---------------------------------
	// [ ���[���h�}�g���N�X�Z�o ]
	//---------------------------------
	MATRIX mtxScl , mtxRot , mtxTrans;

	MatrixIdentity( &m_mtxWorld );

	MatrixScaling( &mtxScl , m_scl.x , m_scl.y , m_scl.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxScl );

	MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxRot );

	MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxTrans );

	glMultMatrixf( m_mtxWorld.m );

	//---------------------------------
	// [ �`�揈�� ]
	//---------------------------------
	if( m_pTexture != NULL )
	{
		m_pTexture->Set();						// �e�N�X�`���ݒ�
	}

	glBegin( GL_TRIANGLE_STRIP );
	{
		glTexCoord2f( 0.0f , 0.0f );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glNormal3f( m_nor.x , m_nor.y , m_nor.z );
		glVertex3f( -m_size.x , 0.0f , -m_size.z );

		glTexCoord2f( 1.0f , 0.0f );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glNormal3f( m_nor.x , m_nor.y , m_nor.z );
		glVertex3f( m_size.x , 0.0f , -m_size.z );

		glTexCoord2f( 0.0f , 1.0f );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glNormal3f( m_nor.x , m_nor.y , m_nor.z );
		glVertex3f( -m_size.x , 0.0f , m_size.z );

		glTexCoord2f( 1.0f , 1.0f );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glNormal3f( m_nor.x , m_nor.y , m_nor.z );
		glVertex3f( m_size.x , 0.0f , m_size.z );
	}
	glEnd();

	//---------------------------------
	// [ �`��㏈�� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glDisable( GL_BLEND );
	glBlendFunc( GL_ONE , GL_ZERO );

}
