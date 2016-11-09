//==============================================================================
// �^�C�g��     :   OpenGL�p�G�f�B�^�[�J��������
// �t�@�C����   :   editorCameraGL.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/07/10
//==============================================================================

//==============================================================================
// �X�V����: -2016/07/10 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "editorCameraGL.h"
#include "rendererGL.h"
#include "input_DX_mause.h"

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
// �֐��� : CEditorCameraGL()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CEditorCameraGL::CEditorCameraGL()
{
	m_angleH = 0.0f;
	m_angleV = 0.0f;
}

//==============================================================================
// �֐��� : ~CEditorCameraGL()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CEditorCameraGL::~CEditorCameraGL()
{
}

//==============================================================================
// �֐��� : bool Init( VECTOR3 posV , VECTOR3 posR )
// ����   : void
// �߂�l : void
// ����   : ����������
//==============================================================================
bool CEditorCameraGL::Init( VECTOR3 posV , VECTOR3 posR )
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
void CEditorCameraGL::Uninit( void )
{
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CEditorCameraGL::Update( void )
{
	//------------------------------------------
	// [ ���͏��̎擾���� ]
	//------------------------------------------
	CInput*        pInputKeyboard = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );
	CInputDXMause* pInputMause    = dynamic_cast< CInputDXMause* >( CInput::GetInput( INPUT_TYPE_DX_MOUSE ) );

	bool bPressW            = false;
	bool bPressS            = false;
	bool bPressA            = false;
	bool bPressD            = false;
	bool bPressQ            = false;
	bool bPressE            = false;
	bool bPressZ            = false;
	bool bPressC            = false;
	bool bPressT            = false;
	bool bPressB            = false;
	bool bPressY            = false;
	bool bPressN            = false;
	bool bPressEnter        = false;
	bool isPressMauseRight  = false;
	bool isPressMauseCenter = false;

	bool bTrigEnter         = false;

	VECTOR3 mauseVel;			// �}�E�X�̉����x

	if( pInputKeyboard != NULL )
	{
		if( m_bMove == true )
		{
			bPressW     = pInputKeyboard->GetPress( DIK_W );
			bPressS     = pInputKeyboard->GetPress( DIK_S );
			bPressA     = pInputKeyboard->GetPress( DIK_A );
			bPressD     = pInputKeyboard->GetPress( DIK_D );
			bPressQ     = pInputKeyboard->GetPress( DIK_Q );
			bPressE     = pInputKeyboard->GetPress( DIK_E );
			bPressZ     = pInputKeyboard->GetPress( DIK_Z );
			bPressC     = pInputKeyboard->GetPress( DIK_C );
			bPressT     = pInputKeyboard->GetPress( DIK_T );
			bPressB     = pInputKeyboard->GetPress( DIK_B );
			bPressY     = pInputKeyboard->GetPress( DIK_Y );
			bPressN     = pInputKeyboard->GetPress( DIK_N );
			bPressEnter = pInputKeyboard->GetPress( DIK_RETURN );
		}

		bTrigEnter = pInputKeyboard->GetTrigger( DIK_RETURN );
	}

	if( pInputMause == NULL )
	{
		return;		// �}�E�X�f�o�C�X���K�v�s���Ȃ��߁A����ȏ㏈�������Ȃ�
	}

	mauseVel.x = pInputMause->GetVelocity().x;
	mauseVel.y = pInputMause->GetVelocity().y;
	mauseVel.z = pInputMause->GetVelocity().z;

	isPressMauseRight  = pInputMause->GetPress( DIM_RIGHT );
	isPressMauseCenter = pInputMause->GetPress( DIM_CENTER );

	//------------------------------------------
	// [ �J�������쏈�� ]
	//------------------------------------------
	// ���_�E�����_����]���W�ւ̕ϊ�
	m_angleH = GetHAngle( &m_posR , &m_posV );
	m_angleV = GetVAngle( &m_posR , &m_posV );
	
	// ���͂����ɉ�]����
	// ���_�ړ�( ��] )
	VECTOR2 radMove = VECTOR2( 0.0f , 0.0f );	// �}�E�X�ړ��l�����ɂ����J�����p�x�̈ړ���

	if( isPressMauseRight )
	{
		radMove = MoveRad( mauseVel );
	}

	m_angleH += radMove.x;		// ���������ւ̉�]

	// -�΁`�΂ɃN�����v
	if( m_angleH > PI )  { m_angleH -= PI2; }
	if( m_angleH < -PI ) { m_angleH += PI2; }

	m_angleV += radMove.y;		// ���������ւ̉�]

	// -��/2�`��/2�ɃN�����v
	if( m_angleV > PI * 0.50f )  { m_angleV = PI * 0.499f; }
	if( m_angleV < -PI * 0.50f ) { m_angleV = -PI * 0.499f; }
	
	// ���s�ړ�
	VECTOR3 vTranslate = VECTOR3( 0.0f , 0.0f , 0.0f );

	if( isPressMauseCenter )
	{
		vTranslate = MoveTranslate( mauseVel );
	}

	// �Y�[������
	if( fabs( mauseVel.z ) > 0.10f )
	{
		mauseVel.z < 0.0f ? m_fDistance += 0.10f : m_fDistance -= 0.10f;

		if( m_fDistance < 0.10f ){ m_fDistance = 0.10f; }
	}

	//------------------------------------------
	// [ ��]���W���R�������W�ւ̕ϊ� ]
	//------------------------------------------
	m_posV = VECTOR3( 0.0f , 0.0f , 0.0f );						// ���_�̏����������Ă���

	// HAngle/VAngle���s��ɕϊ�����
	MATRIX mRot;

	MatrixIdentity( &mRot );
	MatrixRotationYawPitchRoll( &mRot , m_angleH , m_angleV , 0.0f );

	// ���s�ړ�
	Vec3TransformCoord( &vTranslate , &vTranslate , &mRot );
	vTranslate.y = 0.0f;										// XZ���ʂł̈ړ��Ȃ̂�Y�ړ��l�͖�������
	Vec3Add( &m_posR , &m_posR , &vTranslate );					// ���_�𓮂���
	
	// ��]
	VECTOR3 vDir = VECTOR3( 0.0f , 0.0f , m_fDistance );
	Vec3TransformCoord( &vDir , &vDir , &mRot );				// �����x�N�g���̉�]
	Vec3Add( &m_posV , &m_posR , &vDir );

}

