//==============================================================================
// �^�C�g��     :   DirectX�p�L�[�{�[�h���͏���
// �t�@�C����   :   input.DX.Keyboard.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/04/26
//==============================================================================

//==============================================================================
// �X�V����: -2016/04/26 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "input_DX_Keyboard.h"

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
// �֐��� : CInputDXKeyboard()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CInputDXKeyboard::CInputDXKeyboard()
{
	m_pDevKeyboard = NULL;

	for( int i = 0 ; i < DX_KEYBOARD_KEY_MAX ; i++ )
	{
		m_aKeyState[ i ]            = 0;
		m_aKeyStateTrigger[ i ]     = 0;
		m_aKeyStateRelease[ i ]     = 0;
		m_aKeyStateRepeat[ i ]      = 0;
		m_aKeyStateRepeatCount[ i ] = 0;
	}

	m_repeatDelayTime = 0;
}

//==============================================================================
// �֐��� : ~CInputDXKeyboard()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CInputDXKeyboard::~CInputDXKeyboard()
{

}

//==============================================================================
// �֐��� : bool Init( HINSTANCE hInstance , HWND hWnd )
// ����   : HINSTANCE hInstance : �C���X�^���X�n���h��
//          HWND hWnd           : �E�B���h�E�n���h��
// �߂�l : void
// ����   : ����������
//==============================================================================
bool CInputDXKeyboard::Init( HINSTANCE hInstance , HWND hWnd )
{
	/* ===DirectInput�I�u�W�F�N�g�̐���=== */
	if( CreateInputObject( hInstance , hWnd ) == false )
	{
		return false;		// �������s
	}

	/* ===���̓f�o�C�X�̐���=== */
	if( FAILED( GetInputObject()->CreateDevice(
		GUID_SysKeyboard,
		&m_pDevKeyboard,
		NULL ) ) )
	{
		return false;		// �������s
	}

	/* ===�f�[�^�t�H�[�}�b�g�̐ݒ�=== */
	if( FAILED( m_pDevKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		return false;		// �������s
	}

	/* ===���͌n���{�̂̐���=== */
	if( FAILED( m_pDevKeyboard->SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return false;		// �������s
	}

	/* ===�A�N�Z�X���̎擾=== */
	m_pDevKeyboard->Acquire();

	/* ===���s�[�g���Ԃ̑��=== */
	m_repeatDelayTime = 20;

	return true;	// ����������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CInputDXKeyboard::Uninit( void )
{
	/* ===���̓f�o�C�X�̉��=== */
	if( m_pDevKeyboard != NULL )
	{
		m_pDevKeyboard->Unacquire();	// �A�N�Z�X�����
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}

	/* ===DirectInput�I�u�W�F�N�g�̉��=== */
	ReleaseInputObject();
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CInputDXKeyboard::Update( void )
{
	/* ===���͏󋵂̎擾=== */
	BYTE aKeyState[ DX_KEYBOARD_KEY_MAX ];			// �L�[�X�e�[�^�X

	if( SUCCEEDED( m_pDevKeyboard->GetDeviceState( sizeof( aKeyState ) , &aKeyState[ 0 ] ) ) )
	{
		for( int nKeyCnt = 0; nKeyCnt < DX_KEYBOARD_KEY_MAX; nKeyCnt++ )
		{
			m_aKeyStateTrigger[ nKeyCnt ] = aKeyState[ nKeyCnt ] & ~m_aKeyState[ nKeyCnt ];		// �g���K�[����擾

			m_aKeyStateRelease[ nKeyCnt ] = ~aKeyState[ nKeyCnt ] & m_aKeyState[ nKeyCnt ];		// �����[�X����擾

			/* ===���s�[�g����=== */
			if( m_aKeyStateRepeatCount[ nKeyCnt ] == m_repeatDelayTime )
			{
				m_aKeyStateRepeat[ nKeyCnt ] = aKeyState[ nKeyCnt ];		// ���s�[�gON
			}
			/* ===���s�[�g���蕔��=== */
			else if( aKeyState[ nKeyCnt ] )
			{
				m_aKeyStateRepeatCount[ nKeyCnt ]++;						// ���s�[�g�^�C�}�[�J�E���g�A�b�v
			}

			/* ===���s�[�g�I������=== */
			if( m_aKeyStateRelease[ nKeyCnt ] )
			{
				m_aKeyStateRepeatCount[ nKeyCnt ] = 0;						// �^�C�}�[�J�E���g���Z�b�g
			}

			m_aKeyState[ nKeyCnt ] = aKeyState[ nKeyCnt ];					// �v���X����擾
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();	// �A�N�Z�X���擾
	}
}


//==============================================================================
// �֐��� : bool GetPress( int nKey )
// ����   : int nKey : ����Ώۂ̃L�[
// �߂�l : bool�^   : ��������
// ����   : Press����擾����
//==============================================================================
bool CInputDXKeyboard::GetPress( int nKey )
{
	return ( m_aKeyState[ nKey ] & 0x80 ) ? true : false;	// �擪bit����A����������擾����
}

//==============================================================================
// �֐��� : bool GetTrigger( int nKey )
// ����   : int nKey : ����Ώۂ̃L�[
// �߂�l : bool�^   : ��������
// ����   : Trigger����擾����
//==============================================================================
bool CInputDXKeyboard::GetTrigger( int nKey )
{
	return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false;	// �擪bit����A����������擾����
}

//==============================================================================
// �֐��� : bool GetRelease( int nKey )
// ����   : int nKey : ����Ώۂ̃L�[
// �߂�l : bool�^   : ��������
// ����   : Release����擾����
//==============================================================================
bool CInputDXKeyboard::GetRelease( int nKey )
{
	return ( m_aKeyStateRelease[ nKey ] & 0x80 ) ? true : false;	// �擪bit����A����������擾����
}

//==============================================================================
// �֐��� : bool GetRepeat( int nKey )
// ����   : int nKey : ����Ώۂ̃L�[
// �߂�l : bool�^   : ��������
// ����   : Repeat����擾����
//==============================================================================
bool CInputDXKeyboard::GetRepeat( int nKey )
{
	if( m_aKeyStateRepeatCount[ nKey ] == 1 )
	{
		return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false;	// �ŏ��̈��́Atrigger�Ŕ�����Ƃ�
	}
	else
	{
		return ( m_aKeyStateRepeat[ nKey ] & 0x80 ) ? true : false;		// �擪bit����A����������擾����
	}
}

//==============================================================================
// �֐��� : ~CInputDXKeyboard()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
