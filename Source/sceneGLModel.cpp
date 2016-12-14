//==============================================================================
// �^�C�g��     :   OpenGL�p���f���`��p�N���X
// �t�@�C����   :   sceneGLModel.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/11
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/11 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "sceneGLModel.h"
#include "rendererGL.h"

#include "loader.h"

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
#define MOVE_SPEED		( 20.0f )			// �ړ��W��
#define ROTATION_SPEED	( PI * 0.01f )		// ��]�p�ω��W��

enum MAT_TYPE
{								/* ==�}�e���A����ގ��ʎq== */
	MAT_TYPE_AMBIENT = 0 ,			// �A���r�G���g
	MAT_TYPE_DIFFUSE ,				// �f�B�t���[�Y
	MAT_TYPE_SPECULAR ,				// �X�y�L�����[
	MAT_TYPE_EMISSION ,				// �G�~�b�V����
	MAT_TYPE_SINESS ,				// ���ʔ��ˌ��q��
	MAT_TYPE_MAX ,					// ����
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
MAT_TYPE g_matSelect;				// ���ݑI�����Ă���}�e���A��

//==============================================================================
// �֐��� : CSceneGLModel()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CSceneGLModel::CSceneGLModel()
{
	m_pos      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot      = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size     = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_col      = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );
	m_pTexture = NULL;
	m_nor      = VECTOR3( 0.0f , 0.0f , 0.0f );

	m_pModel   = NULL;
	m_numMat   = 0;
	m_pMat     = NULL;

	m_isTexEnable = true;
	m_isMatEnable = true;
}

//==============================================================================
// �֐��� : ~CSceneGLModel()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CSceneGLModel::~CSceneGLModel()
{
}

