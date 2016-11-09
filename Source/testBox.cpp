//==============================================================================
// �^�C�g��     :   �e�X�g�p�N���X
// �t�@�C����   :   testBox.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/08
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/08 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "testbox.h"
#include "rendererGL.h"

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
#define MOVE_SPEED		( 3.0f )			// �ړ��W��
#define ROTATION_SPEED	( PI * 0.01f )		// ��]�p�ω��W��

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
// �֐��� : CTestBox()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CTestBox::CTestBox()
{
	m_pTexture = NULL;

	m_bMove       = false;
	m_isTexEnable = true;
	m_pVtxBuff    = NULL;
}

//==============================================================================
// �֐��� : ~CTestBox()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CTestBox::~CTestBox()
{
}

//==============================================================================
// �֐��� : bool Init( char* texPath )
// ����   : char* texPath : �e�N�X�`���t�@�C���p�X
// �߂�l : void
// ����   : ����������( �e�N�X�`���t�@�C���p�X�L��� )
//==============================================================================
bool CTestBox::Init( char* texPath )
{
	CSceneGL3D::Init( texPath );		// ���N���X�̏����������Ăяo��

	m_size = VECTOR3( 100.0f , 100.0f , 100.0f );
	m_bMove = false;


	CRenderer* pRenderer = GetManager()->GetRenderer();					// �����_���[�̎擾

	//---------------------------------
	// [ �e�N�X�`���ǂݍ��ݏ��� ]
	//---------------------------------
	pRenderer->CreateTexture( texPath , &m_pTexture );					// �e�N�X�`������

	//---------------------------------
	// [ ���_�o�b�t�@�[���� ]
	//---------------------------------
	pRenderer->CreateVertexBuffer( sizeof( VERTEX_3D ) * 4 , &m_pVtxBuff );

	//---------------------------------
	// [ ���_�f�[�^������ ]
	//---------------------------------
	VERTEX_3D* pVtx;

	m_pVtxBuff->Lock( 0 , 0 , ( void** )&pVtx , 0 );

	// �ʒu
	pVtx[ 0 ].pos = VECTOR3( -1000.0f , 1000.0f , 1000.0f );
	pVtx[ 1 ].pos = VECTOR3( 1000.0f , 1000.0f , 1000.0f );
	pVtx[ 2 ].pos = VECTOR3( -1000.0f , 1000.0f , -1000.0f );
	pVtx[ 3 ].pos = VECTOR3( 1000.0f , 1000.0f , -1000.0f );

	// �@��
	pVtx[ 0 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	pVtx[ 1 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	pVtx[ 2 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	pVtx[ 3 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );

	// �F
	pVtx[ 0 ].col = 0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0;
	pVtx[ 1 ].col = 0xff << 24 | 0x00 << 16 | 0xff << 8 | 0x00 << 0;
	pVtx[ 2 ].col = 0xff << 24 | 0x00 << 16 | 0x00 << 8 | 0xff << 0;
	pVtx[ 3 ].col = 0xff << 24 | 0x00 << 16 | 0x00 << 8 | 0x00 << 0;

	// �e�N�X�`��
	pVtx[ 0 ].tex = VECTOR2( 0.0f , 0.0f );
	pVtx[ 1 ].tex = VECTOR2( 1.0f , 0.0f );
	pVtx[ 2 ].tex = VECTOR2( 0.0f , 1.0f );
	pVtx[ 3 ].tex = VECTOR2( 1.0f , 1.0f );

	m_pVtxBuff->Unlock();

	return true;		// ��������
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CTestBox::Uninit( void )
{
	if( m_pTexture != NULL )
	{
		m_pTexture->Release();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	if( m_pVtxBuff != NULL )
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CTestBox::Update( void )
{
	//------------------------------------------
	// [ ���͏��̎擾���� ]
	//------------------------------------------
	CInput* pInput = CInput::GetInput( INPUT_TYPE_DX_KEYBOARD );

	bool isPressW     = false;
	bool isPressS     = false;
	bool isPressA     = false;
	bool isPressD     = false;
	bool isPressQ     = false;
	bool isPressE     = false;
	bool isPressZ     = false;
	bool isPressC     = false;
	bool isPressT     = false;
	bool isPressB     = false;
	bool isPressY     = false;
	bool isPressN     = false;
	bool isPressEnter = false;

	bool isTrigEnter  = false;
	bool isTrigF8     = false;
	bool isTrigF9     = false;

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
			isPressW     = pInput->GetPress( DIK_W );
			isPressS     = pInput->GetPress( DIK_S );
			isPressA     = pInput->GetPress( DIK_A );
			isPressD     = pInput->GetPress( DIK_D );
			isPressQ     = pInput->GetPress( DIK_Q );
			isPressE     = pInput->GetPress( DIK_E );
			isPressZ     = pInput->GetPress( DIK_Z );
			isPressC     = pInput->GetPress( DIK_C );
			isPressT     = pInput->GetPress( DIK_T );
			isPressB     = pInput->GetPress( DIK_B );
			isPressY     = pInput->GetPress( DIK_Y );
			isPressN     = pInput->GetPress( DIK_N );
			isPressEnter = pInput->GetPress( DIK_RETURN );
		}

		isTrigEnter = pInput->GetTrigger( DIK_RETURN );
		isTrigF8    = pInput->GetTrigger( DIK_F8 );
		isTrigF9    = pInput->GetTrigger( DIK_F9 );

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
	// [ �}�e���A������ ]
	//------------------------------------------
	// �e�N�X�`���L���E�����؂�ւ�
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
void CTestBox::Draw( void )
{
	//---------------------------------
	// [ �`��O���� ]
	//---------------------------------
	LPRenderer pRenderer = GetManager()->GetRenderer();		// �����_���[�擾

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	//glCullFace( GL_FRONT );
	//glCullFace( GL_FRONT_AND_BACK );

	//---------------------------------
	// [ ���[���h�}�g���N�X�Z�o ]
	//---------------------------------
	MATRIX mtxScl , mtxRot , mtxTrans;

	MatrixIdentity( &m_mtxWorld );

	MatrixScaling( &mtxScl , m_scl.x , m_scl.y , m_scl.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxScl );

	MatrixRotationYawPitchRoll( &mtxRot , m_rot.y , m_rot.x , m_rot.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxRot );

	MatrixTranslation( &mtxTrans , m_pos.x , m_pos.y , m_pos.z );
	MatrixMultiply( &m_mtxWorld , &m_mtxWorld , &mtxTrans );

	glMultMatrixf( m_mtxWorld.m );

	//---------------------------------------------------------------------
	// [ �`�揈�� ]
	//
	//              [5]
	//   [1][2][3][4]     <= [0]�Ԃ̃|���S���̍�������`��
	// [0]                <= ���}�̏��Ԃ�N���ɕ`��
	//---------------------------------------------------------------------
	if( m_pTexture != NULL && m_isTexEnable )
	{
		m_pTexture->Set();						// �e�N�X�`���ݒ�
	}
	else
	{
		glDisable( GL_TEXTURE_2D );
	}

	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	glDisable( GL_LIGHTING );

	pRenderer->SetStreamSource(
		0 ,
		m_pVtxBuff ,
		0 ,
		sizeof( VERTEX_3D ) );

	pRenderer->SetFVF( GL_FVF_VERTEX_3D );			// ���_�t�H�[�}�b�g�̐ݒ�

	pRenderer->DrawPrimitive(
		PT_TRIANGLE_STRIP ,
		0 ,
		2 );

	//float sizeHalfX = m_size.x * 0.5f;			// X���̃T�C�Y�̔���
	//float sizeHalfZ = m_size.z * 0.5f;			// Z���̃T�C�Y�̔���

	//// ���_�|�C���^�[�𗘗p�����`�揈��
	//int sizeV3 = sizeof( VECTOR3 );
	//int sizeV2 = sizeof( VECTOR2 );

	//int sizeCF32 = sizeof( COLOR_F32 );

	//VECTOR3 posData[ 3 ] = {
	//	VECTOR3( 100.0f , 0.0f , 100.0f ),
	//	VECTOR3( 100.0f , 100.0f , -100.0f ),
	//	VECTOR3( -100.0f , 0.0f , -100.0f ),
	//};

	//VECTOR3 norData[ 3 ] = {
	//	VECTOR3( 0.0f , 1.0f , 0.0f ),
	//	VECTOR3( 0.0f , 1.0f , 0.0f ),
	//	VECTOR3( 0.0f , 1.0f , 0.0f ),
	//};

	///*DWORD colData[ 3 ] = {
	//	COLOR_F32( 1.0f , 0.0f , 0.0f , 1.0f ),
	//	COLOR_F32( 1.0f , 0.0f , 0.0f , 1.0f ),
	//	COLOR_F32( 1.0f , 0.0f , 0.0f , 1.0f ),
	//};*/

	//// �F : �w A B G R �x�̏��Ɋi�[����Ă������I�I
	//// �������_���[�ɐF�ϊ��֐�����������K�v�L�肩��...
	//DWORD colData[ 3 ] = {
	//	0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0 ,
	//	0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0 ,
	//	0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0 ,
	//};

	///*COLOR_F32( 0.0f , 0.0f , 1.0f , 1.0f ),
	//COLOR_F32( 0.0f , 0.0f , 1.0f , 1.0f ),
	//COLOR_F32( 0.0f , 0.0f , 1.0f , 1.0f ),*/

	//VECTOR2 texData[ 3 ] = {
	//	VECTOR2( 0.0f , 0.0f ),
	//	VECTOR2( 1.0f , 0.0f ),
	//	VECTOR2( 0.0f , 1.0f ),
	//};

	//VERTEX_3D vtxData[ 3 ];

	//// �ʒu
	//vtxData[ 0 ].pos = VECTOR3( 100.0f , 0.0f , 100.0f );
	//vtxData[ 1 ].pos = VECTOR3( 100.0f , 100.0f , -100.0f );
	//vtxData[ 2 ].pos = VECTOR3( -100.0f , 0.0f , -100.0f );

	//// �@��
	//vtxData[ 0 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	//vtxData[ 1 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );
	//vtxData[ 2 ].nor = VECTOR3( 0.0f , 1.0f , 0.0f );

	//// �F
	//vtxData[ 0 ].col = 0xff << 24 | 0xff << 16 | 0x00 << 8 | 0x00 << 0;
	//vtxData[ 1 ].col = 0xff << 24 | 0x00 << 16 | 0xff << 8 | 0x00 << 0;
	//vtxData[ 2 ].col = 0xff << 24 | 0x00 << 16 | 0x00 << 8 | 0xff << 0;

	//// �e�N�X�`��
	//vtxData[ 0 ].tex = VECTOR2( 0.0f , 0.0f );
	//vtxData[ 1 ].tex = VECTOR2( 1.0f , 0.0f );
	//vtxData[ 2 ].tex = VECTOR2( 0.0f , 1.0f );

	//glEnableClientState( GL_VERTEX_ARRAY );
	//glEnableClientState( GL_NORMAL_ARRAY );
	//glEnableClientState( GL_COLOR_ARRAY );
	//glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	///*glVertexPointer( 3 , GL_FLOAT , 0 , posData );
	//glNormalPointer( GL_FLOAT , 0 , norData );
	//glColorPointer( 4 , GL_UNSIGNED_BYTE , 0 , colData );
	//glTexCoordPointer( 2 , GL_FLOAT , 0 , texData );*/

	//char* pTop = ( char* )vtxData;
	//int stride = 0;

	//void* pPosPointer = pTop + stride;

	//stride += sizeof( float ) * 3;

	//void* pNorPointer = pTop + stride;

	//stride += sizeof( float ) * 3;

	//void* pColPointer = pTop + stride;

	//stride += sizeof( DWORD );

	//void* pTexPointer = pTop + stride;

	//glVertexPointer( 3 , GL_FLOAT , sizeof( VERTEX_3D ) , pPosPointer );
	//glNormalPointer( GL_FLOAT , sizeof( VERTEX_3D ) , pNorPointer );
	//glColorPointer( 4 , GL_UNSIGNED_BYTE , sizeof( VERTEX_3D ) , pColPointer );
	//glTexCoordPointer( 2 , GL_FLOAT , sizeof( VERTEX_3D ) , pTexPointer );

	//glDrawArrays( GL_TRIANGLE_STRIP , 0 , 3 );

	//glDisableClientState( GL_VERTEX_ARRAY );
	//glDisableClientState( GL_NORMAL_ARRAY );
	//glDisableClientState( GL_COLOR_ARRAY );
	//glDisableClientState( GL_TEXTURE_COORD_ARRAY );

	glEnable( GL_LIGHTING );

	glBlendFunc( GL_ONE , GL_ZERO );
	glDisable( GL_BLEND );

	///////////////////////////////////////////////////////////////////
	// ���o�[�W����
	///////////////////////////////////////////////////////////////////
		//glBegin( GL_TRIANGLE_STRIP );
		//{
		//	/* ==0== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , -1.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , -1.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , -1.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 1.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , -1.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

		//	}

		//	/* ==1== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 1.0f , 0.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 1.0f , 0.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 1.0f , 0.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 1.0f , 0.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );
		//	}

		//	/* ==2== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , 1.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , 1.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , 1.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , 1.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );
		//	}

		//	/* ==3== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( -1.0f , 0.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , +sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( -1.0f , 0.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( -1.0f , 0.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( -1.0f , 0.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );
		//	}

		//	/* ==4== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , -1.0f );
		//		glVertex3f( -sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , -1.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , -1.0f );
		//		glVertex3f( +sizeHalfX , 0.0f , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 0.0f , -1.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );
		//	}

		//	/* ==5== */
		//	{
		//		glTexCoord2f( 0.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 1.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , -sizeHalfZ );

		//		glTexCoord2f( 0.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 1.0f , 0.0f );
		//		glVertex3f( -sizeHalfX , m_size.y , +sizeHalfZ );

		//		glTexCoord2f( 1.0f , 1.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 1.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , -sizeHalfZ );

		//		glTexCoord2f( 1.0f , 0.0f );
		//		glColor4f( m_col.r , m_col.g , m_col.b , m_col.a );
		//		glNormal3f( 0.0f , 1.0f , 0.0f );
		//		glVertex3f( +sizeHalfX , m_size.y , +sizeHalfZ );
		//	}
		//}
		//glEnd();

	//---------------------------------
	// [ �`��㏈�� ]
	//---------------------------------
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glDisable( GL_BLEND );
	glBlendFunc( GL_ONE , GL_ZERO );

	glDisable( GL_CULL_FACE );

	if( !m_isTexEnable )
	{
		glEnable( GL_TEXTURE_2D );
	}

}
