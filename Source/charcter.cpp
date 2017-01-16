//==============================================================================
// �^�C�g��     :   �L�����N�^�[���N���X
// �t�@�C����   :   charcter.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/11/21
//==============================================================================

//==============================================================================
// �X�V����: -2016/11/21 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "charcter.h"
#include "game.h"
#include "cameraGL.h"
#include <math.h>
#include "wall.h"

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
// �֐��� : CCharcter()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CCharcter::CCharcter()
{
	m_pos = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_scl = VECTOR3( 5.0f , 5.0f , 5.0f );
	m_gensui = VECTOR3( 0.025f , 0.025f , 0.025f );

	m_id = 0;
	m_life = 0;

	m_pBoundingSphere = NULL;

	m_pModel = NULL;
	m_numMat = 0;
	m_pMat   = NULL;

}

//==============================================================================
// �֐��� : ~CCharcter()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CCharcter::~CCharcter()
{

}

//==============================================================================
// �֐��� : bool Init( int charcterType )
// ����   : void
// �߂�l : bool�^ : ��������
// ����   : ����������
//==============================================================================
bool CCharcter::Init( int charcterType )
{
	m_pos = VECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = VECTOR3(0.0f, 0.0f, 0.0f);			// �p�x
	m_mov = VECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	m_rotMokuhyou = VECTOR3(0.0f, 0.0f, 0.0f);	// �ڕW�p�x
	m_spinAxcel = 0.0f;							// ��]�̉����x
	m_spinGensui = 8.0f;						// ��]�̌���
	m_life = 3;									// ���C�t
	//m_type = type;								// ���
	m_actionState = ACTION_NONE;				// �A�N�V�����Ȃ�

	m_Width = 4.0f;
	m_Height = 4.0f;
	m_Depth = 4.0f;
	
	switch( charcterType )
	{
		case CCharcter::CHARCTER_TYPE_RABBITS: m_type = CCharcter::CHARCTER_TYPE_RABBITS; break;
		case CCharcter::CHARCTER_TYPE_CAT:     m_type = CCharcter::CHARCTER_TYPE_CAT;     break;
		case CCharcter::CHARCTER_TYPE_PANDA:   m_type = CCharcter::CHARCTER_TYPE_PANDA;   break;
		case CCharcter::CHARCTER_TYPE_PENGUIN: m_type = CCharcter::CHARCTER_TYPE_PENGUIN; break;

		default:
		{
			m_type = CCharcter::CHARCTER_TYPE_RABBITS;
			CDebugConsole::GetInstance()->Print( "Charcter Type Range Over\nvalue : %d\n" , charcterType );
			break;
		}
	}

	char* pModelFilePath[ CHARCTER_TYPE_MAX ] = {
		{ "data\\MODEL\\playerRabbits.obj" },		// �E�T�M
		{ "data\\MODEL\\playerCats.obj" },			// �L
		{ "data\\MODEL\\playerBears.obj" },			// �p���_
		{ "data\\MODEL\\playerPenguins.obj" },		// �y���M��
	};

	char* pMaterialFilePath[ CHARCTER_TYPE_MAX ] = {
		{ "data\\MODEL\\playerRabbits.mtl" },		// �E�T�M
		{ "data\\MODEL\\playerCats.mtl" },			// �L
		{ "data\\MODEL\\playerBears.mtl" },			// �p���_
		{ "data\\MODEL\\playerPenguins.mtl" },		// �y���M��
	};

	//---------------------------------
	// [ ���f���ǂݍ��ݏ��� ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();

	pRenderer->CreateModel( pModelFilePath[ m_type ] , NULL , &m_numMat , &m_pModel );		// ���f������
	
	//m_pModelManager = CParentModelManagerGL::Create( "data\\MODEL\\miku_01.obj" , "data\\MODEL\\miku_01.mtl" );

	if( m_pModel == NULL )
	{
		return false;
	}

	// ���[�V��������
	//m_pMotion = CMotionGL::Create( "data\\ANIMATION\\miku_01_01.anm" );

	//if( m_pMotion == NULL )
	//{
	//	return false;
	//}

	//----------------------------------------------
	// [ �������蔻�萶�� ]
	//----------------------------------------------
	m_pBoundingSphere = CCollider3DSphere::Create( m_pos , 4.0f );		// TODO : ���a�����ߑł��Ȃ̂ŁA�̂��قǏC���\��H

	// ��������
	return true;
}

//==============================================================================
// �֐��� : void Uninit()
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CCharcter::Uninit()
{
	if( m_pMat != NULL )
	{
		m_pMat->Release();
		m_pMat = NULL;
	}

	if( m_pBoundingSphere != NULL )
	{
		m_pBoundingSphere->Release();
		m_pBoundingSphere = NULL;
	}
}

