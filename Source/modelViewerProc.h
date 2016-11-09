//==============================================================================
// �^�C�g��     :   ���f���r���[�A�[�v���V�[�W��
// �t�@�C����   :   modelViewerProc.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/27
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/27 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include <Windows.h>
#include "resource.h"
#include "MV_menuBar.h"
#include "MV_cameraDialog.h"
#include "MV_statusBar.h"
#include "MV_toolBar.h"
#include "MV_accelerator.h"

using namespace ModelViewer;

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �O���錾
//==============================================================================
class CSceneGLModel;
class CAxis;
class CGrid3D;

//==============================================================================
// �N���X�錾
//==============================================================================
class CModelViewerProc
{
	//---------------------------------------------
	// [ �����o�֐� ]
	//---------------------------------------------
public:
	// ��������
	static CModelViewerProc* Create( HINSTANCE hInstance , WORD menuID , WORD accelID );

	// �j������
	void Release( void );

	// ����������
	bool Init( HINSTANCE hInstance , WORD menuID , WORD accelID );

	// �I������
	void Uninit( void );

	// �X�V����
	void Update( void );

	// �C���X�^���X�擾
	static CModelViewerProc* GetModelViewerProc( void ){ return m_pModelViewerProc; }

	// ���j���[�o�[�����擾
	CMenuBar* GetMenu( void ){ return m_pMenuBar; }

	// �E�B���h�E�n���h���֘A
	HWND GetHWND( void ){ return m_hWnd; }
	void SetHWND( HWND hWnd ){ m_hWnd = hWnd; }

	// ���f���֘A
	CSceneGLModel* GetModel( void ){ return m_pModel; }
	void SetModel( CSceneGLModel* pModel ){ m_pModel = pModel; }

	// �_�C�A���O�֘A
	bool MV_CreateDialog( HINSTANCE hInstance , HWND hWndParent );

	CCameraDialog* GetCameraDialog( void ){ return m_pCameraDialog; }

	// �X�e�[�^�X�o�[�֘A
	bool MV_CreateStatusBar( HWND hWndParent );

	CStatusBar* GetStatusBar( void ){ return m_pStatusBar; }

	// �c�[���o�[�֘A
	bool MV_CreateToolBar( HWND hWndParent );

	CToolBar* GetToolBar( void ){ return m_pToolBar; }

	// �A�N�Z�����[�^�֘A
	CAccelerator* GetAccelerator( void ){ return m_pAccelerator; }

private:
	// �R���X�g���N�^
	CModelViewerProc();
	CModelViewerProc( const CModelViewerProc& ){};

	// �f�X�g���N�^
	~CModelViewerProc();

	// �I�y���[�^�[
	void operator=( const CModelViewerProc& ){};

	//---------------------------------------------
	// [ �����o�ϐ� ]
	//---------------------------------------------
private:
	static CModelViewerProc* m_pModelViewerProc;		// �v���V�[�W�������ւ̃|�C���^

	HINSTANCE m_hInstance;								// �C���X�^���X�n���h��
	HWND m_hWnd;										// �E�B���h�E�n���h��

	CMenuBar*      m_pMenuBar;							// ���j���[�o�[�����ւ̃|�C���^
	CStatusBar*    m_pStatusBar;						// �X�e�[�^�X�o�[�����ւ̃|�C���^
	CToolBar*      m_pToolBar;							// �c�[���o�[�����ւ̃|�C���^
	CCameraDialog* m_pCameraDialog;						// �J��������Ɋւ���_�C�A���O�����̃|�C���^
	CAccelerator*  m_pAccelerator;						// �A�N�Z�����[�^�����ւ̃|�C���^

	CSceneGLModel* m_pModel;							// �{���Ώۃ��f�������ւ̃|�C���^

	CAxis* m_pAxis[ 3 ];								// ���`��p
	CGrid3D* m_pGrid;									// �O���b�h���p
};

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
