//==============================================================================
// �^�C�g��     :   ���f���r���[�A�[�p�v���V�[�W��
// �t�@�C����   :   modelViewerProc.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/27
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/27 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WARNING�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "modelViewerProc.h"
#include "sceneGLModel.h"
#include "axis.h"
#include "grid3D.h"
#include <CommCtrl.h>

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================
#pragma comment( lib , "comctl32.lib" )		// �R�����R���g���[���p

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
CModelViewerProc* CModelViewerProc::m_pModelViewerProc = NULL;

//==============================================================================
// �֐��� : CModelViewerProc()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CModelViewerProc::CModelViewerProc()
{
	m_hInstance     = NULL;
	m_hWnd          = NULL;
	m_pMenuBar      = NULL;
	m_pStatusBar    = NULL;
	m_pToolBar      = NULL;
	m_pCameraDialog = NULL;
	m_pAccelerator  = NULL;
	m_pModel        = NULL;

	m_pAxis[ 0 ]    = NULL;
	m_pAxis[ 1 ]    = NULL;
	m_pAxis[ 2 ]    = NULL;
	m_pGrid         = NULL;
}

//==============================================================================
// �֐��� : ~CModelViewerProc()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CModelViewerProc::~CModelViewerProc()
{

}

//==============================================================================
// �֐��� : CModelViewerProc* Create( HINSTANCE hInstance , WORD menuID , WORD accelID )
// ����   : HINSTANCE hInstance : �C���X�^���X�n���h��
//          WORD menuID         : ���j���[�o�[�pID
//          WORD accelID        : �A�N�Z�����[�^�pID
// �߂�l : CModelViewerProc*�^
// ����   : ��������
//==============================================================================
CModelViewerProc* CModelViewerProc::Create( HINSTANCE hInstance , WORD menuID , WORD accelID )
{
	if( m_pModelViewerProc == NULL )
	{
		m_pModelViewerProc = new CModelViewerProc();

		if( m_pModelViewerProc->Init( hInstance , menuID , accelID ) == false )
		{
			m_pModelViewerProc->Release();
			m_pModelViewerProc = NULL;
		}
	}

	return m_pModelViewerProc;
}

//==============================================================================
// �֐��� : void Release( void )
// ����   : void
// �߂�l : void
// ����   : �������
//==============================================================================
void CModelViewerProc::Release( void )
{
	// �I������
	CModelViewerProc::Uninit();

	// ���g�̔j��
	delete this;
}

//==============================================================================
// �֐��� : bool Init( HINSTANCE hInstance , WORD menuID , WORD accelID )
// ����   : HINSTANCE hInstance : �C���X�^���X�n���h��
//          WORD menuID         : ���j���[�o�[�pID
//          WORD accelID        : �A�N�Z�����[�^�pID
// �߂�l : bool�^              : ��������
// ����   : ����������
//==============================================================================
bool CModelViewerProc::Init( HINSTANCE hInstance , WORD menuID , WORD accelID )
{
	// �A�N�Z�����[�^�̐���
	m_pAccelerator = CAccelerator::Create( hInstance , accelID );

	if( m_pAccelerator == NULL )
	{
		return false;
	}

	// ���j���[�̐���
	m_pMenuBar = new CMenuBar;
	m_pMenuBar->CreateMenuName( menuID );

	// �O���b�h����
	m_pGrid = CGrid3D::Create( 20 , 20 , 200.0f , 200.0f );

	// ������
	VECTOR3 root = VECTOR3( 0.0f , 0.0f , 0.0f );

	VECTOR3 axisX = VECTOR3( 2400.0f , 0.0f , 0.0f );
	VECTOR3 axisY = VECTOR3( 0.0f , 2400.0f , 0.0f );
	VECTOR3 axisZ = VECTOR3( 0.0f , 0.0f , 2400.0f );

	float lineVold = 4.0f;

	COLOR_F32 colorX = COLOR_F32( 1.0f , 0.0f , 0.0f , 1.0f );
	COLOR_F32 colorY = COLOR_F32( 0.0f , 1.0f , 0.0f , 1.0f );
	COLOR_F32 colorZ = COLOR_F32( 0.0f , 0.0f , 1.0f , 1.0f );

	m_pAxis[ 0 ] = CAxis::Create( root , axisX , lineVold , colorX );
	m_pAxis[ 1 ] = CAxis::Create( root , axisY , lineVold , colorY );
	m_pAxis[ 2 ] = CAxis::Create( root , axisZ , lineVold , colorZ );

	return true;	// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CModelViewerProc::Uninit( void )
{
	if( m_pMenuBar != NULL )
	{
		delete m_pMenuBar;
		m_pMenuBar = NULL;
	}

	if( m_pCameraDialog != NULL )
	{
		delete m_pCameraDialog;
		m_pCameraDialog = NULL;
	}

	if( m_pStatusBar != NULL )
	{
		m_pStatusBar->Release();
		m_pStatusBar = NULL;
	}

	if( m_pToolBar != NULL )
	{
		m_pToolBar->Release();
		m_pToolBar = NULL;
	}

	if( m_pAccelerator != NULL )
	{
		m_pAccelerator->Release();
		m_pAccelerator = NULL;
	}

	m_pModel = NULL;

	m_pAxis[ 0 ] = NULL;
	m_pAxis[ 1 ] = NULL;
	m_pAxis[ 2 ] = NULL;

	m_pGrid = NULL;
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CModelViewerProc::Update( void )
{
	if( m_pStatusBar != NULL )
	{
		m_pStatusBar->Update();
	}

	if( m_pToolBar != NULL )
	{
		m_pToolBar->Update();
	}
}

//==============================================================================
// �֐��� : bool MV_CreateDialog( HINSTANCE hInstance , HWND hWndParent )
// ����   : HINSTANCE hInstance : �C���X�^���X�n���h��
//          HWND hWndParen      : �e�E�B���h�E�n���h��
// �߂�l : bool�^
// ����   : ���f���r���[�A�[�p�_�C�A���O��������
//==============================================================================
bool CModelViewerProc::MV_CreateDialog( HINSTANCE hInstance , HWND hWndParent )
{
	// �J��������Ɋւ���_�C�A���O�̐���
	m_pCameraDialog = CCameraDialog::Create( hInstance , hWndParent , IDD_DIALOG1 );

	if( m_pCameraDialog == NULL )
	{
		return false;
	}

	return true;
}

//==============================================================================
// �֐��� : bool MV_CreateStatusBar( HWND hWndParent )
// ����   : HWND hWndParen      : �e�E�B���h�E�n���h��
// �߂�l : bool�^
// ����   : ���f���r���[�A�[�p�X�e�[�^�X�o�[��������
//==============================================================================
bool CModelViewerProc::MV_CreateStatusBar( HWND hWndParent )
{
	m_pStatusBar = CStatusBar::Create( hWndParent );

	return m_pStatusBar != NULL ? true : false;
}

//==============================================================================
// �֐��� : bool MV_CreateToolBar( HWND hWndParent )
// ����   : HWND hWndParen      : �e�E�B���h�E�n���h��
// �߂�l : bool�^
// ����   : ���f���r���[�A�[�p�c�[���o�[��������
//==============================================================================
bool CModelViewerProc::MV_CreateToolBar( HWND hWndParent )
{
	m_pToolBar = CToolBar::Create( hWndParent );

	return m_pToolBar != NULL ? true : false;
}
