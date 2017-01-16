//==============================================================================
// �^�C�g��     :   �C���X�^���X�Ǘ��N���X
// �t�@�C����   :   manager.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/09
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/09 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "client.h"

#include "manager.h"

#include "sceneGL.h"
#include "lightGL.h"
#include "soundAL.h"
#include "editorCameraGL.h"
#include "fade.h"
#include "autoRotationCamera.h"

// �e�V�[���̃C���N���[�h
#include "sceneGLModel.h"
#include "sceneGL3D.h"
#include "sceneGL2D.h"
#include "box.h"
#include "skyBox.h"
#include "editorModel.h"
#include "testBox.h"

// �e���[�h�̃C���N���[�h
#include "title.h"
#include "game.h"

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
ALuint g_buffer , g_source;

//==============================================================================
// �ÓI�ϐ�
//==============================================================================

//==============================================================================
// �֐��� : CManager()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CManager::CManager()
{
	m_pRenderer = NULL;
	m_pCamera   = NULL;
	m_pMode     = NULL;

	m_pClient = NULL;
}

//==============================================================================
// �֐��� : ~CManager()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CManager::~CManager()
{
}

//==============================================================================
// �֐��� : bool Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
// ����   : HINSTANCE hInstance
//          HWND hWnd
//          bool bWindow
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CManager::Init( HINSTANCE hInstance , HWND hWnd , bool bWindow )
{
	CDebugConsole::GetInstance()->Init();

	//---------------------------------------------
	// [ �����_���[�̏����� ]
	//---------------------------------------------
	m_pRenderer = CRenderer::Create( RENDERER_TYPE_GL );		// OpenGL�Ő���

	if( m_pRenderer->Init( hInstance , hWnd , bWindow ) == false )
	{
		return false;											// �������s
	}

	//---------------------------------------------
	// [ ���͌n���̐��� ]
	//---------------------------------------------
	CInput::Create( INPUT_TYPE_DX_KEYBOARD , hInstance , hWnd );	// DirectInput���L�[�{�[�h�̐���
	CInput::Create( INPUT_TYPE_DX_MOUSE , hInstance , hWnd );		// DirectInput���}�E�X�̐���

	//---------------------------------------------
	// [ �J�����̐��� ]
	//---------------------------------------------
	m_pCamera = new CAutoRotationCamera;
	//m_pCamera->Init( VECTOR3( 0.0f , 3.0f , 5.0f ) );

	m_pCamera->Init( VECTOR3( 0.0f , 80.0f , 80.0f ) );

	//---------------------------------------------
	// [ ���C�g�̐��� ]
	//---------------------------------------------
	LIGHT_PARAM param;

	// 0�Ԗ�
	param.pos = VECTOR4( -1.0f , 1.0f , -1.0f , 0.0f );

	param.dir = VECTOR3( 1.0f , -1.0f , 1.0f );
	Vec3Normalize( &param.dir , &param.dir );

	param.diffuse = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );
	param.specular = COLOR_F32( 0.5f , 0.5f , 0.5f , 1.0f );

	CLightGL::Create( LIGHT0 , &param , LIGHT_TYPE_DIRECTIONAL );	// ��������

	CLight::GetLight( LIGHT0 )->Enable();							// �L����

	// 1�Ԗ�
	param.pos = VECTOR4( 1.0f , -1.0f , 2.0f , 0.0f );

	param.dir = VECTOR3( -1.0f , 1.0f , -1.0f );
	Vec3Normalize( &param.dir , &param.dir );

	param.diffuse = COLOR_F32( 0.7f , 0.7f , 0.7f , 1.0f );
	param.specular = COLOR_F32( 0.5f , 0.5f , 0.5f , 1.0f );

	CLightGL::Create( LIGHT1 , &param , LIGHT_TYPE_DIRECTIONAL );	// ��������

	CLight::GetLight( LIGHT1 )->Enable();							// �L����

	// 2�Ԗ�
	param.pos = VECTOR4( 0.0f , -1.0f , -1.0f , 0.0f );

	param.dir = VECTOR3( 0.0f , 1.0f , 1.0f );
	Vec3Normalize( &param.dir , &param.dir );

	param.diffuse = COLOR_F32( 0.5f , 0.5f , 0.5f , 1.0f );
	param.specular = COLOR_F32( 0.5f , 0.5f , 0.5f , 1.0f );

	CLightGL::Create( LIGHT2 , &param , LIGHT_TYPE_DIRECTIONAL );	// ��������

	CLight::GetLight( LIGHT2 )->Enable();							// �L����

	//---------------------------------------------
	// [ �t�F�[�h�����̏����� ]
	//---------------------------------------------
	CFade::Init();

	//---------------------------------------------
	// [ �e�V�[���̐��� ]
	//---------------------------------------------
	//CSkyBox* pSkyBox = new CSkyBox;

	//pSkyBox->Init( "data\\TEXTURE\\skyBox00.png" );

	//CSceneGL3D::Create( "data\\TEXTURE\\filed00.jpg" );

	//CSceneGL2D::Create( "data\\TEXTURE\\skyBox00.png" );

	//CSceneGLModel::Create( "data\\MODEL\\miku_01.obj" );

	//CMotionEditModel::Create();

	//---------------------------------------------
	// [ �f�o�b�O�v���V�[�W���̐��� ]
	//---------------------------------------------
	CDebugProc::Create();

	//---------------------------------------------
	// [ �������[�h�̐��� ]
	//---------------------------------------------
	CFade::FadeStart( new CGame( 0 , 1 ) , 120 );

	//---------------------------------------------
	// [ �T�E���h�̐��� ]
	//---------------------------------------------
	CSound* pSound = CSoundAL::Create( 64 );		// �T�E���h��������

	//pSound->Play( pSound->SOUND_LABEL_BGM_TEST00 );

	// �N���C�A���g����
	//m_pClient = CClient::Create();

	return true;	// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CManager::Uninit( void )
{
	//---------------------------------------------
	// [ �����_���[�̉�� ]
	//---------------------------------------------
	if( m_pRenderer != NULL )
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//---------------------------------------------
	// [ ���͌n���̉�� ]
	//---------------------------------------------
	CInput::ReleaseALL();

	//---------------------------------------------
	// [ �J�����̉�� ]
	//---------------------------------------------
	if( m_pCamera != NULL )
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//---------------------------------------------
	// [ ���C�g�̉�� ]
	//---------------------------------------------
	CLight::ReleaseAll();		// ���C�g�������

	//---------------------------------------------
	// [ �t�F�[�h�����̉�� ]
	//---------------------------------------------
	CFade::Uninit();

	//---------------------------------------------
	// [ ���[�h�̉�� ]
	//---------------------------------------------
	if( m_pMode != NULL )
	{
		m_pMode->Release();
		m_pMode = NULL;
	}

	//---------------------------------------------
	// [ �f�o�b�O�v���V�[�W���̉�� ]
	//---------------------------------------------
	CDebugProc::Release();

	//---------------------------------------------
	// [ �T�E���h�̉�� ]
	//---------------------------------------------
	CSound* pSound = CSoundAL::GetSound();

	if( pSound != NULL )
	{
		pSound->Release();
		pSound = NULL;
	}

	//---------------------------------------------
	// [ ���f���f�[�^�̉�� ]
	//---------------------------------------------
	CModel::ReleaseAll();

	// �N���C�A���g�I��
	if( m_pClient != NULL )
	{
		m_pClient->SetFinishFlag( true );
	}

	CDebugConsole::GetInstance()->Uninit();
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CManager::Update( void )
{
	//---------------------------------------------
	// [ �V�X�e���n�̍X�V���� ]
	//---------------------------------------------
	CInput::UpdateAll();		// ���͌n���̍X�V����

	if( m_pCamera != NULL )
	{
		m_pCamera->Update();	// �J�����̍X�V����
	}

	CLight::UpdateAll();		// ���C�g�̍X�V����

	//---------------------------------------------
	// [ �e�V�[���̍X�V���� ]
	//---------------------------------------------
	if( m_pMode != NULL )
	{
		m_pMode->Update();
	}

	//---------------------------------------------
	// [ �t�F�[�h�����̍X�V ]
	//---------------------------------------------
	CFade::Update();

	//---------------------------------------------
	// [ �f�o�b�O�v���V�[�W���̍X�V���� ]
	//---------------------------------------------
	int fps = GetFps();

	CDebugProc::GetDebugProc()->PrintDebugProc( "FPS : %d\n" , fps );

	CDebugProc::GetDebugProc()->Update();

	int test_i = 24;
	float test_f = 2.043f;

	//CDebugProc::GetDebugProc()->PrintDebugProc( "\ntest01\n\n\nt\n\n" , test_i , test_f );
	//CDebugProc::GetDebugProc()->PrintDebugProc( "test03" , test_i , test_f );

	//CDebugProc::GetDebugProc()->PrintDebugProc( "test00\n%d\f%1.2f\n" , test_i , test_f );
	//CDebugProc::GetDebugProc()->PrintDebugProc( "�l�r�S�V�b�N\n" );
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CManager::Draw( void )
{
	//---------------------------------------
	// [ �`�揈�� ]
	//---------------------------------------
	if( m_pRenderer->BeginScene() == true )
	{
		if( m_pCamera != NULL )
		{
			m_pCamera->Set();			// �J�����s��̐ݒ�
		}

		CLight::SetLightAll();			// ���C�g�̐ݒ菈��

		if( m_pMode != NULL )
		{
			m_pMode->Draw();			// �e�V�[���`��
		}

		CFade::Draw();					// �t�F�[�h�`��

		//---------------------------------------------
		// [ �f�o�b�O�v���V�[�W���̕`�揈�� ]
		//---------------------------------------------
		CDebugProc::GetDebugProc()->Draw();

		//---------------------------------------------
		// [ �`��I������ ]
		//---------------------------------------------
		m_pRenderer->EndScene();
		m_pRenderer->SwapBuffer();
	}
}


//==============================================================================
// �֐��� : bool SetMode( CMode* pMode )
// ����   : CMode* pMode : �ݒ肷�郂�[�h
// �߂�l : bool�^
// ����   : ���[�h�ݒ菈��
//==============================================================================
bool CManager::SetMode( CMode* pMode )
{
	// �G���[�`�F�b�N
	if( pMode == NULL )
	{
		MessageBox( NULL , "ErrorCode #0\n���̃��[�h���ݒ肳��Ă��܂���B\n" , "Error" , MB_OK | MB_ICONERROR );
		return false;	// ���[�h���ݒ肳��Ă��Ȃ�
	}

	// ���ݐݒ肳��Ă��郂�[�h�̔j��
	if( m_pMode != NULL )
	{
		m_pMode->Release();
		m_pMode = NULL;
	}

	// �V�������[�h�̐ݒ�
	m_pMode = pMode;

	if( m_pMode->Init() == false )
	{
		m_pMode->Release();
		m_pMode = NULL;

		MessageBox( NULL , "ErrorCode #1\n���������s���܂����B�Q�[�����I�����܂��B\n" , "Error" , MB_OK | MB_ICONERROR );

		exit( -1 );

		return false;
	}

	// �S��������
	return true;
}
