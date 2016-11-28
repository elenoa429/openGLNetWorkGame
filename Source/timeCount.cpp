//==============================================================================
// �^�C�g��     :   ���Ԍv���E�\���N���X
// �t�@�C����   :   timeCount.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/20
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/20 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "timeCount.h"

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
// �֐��� : CTimeCount()
// ����   : void
// �߂�l : void
// ����   : �R���X�g���N�^
//==============================================================================
CTimeCount::CTimeCount() : CScene( PRIORITY_TYPE_UI , OBJ_TYPE_UI )
{
	m_pos  = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_rot  = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_col  = COLOR_F32( 0.0f , 0.0f , 0.0f , 0.0f );

	m_pTexture         = NULL;
	m_ppNumber         = NULL;
	m_numPlace         = 0;
	m_time             = 0;
	m_timeCnt          = 0;
	m_timeDelay        = 0;
	m_isOutputLeftZero = true;
}

//==============================================================================
// �֐��� : ~CTimeCount()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CTimeCount::~CTimeCount()
{

}

//==============================================================================
// �֐��� : CTimeCount* Create( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath )
// ����   : int numPlace     : �\������
//          VECTOR3 pos  : �ʒu
//          VECTOR3 size : �T�C�Y
//          int texDivW      : �e�N�X�`��������( �� )
//          int texDivH      : �e�N�X�`��������( �c )
//          char* texPath    : �e�N�X�`���t�@�C���p�X
// �߂�l : bool�^ : ��������
// ����   : ��������
//==============================================================================
CTimeCount* CTimeCount::Create( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath )
{
	CTimeCount* newInstance;
	newInstance = new CTimeCount;

	if( newInstance->Init( numPlace , pos , size , texDivW , texDivH , texPath ) == false )
	{
		newInstance->Release();
		newInstance = NULL;
	}

	return newInstance;
}

//==============================================================================
// �֐��� : bool Init( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath )
// ����   : int numPlace     : �\������
//          VECTOR3 pos  : �ʒu
//          VECTOR3 size : �T�C�Y
//          int texDivW      : �e�N�X�`��������( �� )
//          int texDivH      : �e�N�X�`��������( �c )
//          char* texPath    : �e�N�X�`���t�@�C���p�X
// �߂�l : bool�^ : ��������
// ����   : ����������
//==============================================================================
bool CTimeCount::Init( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath )
{
	// ���W���̏�����
	m_pos = pos;
	m_rot = VECTOR3( 0.0f , 0.0f , 0.0f );
	m_size = size;

	VECTOR3 halfSize = VECTOR3( m_size.x * 0.5f , m_size.y * 0.5f , m_size.z * 0.5f );

	// �����_���[�擾
	CRenderer* pRenderer = GetManager()->GetRenderer();		// �����_���[�������擾

	// �e�N�X�`���ǂݍ��ݏ���
	pRenderer->CreateTexture( texPath , &m_pTexture );

	// �����\���N���X�̐���
	if( numPlace <= 0 )
	{
		return false;		// �������Ԉ���Ă���̂ŁA�������s
	}

	VECTOR3 setPos = pos;
	VECTOR3 setSize = size;

	setSize.x /= numPlace;							// ���ɕ\���������̂ł�������B���̕\�����@�ɂ������Ȃ�A�ʐݒ�ŁB
	setPos.x -= size.x * 0.5f;						// �����ʒu�����[�ɃZ�b�g

	m_ppNumber = new CNumber2D*[ numPlace ];		// �����������[�N����

	for( int i = 0 ; i < numPlace ; i++ )
	{
		m_ppNumber[ i ] = CNumber2D::Create( setPos , setSize , texDivW , texDivH , m_pTexture );		// ���������f�[�^�擾
		setPos.x += setSize.x;						// �E�ɂ��炵�Ă���
	}

	m_numPlace = numPlace;

	return true;	// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CTimeCount::Uninit( void )
{
	// �e�N�X�`���̉������
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���������̉��
	if( m_ppNumber != NULL )
	{
		for( int i = 0 ; i < m_numPlace ; i++ )
		{
			if( m_ppNumber[ i ] != NULL )
			{
				m_ppNumber[ i ]->Release();
				m_ppNumber[ i ] = NULL;
			}
		}

		delete[] m_ppNumber;
		m_ppNumber = NULL;
	}
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CTimeCount::Update( void )
{
	//-----------------------------------------------
	// [ ���Ԍv�� ]
	//-----------------------------------------------
	if( m_timeCnt == m_timeDelay )
	{
		m_time--;

		if( m_time < 0 ) m_time++;

		CTimeCount::PrintTime();

		m_timeCnt = 0;
	}

	m_timeCnt++;

	//-----------------------------------------------
	// [ �����̍X�V���� ]
	//-----------------------------------------------
	for( int i = 0 ; i < m_numPlace ; i++ )
	{
		if( m_ppNumber[ i ] != NULL )
		{
			m_ppNumber[ i ]->Update();
		}
	}
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CTimeCount::Draw( void )
{
	bool output = m_isOutputLeftZero ? true : false;		// �L�������o������������

	for( int i = 0 ; i < m_numPlace ; i++ )
	{
		if( m_ppNumber[ i ]->GetNum() != 0 || i == ( m_numPlace - 1 ) )
		{
			// �L�����o����or���ꌅ�ɓ��B�ɂ��\������
			output = true;
		}

		if( output )
		{
			if( m_ppNumber[ i ] != NULL )
			{
				m_ppNumber[ i ]->Draw();
			}
		}
	}
}

//==============================================================================
// �֐��� : void SetTime( int time , int delay )
// ����   : int time  : �\������������
//          int delay : ���������炷�܂ł̎���
// �߂�l : void
// ����   : �����ݒ菈��
//==============================================================================
void CTimeCount::SetTime( int time , int delay )
{
	m_time      = time;
	m_timeCnt   = 0;
	m_timeDelay = delay;

	// ���Ԃ̏o��
	CTimeCount::PrintTime();
}


//==============================================================================
// �֐��� : void SetColor( COLOR_F32 col );
// ����   : COLOR_F32 col : �ݒ�F
// �߂�l : void
// ����   : �F�ݒ菈��
//==============================================================================
void CTimeCount::SetColor( COLOR_F32 col )
{
	m_col = col;

	for( int i = 0 ; i < m_numPlace ; i++ )
	{
		if( m_ppNumber[ i ] != NULL )
		{
			m_ppNumber[ i ]->SetCol( col );
		}
	}
}

//==============================================================================
// �֐��� : void PrintTime( void )
// ����   : void
// �߂�l : void
// ����   : ���Ԃ𐔎������ɏo�͂��鏈��
//==============================================================================
void CTimeCount::PrintTime( void )
{
	int value = m_time;												// ���͐��l

	if( value >= 0 )												// �}�C�i�X�l�͓���ۏ؊O�̂��ߏ������Ȃ�
	{
		for( int i = m_numPlace - 1 ; i >= 0 ; i-- )				// ���ʌ�������ꍞ��
		{
			int placeValue = value % 10;							// �ꌅ�̒l�����o��

			if( m_ppNumber[ i ] != NULL )
			{
				m_ppNumber[ i ]->SetNum( placeValue );				// �ꌅ�̒l��ݒ�
			}

			value /= 10;											// ������
		}
	}
}
