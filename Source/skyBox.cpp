//==============================================================================
// �^�C�g��     :   �X�J�C�{�b�N�X�N���X
// �t�@�C����   :   skyBox.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/16
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/16 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "skyBox.h"
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
// �֐��� : CSkyBox()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CSkyBox::CSkyBox()
{
}

//==============================================================================
// �֐��� : ~CSkyBox()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CSkyBox::~CSkyBox()
{
}

//==============================================================================
// �֐��� : CSkyBox* Create( char* texPath )
// ����   : char* texPath : �e�N�X�`���t�@�C���p�X
// �߂�l : CSkyBox*�^
// ����   : ��������
//==============================================================================
CSkyBox* CSkyBox::Create( char* texPath )
{
	CSkyBox* pNewInstance = new CSkyBox;

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
bool CSkyBox::Init( char* texPath )
{
	CSceneGL3D::Init( texPath );

	m_size = VECTOR3( 50000.0f , 50000.0f , 50000.0f );
	m_DivTexU = 4;
	m_DivTexV = 3;
	m_texUnitSize.x = 1.0f / ( float )m_DivTexU;
	m_texUnitSize.y = 1.0f / ( float )m_DivTexV;

	return true;		// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CSkyBox::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	CSceneGL3D::Uninit();
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CSkyBox::Update( void )
{
	CCameraGL* pCamera = GetManager()->GetCamera();

	m_pos = pCamera->GetPosV();

	//m_rot.y += 0.001f;

	if( m_rot.y > PI )
	{
		m_rot.y -= PI2;
	}
	else if( m_rot.y < -PI )
	{
		m_rot.y += PI2;
	}
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CSkyBox::Draw( void )
{
	//---------------------------------
	// [ �`��O���� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_FRONT );

	glDisable( GL_LIGHTING );

	//const GLfloat borderCol[] = { 0.0f , 0.0f , 0.0f , 0.0f };
	//glTexParameterfv( GL_TEXTURE_2D , GL_TEXTURE_BORDER_COLOR , borderCol );
	//glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP );
	//glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP );

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

	//---------------------------------------------------------------------
	// [ �`�揈�� ]
	//
	//              [5]
	//   [1][2][3][4]     <= [0]�Ԃ̃|���S���̍�������`��
	// [0]                <= ���}�̏��Ԃ�N���ɕ`��
	//
	//    [5]
	// [1][2][3][4]       <= ���}�̂悤�ȓW�J���ꂽ�e�N�X�`���𗘗p���邽�߁A
	//    [0]                ��ł��ō��W����
	//---------------------------------------------------------------------
	if( m_pTexture != NULL )
	{
		m_pTexture->Set();						// �e�N�X�`���ݒ�
	}

	float sizeHalfX = m_size.x * 0.5f;			// X���̃T�C�Y�̔���
	float sizeHalfY = m_size.y * 0.5f;			// Y���̃T�C�Y�̔���
	float sizeHalfZ = m_size.z * 0.5f;			// Z���̃T�C�Y�̔���

	glBegin( GL_TRIANGLE_STRIP );
	{
		/* ==0== */
		{
			glTexCoord2f(texUPos(2), texVPos(0));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(0));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, -sizeHalfZ);

		}

		/* ==1== */
		{
			glTexCoord2f(texUPos(3), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(4), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(4), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, +sizeHalfZ);
		}

		/* ==2== */
		{
			glTexCoord2f(texUPos(0), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(0), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(1), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(1), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, +sizeHalfZ);
		}

		/* ==3== */
		{
			glTexCoord2f(texUPos(1), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(1), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, -sizeHalfZ);
		}

		/* ==4== */
		{
			glTexCoord2f(texUPos(2), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(1));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, -sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, -sizeHalfZ);
		}

		/* ==5== */
		{
			glTexCoord2f(texUPos(2), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(2), texVPos(3));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(-sizeHalfX, +sizeHalfY, +sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(2));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, -sizeHalfZ);

			glTexCoord2f(texUPos(3), texVPos(3));
			glColor4f(m_col.r, m_col.g, m_col.b, m_col.a);
			glVertex3f(+sizeHalfX, +sizeHalfY, +sizeHalfZ);
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

	glDisable( GL_CULL_FACE );

	glEnable( GL_LIGHTING );

	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT );

}

//==============================================================================
// �֐��� : float CSkyBox::texUPos( int uPos )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
float CSkyBox::texUPos( int uPos )
{
	float fPosU = m_texUnitSize.x * uPos;

	if( fPosU <= 0.0f )
	{
		fPosU = 0.001f;
	}
	else if( fPosU >= 1.0f )
	{
		fPosU = 0.999f;
	}

	return fPosU;
}

//==============================================================================
// �֐��� : float CSkyBox::texVPos( int vPos )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
float CSkyBox::texVPos( int vPos )
{
	float fPosV = m_texUnitSize.y * vPos;

	if( fPosV <= 0.0f )
	{
		fPosV = 0.001f;
	}
	else if( fPosV >= 1.0f )
	{
		fPosV = 0.999f;
	}

	return fPosV;
}
