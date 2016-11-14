//==============================================================================
// �^�C�g��     :   3D�����̕`��p�N���X
// �t�@�C����   :   box.cpp
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
#include "box.h"
#include "rendererGL.h"

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
#define MOVE_SPEED		( 3.0f )			// �ړ��W��
#define ROTATION_SPEED	( PI * 0.01f )		// ��]�p�ω��W��

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================

//==============================================================================
// �O���[�o���錾
//==============================================================================
CMaterial* pMat;				// �}�e���A���ւ̃|�C���^

enum MAT_TYPE
{								/* ==�}�e���A����ގ��ʎq== */
	MAT_TYPE_AMBIENT = 0,			// �A���r�G���g
	MAT_TYPE_DIFFUSE,				// �f�B�t���[�Y
	MAT_TYPE_SPECULAR,				// �X�y�L�����[
	MAT_TYPE_EMISSION,				// �G�~�b�V����
	MAT_TYPE_SINESS,				// ���ʔ��ˌ��q��
	MAT_TYPE_MAX,					// ����
};

MAT_TYPE matSelect;				// ���ݑI�����Ă���}�e���A��

//==============================================================================
// �֐��� : CBox()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CBox::CBox()
{
	m_pTexture = NULL;

	m_bMove       = false;
	m_isTexEnable = true;

	pMat = NULL;
	matSelect = MAT_TYPE_AMBIENT;
}

//==============================================================================
// �֐��� : ~CBox()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CBox::~CBox()
{
}

