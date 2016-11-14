//==============================================================================
// �^�C�g��     :   OpenGL�p�J��������
// �t�@�C����   :   cameraGL.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/13
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/13 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "cameraGL.h"
#include "rendererGL.h"

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
#define MOVE_SPEED		( 20.0f )
#define ROTATION_SPEED	( PI * 0.01f )

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
// �֐��� : CCameraGL()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CCameraGL::CCameraGL()
{
}

//==============================================================================
// �֐��� : ~CCameraGL()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CCameraGL::~CCameraGL()
{
}

//==============================================================================
// �֐��� : bool Init( VECTOR3 posV , VECTOR3 posR )
// ����   : void
// �߂�l : void
// ����   : ����������
//==============================================================================
bool CCameraGL::Init( VECTOR3 posV , VECTOR3 posR )
{
	m_posV = posV;
	m_posR = posR;
	m_VecU = VECTOR3( 0.0f , 1.0f , 0.0f );

	float dx = m_posR.x - m_posV.x;
	float dy = m_posR.y - m_posV.y;
	float dz = m_posR.z - m_posV.z;

	m_rot       = VECTOR3( 0.0f , atan2f( dx , dz ) , 0.0f );
	m_fDistance = sqrtf( dx * dx + dz * dz );
	m_fov       = 60.0f;		// ����p�́w�x�x�Őݒ�
	m_nearZ     = 1.0f;
	m_farZ      = 200000.0f;

	m_posR.x = m_posV.x + sinf( m_rot.y ) * m_fDistance;
	m_posR.z = m_posV.z + cosf( m_rot.y ) * m_fDistance;
	m_bMove  = true;

	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CCameraGL::Uninit( void )
{
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CCameraGL::Update( void )
{
	//------------------------------------------
	// [ ���͏��̎擾���� ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool bPressW     = false;
	bool bPressS     = false;
	bool bPressA     = false;
	bool bPressD     = false;
	bool bPressQ     = false;
	bool bPressE     = false;
	bool bPressZ     = false;
	bool bPressC     = false;
	bool bPressT     = false;
	bool bPressB     = false;
	bool bPressY     = false;
	bool bPressN     = false;
	bool bPressEnter = false;

	bool bTrigEnter  = false;

	if( pInput != NULL )
	{
		if( m_bMove == true )
		{
			bPressW     = pInput->GetPress( DIK_W );
			bPressS     = pInput->GetPress( DIK_S );
			bPressA     = pInput->GetPress( DIK_A );
			bPressD     = pInput->GetPress( DIK_D );
			bPressQ     = pInput->GetPress( DIK_Q );
			bPressE     = pInput->GetPress( DIK_E );
			bPressZ     = pInput->GetPress( DIK_Z );
			bPressC     = pInput->GetPress( DIK_C );
			bPressT     = pInput->GetPress( DIK_T );
			bPressB     = pInput->GetPress( DIK_B );
			bPressY     = pInput->GetPress( DIK_Y );
			bPressN     = pInput->GetPress( DIK_N );
			bPressEnter = pInput->GetPress( DIK_RETURN );
		}

		bTrigEnter = pInput->GetTrigger( DIK_RETURN );
	}

	//------------------------------------------
	// [ �J�������s�ړ����� ]
	//------------------------------------------
	if( bPressW || bPressA || bPressS || bPressD )
	{
		float fMoveRot = 0.0f;					// �ړ�����

		/* ===�����̎Z�o=== */
		if( bPressW )
		{
			if( bPressA )
			{
				fMoveRot -= PI * -0.75f;		// ����
			}
			else if( bPressD )
			{
				fMoveRot -= PI * 0.75f;			// �E��
			}
			else
			{
				fMoveRot -= PI;					// ��
			}
		}
		else if( bPressS )
		{
			if( bPressA )
			{
				fMoveRot -= PI * -0.25f;		// ����O
			}
			else if( bPressD )
			{
				fMoveRot -= PI * 0.25f;			// �E��O
			}
			else
			{
				fMoveRot -= 0.0f;				// ��O
			}
		}
		else if( bPressA )
		{
			fMoveRot -= PI * -0.5f;				// ��
		}
		else if( bPressD )
		{
			fMoveRot -= PI * 0.5f;				// �E
		}

		fMoveRot -= m_rot.y;

		/* ===�p�x�̐��K��=== */
		if( fMoveRot > PI )
		{
			fMoveRot -= PI2;
		}
		else if( fMoveRot < -PI )
		{
			fMoveRot += PI2;
		}

		/* ===�����ɉ��������_�ړ�����=== */
		m_posV.x -= -sinf( fMoveRot ) * MOVE_SPEED;
		m_posV.z -= cosf( fMoveRot ) * MOVE_SPEED;

		/* ===�����_�̐ݒ�=== */
		m_posR.x = m_posV.x + sinf( m_rot.y ) * m_fDistance;
		m_posR.z = m_posV.z + cosf( m_rot.y ) * m_fDistance;
	}

	if( bPressT )
	{
		m_posV.y += MOVE_SPEED;
	}
	else if( bPressB )
	{
		m_posV.y -= MOVE_SPEED;
	}

	if( bPressY )
	{
		m_posR.y += MOVE_SPEED;
	}
	else if( bPressN )
	{
		m_posR.y -= MOVE_SPEED;
	}

	//------------------------------------------
	// [ �J������]���� ]
	//------------------------------------------
	/* ===�����_=== */
	if( bPressQ )
	{
		m_rot.y += ROTATION_SPEED;
		m_posR.x = m_posV.x + sinf( m_rot.y ) * m_fDistance;
		m_posR.z = m_posV.z + cosf( m_rot.y ) * m_fDistance;
	}
	else if( bPressE )
	{
		m_rot.y -= ROTATION_SPEED;
		m_posR.x = m_posV.x + sinf( m_rot.y ) * m_fDistance;
		m_posR.z = m_posV.z + cosf( m_rot.y ) * m_fDistance;
	}

	/* ===���_=== */
	if( bPressZ )
	{
		m_rot.y += ROTATION_SPEED;
		m_posV.x = m_posR.x - sinf( m_rot.y ) * m_fDistance;
		m_posV.z = m_posR.z - cosf( m_rot.y ) * m_fDistance;
	}
	else if( bPressC )
	{
		m_rot.y -= ROTATION_SPEED;
		m_posV.x = m_posR.x - sinf( m_rot.y ) * m_fDistance;
		m_posV.z = m_posR.z - cosf( m_rot.y ) * m_fDistance;
	}

	if( m_rot.y > PI )
	{
		m_rot.y -= PI2;
	}
	else if( m_rot.y < -PI )
	{
		m_rot.y += PI2;
	}

	//------------------------------------------
	// [ �J�������Z�b�g���� ]
	//------------------------------------------
	if( bPressEnter )
	{
		//CCameraGL::Init();
	}

	if( bTrigEnter )
	{
		m_bMove = m_bMove ? false : true;
	}

	//------------------------------------------
	// [ ���\������ ]
	//------------------------------------------
	//CDebugProc::GetDebugProc()->PrintDebugProc( "\n\n\nCAMERA_POSV : ( %3.3f : %3.3f : %3.3f )\n" , m_posV.x , m_posV.y , m_posV.z );
	//CDebugProc::GetDebugProc()->PrintDebugProc( "CAMERA_POSR : ( %3.3f : %3.3f : %3.3f )\n" , m_posR.x , m_posR.y , m_posR.z );
}

//==============================================================================
// �֐��� : void Set( void )
// ����   : void
// �߂�l : void
// ����   : �J�����ݒ菈��
//==============================================================================
void CCameraGL::Set( void )
{
	/* ===�J�����ݒ�( 3D )=== */
	glViewport( 0 , 0 , ( int ) SCREEN_WIDTH , ( int ) SCREEN_HEIGHT );			// �r���[�|�[�g�̐ݒ�

	glMatrixMode( GL_PROJECTION );												// �s�񃂁[�h�ؑ�
	glLoadIdentity();															// �ˉe�s��̏�����

	float aspect = ( float )SCREEN_WIDTH / ( float )SCREEN_HEIGHT;				// �A�X�y�N�g��

	gluPerspective( m_fov , aspect , m_nearZ , m_farZ );						// �ˉe�s��̐ݒ�

	glMatrixMode( GL_MODELVIEW );												// �s�񃂁[�h��߂�
	glLoadIdentity();															// �r���[�s��̏�����

	gluLookAt(																	/* ===�J�����r���[�ݒ�=== */
		m_posV.x , m_posV.y , m_posV.z,												// ���_
		m_posR.x , m_posR.y , m_posR.z,												// �����_
		m_VecU.x , m_VecU.y , m_VecU.z );											// ������x�N�g��

	glEnable( GL_DEPTH_TEST );													// Z�o�b�t�@�[ON
}

//==============================================================================
// �֐��� : void Set2D( void )
// ����   : void
// �߂�l : void
// ����   : 2D�J�����ݒ菈��
//==============================================================================
void CCameraGL::Set2D( void )
{
	glMatrixMode( GL_PROJECTION );												// �s�񃂁[�h�ؑ�
	glPushMatrix();																// �ˉe�s��̑ޔ�
	glLoadIdentity();															// �ˉe�s��̏�����
	glOrtho( 0 , SCREEN_WIDTH , SCREEN_HEIGHT , 0 , 0.0f , 1.0f );				// ���ˉe�ϊ��ݒ�

	glMatrixMode( GL_MODELVIEW );												// �s�񃂁[�h�ؑ�
	glPushMatrix();																// �r���[�s��̑ޔ�
	glLoadIdentity();															// �r���[�s��̏�����

	glDisable( GL_LIGHTING );													// ���C�gOFF
}

//==============================================================================
// �֐��� : void End2D( void )
// ����   : void
// �߂�l : void
// ����   : 2D�p�J�����s��I���ݒ�
//==============================================================================
void CCameraGL::End2D( void )
{
	glMatrixMode( GL_PROJECTION );												// �s�񃂁[�h�ؑ�
	glPopMatrix();																// �ˉe�s��̕���

	glMatrixMode( GL_MODELVIEW );												// �s�񃂁[�h�ؑ�
	glPopMatrix();																// �r���[�s��̕���

	glEnable( GL_LIGHTING );													// ���C�gON
}
