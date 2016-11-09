//==============================================================================
// �^�C�g��     :   ���f���r���[�A�[�p�X�e�[�^�X�o�[����
// �t�@�C����   :   MV_statusBar.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/07/11
//==============================================================================

//==============================================================================
// �X�V����: -2016/07/11 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WARNING�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "MV_statusBar.h"
#include "modelViewerProc.h"
#include "manager.h"
#include <CommCtrl.h>
#include <stdio.h>

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
#define STATUS_BAR_ID	( 501 )

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
// �֐��� : CStatusBar()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CStatusBar::CStatusBar()
{
	m_hParent = NULL;
	m_hStatus = NULL;
}

//==============================================================================
// �֐��� : bool Init( HWND hParent )
// ����   : HWND hParent : �e�n���h��
// �߂�l : bool�^
// ����   : ��������
//==============================================================================
CStatusBar* CStatusBar::Create( HWND hParent )
{
	CStatusBar* newInstance = new CStatusBar;

	if( newInstance->Init( hParent ) == false )
	{
		delete newInstance;
		newInstance = NULL;
	}

	return newInstance;
}

//==============================================================================
// �֐��� : void Release( void )
// ����   : void
// �߂�l : void
// ����   : �������
//==============================================================================
void CStatusBar::Release( void )
{
	delete this;
}

//==============================================================================
// �֐��� : bool Init( HWND hParent )
// ����   : HWND hParent : �e�n���h��
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CStatusBar::Init( HWND hParent )
{
	m_hParent = hParent;

	m_hStatus = CreateStatusWindow(
		WS_CHILD | WS_VISIBLE | CCS_BOTTOM | WS_CLIPCHILDREN ,
		"" , hParent , STATUS_BAR_ID );

	return true;
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CStatusBar::Update( void )
{
	DrawStatus();

	// �`��I�[�_�[
	InvalidateRect( m_hStatus , NULL , FALSE );
}

//==============================================================================
// �֐��� : void DrawStatus( void )
// ����   : void
// �߂�l : void
// ����   : �X�e�[�^�X�\������
//==============================================================================
void CStatusBar::DrawStatus( void )
{
	// ���W�̕`��
	char str[ 256 ] = { 0 };
	CCameraGL* pCamera = GetManager()->GetCamera();

	if( pCamera == NULL )
	{
		return;
	}


	VECTOR3 posV = pCamera->GetPosV();

	sprintf( str , "CameraEye ( X = %3.3f ; Y = %3.3f ; Z = %3.3f )\n" , posV.x , posV.y , posV.z );

	SendMessage( m_hStatus , SB_SETTEXT , 0 , ( LPARAM )str );
}