//==============================================================================
// �֐��� : bool Init( char* texPath )
// ����   : char* texPath : �e�N�X�`���t�@�C���p�X
// �߂�l : void
// ����   : ����������( �e�N�X�`���t�@�C���p�X�L��� )
//==============================================================================
bool CBox::Init( char* texPath )
{
	CSceneGL3D::Init( texPath );		// ���N���X�̏����������Ăяo��

	m_size = VECTOR3( 100.0f , 100.0f , 100.0f );
	m_bMove = false;
	pMat = CMaterialGL::Create();	// �}�e���A������
	pMat->m_isShininessEnable = true;


	//---------------------------------
	// [ �e�N�X�`���ǂݍ��ݏ��� ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();					// �����_���[�̎擾
	pRenderer->CreateTexture( texPath , &m_pTexture );					// �e�N�X�`������

	return true;		// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CBox::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		delete m_pTexture;
		m_pTexture = NULL;
	}
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CBox::Update( void )
{
	//------------------------------------------
	// [ ���͏��̎擾���� ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isPressW     = false;
	bool isPressS     = false;
	bool isPressA     = false;
	bool isPressD     = false;
	bool isPressQ     = false;
	bool isPressE     = false;
	bool isPressZ     = false;
	bool isPressC     = false;
	bool isPressT     = false;
	bool isPressB     = false;
	bool isPressY     = false;
	bool isPressN     = false;
	bool isPressEnter = false;

	bool isTrigEnter  = false;
	bool isTrigF8     = false;
	bool isTrigF9     = false;

	bool isRepeat_1 = false;
	bool isRepeat_2 = false;
	bool isRepeat_3 = false;
	bool isRepeat_4 = false;
	bool isRepeat_5 = false;
	bool isRepeat_6 = false;
	bool isRepeat_7 = false;
	bool isRepeat_8 = false;
	bool isRepeat_9 = false;
	bool isRepeat_0 = false;

	if( pInput != NULL )
	{
		if( m_bMove == true )
		{
			isPressW     = pInput->GetPress( DIK_W );
			isPressS     = pInput->GetPress( DIK_S );
			isPressA     = pInput->GetPress( DIK_A );
			isPressD     = pInput->GetPress( DIK_D );
			isPressQ     = pInput->GetPress( DIK_Q );
			isPressE     = pInput->GetPress( DIK_E );
			isPressZ     = pInput->GetPress( DIK_Z );
			isPressC     = pInput->GetPress( DIK_C );
			isPressT     = pInput->GetPress( DIK_T );
			isPressB     = pInput->GetPress( DIK_B );
			isPressY     = pInput->GetPress( DIK_Y );
			isPressN     = pInput->GetPress( DIK_N );
			isPressEnter = pInput->GetPress( DIK_RETURN );
		}

		isTrigEnter = pInput->GetTrigger( DIK_RETURN );
		isTrigF8    = pInput->GetTrigger( DIK_F8 );
		isTrigF9    = pInput->GetTrigger( DIK_F9 );

		isRepeat_1 = pInput->GetRepeat( DIK_1 );
		isRepeat_2 = pInput->GetRepeat( DIK_2 );
		isRepeat_3 = pInput->GetRepeat( DIK_3 );
		isRepeat_4 = pInput->GetRepeat( DIK_4 );
		isRepeat_5 = pInput->GetRepeat( DIK_5 );
		isRepeat_6 = pInput->GetRepeat( DIK_6 );
		isRepeat_7 = pInput->GetRepeat( DIK_7 );
		isRepeat_8 = pInput->GetRepeat( DIK_8 );
		isRepeat_9 = pInput->GetRepeat( DIK_9 );
		isRepeat_0 = pInput->GetRepeat( DIK_0 );
	}

	//------------------------------------------
	// [ �ړ����� ]
	//------------------------------------------
	if( m_bMove == true )
	{
		// ���s�ړ�
		if( isPressW || isPressA || isPressS || isPressD )
		{
			float fMoveRot = 0.0f;					// �ړ�����

			// �����̎Z�o
			if( isPressW )
			{
				if( isPressA )
				{
					fMoveRot -= PI * -0.75f;		// ����
				}
				else if( isPressD )
				{
					fMoveRot -= PI * 0.75f;			// �E��
				}
				else
				{
					fMoveRot -= PI;					// ��
				}
			}
			else if( isPressS )
			{
				if( isPressA )
				{
					fMoveRot -= PI * -0.25f;		// ����O
				}
				else if( isPressD )
				{
					fMoveRot -= PI * 0.25f;			// �E��O
				}
				else
				{
					fMoveRot -= 0.0f;				// ��O
				}
			}
			else if( isPressA )
			{
				fMoveRot -= PI * -0.5f;				// ��
			}
			else if( isPressD )
			{
				fMoveRot -= PI * 0.5f;				// �E
			}

			fMoveRot -= GetManager()->GetCamera()->GetRot().y;

			// �p�x�̐��K��
			if( fMoveRot > PI )
			{
				fMoveRot -= PI2;
			}
			else if( fMoveRot < -PI )
			{
				fMoveRot += PI2;
			}

			// �����ɉ������ړ�����
			m_pos.x -= -sinf( fMoveRot ) * MOVE_SPEED;
			m_pos.z -= cosf( fMoveRot ) * MOVE_SPEED;
		}

		// �㉺�ړ�
		if( isPressZ )
		{
			m_pos.y += MOVE_SPEED;
		}
		else if( isPressC )
		{
			m_pos.y -= MOVE_SPEED;
		}
	}

	//------------------------------------------
	// [ ��]���� ]
	//------------------------------------------
	if( m_bMove == true )
	{
		if( isPressQ )
		{
			m_rot.y += ROTATION_SPEED;
		}
		else if( isPressE )
		{
			m_rot.y -= ROTATION_SPEED;
		}

		if( m_rot.y > PI )
		{
			m_rot.y -= PI2;
		}
		else if( m_rot.y < -PI )
		{
			m_rot.y += PI2;
		}
	}

	//------------------------------------------
	// [ ������]���� ]
	//------------------------------------------
	static float moveRad = 0.0f;
	static float moveLen = 100.0f;

	//if( m_bMove == false )
	//{
	//	/*m_rot.x += PI * 0.01f;

	//	if( m_rot.x > PI )
	//	{
	//		m_rot.x -= PI2;
	//	}*/

	//	m_rot.y += PI * 0.01f;

	//	if( m_rot.y > PI )
	//	{
	//		m_rot.y -= PI2;
	//	}

	//	/*m_rot.z += PI * 0.02f;

	//	if( m_rot.z > PI )
	//	{
	//		m_rot.z -= PI2;
	//	}*/

	//	m_pos.y = sinf( moveRad ) * moveLen;
	//	//m_pos.x = cosf( moveRad ) * moveLen;

	//	moveRad += PI * 0.01f;

	//	if( moveRad > PI )
	//	{
	//		moveRad -= PI2;
	//	}
	//}

	//------------------------------------------
	// [ �ړ��t���O�؂�ւ����� ]
	//------------------------------------------
	if( isTrigEnter )
	{
		m_bMove = m_bMove ? false : true;
	}

	//------------------------------------------
	// [ �}�e���A������ ]
	//------------------------------------------
	if( pMat != NULL )
	{
		CDebugProc::GetDebugProc()->PrintDebugProc( "[ Material ]\n" );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Ambient  : ( %1.3f : %1.3f : %1.3f : %1.3f )\n" , pMat->m_ambient.r , pMat->m_ambient.g , pMat->m_ambient.b , pMat->m_ambient.a );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Diffuse  : ( %1.3f : %1.3f : %1.3f : %1.3f )\n" , pMat->m_diffuse.r , pMat->m_diffuse.g , pMat->m_diffuse.b , pMat->m_diffuse.a );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Specular : ( %1.3f : %1.3f : %1.3f : %1.3f )\n" , pMat->m_specular.r , pMat->m_specular.g , pMat->m_specular.b , pMat->m_specular.a );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Emission : ( %1.3f : %1.3f : %1.3f : %1.3f )\n" , pMat->m_emission.r , pMat->m_emission.g , pMat->m_emission.b , pMat->m_emission.a );
		CDebugProc::GetDebugProc()->PrintDebugProc( "Shiness  : ( %1.3f )\n\n" , pMat->m_shininess );

		// �ω��ʃp�����[�^�ݒ�
		float rMove = 0.0f;
		float gMove = 0.0f;
		float bMove = 0.0f;
		float aMove = 0.0f;

		if( isRepeat_1 ) rMove = -0.02f;
		else if( isRepeat_2 ) rMove = 0.02f;

		if( isRepeat_3 ) gMove = -0.02f;
		else if( isRepeat_4 ) gMove = 0.02f;

		if( isRepeat_5 ) bMove = -0.02f;
		else if( isRepeat_6 ) bMove = 0.02f;

		if( isRepeat_7 ) aMove = -0.02f;
		else if( isRepeat_8 ) aMove = 0.02f;

		// �ω��ʑ��
		CDebugProc::GetDebugProc()->PrintDebugProc( "SelectType :" );

		switch( matSelect )
		{
			case MAT_TYPE_AMBIENT:
			{
				pMat->m_ambient.r += rMove;
				pMat->m_ambient.g += gMove;
				pMat->m_ambient.b += bMove;
				pMat->m_ambient.a += aMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Ambient\n" );
				break;
			}

			case MAT_TYPE_DIFFUSE:
			{
				pMat->m_diffuse.r += rMove;
				pMat->m_diffuse.g += gMove;
				pMat->m_diffuse.b += bMove;
				pMat->m_diffuse.a += aMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Diffuse\n" );
				break;
			}

			case MAT_TYPE_SPECULAR:
			{
				pMat->m_specular.r += rMove;
				pMat->m_specular.g += gMove;
				pMat->m_specular.b += bMove;
				pMat->m_specular.a += aMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Specular\n" );
				break;
			}

			case MAT_TYPE_EMISSION:
			{
				pMat->m_emission.r += rMove;
				pMat->m_emission.g += gMove;
				pMat->m_emission.b += bMove;
				pMat->m_emission.a += aMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Emission\n" );
				break;
			}

			case MAT_TYPE_SINESS:
			{
				rMove *= 100.0f;

				pMat->m_shininess += rMove;

				CDebugProc::GetDebugProc()->PrintDebugProc( "Shiness\n" );
				break;
			}

			default:
			{
				break;
			}
		}

		// ����Ώۂ̐؂�ւ�
		if( isRepeat_9 )
		{
			matSelect = ( MAT_TYPE )( matSelect - 1 );

			if( matSelect <= -1 )
			{
				matSelect = ( MAT_TYPE )( MAT_TYPE_MAX - 1 );
			}
		}
		else if( isRepeat_0 )
		{
			matSelect = ( MAT_TYPE )( matSelect + 1 );

			if( matSelect >= MAT_TYPE_MAX )
			{
				matSelect = ( MAT_TYPE )0;
			}
		}

		// �f�t�H���g�̒l�ɖ߂�
		if( isTrigF8 )
		{
			CMaterialGL matDef;

			*pMat = matDef;
			pMat->m_isShininessEnable = true;
		}
	}

	// �e�N�X�`���L���E�����؂�ւ�
	if( isTrigF9 )
	{
		m_isTexEnable = m_isTexEnable ? false : true;
	}
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CBox::Draw( void )
{
	//---------------------------------
	// [ �`��O���� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	//glCullFace( GL_FRONT );
	//glCullFace( GL_FRONT_AND_BACK );

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
	//---------------------------------------------------------------------
	if( m_pTexture != NULL && m_isTexEnable )
	{
		m_pTexture->Set();						// �e�N�X�`���ݒ�
	}
	else
	{
		glDisable( GL_TEXTURE_2D );
	}

	if( pMat != NULL )
	{
		pMat->Set();							// �}�e���A���ݒ�
	}

	float sizeHalfX = m_size.x * 0.5f;			// X���̃T�C�Y�̔���
	float sizeHalfZ = m_size.z * 0.5f;			// Z���̃T�C�Y�̔���

	glBegin( GL_TRIANGLE_STRIP );
	{
		/* ==0== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , -1.0f , 0.0f );
			glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , -1.0f , 0.0f );
			glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , -1.0f , 0.0f );
			glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 1.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , -1.0f , 0.0f );
			glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

		}

		/* ==1== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 1.0f , 0.0f , 0.0f );
			glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 1.0f , 0.0f , 0.0f );
			glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 1.0f , 0.0f , 0.0f );
			glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 1.0f , 0.0f , 0.0f );
			glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );
		}

		/* ==2== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , 1.0f );
			glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );
		}

		/* ==3== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( -1.0f , 0.0f , 0.0f );
			glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( -1.0f , 0.0f , 0.0f );
			glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( -1.0f , 0.0f , 0.0f );
			glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 1.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( -1.0f , 0.0f , 0.0f );
			glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );
		}

		/* ==4== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , -1.0f );
			glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , -1.0f );
			glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , -1.0f );
			glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

			glTexCoord2f( 1.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 0.0f , -1.0f );
			glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );
		}

		/* ==5== */
		{
			glTexCoord2f( 0.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 1.0f , 0.0f );
			glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );

			glTexCoord2f( 0.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 1.0f , 0.0f );
			glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );

			glTexCoord2f( 1.0f , 1.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 1.0f , 0.0f );
			glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );

			glTexCoord2f( 1.0f , 0.0f );
			glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
			glNormal3f( 0.0f , 1.0f , 0.0f );
			glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );
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

	if( !m_isTexEnable )
	{
		glEnable( GL_TEXTURE_2D );
	}

	if( pMat != NULL )
	{
		CMaterialGL pDefMat;

		pDefMat.Set();							// �}�e���A���ݒ�
	}
}
