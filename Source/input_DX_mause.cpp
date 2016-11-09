//==============================================================================
// �^�C�g��     :   DirectX�p�}�E�X���͏���
// �t�@�C����   :   input.DX.mause.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/03
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/03 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "input_DX_mause.h"
#include "debugProc.h"

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
// �֐��� : CInputDXMause()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CInputDXMause::CInputDXMause()
{
	m_pDevInput = NULL;

	for ( int i = 0 ; i < DIM_KEY_MAX ; i++ )
	{
		m_aKeyState[ i ] = 0;
		m_aKeyStateTrigger[ i ] = 0;
		m_aKeyStateRelease[ i ] = 0;
		m_aKeyStateRepeat[ i ] = 0;
		m_aKeyStateRepeatCount[ i ] = 0;
	}

	m_repeatDelayTime = 0;

	m_screenPos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	m_velocity  = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
}

//==============================================================================
// �֐��� : ~CInputDXMause()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CInputDXMause::~CInputDXMause()
{

}

//==============================================================================
// �֐��� : bool Init( HINSTANCE hInstance , HWND hWnd )
// ����   : HINSTANCE hInstance : �C���X�^���X�n���h��
//          HWND hWnd           : �E�B���h�E�n���h��
// �߂�l : void
// ����   : ����������
//==============================================================================
bool CInputDXMause::Init( HINSTANCE hInstance , HWND hWnd )
{
	// DirectInput�I�u�W�F�N�g�̐���
	if( CreateInputObject( hInstance , hWnd ) == false )
	{
		return false;		// �������s
	}

	// ���̓f�o�C�X�̐���
	if ( FAILED( GetInputObject()->CreateDevice(
		GUID_SysMouse,
		&m_pDevInput,
		NULL ) ) )
	{
		return false;		// �������s
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if ( FAILED( m_pDevInput->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		return false;		// �������s
	}

	// �����[�h�̐ݒ�
	DIPROPDWORD DIProp;																// ���[�h�ݒ�p�ϐ�

	DIProp.diph.dwSize       = sizeof( DIProp );									// 
	DIProp.diph.dwHeaderSize = sizeof( DIProp.diph );								// 
	DIProp.diph.dwObj        = 0;													// 
	DIProp.diph.dwHow        = DIPH_DEVICE;											// 
	DIProp.dwData            = DIPROPAXISMODE_REL;									// ���̒l�̃��[�h�ݒ�

	if( FAILED( m_pDevInput->SetProperty( DIPROP_AXISMODE , &DIProp.diph ) ) )	// �ݒ蕔��
	{
		return false;
	}

	// ���͌n���{�̂̐���
	if( FAILED( m_pDevInput->SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return false;
	}

	// �A�N�Z�X���̎擾
	m_pDevInput->Acquire();

	// ���s�[�g���Ԃ̑��
	m_repeatDelayTime = 20;

	// �E�B���h�E�n���h���i�[
	m_hwnd = hWnd;

	return true;	// ����������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CInputDXMause::Uninit( void )
{
	// ���̓f�o�C�X�̉��
	if ( m_pDevInput != NULL )
	{
		m_pDevInput->Unacquire();	// �A�N�Z�X�����
		m_pDevInput->Release();
		m_pDevInput = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̉��
	ReleaseInputObject();
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CInputDXMause::Update( void )
{
	// ���͏󋵂̎擾
	DIMOUSESTATE2 DIMouseState2;						// �}�E�X�̃X�e�[�^�X

	if ( SUCCEEDED( m_pDevInput->GetDeviceState( sizeof( DIMOUSESTATE2 ) , &DIMouseState2 ) ) )
	{
		for ( int nKeyCnt = 0; nKeyCnt < DIM_KEY_MAX; nKeyCnt++ )
		{
			m_aKeyStateTrigger[ nKeyCnt ] = DIMouseState2.rgbButtons[ nKeyCnt ] & ~m_aKeyState[ nKeyCnt ];		// �g���K�[����擾

			m_aKeyStateRelease[ nKeyCnt ] = ~DIMouseState2.rgbButtons[ nKeyCnt ] & m_aKeyState[ nKeyCnt ];		// �����[�X����擾

			// ���s�[�g����
			if ( m_aKeyStateRepeatCount[ nKeyCnt ] == m_repeatDelayTime )
			{
				m_aKeyStateRepeat[ nKeyCnt ] = DIMouseState2.rgbButtons[ nKeyCnt ];		// ���s�[�gON
			}
			// ���s�[�g���蕔��
			else if ( DIMouseState2.rgbButtons[ nKeyCnt ] )
			{
				m_aKeyStateRepeatCount[ nKeyCnt ]++;						// ���s�[�g�^�C�}�[�J�E���g�A�b�v
			}

			// �s�[�g�I������
			if ( m_aKeyStateRelease[ nKeyCnt ] )
			{
				m_aKeyStateRepeatCount[ nKeyCnt ] = 0;						// �^�C�}�[�J�E���g���Z�b�g
			}

			m_aKeyState[ nKeyCnt ] = DIMouseState2.rgbButtons[ nKeyCnt ];	// �v���X����擾
		}

		//-------------------------------------------------------
		// [ �}�E�X���W�̌��݈ʒu���擾�E�i�[ ]
		//-------------------------------------------------------
		// �J�[�\���ړ����x�̎擾
		m_velocity.x = ( float )DIMouseState2.lX;	// X
		m_velocity.y = ( float )DIMouseState2.lY;	// Y
		m_velocity.z = ( float )DIMouseState2.lZ;	// Z

		// �N���C�A���g�̈�ł̃}�E�X���W�����߂�
		POINT mausePos;											// �}�E�X�ʒu

		GetCursorPos( &mausePos );								// �}�E�X���W�擾
		ScreenToClient( m_hwnd , &mausePos );

		m_screenPos.x = ( float )mausePos.x;
		m_screenPos.y = ( float )mausePos.y;
		m_screenPos.z += ( float )DIMouseState2.lZ;
		
		// �N�����v����
		if( m_screenPos.x < 0.0f ) m_screenPos.x = 0.0f;
		else if( m_screenPos.x > SCREEN_WIDTH ) m_screenPos.x = SCREEN_WIDTH;
		
		if( m_screenPos.y < 0.0f ) m_screenPos.y = 0.0f;
		else if( m_screenPos.y > SCREEN_HEIGHT ) m_screenPos.y = SCREEN_HEIGHT;

	}
	else
	{
		m_pDevInput->Acquire();		// �A�N�Z�X���擾
	}
}


//==============================================================================
// �֐��� : bool GetPress( int nKey )
// ����   : int nKey : ����Ώۂ̃L�[
// �߂�l : bool�^   : ��������
// ����   : Press����擾����
//==============================================================================
bool CInputDXMause::GetPress( int nKey )
{
	return ( m_aKeyState[ nKey ] & 0x80 ) ? true : false;	// �擪bit����A����������擾����
}

//==============================================================================
// �֐��� : bool GetTrigger( int nKey )
// ����   : int nKey : ����Ώۂ̃L�[
// �߂�l : bool�^   : ��������
// ����   : Trigger����擾����
//==============================================================================
bool CInputDXMause::GetTrigger( int nKey )
{
	return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false;	// �擪bit����A����������擾����
}

//==============================================================================
// �֐��� : bool GetRelease( int nKey )
// ����   : int nKey : ����Ώۂ̃L�[
// �߂�l : bool�^   : ��������
// ����   : Release����擾����
//==============================================================================
bool CInputDXMause::GetRelease( int nKey )
{
	return ( m_aKeyStateRelease[ nKey ] & 0x80 ) ? true : false;	// �擪bit����A����������擾����
}

//==============================================================================
// �֐��� : bool GetRepeat( int nKey )
// ����   : int nKey : ����Ώۂ̃L�[
// �߂�l : bool�^   : ��������
// ����   : Repeat����擾����
//==============================================================================
bool CInputDXMause::GetRepeat( int nKey )
{
	if ( m_aKeyStateRepeatCount[ nKey ] == 1 )
	{
		return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false;	// �ŏ��̈��́Atrigger�Ŕ�����Ƃ�
	}
	else
	{
		return ( m_aKeyStateRepeat[ nKey ] & 0x80 ) ? true : false;		// �擪bit����A����������擾����
	}
}

//==============================================================================
// �֐��� : D3DXVECTOR3 GetPosToWorld( D3DXMATRIX mtxProj , D3DXMATRIX mtxView , float fZ )
// ����   : D3DXMATRIX mtxProj : �v���W�F�N�V�����s��
//          D3DXMATRIX mtxView : �r���[�s��
//          float fZ           : �ˉe��Ԃ�Z�l( 0.0 �` 1.0 )
// �߂�l : D3DXVECTOR3�^      : ��������
// ����   : �}�E�X���[���h���W�擾����
//==============================================================================
D3DXVECTOR3 CInputDXMause::GetPosToWorld( D3DXMATRIX mtxProj , D3DXMATRIX mtxView , float fZ )
{
	D3DXMATRIX mtxInvView;				// �r���[�s��p
	D3DXMATRIX mtxInvProj;				// �v���W�F�N�V�����s��p
	D3DXMATRIX mtxVp , mtxInvVp;		// �r���[�|�[�g�s��p

	// �r���[�̋t�s��擾
	D3DXMatrixInverse( &mtxInvView , NULL , &mtxView );

	// �v���W�F�N�V�����̋t�s��擾
	D3DXMatrixInverse( &mtxInvProj , NULL , &mtxProj );

	// �r���[�|�[�g�̋t�s��擾
	D3DXMatrixIdentity( &mtxVp );

	mtxVp._11 = SCREEN_WIDTH / 2.0f;
	mtxVp._22 = -SCREEN_HEIGHT / 2.0f;
	mtxVp._41 = SCREEN_WIDTH / 2.0f;
	mtxVp._42 = SCREEN_HEIGHT / 2.0f;

	D3DXMatrixInverse( &mtxInvVp , NULL , &mtxVp );

	// �t�ϊ�
	D3DXVECTOR3 out;
	D3DXVECTOR3 mausePos = m_screenPos;
	mausePos.z = fZ;
	D3DXMATRIX tmp = mtxInvVp * mtxInvProj * mtxInvView;
	D3DXVec3TransformCoord( &out , &mausePos , &tmp );

	return out;
}

//==============================================================================
// �֐��� : ~CInputDXMause()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
