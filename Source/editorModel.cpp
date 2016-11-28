//==============================================================================
// �^�C�g��     :   ���[�V�����ҏW�p���f��
// �t�@�C����   :   editorModel.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/09/06
//==============================================================================

//==============================================================================
// �X�V����: -2016/09/06 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "editorModel.h"
#include "main.h"
#include <vector>

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
// �֐��� : CMotionEditModel()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CMotionEditModel::CMotionEditModel()
{
	m_pos           = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot           = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_pModelManager = NULL;
	m_editModeIdx   = 0;

	m_pMotion       = NULL;

	MatrixIdentity( &m_mtxWorld );
}

//==============================================================================
// �֐��� : ~CMotionEditModel()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CMotionEditModel::~CMotionEditModel()
{

}

//==============================================================================
// �֐��� : CMotionEditModel* Create( void )
// ����   : void
// �߂�l : CMotionEditModel*�^
// ����   : ��������
//==============================================================================
CMotionEditModel* CMotionEditModel::Create( void )
{
	CMotionEditModel* newInstance = new CMotionEditModel;

	if( newInstance->Init() == false )
	{
		newInstance->Release();
		newInstance = NULL;
	}

	return newInstance;
}

//==============================================================================
// �֐��� : bool Init( void )
// ����   : void
// �߂�l : void
// ����   : ����������
//==============================================================================
bool CMotionEditModel::Init( void )
{
	// ���f�����[�N��������
	//m_pModelManager = CParentModelManagerGL::Create();
	//
	//if( m_pModelManager == NULL )
	//{
	//	return false;
	//}

	// ���[�V��������
	//m_pMotion = CMotionGL::Create( "data\\ANIMATION\\miku_01_01.anm" );
	//
	//if( m_pMotion == NULL )
	//{
	//	return false;
	//}

	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CMotionEditModel::Uninit( void )
{
	// ���f�������̉��
	if( m_pModelManager != NULL )
	{
		m_pModelManager->Release();
		m_pModelManager = NULL;
	}

	// ���[�V�����������
	if( m_pMotion != NULL )
	{
		m_pMotion->Release();
		m_pMotion = NULL;
	}
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CMotionEditModel::Update( void )
{
	//---------------------------------------------------
	// [ �L�[���͏󋵎擾 ]
	//---------------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isMoveForward = false;
	bool isMoveBack    = false;
	bool isMoveLeft    = false;
	bool isMoveRight   = false;
	bool isMoveUp      = false;
	bool isMoveDown    = false;
	bool isRotLeft     = false;
	bool isRotRight    = false;

	if( pInput != NULL )
	{
		isMoveForward = pInput->GetPress( DIK_W );
		isMoveBack    = pInput->GetPress( DIK_S );
		isMoveLeft    = pInput->GetPress( DIK_A );
		isMoveRight   = pInput->GetPress( DIK_D );
		isMoveUp      = pInput->GetPress( DIK_Q );
		isMoveDown    = pInput->GetPress( DIK_E );
		isRotLeft     = pInput->GetPress( DIK_Z );
		isRotRight    = pInput->GetPress( DIK_C );
	}

	//---------------------------------------------------
	// [ �ړ����� ]
	//---------------------------------------------------
	if( isMoveForward )		m_pos.z -= 1.0f;
	if( isMoveBack )		m_pos.z += 1.0f;
	if( isMoveLeft )		m_pos.x -= 1.0f;
	if( isMoveRight )		m_pos.x += 1.0f;
	if( isMoveUp )			m_pos.y += 1.0f;
	if( isMoveDown )		m_pos.y -= 1.0f;
	if( isRotLeft )			m_rot.y -= PI * 0.01f;
	if( isRotRight )		m_rot.y += PI * 0.01f;

	//---------------------------------------------------
	// [ ���[�V�������� ]
	//---------------------------------------------------
	//m_pMotion->Update();
	//m_pMotion->SetMotionData( m_pModelManager );
	//
	//m_pModelManager->Update();

}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CMotionEditModel::Draw( void )
{
	// ----------------------------------------------------------------------
	// [ ���[���h�}�g���b�N�X�̐������� ]
	// ----------------------------------------------------------------------
	MATRIX mtxRot , mtxTrans;													// �s��p���[�N
	MatrixIdentity( &m_mtxWorld );												// �s�񏉊���

	MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );		// ��]�̍s����Z�o
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxRot );						// ��]�s��̍���

	MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );				// �ʒu�̍s����Z�o
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxTrans );					// �ʒu�s��̍���

	// ���f���̕`��
	//m_pModelManager->Draw( &m_mtxWorld );
}

