//==============================================================================
// �^�C�g��     :   �v���C���[�N���X
// �t�@�C����   :   player.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/11/28
//==============================================================================

//==============================================================================
// �X�V����: -2016/11/28 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "player.h"
#include "input.h"
#include "cameraGL.h"


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
// �֐��� : CPlayer()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CPlayer::CPlayer()
{
	m_axcel = 0.0275f;
	m_axcelAttack = 0.0f;
}

//==============================================================================
// �֐��� : ~CPlayer()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CPlayer::~CPlayer()
{

}

//==============================================================================
// �֐��� : CPlayer* Create( int charcterType )
// ����   : int charcterType : �L�����N�^�[�^�C�v
// �߂�l : CPlayer*�^
// ����   : ��������
//==============================================================================
CPlayer* CPlayer::Create( int charcterType )
{
	CPlayer* pNewInstance = new CPlayer;

	if( pNewInstance->Init( charcterType ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// �֐��� : bool Init( int charcterType )
// ����   : int charcterType
// �߂�l : bool�^ : ��������
// ����   : ����������
//==============================================================================
bool CPlayer::Init( int charcterType )
{
	if( CCharcter::Init( charcterType ) == false )
	{
		return false;
	}

	return true;
}

//==============================================================================
// �֐��� : void Uninit()
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CPlayer::Uninit()
{
	CCharcter::Uninit();
}

//==============================================================================
// �֐��� : void Update()
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CPlayer::Update( void )
{
	CCharcter::Update();

	if( m_actionState != ACTION_ATTACK && m_actionState != ACTION_DEAD)
		walk();		// �A�^�b�N��ԂɈڍs

	else if( m_actionState == ACTION_ATTACK &&
		abs(m_mov.x) <= 0.0001f &&
		abs(m_mov.z) <= 0.0001f )
	{// �A�^�b�N��Ԃ��猳�ɖ߂�
		m_actionState = ACTION_NONE;		// ��ԂȂ�
		m_axcel -= m_axcelAttack;			// �����x�����ɖ߂�
		m_gensui.x -= m_gensuiAttack.x;		// ������
		m_gensui.y -= m_gensuiAttack.y;		// ���Ƃ�
		m_gensui.z -= m_gensuiAttack.z;		// �߂�
	}

	// ���\��
	CDebugProc::GetDebugProc()->PrintDebugProc( "[ PLAYER ]\n" );
	CDebugProc::GetDebugProc()->PrintDebugProc( "POS : ( %3.3f : %3.3f : %3.3f )\n" , m_pos.x , m_pos.y , m_pos.z );
	CDebugProc::GetDebugProc()->PrintDebugProc( "ROT : ( %3.3f : %3.3f : %3.3f )\n" , m_rot.x , m_rot.y , m_rot.z );
	CDebugProc::GetDebugProc()->PrintDebugProc( "MOV : ( %3.3f : %3.3f : %3.3f )\n" , m_mov.x , m_mov.y , m_mov.z );

	//------------------------------------------
	// [ ��] ]
	//------------------------------------------
	Rotation();
}

//==============================================================================
// �֐��� : void Draw()
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CPlayer::Draw( void )
{
	CCharcter::Draw();
}

//==============================================================================
// �֐��� : void walk( void )
// ����   : void
// �߂�l : void
// ����   : �ړ�����
//==============================================================================
void CPlayer::walk( void )
{
	//---------------------------------------------------
	// [ �J�����̊p�x���擾 ]
	//---------------------------------------------------
	CManager* manager = GetManager();
	CCameraGL* camera = manager->GetCamera();
	VECTOR3 cameraRot = camera->GetRot();

	//------------------------------------------
	// [ ���͏��̎擾���� ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	if( pInput->GetPress( DIK_W ) == true &&
		pInput->GetPress( DIK_A ) == false &&
		pInput->GetPress( DIK_D ) == false)
	{// ��L�[�݂̂Ő^��Ɉړ�
		m_actionState = ACTION_MOVE;				// �ړ����
		m_rotMokuhyou.y = cameraRot.y;				// �ڕW�p�x��ݒ�
		m_mov.x -= sinf(cameraRot.y) * (m_axcel);	// �ړ��͂w��ݒ�
		m_mov.z -= cosf(cameraRot.y) * (m_axcel);	// �ړ��͂y��ݒ�
	}
	else if( pInput->GetPress( DIK_S ) == true &&
			 pInput->GetPress( DIK_A ) == false &&
			 pInput->GetPress( DIK_D ) == false)
	{// ���L�[�݂̂Ő^��Ɉړ�
		m_actionState = ACTION_MOVE;				// �ړ����
		m_rotMokuhyou.y = cameraRot.y + PI;			// �ڕW�p�x��ݒ�
		m_mov.x += sinf(cameraRot.y) * (m_axcel);	// �ړ��͂w��ݒ�
		m_mov.z += cosf(cameraRot.y) * (m_axcel);	// �ړ��͂y��ݒ�
	}
	else if( pInput->GetPress( DIK_A ) == true )
    {
		m_actionState = ACTION_MOVE;				// �ړ����

        if( pInput -> GetPress( DIK_W ) )
        {//�����
            m_rotMokuhyou.y = cameraRot.y + PI / 4;// ���x�ɌX���邩
            m_mov.x += sinf( cameraRot.y - PI / 4 - PI / 2 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 4 - PI / 2 ) * ( m_axcel );
        }
        else if( pInput -> GetPress( DIK_S ) )
        {//������
            m_rotMokuhyou.y = cameraRot.y + PI / 1.5; //���x�ɌX���邩
            m_mov.x += sinf( cameraRot.y - PI / 4 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 4 ) * ( m_axcel );
        }
        else
        {//����
            m_rotMokuhyou.y = cameraRot.y + PI / 2; //���x�ɌX���邩
            m_mov.x += sinf( cameraRot.y - PI / 2 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 2 ) * ( m_axcel );
        }
    }
    else if( pInput->GetPress( DIK_D ) == true )
    {
		m_actionState = ACTION_MOVE;				// �ړ����

        if( pInput -> GetPress( DIK_W ) )
        {//�E���
            m_rotMokuhyou.y = cameraRot.y - PI / 4;// ���x�ɌX���邩
            m_mov.x -= sinf( cameraRot.y - PI / 4 - PI / 2 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 4 - PI / 2 ) * ( m_axcel );
        }
        else if( pInput -> GetPress( DIK_S ) )
        {//�E����
            m_rotMokuhyou.y = cameraRot.y - PI / 1.5; //���x�ɌX���邩
            m_mov.x -= sinf( cameraRot.y - PI / 4 ) * ( m_axcel );
            m_mov.z += cosf( cameraRot.y - PI / 4 ) * ( m_axcel );
        }
        else
        {//�E�L�[�ŉE
            m_rotMokuhyou.y = cameraRot.y - PI / 2; //���x�ɌX���邩
            m_mov.x -= sinf( cameraRot.y - PI / 2 ) * ( m_axcel );
            m_mov.z -= cosf( cameraRot.y - PI / 2 ) * ( m_axcel );
        }
    }


	if( pInput -> GetPress( DIK_J ) )
	{//�A�^�b�N
		if( m_actionState != ACTION_ATTACK)				// �ړ����
		m_actionState = ACTION_ATTACK;
		m_axcel += m_axcelAttack;
		m_gensui.x += m_gensuiAttack.x;
		m_gensui.y += m_gensuiAttack.y;
		m_gensui.z += m_gensuiAttack.z;
		m_mov.x += sinf( m_rotMokuhyou.y ) * ( m_axcel );
        m_mov.z += cosf( m_rotMokuhyou.y ) * ( m_axcel );
	}
}

//==============================================================================
// �֐��� : �T���v��
// ����   : void
// �߂�l : void
// ����   : �T���v������
//==============================================================================

