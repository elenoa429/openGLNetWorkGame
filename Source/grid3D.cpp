//==============================================================================
// �^�C�g��     :   �O���b�h���`��N���X
// �t�@�C����   :   grid3D.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/07/08
//==============================================================================

//==============================================================================
// �X�V����: -2016/07/08 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "grid3D.h"
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
// �֐��� : CGrid3D()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CGrid3D::CGrid3D()
{
	m_numW    = 0;
	m_numH    = 0;
	m_marginW = 0.0f;
	m_marginH = 0.0f;
}

//==============================================================================
// �֐��� : ~CGrid3D()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CGrid3D::~CGrid3D()
{
}

//==============================================================================
// �֐��� : CGrid3D* Create( int w , int h , float mW , float mH )
// ����   : char* texPath : �e�N�X�`���t�@�C���p�X
// �߂�l : CGrid3D*�^
// ����   : ��������
//==============================================================================
CGrid3D* CGrid3D::Create( int w , int h , float mW , float mH )
{
	CGrid3D* pNewInstance = new CGrid3D;

	if( pNewInstance->Init( w , h , mW , mH ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// �֐��� : bool Init( int w , int h , float mW , float mH )
// ����   : int w    : ����
//          int h    : �c��
//          float mW : ���Ԋu
//          float mH : �c�Ԋu
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CGrid3D::Init( int w , int h , float mW , float mH )
{
	//---------------------------------
	// [ �l������ ]
	//---------------------------------
	m_numW    = w;
	m_numH    = h;
	m_marginW = mW;
	m_marginH = mH;
	m_col     = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );
	m_scl     = VECTOR3( 1.0f , 1.0f , 1.0f );

	return true;		// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CGrid3D::Uninit( void )
{

}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CGrid3D::Update( void )
{

}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CGrid3D::Draw( void )
{
	//---------------------------------
	// [ �`��O���� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glDisable( GL_BLEND );
	glBlendFunc( GL_ONE , GL_ZERO );

	glDisable( GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );

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
	VECTOR3 lineFrom;
	VECTOR3 lineTo;

	float lenW = m_marginW * m_numW;
	float lenH = m_marginH * m_numH;

	glBegin( GL_LINES );
	{
		// �s�`��
		lineFrom = VECTOR3( lenW * -0.5f , 0.0f , lenH * -0.5f );
		lineTo   = VECTOR3( lenW * 0.5f , 0.0f , lenH * -0.5f );

		for( int h = 0 ; h < m_numH + 1 ; h++ )
		{
			// From
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glVertex3f( lineFrom.x , lineFrom.y , lineFrom.z );

			// To
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glVertex3f( lineTo.x , lineTo.y , lineTo.z );

			lineFrom.z += m_marginH;
			lineTo.z   += m_marginH;
		}

		// ��`��
		lineFrom = VECTOR3( lenW * -0.5f , 0.0f , lenH * -0.5f );
		lineTo   = VECTOR3( lenW * -0.5f , 0.0f , lenH * 0.5f );

		for( int w = 0 ; w < m_numW + 1 ; w++ )
		{
			// From
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glVertex3f( lineFrom.x , lineFrom.y , lineFrom.z );

			// To
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glVertex3f( lineTo.x , lineTo.y , lineTo.z );

			lineFrom.x += m_marginW;
			lineTo.x   += m_marginW;
		}
		
	}
	glEnd();

	//---------------------------------
	// [ �`��㏈�� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glDisable( GL_BLEND );
	glBlendFunc( GL_ONE , GL_ZERO );

	glEnable( GL_LIGHTING );
	glEnable( GL_TEXTURE_2D );

}
