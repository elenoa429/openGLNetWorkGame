//==============================================================================
// �^�C�g��     :   ���U���g���[�h�I�u�W�F�N�g
// �t�@�C����   :   result.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/07/11
//==============================================================================

//==============================================================================
// �X�V����: -2016/07/11 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "title.h"
#include "result.h"
#include "main.h"
#include "fade.h"
#include "sceneGL2D.h"

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
// �֐��� : CResult()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CResult::CResult( bool isClear )
{
}

//==============================================================================
// �֐��� : ~CResult()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CResult::~CResult()
{

}

//==============================================================================
// �֐��� : bool Init( void )
// ����   : void
// �߂�l : void
// ����   : ����������
//==============================================================================
bool CResult::Init( void )
{
	CSceneGL2D::Create( "data\\TEXTURE\\fighter00.png" );
	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CResult::Uninit( void )
{
	//---------------------------------------------
	// [ �e�V�[���̉������ ]
	//---------------------------------------------
	CScene::ReleaseAll();
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CResult::Update( void )
{
	//---------------------------------------------
	// [ �e�V�[���̍X�V���� ]
	//---------------------------------------------
	CScene::UpdateAll();

	//---------------------------------------------
	// [ ���[�h�؂�ւ� ]
	//---------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	if( pInput != NULL )
	{
		if( pInput->GetTrigger( DIK_RETURN ) )
		{
			CFade::FadeStart( new CTitle , 30 );
		}
	}

}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CResult::Draw( void )
{
	//---------------------------------------------
	// [ �e�V�[���̕`�揈�� ]
	//---------------------------------------------
	CScene::DrawAll();
}