//==============================================================================
// �֐��� : CSceneGLModel* Create( char* modelFileName )
// ����   : char* modelFileName : ���f���t�@�C����
// �߂�l : CSceneGLModel*�^
// ����   : ��������
//==============================================================================
CSceneGLModel* CSceneGLModel::Create( char* modelFileName )
{
	CSceneGLModel* pNewInstance = new CSceneGLModel();

	if( pNewInstance->Init( modelFileName ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// �֐��� : bool Init( char* modelFileName )
// ����   : char* modelFileName : ���f���t�@�C����
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CSceneGLModel::Init( char* modelPath )
{
	//---------------------------------
	// [ �p�����[�^���������� ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();						// �����_���[�̎擾

	m_pos = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_scl = VECTOR3( 1.0f , 1.0f , 1.0f );
	m_nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	m_size = VECTOR3( 1.0f , 0.0f , 1.0f );
	m_col = COLOR_F32( 1.0f , 1.0f , 1.0f , 1.0f );

	MatrixIdentity( &m_mtxWorld );
	m_pTexture = NULL;

	m_bMove = false;

	//---------------------------------
	// [ ���f���ǂݍ��ݏ��� ]
	//---------------------------------
	pRenderer->CreateModel( modelPath , NULL , &m_numMat , &m_pModel );		// ���f������

	//---------------------------------------------
	// [ �}�e���A���ǂݍ��ݏ���( ���Ŗ��ߍ��� ) ]
	//---------------------------------------------
	CLoader* pLoader = new CLoader;

	//pLoader->MaterialLoad( "data\\MODEL\\miku_01.mtl" , &m_pMat );

	delete pLoader;
	pLoader = NULL;

	//---------------------------------
	// [ �e�N�X�`���ǂݍ��ݏ��� ]
	//---------------------------------
	//pRenderer->CreateTexture( "data\\MODEL\\miku_01.bmp" , &m_pTexture );	// �e�N�X�`������

	return true;		// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CSceneGLModel::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	if( m_pMat != NULL )
	{
		m_pMat->Release();
		m_pMat = NULL;
	}
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CSceneGLModel::Update( void )
{
	//------------------------------------------
	// [ ���͏��̎擾���� ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isPressW = false;
	bool isPressS = false;
	bool isPressA = false;
	bool isPressD = false;
	bool isPressQ = false;
	bool isPressE = false;
	bool isPressZ = false;
	bool isPressC = false;
	bool isPressT = false;
	bool isPressB = false;
	bool isPressY = false;
	bool isPressN = false;
	bool isPressEnter = false;

	bool isTrigEnter = false;
	bool isTrigSpace = false;
	bool isTrigF8 = false;
	bool isTrigF9 = false;

	bool isRepeat_1 = false;
	bool isRepeat_2 = false;
	bool isRepeat_3 = false;
	bool isRepeat_4 = false;
	bool isRepeat_5 = false;
	bool isRepeat_6 = false;
	bool isRepeat_7 = false;
	bool isRepeat_8 = false;
	bool isRepeat_9 = false;
	bool isRepeat_0 = false;

	if( pInput != NULL )
	{
		if( m_bMove == true )
		{
			isPressW = pInput->GetPress( DIK_W );
			isPressS = pInput->GetPress( DIK_S );
			isPressA = pInput->GetPress( DIK_A );
			isPressD = pInput->GetPress( DIK_D );
			isPressQ = pInput->GetPress( DIK_Q );
			isPressE = pInput->GetPress( DIK_E );
			isPressZ = pInput->GetPress( DIK_Z );
			isPressC = pInput->GetPress( DIK_C );
			isPressT = pInput->GetPress( DIK_T );
			isPressB = pInput->GetPress( DIK_B );
			isPressY = pInput->GetPress( DIK_Y );
			isPressN = pInput->GetPress( DIK_N );
			isPressEnter = pInput->GetPress( DIK_RETURN );
		}

		isTrigEnter = pInput->GetTrigger( DIK_RETURN );
		isTrigSpace = pInput->GetTrigger( DIK_SPACE );
		isTrigF8 = pInput->GetTrigger( DIK_F8 );
		isTrigF9 = pInput->GetTrigger( DIK_F9 );

		isRepeat_1 = pInput->GetRepeat( DIK_1 );
		isRepeat_2 = pInput->GetRepeat( DIK_2 );
		isRepeat_3 = pInput->GetRepeat( DIK_3 );
		isRepeat_4 = pInput->GetRepeat( DIK_4 );
		isRepeat_5 = pInput->GetRepeat( DIK_5 );
		isRepeat_6 = pInput->GetRepeat( DIK_6 );
		isRepeat_7 = pInput->GetRepeat( DIK_7 );
		isRepeat_8 = pInput->GetRepeat( DIK_8 );
		isRepeat_9 = pInput->GetRepeat( DIK_9 );
		isRepeat_0 = pInput->GetRepeat( DIK_0 );
	}

	//------------------------------------------
	// [ �ړ����� ]
	//------------------------------------------
	if( m_bMove == true )
	{
		// ���s�ړ�
		if( isPressW || isPressA || isPressS || isPressD )
		{
			float fMoveRot = 0.0f;					// �ړ�����

													// �����̎Z�o
			if( isPressW )
			{
				if( isPressA )
				{
					fMoveRot -= PI * -0.75f;		// ����
				}
				else if( isPressD )
				{
					fMoveRot -= PI * 0.75f;			// �E��
				}
				else
				{
					fMoveRot -= PI;					// ��
				}
			}
			else if( isPressS )
			{
				if( isPressA )
				{
					fMoveRot -= PI * -0.25f;		// ����O
				}
				else if( isPressD )
				{
					fMoveRot -= PI * 0.25f;			// �E��O
				}
				else
				{
					fMoveRot -= 0.0f;				// ��O
				}
			}
			else if( isPressA )
			{
				fMoveRot -= PI * -0.5f;				// ��
			}
			else if( isPressD )
			{
				fMoveRot -= PI * 0.5f;				// �E
			}

			fMoveRot -= GetManager()->GetCamera()->GetRot().y;

			// �p�x�̐��K��
			if( fMoveRot > PI )
			{
				fMoveRot -= PI2;
			}
			else if( fMoveRot < -PI )
			{
				fMoveRot += PI2;
			}

			// �����ɉ������ړ�����
			m_pos.x -= -sinf( fMoveRot ) * MOVE_SPEED;
			m_pos.z -= cosf( fMoveRot ) * MOVE_SPEED;
		}

		// �㉺�ړ�
		if( isPressZ )
		{
			m_pos.y += MOVE_SPEED;
		}
		else if( isPressC )
		{
			m_pos.y -= MOVE_SPEED;
		}
	}

	//------------------------------------------
	// [ ��]���� ]
	//------------------------------------------
	if( m_bMove == true )
	{
		if( isPressQ )
		{
			m_rot.y += ROTATION_SPEED;
		}
		else if( isPressE )
		{
			m_rot.y -= ROTATION_SPEED;
		}

		if( m_rot.y > PI )
		{
			m_rot.y -= PI2;
		}
		else if( m_rot.y < -PI )
		{
			m_rot.y += PI2;
		}
	}

	//------------------------------------------
	// [ ������]���� ]
	//------------------------------------------
	static float moveRad = 0.0f;
	static float moveLen = 100.0f;

	//if( m_bMove == false )
	//{
	//	/*m_rot.x += PI * 0.01f;

	//	if( m_rot.x > PI )
	//	{
	//		m_rot.x -= PI2;
	//	}*/

	//	m_rot.y += PI * 0.01f;

	//	if( m_rot.y > PI )
	//	{
	//		m_rot.y -= PI2;
	//	}

	//	/*m_rot.z += PI * 0.02f;

	//	if( m_rot.z > PI )
	//	{
	//		m_rot.z -= PI2;
	//	}*/

	//	m_pos.y = sinf( moveRad ) * moveLen;
	//	//m_pos.x = cosf( moveRad ) * moveLen;

	//	moveRad += PI * 0.01f;

	//	if( moveRad > PI )
	//	{
	//		moveRad -= PI2;
	//	}
	//}

	//------------------------------------------
	// [ �ړ��t���O�؂�ւ����� ]
	//------------------------------------------
	if( isTrigEnter )
	{
		m_bMove = m_bMove ? false : true;
	}

	//------------------------------------------
	// [ �e�N�X�`���L���E�����؂�ւ� ]
	//------------------------------------------
	if( isTrigF9 )
	{
		m_isTexEnable = m_isTexEnable ? false : true;
	}
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CSceneGLModel::Draw( void )
{
	//---------------------------------
	// [ �`��O���� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glEnable( GL_NORMALIZE );

	//---------------------------------
	// [ ���[���h�}�g���N�X�Z�o ]
	//---------------------------------
	glTranslatef( m_pos.x , m_pos.y , m_pos.z );

	glRotatef( RadToDeg( m_rot.z ) , 0.0f , 0.0f , 1.0f );
	glRotatef( RadToDeg( m_rot.y ) , 0.0f , 1.0f , 0.0f );
	glRotatef( RadToDeg( m_rot.x ) , 1.0f , 0.0f , 0.0f );

	glScalef( m_scl.x , m_scl.y , m_scl.z );

	//MATRIX mtxScl , mtxRot , mtxTrans;
	//
	//MatrixIdentity( &m_mtxWorld );
	//
	//MatrixScaling( &mtxScl , m_scl.x , m_scl.y , m_scl.z );
	//MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxScl );
	//
	//MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );
	//MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxRot );
	//
	//MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );
	//MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxTrans );
	//
	//glMultMatrixf( m_mtxWorld.m );

	//---------------------------------
	// [ �`�揈�� ]
	//---------------------------------
	if( m_isTexEnable && m_pTexture != NULL )
	{
		m_pTexture->Set();						// �e�N�X�`���ݒ�
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D , 0 );
		glDisable( GL_TEXTURE_2D );
	}

	if( m_isMatEnable && m_pMat != NULL )
	{
		m_pMat->Set();							// �}�e���A���ݒ�
	}

	//glPolygonMode( GL_FRONT_AND_BACK , GL_LINE );

	for( DWORD matCnt = 0 ; matCnt < m_numMat ; matCnt++ )
	{
		m_pModel->DrawSubset( matCnt );
	}

	//m_pModel->DrawSubset( 0 );
	//m_pModel->DrawSubset( 1 );
	//m_pModel->DrawSubset( 2 );

	//glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );

	//---------------------------------
	// [ �`��㏈�� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glDisable( GL_NORMALIZE );

	if( m_pMat != NULL )
	{
		CMaterialGL pDefMat;

		pDefMat.Set();							// �����}�e���A���ݒ�
	}

	if( !m_isTexEnable )
	{
		glEnable( GL_TEXTURE_2D );
	}

}
