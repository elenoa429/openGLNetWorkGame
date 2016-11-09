//==============================================================================
// �^�C�g��     :   �e�q�֌W�t�����f���p�}�l�[�W��( OpenGL�p )
// �t�@�C����   :   parentModelManagerGL.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/09/09
//==============================================================================

//==============================================================================
// �X�V����: -2016/09/09 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "parentModelManagerGL.h"
#include "main.h"
#include "loader.h"

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
// �֐��� : CParentModelManagerGL()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CParentModelManagerGL::CParentModelManagerGL()
{

}

//==============================================================================
// �֐��� : ~CParentModelManagerGL()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CParentModelManagerGL::~CParentModelManagerGL()
{

}

//==============================================================================
// �֐��� : CParentModelManagerGL* Create( void )
// ����   : void
// �߂�l : CParentModelManagerGL*�^
// ����   : ��������
//==============================================================================
CParentModelManagerGL* CParentModelManagerGL::Create( void )
{
	CParentModelManagerGL* pNewInstance = new CParentModelManagerGL;

	if( pNewInstance->Init() == false )
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
void CParentModelManagerGL::Release( void )
{
	this->Uninit();
	delete this;
}

//==============================================================================
// �֐��� : bool Init( void )
// ����   : void
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CParentModelManagerGL::Init( void )
{
	CModel* pModel;
	DWORD numMat;

	//---------------------------------
	// [ ���f���ǂݍ��ݏ��� ]
	//---------------------------------
	CRenderer* pRenderer = GetManager()->GetRenderer();										// �����_���[�̎擾

	pRenderer->CreateModel( "data\\MODEL\\miku_01.obj" , NULL , &numMat , &pModel );		// ���f������

	//---------------------------------
	// [ �e�q�֌W�ݒ菈�� ]
	//---------------------------------
	CModelGL* pModelGL = dynamic_cast< CModelGL* >( pModel );

	CParentModelGL* pModelWork[ 3 ] = { NULL };

	pModelWork[ 0 ] = CParentModelGL::Create( pModelGL , 0 );
	PushModelData( pModelWork[ 0 ] );

	pModelWork[ 1 ] = CParentModelGL::Create( pModelGL , 1 );
	PushModelData( pModelWork[ 1 ] );

	pModelWork[ 2 ] = CParentModelGL::Create( pModelGL , 2 );
	PushModelData( pModelWork[ 2 ] );

	pModelWork[ 0 ]->SetParent( pModelWork[ 2 ] );
	pModelWork[ 1 ]->SetParent( pModelWork[ 2 ] );

	//---------------------------------------------
	// [ �}�e���A���ǂݍ��ݏ���( ���Ŗ��ߍ��� ) ]
	//---------------------------------------------
	CLoader* pLoader = new CLoader;

	pLoader->MaterialLoad( "data\\MODEL\\miku_01.mtl" , &m_pMat );

	delete pLoader;
	pLoader = NULL;

	//---------------------------------
	// [ �e�N�X�`���ǂݍ��ݏ��� ]
	//---------------------------------
	pRenderer->CreateTexture( "data\\MODEL\\miku_01.bmp" , &m_pTexture );	// �e�N�X�`������

	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CParentModelManagerGL::Uninit( void )
{
	// ���f���f�[�^���
	std::vector< CParentModelGL* >::iterator itr;	// ���f�����X�g�̃C�e���[�^

	for( itr = m_modelList.begin() ; itr != m_modelList.end() ; itr++ )
	{
		CParentModelGL* pModel = *itr;
		pModel->Release();
		pModel = NULL;
	}

	m_modelList.clear();	// ���X�g���폜
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CParentModelManagerGL::Update( void )
{
	std::vector< CParentModelGL* >::iterator itr;	// ���f�����X�g�̃C�e���[�^

	for( itr = m_modelList.begin() ; itr != m_modelList.end() ; itr++ )
	{
		CParentModelGL* pModel = *itr;
		pModel->Update();
	}
}

//==============================================================================
// �֐��� : void Draw( D3DXMATRIX* pMtxParent )
// ����   : MATRIX* pMtxParent : ��e�}�g���N�X( ���[�J�����W( 0 ; 0 ; 0 ) )�ɂ�����
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CParentModelManagerGL::Draw( MATRIX* pMtxParent )
{
	std::vector< CParentModelGL* >::iterator itr;	// ���f�����X�g�̃C�e���[�^

	if( m_pTexture != NULL )
	{
		m_pTexture->Set();						// �e�N�X�`���ݒ�
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D , 0 );
		glDisable( GL_TEXTURE_2D );
	}

	if( m_pMat != NULL )
	{
		m_pMat->Set();							// �}�e���A���ݒ�
	}

	for( itr = m_modelList.begin() ; itr != m_modelList.end() ; itr++ )
	{
		CParentModelGL* pModel = *itr;
		pModel->Draw( pMtxParent );
	}

	if( m_pMat != NULL )
	{
		CMaterialGL pDefMat;

		pDefMat.Set();							// �����}�e���A���ݒ�
	}
}

//==============================================================================
// �֐��� : bool PushModelData( CParentModelGL* pModelData )
// ����   : void
// �߂�l : void
// ����   : ���f���o�^����
//==============================================================================
bool CParentModelManagerGL::PushModelData( CParentModelGL* pModelData )
{
	// �G���[�`�F�b�N
	if( pModelData == NULL )
	{
		return false;
	}

	// �f�[�^�o�^
	m_modelList.push_back( pModelData );

	return true;
}

//==============================================================================
// �֐��� : bool RemoveModelData( int idx )
// ����   : int idx : �폜���郂�f���̃C���f�b�N�X( -1�ōŌ�� )
// �߂�l : bool�^
// ����   : �Ή��������f�����폜���鏈��
//==============================================================================
bool CParentModelManagerGL::RemoveModelData( int idx )
{
	// �G���[�`�F�b�N
	int size = m_modelList.size();

	if( idx > size || idx < -1 )
	{
		return false;
	}

	// ���f���폜
	if( idx == -1 )
	{
		m_modelList.pop_back();
	}
	else
	{
		m_modelList.erase( m_modelList.begin() + idx );
	}

	return true;
}

//==============================================================================
// �֐��� : CParentModelGL* GetModelData( int idx )
// ����   : int idx : �擾�ΏۃC���f�b�N�X
// �߂�l : CParentModelGL*�^
// ����   : �w�肵���ʒu�̃��f���f�[�^�擾����
//==============================================================================
CParentModelGL* CParentModelManagerGL::GetModelData( int idx )
{
	// �G���[�`�F�b�N
	int size = m_modelList.size();

	if( idx >= size || idx < 0 )
	{
		return NULL;
	}

	// �w�肵���v�f�̕ԋp
	std::vector< CParentModelGL* >::iterator itr = m_modelList.begin();

	return *( itr + idx );
}

//==============================================================================
// �֐��� : int GetModelListSize( void )
// ����   : void
// �߂�l : int�^
// ����   : ���f�����X�g�̃T�C�Y�擾����
//==============================================================================
int CParentModelManagerGL::GetModelListSize( void )
{
	return m_modelList.size();
}