//==============================================================================
// �֐��� : void Update()
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CCharcter::Update( void )
{
	/*������
	**********************************************/
	m_pos.x += m_mov.x;
	m_pos.z += m_mov.z;

	/*�ړ��ʂ�����
	*************************************************/
	m_mov.x += ( 0.0f - m_mov.x ) * m_gensui.x;
	m_mov.z += ( 0.0f - m_mov.z ) * m_gensui.z;

	// �����蔻��X�V
	m_pBoundingSphere->SetPos( m_pos );

	// ���̃v���C���[�Ƃ̓����蔻�菈��
	CGame* pGameMode = dynamic_cast< CGame* >( GetManager()->GetMode() );

	if( pGameMode != NULL )
	{
		for( int i = 0 ; i < PLAYER_MAX ; i++ )
		{
			if( i != m_id )
			{
				CCharcter* pOtherPlayer = pGameMode->GetCharcter( i );
				CCollider3DSphere* pCollider = pOtherPlayer->GetBoundingSphere();

				if( m_pBoundingSphere->Collide( *pCollider ) )
				{
					VECTOR3 dentValue = m_pBoundingSphere->GetDent( *pCollider , 1.0f );
					m_pos.x += dentValue.x * 0.1f;
					m_pos.z += dentValue.z * 0.1f;

					VECTOR3 setMove = pOtherPlayer->GetMov();

					setMove.x += m_mov.x * 1.75f;
					setMove.z += m_mov.z * 1.75f;

					setMove.x -= dentValue.x;
					setMove.z -= dentValue.z;
					pOtherPlayer->SetMov( setMove );

					CDebugConsole::GetInstance()->Print( "HIT : %d->%d\n" , m_id , i );
				}
			}
		}
	}

	// �ǂƂ̓����蔻��
	if( m_pos.x + m_mov.x - m_Width / 2 < -WALL_WIDTH / 2 ||
		m_pos.x + m_mov.x + m_Width / 2 > WALL_WIDTH / 2 )
	{
		m_mov.x *= -2.0f;
		CDebugConsole::GetInstance()->Print( "WALL HIT X : %d\n" , m_id );
		m_life--;
	}

	if( m_pos.z + m_mov.z - m_Depth / 2 < -WALL_DEPTH / 2 ||
		m_pos.z + m_mov.z + m_Depth / 2 > WALL_DEPTH / 2 )
	{
		m_mov.z *= -2.0f;
		CDebugConsole::GetInstance()->Print( "WALL HIT Z : %d\n" , m_id  );
		m_life--;
	}

	//---------------------------------------
	// [ ��ԏ��� ]
	//---------------------------------------
	if( m_life <= 0 )
	{
		// TODO : �����ɏ�ԑJ�ڂŎ��S��Ԃ�����
	}
}

//==============================================================================
// �֐��� : void Draw()
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CCharcter::Draw( void )
{
	// ----------------------------------------------------------------------
	// [ ���[���h�}�g���b�N�X�̐������� ]
	// ----------------------------------------------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glTranslatef( m_pos.x , m_pos.y , m_pos.z );

	glRotatef( RadToDeg( m_rot.z ) , 0.0f , 0.0f , 1.0f );
	glRotatef( RadToDeg( m_rot.y ) , 0.0f , 1.0f , 0.0f );
	glRotatef( RadToDeg( m_rot.x ) , 1.0f , 0.0f , 0.0f );

	glScalef( m_scl.x , m_scl.y , m_scl.z );

	//---------------------------------
	// [ �`��O���� ]
	//---------------------------------
	glEnable( GL_NORMALIZE );
	glBindTexture( GL_TEXTURE_2D , 0 );
	glDisable( GL_TEXTURE_2D );

	//---------------------------------
	// [ �`�揈�� ]
	//---------------------------------
	if( m_life > 0 )
	{
		for( DWORD matCnt = 0 ; matCnt < m_numMat ; matCnt++ )
		{
			m_pModel->DrawSubset( matCnt );
		}
	}

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

	glEnable( GL_TEXTURE_2D );
}

//==============================================================================
// �֐��� : void CCharcter :: Rotation( void )
// ����   : void
// �߂�l : void
// ����   : �L�����N�^�[����]������
//==============================================================================
void CCharcter :: Rotation( void )
{
	if( m_rotMokuhyou.y < -PI )
	{//�ڕW�p�x������������ƒ���
		m_rotMokuhyou.y = PI * 2 + m_rotMokuhyou.y;
	}
	else if( m_rotMokuhyou.y > PI )
	{//�ڕW�p�x���傫������ƒ���
		m_rotMokuhyou.y = m_rotMokuhyou.y - PI * 2;
	}

	if( m_rot.y < -PI )
	{//�ŏ��l���߂����̂Ŋp�x�͖߂�
		m_rot.y = PI;
	}
	else if( m_rot.y > PI )
	{//�ő�l���߂����̂Ŋp�x�͖߂�
		m_rot.y = -PI;
	}

	if( m_rotMokuhyou.y != m_rot.y )
	{//�v���C���[�L�����̊p�x��ς���

		if ( m_rotMokuhyou.y - m_rot.y < -PI )
		{//�ڕW�p�ƍ��̊p�x���������܂����ł���Ƃ�

			m_rot.y += ( PI * 2 + m_rotMokuhyou.y - m_rot.y ) / m_spinGensui;      // ��
		}
		else if ( m_rotMokuhyou.y - m_rot.y > PI )
		{//�ڕW�p�ƍ��̊p�x���������܂����ł���Ƃ�

			m_rot.y += ( -PI * 2 + m_rotMokuhyou.y - m_rot.y ) / m_spinGensui;     // ��
		}
		else
		{//����ȊO�̎�

			m_rot.y += ( m_rotMokuhyou.y - m_rot.y ) / m_spinGensui;  // ��
		}
	}
}

//==============================================================================
// �֐��� : �T���v��
// ����   : void
// �߂�l : void
// ����   : �T���v������
//==============================================================================

