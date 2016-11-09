//==============================================================================
// �^�C�g��     :   ���f���r���[�A�[�p���j���[�o�[
// �t�@�C����   :   MV_menuBar.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/07/01
//==============================================================================

//==============================================================================
// �X�V����: -2016/07/01 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WARNING�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "MV_menuBar.h"
#include "modelViewerProc.h"
#include "sceneGLModel.h"
#include "light.h"

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
// �֐��� : CMenuBar()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CMenuBar::CMenuBar()
{
	m_menuName = NULL;
	m_hMenu    = NULL;
}

//==============================================================================
// �֐��� : bool CreateMenuName( WORD id )
// ����   : WORD id : �����Ώۂ�ID
// �߂�l : bool�^
// ����   : ���j���[�o�[������
//==============================================================================
bool CMenuBar::CreateMenuName( WORD id )
{
	m_menuName = MAKEINTRESOURCE( id );

	return true;
}

//==============================================================================
// �֐��� : bool OperateMenu( WPARAM wParam )
// ����   : WPARAM wParam : �R�}���h�̓������p�����[�^
// �߂�l : bool�^        : ���j���[���씻��
// ����   : ���j���[���쏈��( WM_COMMAND���ŌĂяo�� )
//==============================================================================
bool CMenuBar::OperateMenu( WPARAM wParam )
{
	switch( LOWORD( wParam ) )
	{
		case FILE_OPEN:
		{
			// ���f���I�[�v��
			CModelViewerProc* pMVProc = CModelViewerProc::GetModelViewerProc();

			if( pMVProc == NULL )
			{
				return false;
			}

			char currentDirectory[ MAX_PATH ] = { 0 };		// ���̃A�v���P�[�V�����̃f�B���N�g��
			char modelFileFullPath[ MAX_PATH ] = { 0 };		// ���f���t�@�C���̃t���p�X

			OPENFILENAME of = { 0 };

			GetCurrentDirectory( MAX_PATH , currentDirectory );
			strcpy( modelFileFullPath , currentDirectory );
			strcat( modelFileFullPath , "\\data\\MODEL\\_\0" );

			of.lStructSize = sizeof( OPENFILENAME );
			of.hwndOwner = pMVProc->GetHWND();
			of.lpstrFilter = "�I�u�W�F�N�g�t�@�C��(*.obj)\0*.obj\0";
			of.lpstrFile = modelFileFullPath;
			of.nMaxFile = MAX_PATH;
			of.lpstrDefExt = "obj";

			if( GetOpenFileName( &of ) )
			{
				CSceneGLModel* pModel = pMVProc->GetModel();

				if( pModel != NULL )
				{
					pModel->Release();
					pModel = NULL;
				}

				SetCurrentDirectory( currentDirectory );				// �f�B���N�g����߂�

																		// �t���p�X�𕪉����A���f���t�@�C���̃p�X�݂̂��擾
				char chrDrive[ MAX_PATH ];								// �h���C�u��
				char chrDir[ MAX_PATH ];								// �f�B���N�g����
				char chrFile[ MAX_PATH ];								// �t�@�C����
				char chrExt[ MAX_PATH ];								// �g���q

				_splitpath( modelFileFullPath , chrDrive , chrDir , chrFile , chrExt );

				strcat( chrFile , chrExt );

				// ���݂̊K�w����̑��΃p�X�𐶐�
				char modelFileName[ MAX_PATH ] = { 0 };

				strcpy( modelFileName , "data\\MODEL\\" );
				strcat( modelFileName , chrFile );

				// ���f����������
				pModel = CSceneGLModel::Create( modelFileName );

				pMVProc->SetModel( pModel );
			}

			return true;
		}

		case DESTROY_EXE:
		{
			// �I������
			CModelViewerProc* pMVProc = CModelViewerProc::GetModelViewerProc();

			if( pMVProc == NULL )
			{
				return false;
			}

			PostMessage( pMVProc->GetHWND() , WM_CLOSE , 0 , 0 );

			return true;
		}

		case CAMERA_DIAROG_OPEN:
		{
			// �J�����_�C�A���O�I�[�v��
			CModelViewerProc::GetModelViewerProc()->GetCameraDialog()->ShowDialog( SW_SHOW );

			// ���j���[�o�[�̃`�F�b�N��Ԃ�ύX
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = MFS_CHECKED;
			menuInfo.fMask  = MIIM_STATE;

			SetMenuItemInfo( GetHandle() , CAMERA_DIAROG_OPEN , FALSE , &menuInfo );
			return true;
		}

		case SET_LIGHT:
		{
			// ���C�g�؂�ւ�
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = MFS_CHECKED;
			menuInfo.fMask  = MIIM_STATE;

			GetMenuItemInfo( GetHandle() , SET_LIGHT , FALSE , &menuInfo );

			bool eneble;

			if( menuInfo.fState == MFS_CHECKED )
			{
				eneble = false;
				menuInfo.fState = MFS_UNCHECKED;
			}
			else
			{
				eneble = true;
				menuInfo.fState = MFS_CHECKED;
			}

			CLight::SetLightAllEnable( eneble );

			SetMenuItemInfo( GetHandle() , SET_LIGHT , FALSE , &menuInfo );

			return true;
		}

		case SET_TEXTURE:
		{
			// �e�N�X�`���؂�ւ�
			CSceneGLModel* pModel = CModelViewerProc::GetModelViewerProc()->GetModel();

			if( pModel == NULL )
			{
				return false;
			}
			
			bool flags = pModel->GetTexEnable();
			pModel->SetTexEnable( flags ? false : true );

			// ���j���[�o�[�̃`�F�b�N��Ԃ�ύX
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = flags ? MFS_UNCHECKED : MFS_CHECKED;
			menuInfo.fMask = MIIM_STATE;

			SetMenuItemInfo( GetHandle() , SET_TEXTURE , FALSE , &menuInfo );
			return true;
		}

		case SET_MATERIAL:
		{
			// �}�e���A���؂�ւ�
			CSceneGLModel* pModel = CModelViewerProc::GetModelViewerProc()->GetModel();

			if( pModel == NULL )
			{
				return false;
			}

			bool flags = pModel->GetMatEnable();
			pModel->SetMatEnable( flags ? false : true );

			// ���j���[�o�[�̃`�F�b�N��Ԃ�ύX
			MENUITEMINFO menuInfo;

			menuInfo.cbSize = sizeof( MENUITEMINFO );
			menuInfo.fState = flags ? MFS_UNCHECKED : MFS_CHECKED;
			menuInfo.fMask = MIIM_STATE;

			SetMenuItemInfo( GetHandle() , SET_MATERIAL , FALSE , &menuInfo );
			return true;
		}

		case POLYGON_FILL:
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			return true;
		}

		case POLYGON_WIRE:
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			return true;
		}

		case POLYGON_POINT:
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
			return true;
		}

		default:
		{
			return false;	// ���������s���Ă��Ȃ�
		}
	}

	return false;
}
