//==============================================================================
// �^�C�g��     :   ���f���r���[�A�[�p�J�����_�C�A���O
// �t�@�C����   :   MV_cameraDialog.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/07/01
//==============================================================================

//==============================================================================
// �X�V����: -2016/07/01 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "MV_cameraDialog.h"
#include "resource.h"
#include "cameraGL.h"
#include "modelViewerProc.h"

using namespace ModelViewer;

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
enum OPERATE_DIALOG
{
	AXIS_X = IDC_BUTTON1 ,
	AXIS_Y = IDC_BUTTON2 ,
	AXIS_Z = IDC_BUTTON3 ,
};

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
// �֐��� : CCameraDialog()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CCameraDialog::CCameraDialog()
{
	m_hDlg = NULL;
}

//==============================================================================
// �֐��� : ~CCameraDialog()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CCameraDialog::~CCameraDialog()
{

}

//==============================================================================
// �֐��� : CCameraDialog* Create( HINSTANCE hInstance , HWND hWndParent , WORD id )
// ����   : HINSTANCE hInstance : �C���X�^���X�n���h��
//          HWND hWndParent     : �e�E�B���h�E�n���h��
//          WORD id             : �����Ώۂ̃_�C�A���OID
// �߂�l : CCameraDialog*�^
// ����   : ��������
//==============================================================================
CCameraDialog* CCameraDialog::Create( HINSTANCE hInstance , HWND hWndParent , WORD id )
{
	CCameraDialog* pNewInstance = new CCameraDialog;

	if( pNewInstance->Init( hInstance , hWndParent , id ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// �֐��� : void Release( void )
// ����   : void
// �߂�l : void
// ����   : �������
//==============================================================================
void CCameraDialog::Release( void )
{
	CCameraDialog::Uninit();

	delete this;
}

//==============================================================================
// �֐��� : bool Init( HINSTANCE hInstance , HWND hWndParent , WORD id )
// ����   : HINSTANCE hInstance : �C���X�^���X�n���h��
//          HWND hWndParent     : �e�E�B���h�E�n���h��
//          WORD id             : �����Ώۂ̃_�C�A���OID
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CCameraDialog::Init( HINSTANCE hInstance , HWND hWndParent , WORD id )
{
	m_hDlg = CreateDialog(
				hInstance,
				MAKEINTRESOURCE( id ),
				hWndParent,
				CameraDialogProc );

	if( m_hDlg == NULL )
	{
		return false;
	}

	ShowWindow( m_hDlg , SW_SHOW );

	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CCameraDialog::Uninit( void )
{
	if( m_hDlg != NULL )
	{
		DestroyWindow( m_hDlg );
		m_hDlg = NULL;
	}
}

//==============================================================================
// �֐��� : BOOL CALLBACK CameraDialogProc( HWND hDlg , UINT msg , WPARAM wParam , LPARAM lParam )
// ����   : void
// �߂�l : void
// ����   : �J�����_�C�A���O�p�v���V�[�W��
//==============================================================================
BOOL CALLBACK CameraDialogProc( HWND hDlg , UINT msg , WPARAM wParam , LPARAM lParam )
{
	//----------------------------------------
	// [ �e�폈�� ]
	//----------------------------------------
	switch( msg )
	{
		case WM_INITDIALOG:
		{
			return TRUE;
		}

		case WM_COMMAND:
		{
			CCameraGL* pCamera = GetManager()->GetCamera();
			VECTOR3 posV;
			VECTOR3 posR;
			VECTOR3 rot;

			switch( LOWORD( wParam ) )
			{
				case AXIS_X:
				{
					pCamera->Init( VECTOR3( 1000.0f , 0.0f , 0.0f ) );
					break;
				}

				case AXIS_Y:
				{
					pCamera->SetPosV( VECTOR3( 0.0f , 1000.0f , 0.0f ) );

					break;
				}

				case AXIS_Z:
				{
					pCamera->Init( VECTOR3( 0.0f , 0.0f , 1000.0f ) );

					break;
				}

				default:
				{
					break;
				}
			}

			break;
		}

		case WM_CLOSE:
		{
			// �E�B���h�E�B��
			ShowWindow( hDlg , SW_HIDE );

			// ���j���[�o�[�̃`�F�b�N��Ԃ�ύX
			CMenuBar* pMenu = CModelViewerProc::GetModelViewerProc()->GetMenu();
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = MFS_UNCHECKED;
			menuInfo.fMask  = MIIM_STATE;

			SetMenuItemInfo( 
				pMenu->GetHandle(),
				pMenu->CAMERA_DIAROG_OPEN,
				FALSE,
				&menuInfo );

			return TRUE;
		}

		default:
		{
			break;
		}
	}

	return FALSE;
}
