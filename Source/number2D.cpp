//==============================================================================
// �^�C�g��     :   2D�p�����\���N���X
// �t�@�C����   :   number2D.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/19
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/19 ��������
//           �E����J�n
//           -2016/11/21��������
//           �EOpenGL�p�ɏ������ꕔ�ύX
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "number2D.h"
#include "main.h"
#include "rendererDX.h"

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
const int CNumber2D::m_vtxNum  = 4;			// �K�v���_��
const int CNumber2D::m_primNum = 2;			// �K�v�v���~�e�B�u��

//==============================================================================
// �֐��� : CNumber2D()
// ����   : void
// �߂�l : void
// ����   : �R���X�g���N�^
//==============================================================================
CNumber2D::CNumber2D()
{
	m_pTexture = NULL;
	m_length   = 0.0f;
	m_angle    = 0.0f;
}

//==============================================================================
// �֐��� : ~CNumber2D()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CNumber2D::~CNumber2D()
{

}

//==============================================================================
// �֐��� : CNumber2D* Create( VECTOR3 pos , VECTOR3 size , CTexture* pTexture )
// ����   : VECTOR3 pos        : �ʒu
//          VECTOR3 size       : �T�C�Y
//          CTexture* pTexture : �e�N�X�`���ւ̃|�C���^
// �߂�l : bool�^ : ��������
// ����   : ��������
//==============================================================================
CNumber2D* CNumber2D::Create( VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , CTexture* pTexture )
{
	CNumber2D* newInstance;
	newInstance = new CNumber2D;

	if( newInstance->Init( pos , size , texDivW , texDivH , pTexture ) == false )
	{
		newInstance->Release();
		newInstance = NULL;
	}

	return newInstance;
}

//==============================================================================
// �֐��� : bool Init( VECTOR3 pos , VECTOR3 size , CTexture* pTexture )
// ����   : VECTOR3 pos             : �ʒu
//          VECTOR3 size            : �T�C�Y
//          CTexture* pTexture : �e�N�X�`���ւ̃|�C���^
// �߂�l : bool�^ : ��������
// ����   : ����������
//==============================================================================
bool CNumber2D::Init( VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , CTexture* pTexture )
{
	// ���̏������������s��
	CNumber::Init( texDivW , texDivH );

	// ���W���̏�����
	m_pos      = pos;
	m_rot      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size     = size;
	m_pTexture = pTexture;

	VECTOR3 halfSize = VECTOR3( m_size.x * 0.5f , m_size.y * 0.5f , m_size.z * 0.5f );

	m_length = sqrtf( ( halfSize.x * halfSize.x ) + ( halfSize.y * halfSize.y ) );
	m_angle = atan2f( m_size.x , m_size.y );

	return true;	// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CNumber2D::Uninit( void )
{
	// �e�N�X�`���͊O������ݒ肷��̂ŁA�����ł͉�����Ȃ�
	m_pTexture = NULL;
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CNumber2D::Update( void )
{
	
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CNumber2D::Draw( void )
{
	//---------------------------------
	// [ �`��O�ݒ� ]
	//---------------------------------
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_DEPTH_TEST );													// Z�o�b�t�@�[OFF

	if( m_pTexture != NULL )
	{
		m_pTexture->Set();		// �e�N�X�`���ݒ�
	}

	//---------------------------------
	// [ �J�����ݒ菈�� ]
	//---------------------------------
	CCameraGL* pCamera = ( CCameraGL* )GetManager()->GetCamera();	// �J�����擾
	pCamera->Set2D();												// 2D�J�����ݒ�

	//---------------------------------
	// [ �|���S���`�揈�� ]
	//---------------------------------
	float halfX = m_size.x * 0.5f;
	float halfY = m_size.y * 0.5f;

	glBegin( GL_TRIANGLE_STRIP );
	{
		glTexCoord2f( m_tex.x , m_tex.y );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glVertex3f( m_pos.x - sinf( m_angle + m_rot.z ) * m_length , m_pos.y - cosf( m_angle + m_rot.z ) * m_length , 0.0f );

		glTexCoord2f( m_tex.x + m_texLen.x , m_tex.y );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glVertex3f( m_pos.x + sinf( m_angle - m_rot.z ) * m_length , m_pos.y - cosf( m_angle - m_rot.z ) * m_length , 0.0f );

		glTexCoord2f( m_tex.x , m_tex.y - m_texLen.y );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glVertex3f( m_pos.x - sinf( m_angle - m_rot.z ) * m_length , m_pos.y + cosf( m_angle - m_rot.z ) * m_length , 0.0f );

		glTexCoord2f( m_tex.x + m_texLen.x , m_tex.y - m_texLen.y );
		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		glVertex3f( m_pos.x + sinf( m_angle + m_rot.z ) * m_length , m_pos.y + cosf( m_angle + m_rot.z ) * m_length , 0.0f );
	}
	glEnd();

	//---------------------------------
	// [ �`��㏈�� ]
	//---------------------------------
	glBlendFunc( GL_ONE , GL_ZERO );
	glDisable( GL_BLEND );

	glEnable( GL_DEPTH_TEST );													// Z�o�b�t�@�[ON

	pCamera->End2D();															// 2D�J�����I���ݒ�
}

//==============================================================================
// �֐��� : void SetSize( VECTOR3 size )
// ����   : void
// �߂�l : void
// ����   : �T�C�Y�ݒ菈��
//==============================================================================
void CNumber2D::SetSize( VECTOR3 size )
{
	m_size = size;

	// �Ίp���֘A�̎Z�o
	VECTOR3 halfSize = VECTOR3( m_size.x * 0.5f , m_size.y * 0.5f , m_size.z * 0.5f );

	m_length = sqrtf( ( halfSize.x * halfSize.x ) + ( halfSize.y * halfSize.y ) );
	m_angle = atan2f( m_size.x , m_size.y );

}