//==============================================================================
// �֐��� : float GetHAngle( VECTOR3* vEye , VECTOR3* vTgt )
// ����   : VECTOR3* vPosV : ���_
//          VECTOR3* vPosR : �����_
// �߂�l : float�^        : �����̃��W�A���p��ԋp
// ����   : ���������擾����
//==============================================================================
float CEditorCameraGL::GetHAngle( VECTOR3* vPosV , VECTOR3* vPosR )
{
	// �����_�ւ̌����x�N�g�������߂�
	VECTOR3 vDir;
	Vec3Subtract( &vDir , vPosR , vPosV );

	// HAngle(XZ���ʂł̊p�x)�����߂�
	float rad = atan2f( -vDir.z , vDir.x );

	rad += PI * 0.5f;

	// -�΁`�΂ɃN�����v
	if( rad > PI )  { rad -= PI2; }
	if( rad < -PI ) { rad += PI2; }

	return rad;
}

//==============================================================================
// �֐��� : float GetVAngle( VECTOR3* vPosV , VECTOR3* vPosR )
// ����   : VECTOR3* vPosV : ���_
//          VECTOR3* vPosR : �����_
// �߂�l : float�^        : �����̃��W�A���p��ԋp
// ����   : ���������擾
//==============================================================================
float CEditorCameraGL::GetVAngle( VECTOR3* vPosV , VECTOR3* vPosR )
{
	// �����_�ւ̌����x�N�g�������߂�
	VECTOR3 vDir;
	Vec3Subtract( &vDir , vPosR , vPosV );

	float fFront;
	{
		// �J�����̑O�������l
		VECTOR3 vFront;
		vFront = vDir;

		vFront.y = 0;	// XZ���ʂł̋����Ȃ̂�Y�͂���Ȃ�
		fFront = Vec3Length( &vFront );
	}

	// Y����XZ���ʂ̑O�������Ƃ̊p�x�����߂�
	float rad = atan2f( -vDir.y , fFront );

	// -��/2�`��/2�ɃN�����v
	if( rad > PI * 0.50f )  { rad = PI * 0.50f; }
	if( rad < -PI * 0.50f ) { rad = -PI * 0.50f; }

	return rad;
}

//==============================================================================
// �֐��� : float GetVAngle( VECTOR3* vPosV , VECTOR3* vPosR )
// ����   : VECTOR3 vel : �}�E�X�����x
// �߂�l : VECTOR2�^   : ���W�A���ړ��ʂ�ԋp
// ����   : �}�E�X�̉����x����p�x�ړ��ʂ𐶐����鏈��
//==============================================================================
VECTOR2 CEditorCameraGL::MoveRad( VECTOR3 vel )
{
	VECTOR2 out;
	const float maxMoveRad = PI * 0.010f;

	// �ړ��ʌW�����Βl�Łw 1.0 �x�ɃN�����v
	out.x = vel.x < 0.0f ? max( vel.x , -1.0f ) : min( vel.x , 1.0f );
	out.y = vel.y < 0.0f ? max( vel.y , -1.0f ) : min( vel.y , 1.0f );

	// �f�b�h�]�[����ݒ�
	out.x = fabs( vel.x ) < 0.10f ? 0.0f : vel.x;
	out.y = fabs( vel.y ) < 0.10f ? 0.0f : vel.y;

	// �Z�o�����W�������ɁA�ړ��ʂ�ݒ�
	out.x *= maxMoveRad;
	out.y *= maxMoveRad;

	return out;
}

//==============================================================================
// �֐��� : float GetVAngle( VECTOR3* vPosV , VECTOR3* vPosR )
// ����   : VECTOR3 vel : �}�E�X�����x
// �߂�l : VECTOR2�^   : ���W�A���ړ��ʂ�ԋp
// ����   : �}�E�X�̉����x����A���s�ړ��ʂ��Z�o
//==============================================================================
VECTOR3 CEditorCameraGL::MoveTranslate( VECTOR3 vel )
{
	VECTOR3 out = VECTOR3( 0.0f , 0.0f , 0.0f );
	const float maxMoveT = 10.0f;

	// �ړ��ʌW�����Βl�Łw 1.0 �x�ɃN�����v
	out.x = vel.x < 0.0f ? max( vel.x , -1.0f ) : min( vel.x , 1.0f );
	out.z = vel.y < 0.0f ? max( vel.y , -1.0f ) : min( vel.y , 1.0f );

	// �f�b�h�]�[����ݒ�
	out.x = fabs( vel.x ) < 0.10f ? 0.0f : vel.x;
	out.z = fabs( vel.y ) < 0.10f ? 0.0f : vel.y;

	// �Z�o�����W�������ɁA�ړ��ʂ�ݒ�
	out.x *= maxMoveT;
	out.z *= maxMoveT;

	return out;
}