//==============================================================================
// �֐��� : void EditIdx( void )
// ����   : void
// �߂�l : void
// ����   : �C���f�b�N�X�ҏW����
//==============================================================================
void CMotionEditModel::EditIdx( void )
{
	// ----------------------------------------------------------------------
	// [ �L�[���͏󋵂̎擾 ]
	// ----------------------------------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isMoveIdxUp = false;
	bool isMoveIdxDown = false;

	if( pInput != NULL )
	{
		isMoveIdxUp = pInput->GetTrigger( DIK_UP );
		isMoveIdxDown = pInput->GetTrigger( DIK_DOWN );
	}

	// ----------------------------------------------------------------------
	// [ ���f���C���f�b�N�X���� ]
	// ----------------------------------------------------------------------
	if( isMoveIdxUp )
	{
		m_editModeIdx--;

		if( m_editModeIdx < 0 )
		{
			m_editModeIdx = 0;
		}
	}

	if( isMoveIdxDown )
	{
		m_editModeIdx++;

		if( m_editModeIdx >= m_pModelManager->GetModelListSize() )
		{
			m_editModeIdx = ( m_pModelManager->GetModelListSize() - 1 );
		}
	}
}

//==============================================================================
// �֐��� : void EditPos( void )
// ����   : void
// �߂�l : void
// ����   : ���f�����[�J�����W�ҏW����
//==============================================================================
void CMotionEditModel::EditPos( void )
{
	// ----------------------------------------------------------------------
	// [ �L�[���͏󋵂̎擾 ]
	// ----------------------------------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isMovePosXUp = false;
	bool isMovePosXDown = false;
	bool isMovePosXReset = false;
	bool isMovePosYUp = false;
	bool isMovePosYDown = false;
	bool isMovePosYReset = false;
	bool isMovePosZUp = false;
	bool isMovePosZDown = false;
	bool isMovePosZReset = false;

	if( pInput != NULL )
	{
		//isMovePosXUp    = pInput->GetRepeat();
		//isMovePosXDown  = pInput->GetRepeat();
		//isMovePosXReset = pInput->GetTrigger();
		//isMovePosYUp    = pInput->GetRepeat();
		//isMovePosYDown  = pInput->GetRepeat();
		//isMovePosXReset = pInput->GetTrigger();
		//isMovePosZUp    = pInput->GetRepeat();
		//isMovePosZDown  = pInput->GetRepeat();
		//isMovePosXReset = pInput->GetTrigger();
	}

	// ----------------------------------------------------------------------
	// [ ���f�����[�J���ʒu���� ]
	// ----------------------------------------------------------------------

}

//==============================================================================
// �֐��� : void EditRot( void )
// ����   : void
// �߂�l : void
// ����   : ���f�����[�J���p�x�ҏW����
//==============================================================================
void CMotionEditModel::EditRot( void )
{

}

//==============================================================================
// �֐��� : void ViewImfModel( void )
// ����   : void
// �߂�l : void
// ����   : ���f�����\������
//==============================================================================
void CMotionEditModel::ViewImfModel( void )
{
	// ----------------------------------------------------------------------
	// [ ���\�� ]
	// ----------------------------------------------------------------------
	//CDebugProc::Print( "[ MODEL ]\n" );
	//CDebugProc::Print( "Index : %d\n" , m_editModeIdx );

	//// ���f�����
	//CParentModelDX* pModel = m_pModelManager->GetModelData( m_editModeIdx );

	//if( pModel != NULL )
	//{
	//	D3DXVECTOR3 posData = pModel->GetPos();
	//	D3DXVECTOR3 rotData = pModel->GetRot();
	//	char* filePath = pModel->GetModelFilePath();

	//	if( filePath != NULL )
	//	{
	//		CDebugProc::Print( "Path  : %s\n" , filePath );
	//	}

	//	CDebugProc::Print( "Pos   : ( %3.3f ; %3.3f ; %3.3f )\n" , posData.x , posData.y , posData.z );
	//	CDebugProc::Print( "Rot   : ( %3.3f ; %3.3f ; %3.3f )\n" , rotData.x , rotData.y , rotData.z );
	//}
}

//==============================================================================
// �֐��� : void ViewImfMotion( void )
// ����   : void
// �߂�l : void
// ����   : ���[�V�������\������
//==============================================================================
void CMotionEditModel::ViewImfMotion( void )
{
	// ----------------------------------------------------------------------
	// [ ���\�� ]
	// ----------------------------------------------------------------------
	//CDebugProc::Print( "[ MOTION ]\n" );
}
